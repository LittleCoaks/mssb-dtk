---
description: Best-effort rename of a matched function's placeholder symbol(s) to a real name, backed by evidence.
argument-hint: <function-name>
---

## Goal

For the function named in `$ARGUMENTS` (or a placeholder symbol it directly
depends on), try to replace an auto-generated placeholder name — `fn_80008E00`
(DOL), `fn_3_1CE90` (REL, module+offset), `lbl_...`, `jumptable_...` — with a
real, descriptive one, following the naming conventions already used
elsewhere in this codebase.

This is a **separate task from matching**, run on its own, not automatically
after every `/match-function`. Treat it as expensive: it's research and
judgment, not a mechanical fix, and it can legitimately end with "no rename,
not enough evidence" — that is a valid, complete outcome, not a failure to
push through.

**Precondition:** the target function should already be matched (or as close
to it as `/match-function` could get). Naming a function whose C source might
still change during matching wastes the research; if you find it isn't
matched yet, say so and stop rather than proceeding.

## Check the cheap path first

Most of the mechanical renames in this repo already came from
`tools/ghidra_rename.py`, which cross-references every repo placeholder
against the names already present in the project's Ghidra database
(`.ghidra_cache/`) and proposes any that translate cleanly to a legal C
identifier. Per `docs/file_map.md`, that pass is **largely exhausted for the
DOL already** (as of the last count, only two real upgrades remained there),
but it's still worth a targeted check for the specific symbol at hand:

```
python tools/ghidra_query.py name NAME        # decomp placeholder -> Ghidra name, if any
python tools/ghidra_query.py decomp NAME       # Ghidra's own decompiler output for it
python tools/ghidra_rename.py plan --kind func # full plan; grep it for NAME
```

If `ghidra_rename.py plan` already proposes a real name for this exact
symbol, that's your answer (still sanity-check it against the function body —
Ghidra names come from several authors with inconsistent conventions per that
script's own docstring). If it's listed in the plan's `skipped` section
(ambiguous / low-information / no Ghidra data at that address) or there's no
Ghidra data at all, move on to manual research below.

## Manual research (when the cheap path doesn't resolve it)

Gather evidence before proposing anything; more than one of these agreeing is
what makes a name trustworthy rather than a guess:

- **The function body.** What does it call? Calls to already-real-named
  functions are the strongest single signal. What structs/fields does it
  touch, what constants or enum-like values does it compare against?
- **Callers.** Grep for who calls this function and how — a dispatch table
  entry, an event handler, a per-frame update slot, a getter/setter — often
  says more about intent than the body alone.
- **Neighbors and file context.** What else is in this translation unit, and
  what does `docs/file_map.md` already say the file is for? Reuse its
  evidence hierarchy at single-function grain: named siblings in the same
  file > call graph > structural placement alone. If the file itself is only
  `inferred`-confidence in that document, be more conservative here too.
- **Mangled C++ names nearby** (e.g. `__dt__13mDoExt_bckAnmFv`) can identify
  the class family a function belongs to even when the function itself has no
  Ghidra name.
- **Existing naming conventions.** Match the style already used around it —
  don't invent a new prefix or casing convention for one function.

## Confidence gate

- **High** (an unambiguous purpose, corroborated by more than one signal
  above): propose the rename and apply it.
- **Medium** (plausible, single signal, or consistent with file theme but not
  proven): propose it, say explicitly what's uncertain, and apply it only if
  the user asked for renames to be applied rather than just proposed.
- **Low / no real signal**: do not invent a name. Leave the placeholder and
  say why. `docs/file_map.md` states this project's own philosophy on this
  exact tradeoff: *"inventing one would bury a guess in something that reads
  like a fact"* — a wrong name actively misleads every future reader in a way
  a placeholder never does.

## Applying a rename

A rename is never one-sided: `config/*/symbols.txt` names the target side and
`src/**/*.c` + `include/**/*.h` name our side, and they must change together
or the rename manufactures a fresh `SYMBOL_NAME` mismatch. Follow
`tools/ghidra_rename.py`'s approach rather than reinventing it:

1. Sanitize the proposed name into a legal C identifier if needed (reuse
   `ghidra_rename.sanitize` for this rather than writing new rules).
2. Check the name isn't already used anywhere in the config (collision check,
   same as `ghidra_rename.build_plan` does) — a collision means picking a
   different name, not overwriting.
3. Rewrite the symbol everywhere it's referenced: the `config/*/symbols.txt`
   entry and every `src`/`include` occurrence.
4. Rebuild (`ninja`) and re-diff (`tools/match_classify.py scan --function
   NAME` or the relevant unit). **The match percentage must be unchanged** —
   a name can't affect codegen. Any change in score means something in the
   rename went wrong (wrong symbol, partial match, collision); investigate
   and fix before keeping it, don't just accept a lucky-looking improvement.

## Scope per run

Default to one function (and, incidentally, symbols it references that you
already gathered solid evidence for while researching it) per invocation.
Don't go rename-hunting broadly across a file unless the user asked for that
explicitly — small, reviewable, evidenced renames beat a large batch of
mixed-confidence ones.

## Report

End with a short summary: what was renamed (old → new) and the evidence for
it, what was proposed but not applied (medium confidence, awaiting
confirmation) if not auto-applying, and what was left alone and why (low
confidence — say what evidence is still missing, e.g. "no named callers yet",
"pure arithmetic, nothing distinguishing").

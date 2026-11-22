# main/Unknown/File_0x80037054  [S1] (rope / chain simulation TU, hugeAnimStruct objects)

Baseline: empty source, 0%. After [S1]: .text 21.83% (12 of 20 functions drafted), link ok. Not yet drafted (still link from asm):
fn_80037054 (712), fn_8003731C (1100), fn_80037768 (508), fn_80037BAC (1520), fn_8003819C (544), fn_800387B0 (920),
fn_80038F08 (1032), fn_80039310 (1852) = the integrator/constraint core.

| function | status | pct |
|---|---|---|
| fn_80037964, fn_80038E2C, fn_80039A4C | matched | 100 |
| fn_80037B18 | pending | 99.59 |
| fn_80038B48 | pending | 99.09 |
| fn_800385F0 | pending | 98.02 |
| fn_80037984 | pending | 95.94 |
| fn_80038EC4 | pending | 94.12 |
| fn_80037AA0 | pending | 79.17 |
| fn_80038CD0 | pending | 75.49 |
| fn_800383BC | pending | 75.43 |
| fn_80038418 | pending | 74.42 |
| fn_80037054, fn_8003731C, fn_80037768, fn_80037BAC, fn_8003819C, fn_800387B0, fn_80038F08, fn_80039310 | pending (not drafted) | 0 |

## Findings
- Object layout (raw offsets): rope/rigid simulation record init in fn_800385F0 (0x0 pos?, 0x24 mass, 0x28 1/mass, 0x30/0x34/0x38 inertia,
  0x3C/0x40/0x44 inverse inertia, 0x48 dt (1/60 / substeps@0x4C), 0x58/0x88/0xB8 matrices, 0xE8 pos, 0xF4 quat, 0x110.. velocities,
  0x140 angular velocity, 0x14C/0x14D flags). fn_80038418 sets target pose and derives linear/angular velocity (acos/sin of the
  relative quaternion angle * 60). fn_80038E2C sets rope defaults (substeps 8 -> dt = 1/8/60).
- fn_80038CD0 builds a rope: count nodes of 0x40 bytes {mass, 1/mass, y(0x8), pos(0xC), prev(0x18), vel(0x24), force(0x30), pinned(0x3C)};
  end nodes get `mass`, middle nodes 2*mass, node 0 is pinned. fn_80038B48 is the Verlet step (damping obj+0x24, gravity step obj+0x1C,
  ground bounce with restitution obj+0x4 when node y < obj y).
- fn_80037984/80037AA0: a drawing task that follows a hand-track bone (getHandTrackFlags bit 0x10000000 switches to fn_80038418's pose-copy
  mode, then the task removes itself via fn_80037964).

## Hypothesis log
[S1] 37984: node pointer chain written with raw derefs (95.9%); next: register order (obj null check hoisted by compiler).
[S1] 38CD0 75.5%: next: loop form (target keeps node ptr increments and 'count-1' compare), float conv of i.
[S1] 38418 74.4%: next: stack layout (q/m1/m2/v), acos/sin result handling.
[S1] 383BC/37AA0: only register assignment differs.

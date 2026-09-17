# File descriptor tables

Every asset in `ZZZZ.dat` (and the three RELs in `aaaa.dat`) is described by a 16-byte record that is passed to
`ARAMTransfer` / `diskReadRelated`:

```c
typedef struct FileDescriptor {
    u16 pad;           // 0
    u8  repeatBits;    // LZSS length field width (0 = stored)
    u8  lookbackBits;  // LZSS distance field width
    u32 flagsSize;     // bits 28-31: 4 = compressed; bits 0-27: decompressed size
    u32 offset;        // byte offset in the archive
    u32 discSize;      // bytes to read
} FileDescriptor;
```

The tables of these records were named from the code that indexes them and from what the files they point at
contain (checked with the MSSB Editor, which decodes every file). Naming: `PascalCaseFiles` for a table,
`camelCaseFileDescriptor` for a single record; a per-module copy of a list carries a `_module` / scene / address suffix.
Confidence follows `.claude/commands/label-symbols.md`: *code* = a function that reads it was found, *content* = named
from what the files are, no reader found.

Many of these sit inside a compiler data pool: code loads the pool base and adds an immediate, so only the base
carries a relocation. That is why C in `src/` may still write `lbl_2_data_720[0x5F4]` for what is named
`MenuCommonTexFiles_text0323C` here, and why splitting the symbol does not change any match.

## main.dol

| symbol | was | evidence | index / contents |
|---|---|---|---|
| `CharacterFiles` | `lbl_800F1D78` | code, high | [roster slot 0..53][track 0..18]. Roster slot order: Mario, Luigi, DK, Diddy, Peach, Daisy, Yoshi, Baby Mario, Baby Luigi, Bowser, Wario, Waluigi, Koopa(red), Toad(red), Boo, Toadette, Shy Guy(red), Birdo, Monty, Bowser Jr, Paratroopa(red), Pianta x3, Noki x3, Hammer Bro, Toadsworth, Toad x4, Magikoopa x4, King Boo, Petey, Dixie, Goomba, Paragoomba, Koopa(green), Paratroopa(green), Shy Guy x4, Dry Bones x4, Fire Bro, Boomerang Bro (not character id; id->slot goes through the table at 0x80108DB8). Track 0 = full-detail model pack (gpc+tpl), track 1 = low-detail model pack for distant cameras, tracks 2..18 = 17 animation banks. Track 8 is frequently the same-size shared bank (210656 bytes) and track 14 is a 15742-byte bank common to almost all slots. Variant slots reuse the base slot's anim entries (same entry ids) but have unique model entries. |
| `AramCharacterFiles` | `lbl_800EFD38` | code, medium | Four consecutive runs, lengths in lbl_803CB7E0: [0..53] by character slot id (54 slots; 0-32 model containers, 33-53 variant texture sets); [54..431] = 54 + charSlot*7 + item (item 0 L hand, 1 R hand, 2 L glove, 3 R glove, 4 batting, 5 pitching, 6 catching hand-pose track); [432..485] by character slot -> animation file (variants repeat the base entry id); [486..514] hand-pose event set id 0..28. |
| `CharacterHandFiles` | `lbl_800F5D98` | code, medium | [character slot id 0..53][0 L hand (batting), 1 R hand (batting), 2 L glove, 3 R glove, 4 L hand (pitching), 5 R hand (pitching)] |
| `CommonUIFiles_main` | `lbl_800EEFD0` | code, medium | Common UI file enum: 0 HUD text, 1 HUD frames, 2 controls screen, 3 results/ranking, 4 play-call text, 5 menu bars/cursors, 6-13 help screens 1-8, 14 practice icons, 15 text glyph sheets, 16 team logos (all), 17-28 team logos per captain (Mario, Luigi, Peach, Daisy, Yoshi, Birdo, Wario, Waluigi, DK, Diddy, Bowser, Bowser Jr.), 29 help text, 30 sky panoramas, 31 records book, 32 stadium previews, 33 options text, 34-35 title screen, 36 team-setup backgrounds, 37 dotted portraits, 38-44 blank textures, 45-61 loading tips. |
| `BootSequenceFiles` | `lbl_801092C8` | code, medium | 0 = intro movie (movie1.HVQM4), 1 = boot screen textures |
| `titleScreenTexturesFileDescriptor` | `lbl_801092E8` | code, medium | single descriptor |
| `testTextFileDescriptor` | `lbl_80109044` | content, medium | single descriptor |
| `BallModelFiles` | `lbl_800EE910` | code, high | index = (stadium == Toy Field): 0 normal ball/cursor props, 1 Toy Field ball |
| `skyPanoramaFileDescriptor` | `lbl_800FB5B0` | code, medium | single descriptor |
| `HandPoseEventSetFiles` | split from `lbl_800F71D8` | code, medium | hand-pose event set id 0..28 (disc copy used when the ARAM preload is absent); slot 29 is an extra file never indexed by fn_80021ADC (meaning unknown). |
| `MinigameCommonFiles` | split from `lbl_800EE930` | code, medium | 0 = coin model, 1 = Toy Field block/shadow models, 2 = minigame description text. Fixed roles, not an id index. |

## game.rel

| symbol | was | evidence | index / contents |
|---|---|---|---|
| `CommonUIFiles_inGame` | `lbl_3_data_3D80` | code, medium | 0..61 common UI file enum (see commonUIFiles_main); 62 coin00 model, 63 ball_kage/shadow models, 64 text strings (23), 65 text strings (168), 66 p_machine00 (pitching machine). |
| `CommonUIFiles_matchEnd` | `lbl_3_data_6130` | code, medium | Common UI file enum, same as commonUIFiles_main. |
| `CommonUIFiles_pauseMenu` | `lbl_3_data_F538` | code, medium | Common UI file enum, same as commonUIFiles_main. |
| `CommonUIFiles_practicePause` | `lbl_3_data_10598` | code, medium | Common UI file enum, same as commonUIFiles_main. |
| `CommonUIFiles_minigame` | `lbl_3_data_21EC8` | code, medium | Common UI file enum, same as commonUIFiles_main. |
| `MinigameCommonFiles_game` | `lbl_3_data_225F0` | code, medium | 0 coin, 1 Toy Field blocks/shadows, 2 minigame description text |
| `PracticeScreenFiles` | `lbl_3_data_10578` | code, high | 0 = practice text, 1 = pitching machine model |
| `sequencedSongsFileDescriptor` | `lbl_3_data_3D60` | code, medium | single descriptor |
| `teamStarModelFileDescriptorGame` | `lbl_3_data_11380` | code, high | single descriptor |
| `cameraDataFileDescriptor` | `lbl_3_data_20FDC` | code, medium | single descriptor |
| `StadiumFiles_game` | split from `lbl_3_data_7EC` | code, high | same as StadiumFiles: [stadium id][variant] |
| `StadiumPropFiles` | split from `marioStadiumCDR` | code, high | STADIUM_ID 0..6 (same order as StadiumFiles rows) |
| `rosterFileDescriptorGame` | split from `lbl_3_data_0` | code, high | single descriptor |
| `contactWordModelsFileDescriptor` | split from `lbl_3_data_1146C` | code, medium | UI record list; the single descriptor is at +0x180 |

## menus.rel

| symbol | was | evidence | index / contents |
|---|---|---|---|
| `ChallengeMapCharacterFiles` | `lbl_2_data_2F990` | code, medium | challenge-mode map character id: 0 Mario, 1 Peach, 2 Wario, 3 DK, 4 Yoshi, 5 Bowser, 6 Bowser Jr, 7 Pianta, 8 Toad, 9 Magikoopa, 10 Koopa, 11 Shy Guy, 12 Toadsworth (first 5 = playable captains in challenge order, matching lbl_2_data_1326C) |
| `ChallengeTexFiles` | `lbl_2_data_1326C` | code, medium | 0 = challenge-mode common backgrounds; 1..6 = captain artwork for challenge captain id 0..5 (Mario, Peach, Wario, DK, Yoshi, Bowser). Slot 0 is the odd one. |
| `movie2FileDescriptor` | `lbl_2_data_12170` | content, medium | single descriptor |
| `movie3FileDescriptor` | `lbl_2_data_12180` | content, medium | single descriptor |
| `challengeDialogueTextFileDescriptor` | `lbl_2_data_12298` | content, medium | single descriptor |
| `recordsBookTexturesFileDescriptor` | `lbl_2_data_1FF84` | code, medium | single descriptor |
| `RecordsBookFiles` | `lbl_2_data_1FF94` | code, medium | 0 = records/bio text, 1 = Toadsworth and hand models |
| `menuBarsFileDescriptorRecordsScreen` | `lbl_2_data_20BF0` | code, medium | single descriptor |
| `rosterFileDescriptorMenus` | `lbl_2_data_C8` | code, high | single descriptor |
| `teamStarModelFileDescriptorMenus` | `lbl_2_data_4B90` | code, medium | single descriptor |
| `skyPanoramaFileDescriptorChallengeMap` | `lbl_2_data_1F894` | code, high | single descriptor |
| `challengeMapTexturesFileDescriptor` | `lbl_2_data_1F884` | code, high | single descriptor |
| `menuBarsFileDescriptor` | `lbl_2_data_1324C` | code, medium | single descriptor |
| `stadiumPreviewsFileDescriptor` | `lbl_2_data_1325C` | code, medium | single descriptor |
| `menuFontFileDescriptor` | `lbl_2_data_132DC` | code, medium | single descriptor |
| `challengeMapModelsFileDescriptor` | `lbl_2_data_2FE48` | code, medium | single descriptor |
| `recordsScreenTextFileDescriptor` | split from `lbl_2_data_20C00` | code, medium | single descriptor |
| `cupModelsFileDescriptorChallengeMap` | split from `lbl_2_data_2FE58` | code, medium | single descriptor |
| `MenuCommonTexFiles_mainMenu` | split from `lbl_2_data_180` | content, medium | 0 sky/stadium background panoramas (1740), 1 help text pages (1739), 2 options text (1754), 3 team-name logos all captains (865), 4..15 team-name logos per captain: Mario, Luigi, Peach, Daisy, Yoshi, Birdo, Wario, Waluigi, DK, Diddy, Bowser, Bowser Jr (866-877) |
| `MenuCommonTexFiles_text0323C` | split from `lbl_2_data_720` | code, high | same 16 slots as menuCommonTexFiles_mainMenu; code uses 0, 1 and 3 |
| `MenuCommonTexFiles_captainSelect` | split from `lbl_2_data_19E8` | content, medium | same 16 slots as menuCommonTexFiles_* |
| `ChallengeMapSceneFiles` | split from `lbl_2_data_2ECE4` | code, medium | UI record list (ends with type 3), not a descriptor table; trailing pair: 0 = challenge map textures, 1 = sky panoramas |

## debug.rel

| symbol | was | evidence | index / contents |
|---|---|---|---|
| `StadiumFiles_debug_10518` | `lbl_1_data_10518` | code, high | [stadium id][variant]; code only uses element 0 |
| `StadiumFiles_debug_10674` | `lbl_1_data_10674` | code, high | [stadium id][variant]; code only uses element 0 |
| `skyPanoramaFileDescriptorDebug` | `lbl_1_data_B70` | code, medium | single descriptor |
| `StadiumPropFiles_debug` | split from `lbl_1_data_0` | code, medium | STADIUM_ID 0..6 |
| `movie1FileDescriptorDebug` | split from `lbl_1_data_112D8` | code, medium | single descriptor |
| `chainModelFileDescriptorDebug` | split from `lbl_1_data_104F4` | code, medium | single descriptor |
| `teamStarModelFileDescriptorDebug` | split from `lbl_1_data_ADE0` | code, medium | single descriptor |
| `StadiumFiles_debug_8D0` | split from `lbl_1_data_8C8` | content, medium | [stadium id][variant], same as StadiumFiles |
| `DebugTexFiles` | split from `lbl_1_data_CC8` | content, medium | debug texture pack id 0..10 -> entries 878..888 in order |
| `DebugBallFiles` | split from `lbl_1_data_2398` | code, medium | [2] ball.gpc and toy_ball.gpc packs, +0x8040 |
| `HandPoseEventSetFiles_debug` | split from `lbl_1_data_2398` | code, medium | [30] copy of HandPoseEventSetFiles, +0x8060 |
| `DebugCharacterHandFiles` | split from `lbl_1_data_2398` | code, medium | [54] hand packs by roster slot, +0x8240 |

## Still placeholders

Symbols that hold descriptors but were left alone, and why:

- `lbl_800EF508` (dol): This is a no-rename proposal. The symbol is already audioFileTable in config/GYQE01/symbols.txt (line 4207, size 0x300, which is 48 descriptors), and include/Unknown/File_0x80062a94.h documents it. The collision flag is set only because the name is this symbol's own existing name.
- `lbl_1_data_196C` (debug): The name rests on content alone. The function that reads the table was never decompiled, and the 'debug-menu sound test' index meaning is a guess. The table is also not a copy of audioFileTable: it has 50 slots, some entries appear twice, and entry 77 is missing, so its purpose is unknown. Repo poli
- `lbl_800E8AA8` (dol): The address is already named relFileTable (size 0x440) at config/GYQE01/symbols.txt:4161, so there is nothing to rename. The collision flag is only the symbol matching itself. The existing name stays per policy. No split: nobody verified that code references +0x30 or +0x60 separately.
- `lbl_1_data_FB98` (debug): No rename is correct. Per the proposal (not re-checked here), the symbol mixes 63 descriptors with float and viewer data under one float-typed object, so a whole-symbol name would mislead. Split it first.
- `lbl_2_data_12EC0` (menus): Same problem as lbl_2_data_241C: '_rep08E8' is an unprecedented split-file suffix. The object is also 0x368 bytes, 54 descriptors plus two trailing pointers, so an array name misdescribes it until it is split or typed as a struct. The scene is not identified. Keep the placeholder.
- `lbl_1_data_F968` (debug): The facts check out: fn_1_1CBE4 indexes it by (u8)item+0x14 << 4 and calls ARAMTransfer, and the dossier shows 24 development test-model packs. The symbol is 0x1A0 bytes, though, and its last 0x20 bytes are function pointers. The data asm shows fn_1_26AF8 relocations inside it, not the fn_1_1ADA4 / 
- `cursorToStadIDMapping` (menus): No rename; shrink to 8 bytes and add menuCommonTexFiles_stadiumSelect at +0x8 (no collision).
- `lbl_2_data_15C8` (menus): Content-identical table; scene unknown so address qualifier is the honest choice. Note the qualifier is the blob address, sub-symbol lives at +0x2EC; blob label stays.
- `lbl_2_data_2A3C0` (menus): Content-identical; address qualifier only, no scene guessed.
- `lbl_2_data_2B3A4` (menus): Content-identical; address qualifier only. Blob label stays for +0..0x38.
- `lbl_2_data_2E02C` (menus): Content-identical; address qualifier only. Blob label stays.
- `lbl_2_data_2FFF8` (menus): Content-identical; address qualifier only.
- `lbl_3_data_3D70` (game): The dossier confirms entry 29 is a one-song container. The name claims nothing beyond that.
- `lbl_1_data_108F0` (debug): No rename. The symbol is a mixed object and needs a split first.
- `lbl_2_data_1323C` (menus): The 'Common' qualifier is a guess because the scene of the loader-stub TU is unknown. Keep the placeholder.
- `lbl_2_data_2E944` (menus): The meaning of the Vec data is inferred from its shape only. Split the symbol first; only the +0x60 descriptor (cup models) is identified.
- `lbl_1_data_A940` (debug): No rename. It is a mixed struct with an unresolved first record.

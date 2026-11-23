# main/Unknown/File_0x80037054  [S1] (rope / chain / rigid-body simulation TU, hugeAnimStruct objects)

Baseline: empty source, 0%. After [S1] (2nd session): .text 84.65%, .sdata2 86.4%; ALL 20 functions drafted, every size equal
to the target. Uses the canonical HugeAnimStruct (include/HugeAnimStruct.h). Link ok.

| function | status | pct |
|---|---|---|
| fn_80037964, fn_80038E2C, fn_80039A4C, fn_80037AA0, fn_80038EC4 | matched | 100 |
| fn_80037B18 | pending | 99.59 |
| fn_80038B48 | pending | 99.09 |
| fn_800385F0 | pending | 98.02 |
| fn_80037984 | pending | 95.94 |
| fn_80037054 | pending | 95.93 |
| fn_800387B0 | pending | 91.00 |
| fn_80037768 | pending | 88.72 |
| fn_80038F08 | pending | 86.21 |
| fn_80039310 | pending | 84.16 |
| fn_8003731C | pending | 77.78 |
| fn_80038CD0 | pending | 75.49 |
| fn_800383BC | pending | 75.43 |
| fn_80038418 | pending | 74.42 |
| fn_80037BAC | pending | 73.36 |
| fn_8003819C | pending | 71.32 |

next (all): register allocation / stack layout of the Vec locals; none were ground. readability pass: pending for the five 100% functions (none have enum-shaped values).

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

## Session-2 findings
- fn_80037054 integrates a rigid body (state copy of 0x154 bytes, substeps of dt = obj+0x48) using fn_8003731C for contact forces;
  fn_80037BAC is the collision-impulse variant (two probe points pt[0]=+0xC, pt[1]=+0, flag -1 = reject step and halve dt).
  fn_8003819C accumulates gravity/drag/force per 0..10 sample along the body; fn_800387B0 is the rope spring/damper/friction
  force pass; fn_80039310 is a box tipping simulation (RK4 gyroscopic, two corner probes, settles when energy <= restLimit).
  fn_80038F08 is the 3-state (copy / measure velocity / run fn_80039310) hand-bone capture machine at lbl_800F79B8+0x78.
- All of this uses raw offsets via RF32/RU32; the object layout is in the first-session findings above.

#ifndef __MENUS_CSS_WORK_H_
#define __MENUS_CSS_WORK_H_

#include "mssbTypes.h"

/* The two team-select work areas in the menus REL bss:
 * - cssWork (CssWork, 0xC4C bytes, only 0x00-0x66 used): character-select
 *   work area, shared with captain select (Z menu) and stadium select
 *   (0x57/0x58). Per-team fields are indexed by team.
 * - capSelectState (CapSelectState, 0x54 bytes, memset as one block):
 *   captain-select state, reused by character select for its 4 preview
 *   models. Per-slot fields are indexed by model slot (port on captain
 *   select).
 * Each file declares its own extern. Most declare the struct types below.
 * text_0323C.c still declares both as u8 arrays, because the struct form
 * changes the codegen of several of its functions; it uses the byte-offset
 * #defines and accessor macros below (menu_camera.h style), and the
 * CSS_WORK_VIEW / CAP_SELECT_STATE_VIEW casts in functions where the typed
 * view compiles the same. Fields not named here are unknown or low
 * confidence. */

/* cssWork byte offsets. */
#define CSS_WORK_LINEUP_CURSOR                0x00 /* s32[2]: E(s32, FIELDING_POSITION) 0-8, CSS_LINEUP_CURSOR_DONE, CSS_LINEUP_CURSOR_RANDOM */
#define CSS_WORK_LINEUP_CURSOR_PREV           0x08 /* s32[2]: lineup cursor before the last move; the move animations copy the cursor here */
#define CSS_WORK_PRESET_LINEUP                0x10 /* s32[2]: challenge: which challengeRosters lineup (1-3) loads by default */
#define CSS_WORK_GRID_CURSOR_PREV             0x20 /* s32[2]: menuCursors[8 + team] (the grid cursor) before it last moved */
#define CSS_WORK_CHALLENGE_FILE_LOAD_DONE     0x28 /* u8[4]: cssUnloadScreen, challenge: each file-load step done */
#define CSS_WORK_CHALLENGE_MUSIC_RESTARTED    0x2C /* u8: cssUnloadScreen, challenge: menu music restart finished */
#define CSS_WORK_CHALLENGE_MUSIC_STEP         0x2D /* u8: cssUnloadScreen, challenge: 0 start the restart, 1 wait for it */
#define CSS_WORK_RETURN_TO_CAPTAIN_SELECT     0x2E /* u8: cssChangeScreens: nonzero goes back to captain select (screen 9) */
#define CSS_WORK_CPU_DIFFICULTY_STEP          0x33 /* u8: cssSelectCPUDifficulty: 0 open the menu, 1 input (fn_2_87A8), 2 finish */
#define CSS_WORK_CPU_DIFFICULTY_MENU_OPENED   0x34 /* u8: gates the one-time CPU_DIFFICULTY_OPEN process */
#define CSS_WORK_CPU_DIFFICULTY_CANCELLED     0x35 /* u8: fn_2_87A8: B sets it, A clears it */
#define CSS_WORK_EXIT_DELAY_TIMER             0x36 /* s8: frames to wait before leaving (teamSelectScreenMain states 3/7, cssChangeScreens) */
#define CSS_WORK_ROSTER_COMPLETE              0x37 /* u8[2]: all 9 slots filled; allows moving onto DONE */
#define CSS_WORK_RESERVED_OTHER_GRID_CHAR     0x3B /* u8[2]: cssRandomFillRoster: the other team's grid character was marked taken */
#define CSS_WORK_CHALLENGE_ROSTER_LOCKED      0x3F /* u8: challenge: no grid character free; B and the lineup are locked */
#define CSS_WORK_ON_CHARACTER_GRID            0x41 /* u8[2]: the team's cursor is on the character grid, not the lineup */
#define CSS_WORK_RANDOM_FILL_AFTER_CLEAR      0x43 /* u8[2]: fn_2_5184: run cssRandomFillRoster once the clear animation ends */
#define CSS_WORK_Z_MENU_OPEN                  0x45 /* u8[2]: Z menu shown (both screens) */
#define CSS_WORK_Z_MENU_PAGE                  0x47 /* u8[2]: E(u8, Z_MENU_PAGE) */
#define CSS_WORK_Z_MENU_PAGE_DRAWN            0x49 /* u8[2]: the page draw functions ran their setup */
#define CSS_WORK_Z_MENU_ACTIVE                0x4B /* u8[2]: set on open; cleared after the close animation */
#define CSS_WORK_Z_MENU_CHAR_ID               0x4D /* s8[2]: E(s8, CHAR_ID) the character the page was drawn for */
#define CSS_WORK_VARIANT_CHANGED              0x50 /* u8[2]: L cycled the slot character's colour variant; redraw its icon */
#define CSS_WORK_ROSTER_CLEAR_PENDING         0x52 /* u8[2]: Y (clear roster) pressed; input ignored until the clear animation ends */
#define CSS_WORK_ROSTER_CLEAR_ANIMATING       0x54 /* u8[2]: clear animation running */
#define CSS_WORK_LEAVING_SCREEN               0x56 /* u8: set on every back-out path */
#define CSS_WORK_CHALLENGE_STADIUM_MAX_CURSOR 0x57 /* u8: stadium select, challenge: highest selectable stadium */
#define CSS_WORK_STADIUM_CHOSEN               0x58 /* u8: stadium select: a valid pick was made */
#define CSS_WORK_LINEUP_EDIT_MODE             0x59 /* u8[2]: R: fielding-position editor (fn_2_3624) has the input */
#define CSS_WORK_SWAP_SOURCE_SELECTED         0x5F /* u8[2]: lineup editor: first A pick made */
#define CSS_WORK_SWAP_SOURCE_POSITION         0x61 /* s8[2]: E(s8, FIELDING_POSITION) first A pick; FIELDING_POSITION_NONE when unset */
#define CSS_WORK_ENTER_LINEUP_EDIT_AFTER_MOVE 0x63 /* u8[2]: R on the random button: enter the editor once the cursor move ends */
#define CSS_WORK_READY_AFTER_LINEUP_EDIT      0x65 /* u8[2]: A on DONE in the editor: send the ready process afterwards */

/* CSS_WORK_LINEUP_CURSOR values besides the fielding positions 0-8. */
#define CSS_LINEUP_CURSOR_DONE   9  /* the DONE button: A readies the team */
#define CSS_LINEUP_CURSOR_RANDOM 10 /* the random-fill / clear button (fn_2_5184) */

/* For files that declare cssWork as u8[]: the lineup cursor and its previous
 * value. The original code uses both the byte-offset form and the s32-array
 * form, and they compile differently, so both are kept. */
#define CSS_CURSOR(slot)          (*(s32 *)&cssWork[(slot) * 4])
#define CSS_PREV_CURSOR(slot)     (*(s32 *)&cssWork[(slot) * 4 + 8])
#define CSS_CURSOR_S32(slot)      (((s32 *)cssWork)[(slot)])
#define CSS_PREV_CURSOR_S32(slot) (((s32 *)cssWork)[(slot) + 2])

/* capSelectState byte offsets. */
#define CAP_STATE_LOAD_QUEUE_HEAD       0x00 /* s8: model-load ring buffer write index (mod 10) */
#define CAP_STATE_LOAD_QUEUE_TAIL       0x01 /* s8: model-load ring buffer read index (mod 10) */
#define CAP_STATE_LOAD_QUEUE            0x02 /* s8[10]: slots waiting for a model load; -1 = empty */
#define CAP_STATE_CAPTAIN_LOCKED        0x10 /* u8[2]: captain chosen (captainSelect_APress), cleared by B */
#define CAP_STATE_PLAY_CAPTAIN_VOICE    0x12 /* u8[2]: play the chosen captain's voice once */
#define CAP_STATE_MODEL_LOAD_REQUESTED  0x14 /* u8[4]: queue a model load for this slot */
#define CAP_STATE_MODEL_LOAD_DONE       0x18 /* u8: a model load finished (fn_2_18148) */
#define CAP_STATE_INITIAL_MODELS_LOADED 0x19 /* u8: all slot models loaded once; input is ignored until then */
#define CAP_STATE_MODEL_LOAD_BUSY       0x1A /* u8: a queued load is running; input is ignored */
#define CAP_STATE_MODEL_LOADER_IDLE     0x1B /* u8: inverse of MODEL_LOAD_BUSY */
#define CAP_STATE_MODEL_LOAD_DELAY      0x1C /* u8[4]: frames the cursor has been still; the load is requested at 15 */
#define CAP_STATE_LOADING_SLOT          0x27 /* s8[4]: set to the slot index when its load starts; -1 at init */
#define CAP_STATE_MODEL_SLOT_COUNT      0x2D /* u8: 1 challenge, 2 captain select, 4 character select */
#define CAP_STATE_TEAM_CONFIRMED        0x2E /* u8[2]: character select: team ready */
#define CAP_STATE_MODEL_ANIM_SETTLED    0x40 /* u8[2]: selected/deselected animation finished (indexed up to MODEL_SLOT_COUNT) */
#define CAP_STATE_MODEL_LOAD_QUEUED     0x42 /* u8[4]: a load for this slot is in the queue */
#define CAP_STATE_SHOW_MODEL_ON_LOAD    0x46 /* u8[4]: captainSelect_setShowModelOnLoad; copied into CapSlot.visible */
#define CAP_STATE_DEBUG_CAMERA_MENU     0x4A /* u8: debug camera tweak; force-cleared every frame */

/* The typed layouts. Byte fields are u8 because the code reads them unsigned
 * unless it casts. */
typedef struct CssWork {
    /* 0x00 */ s32 lineupCursor[2];     // E(s32, FIELDING_POSITION) 0-8, CSS_LINEUP_CURSOR_DONE, CSS_LINEUP_CURSOR_RANDOM
    /* 0x08 */ s32 lineupCursorPrev[2];
    /* 0x10 */ s32 presetLineup[2];     // challenge: challengeRosters lineup 1-3
    /* 0x18 */ u8 _18[0x20 - 0x18];
    /* 0x20 */ s32 gridCursorPrev[2];   // menuCursors[8 + team] before it last moved
    /* 0x28 */ u8 challengeFileLoadDone[4];
    /* 0x2C */ u8 challengeMusicRestarted;
    /* 0x2D */ u8 challengeMusicStep;
    /* 0x2E */ u8 returnToCaptainSelect;
    /* 0x2F */ u8 _2F[2];               // only read (fn_2_9F70), as an index into presetLineup
    /* 0x31 */ u8 _31[2];
    /* 0x33 */ u8 cpuDifficultyStep;    // 0 open, 1 input, 2 finish
    /* 0x34 */ u8 cpuDifficultyMenuOpened;
    /* 0x35 */ u8 cpuDifficultyCancelled;
    /* 0x36 */ u8 exitDelayTimer;       // read as s8
    /* 0x37 */ u8 rosterComplete[2];
    /* 0x39 */ u8 _39[2];
    /* 0x3B */ u8 reservedOtherGridChar[2];
    /* 0x3D */ u8 _3D[2];               // only cleared, and tested with rosterComplete
    /* 0x3F */ u8 challengeRosterLocked;
    /* 0x40 */ u8 _40;
    /* 0x41 */ u8 onCharacterGrid[2];
    /* 0x43 */ u8 randomFillAfterClear[2];
    /* 0x45 */ u8 zMenuOpen[2];
    /* 0x47 */ E(u8, Z_MENU_PAGE) zMenuPage[2];
    /* 0x49 */ u8 zMenuPageDrawn[2];
    /* 0x4B */ u8 zMenuActive[2];
    /* 0x4D */ u8 zMenuCharID[2];       // CHAR_ID, compared unsigned
    /* 0x4F */ u8 _4F;                  // set when both 2P teams confirm; never read
    /* 0x50 */ u8 variantChanged[2];
    /* 0x52 */ u8 rosterClearPending[2];
    /* 0x54 */ u8 rosterClearAnimating[2];
    /* 0x56 */ u8 leavingScreen;
    /* 0x57 */ u8 challengeStadiumMaxCursor;
    /* 0x58 */ u8 stadiumChosen;
    /* 0x59 */ u8 lineupEditMode[2];
    /* 0x5B */ u8 _5B[0x5F - 0x5B];
    /* 0x5F */ u8 swapSourceSelected[2];
    /* 0x61 */ u8 swapSourcePosition[2]; // FIELDING_POSITION, read as s8
    /* 0x63 */ u8 enterLineupEditAfterMove[2];
    /* 0x65 */ u8 readyAfterLineupEdit[2];
    /* 0x67 */ u8 _67[0xC4C - 0x67];    // never referenced
} CssWork; // size: 0xC4C

typedef struct CapSelectState {
    /* 0x00 */ s8 loadQueueHead;
    /* 0x01 */ s8 loadQueueTail;
    /* 0x02 */ s8 loadQueue[10];        // slots waiting for a model load; -1 = empty
    /* 0x0C */ s32 _0C;                 // only set to -1
    /* 0x10 */ u8 captainLocked[2];
    /* 0x12 */ u8 playCaptainVoice[2];
    /* 0x14 */ u8 modelLoadRequested[4];
    /* 0x18 */ u8 modelLoadDone;
    /* 0x19 */ u8 initialModelsLoaded;
    /* 0x1A */ u8 modelLoadBusy;
    /* 0x1B */ u8 modelLoaderIdle;
    /* 0x1C */ u8 modelLoadDelay[4];
    /* 0x20 */ u8 _20;
    /* 0x21 */ s8 _21[2];               // only set to -1
    /* 0x23 */ u8 _23[4];               // [0..1] memset to -1
    /* 0x27 */ s8 loadingSlot[4];
    /* 0x2B */ u8 _2B[2];
    /* 0x2D */ u8 modelSlotCount;       // 1 challenge, 2 captain select, 4 character select
    /* 0x2E */ u8 teamConfirmed[2];
    /* 0x30 */ u8 _30[2];
    /* 0x32 */ u8 _32;                  // set and cleared with modelLoadDone; never read
    /* 0x33 */ u8 _33[0x40 - 0x33];
    /* 0x40 */ u8 modelAnimSettled[2];  // indexed up to modelSlotCount (4 on the CSS runs into modelLoadQueued)
    /* 0x42 */ u8 modelLoadQueued[4];
    /* 0x46 */ u8 showModelOnLoad[4];
    /* 0x4A */ u8 debugCameraMenu;
    /* 0x4B */ u8 _4B;
    /* 0x4C */ u8 _4C[0x54 - 0x4C];
} CapSelectState; // size: 0x54

/* Typed views for files that declare the blocks as u8[] (text_0323C.c). */
#define CSS_WORK_VIEW         (*(CssWork *)cssWork)
#define CAP_SELECT_STATE_VIEW (*(CapSelectState *)capSelectState)

/* lbl_2_bss_100B4 (2 bytes, declared u8): byte 0 is set before every
 * captain/character-select exit (the model-load tasks remove themselves once
 * it is set); byte 1 is set while a captain model loads (fn_2_18148). */
#define CAP_SELECT_MODEL_LOADING (((u8 *)&lbl_2_bss_100B4)[1])

#endif // !__MENUS_CSS_WORK_H_

#ifndef __MENUS_CSS_WORK_H_
#define __MENUS_CSS_WORK_H_

#include "mssbTypes.h"

/* Byte offsets into the team-select work areas, menu_camera.h style. The code
 * indexes these blocks as raw bytes, and several matched functions depend on
 * the exact access shape, so they stay u8 arrays for now. Each file declares
 * its own extern. Fields not listed here are unknown or low confidence. */

/* lbl_2_bss_F468 (0xC4C bytes, only 0x00-0x66 used): character-select work
 * area, shared with captain select (Z menu) and stadium select (0x57/0x58).
 * Per-team fields are indexed by team. */
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

/* The lineup cursor and its previous value. The original code uses both the
 * byte-offset form and the s32-array form, and they compile differently, so
 * both are kept. */
#define CSS_CURSOR(slot)          (*(s32 *)&lbl_2_bss_F468[(slot) * 4])
#define CSS_PREV_CURSOR(slot)     (*(s32 *)&lbl_2_bss_F468[(slot) * 4 + 8])
#define CSS_CURSOR_S32(slot)      (((s32 *)lbl_2_bss_F468)[(slot)])
#define CSS_PREV_CURSOR_S32(slot) (((s32 *)lbl_2_bss_F468)[(slot) + 2])
/* CSS_WORK_GRID_CURSOR_PREV as an s32 array. */
#define CSS_GRID_CURSOR_PREV_S32(slot) (((s32 *)lbl_2_bss_F468)[(slot) + 8])

/* lbl_2_bss_100B8 (0x54 bytes, memset as one block): captain-select state,
 * reused by character select for its 4 preview models. Per-slot fields are
 * indexed by model slot (port on captain select). */
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

#endif // !__MENUS_CSS_WORK_H_

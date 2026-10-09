#define SQRT2_LINKAGE static
#include "game/match_setup/controller_input.h"
#define REP_HEADER_DATA_FN getRepHeaderData_controllerInput
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"

extern void fn_800A97D0(s32 arg0, s32 arg1);

// .text:0x0006D4A0 size:0xC4 mapped:0x806AC534
void resetInputTrackers(void) {
    int i;
    for (i = 0; i < 4; i++) {
        g_Controls[i].controlStickAngle = 0;
        g_Controls[i].controlStickMagnitude = 0;
        g_Controls[i].buttonInput = 0;
        g_Controls[i].newButtonInput = 0;
        g_Controls[i]._08 = 0;
        g_Controls[i].right_left = 0;
        g_Controls[i].up_down = 0;
        g_Controls[i].rightTriggerDistance = 0;
        g_Controls[i].leftTriggerDistance = 0;
    }
    fn_800A97D0(0x10, 0x1e);
}

// .text:0x0006D304 size:0x19C mapped:0x806AC398
void UpdateControllerInputs(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InputStruct* c = &g_Controls[i];
        lbl_803C77B8_s* src = (lbl_803C77B8_s*)((u8*)&AtBat_ButtonInput1 + i * 0x20);
        u16 prev;
        c->_0E = 0;
        prev = c->buttonInput;
        c->buttonInput = src->_00;
        c->newButtonInput = src->_02;
        c->_08 = ((u16*)src)[2];
        c->right_left = ((s8*)src)[0x10];
        c->up_down = ((s8*)src)[0x11];
        c->leftTriggerDistance = ((s8*)src)[0x14];
        c->rightTriggerDistance = ((s8*)src)[0x15];
        if ((c->newButtonInput & INPUT_TRIGGER_L) && (prev & INPUT_TRIGGER_L)) {
            c->newButtonInput &= (u16)~INPUT_TRIGGER_L;
        }
        if (c->leftTriggerDistance >= 120.0f) {
            if (!(prev & INPUT_TRIGGER_L)) {
                c->newButtonInput |= INPUT_TRIGGER_L;
            }
            c->buttonInput |= INPUT_TRIGGER_L;
        }
        if ((c->newButtonInput & INPUT_TRIGGER_R) && (prev & INPUT_TRIGGER_R)) {
            c->newButtonInput &= (u16)~INPUT_TRIGGER_R;
        }
        if (c->rightTriggerDistance >= 120.0f) {
            if (!(prev & INPUT_TRIGGER_R)) {
                c->newButtonInput |= INPUT_TRIGGER_R;
            }
            c->buttonInput |= INPUT_TRIGGER_R;
        }
        InterpretControllerInputsIntoMagnitude(i);
    }
}

// .text:0x0006CD88 size:0x57C mapped:0x806ABE1C
void InterpretControllerInputsIntoMagnitude(int port) {
    s16 angle = -1;
    int magnitude;
    f32 z;
    f32 x;
    f32 mag;
    z = g_Controls[port].right_left;
    x = g_Controls[port].up_down;
    mag = dolsqrtf2(z * z + x * x) - 16.0f;
    if (mag <= 0.0f) {
        u16 in = g_Controls[port].buttonInput;
        if ((in & INPUT_BUTTON_UP) && (in & INPUT_BUTTON_RIGHT)) {
            g_Controls[port].controlStickAngle = 0x200;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if ((in & INPUT_BUTTON_UP) && (in & INPUT_BUTTON_LEFT)) {
            g_Controls[port].controlStickAngle = 0x600;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if ((in & INPUT_BUTTON_DOWN) && (in & INPUT_BUTTON_RIGHT)) {
            g_Controls[port].controlStickAngle = 0xE00;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if ((in & INPUT_BUTTON_DOWN) && (in & INPUT_BUTTON_LEFT)) {
            g_Controls[port].controlStickAngle = 0xA00;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if (in & INPUT_BUTTON_UP) {
            g_Controls[port].controlStickAngle = 0x400;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if (in & INPUT_BUTTON_RIGHT) {
            g_Controls[port].controlStickAngle = 0;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if (in & INPUT_BUTTON_DOWN) {
            g_Controls[port].controlStickAngle = 0xC00;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else if (in & INPUT_BUTTON_LEFT) {
            g_Controls[port].controlStickAngle = 0x800;
            g_Controls[port].controlStickMagnitude = 0x40;
        } else {
            g_Controls[port].controlStickAngle = -1;
            g_Controls[port].controlStickMagnitude = 0;
        }
    } else {
        if (mag > 56.0f) {
            mag = 56.0f;
        }
        magnitude = (s16)(64.0f * mag / 56.0f);
        if (magnitude != 0) {
            int r;
            f32 k;
            angle = radToShortAngle(atan2(x, z));
            r = angle % 1024;
            if (r > 512) {
                r = 1024 - r;
            }
            k = (f32)r / 512.0f;
            k = k * 0.27208483f;
            z += z * k;
            x += x * k;
            g_Controls[port].right_left = z;
            g_Controls[port].up_down = x;
            mag = dolsqrtf2(z * z + x * x) - 16.0f;
            if (mag > 56.0f) {
                mag = 56.0f;
            }
            magnitude = (s16)(64.0f * mag / 56.0f);
        }
        g_Controls[port].controlStickAngle = angle;
        g_Controls[port].controlStickMagnitude = magnitude;
    }
}

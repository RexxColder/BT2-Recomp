#include "common.h"

/* menu overlay: character-change / transformation screen state machine (one step per frame).
   The state number lives in M+0x198; arg0 is a flag the screen clears when it wants to leave. */

s32 func_001018B8(void);
s32 ColorFade_IsFadingOut(void);
s32 func_0026EB60(u8 *obj);
s32 func_0026EB70(u8 *obj);
void func_0026EB78(u8 *obj, const char *name);
void func_002493C0(s32 a, s32 b, s32 c, s32 d, s32 e);
void func_003ECA78(s32 v);
void EftShotFx_Update_2494A0(void);
s32 rand(void);
void func_00243A80(s32 a, s32 b, s32 c);
void func_00298460(s32 a, s32 b, s32 c);
void func_00297FE0(s32 a, s32 sound, s32 c, s32 d, s32 e);

extern u8 *D_00428F4C __attribute__((section(".data")));   /* screen object */
extern u8 *D_003876A4;                                      /* game settings */
extern u32 D_003B0C34;                                      /* buttons pressed */
extern char D_0042A150[], D_0042A258[], D_0042A268[], D_0042A280[], D_0042A290[];
extern char D_0042A2A0[], D_0042A2B0[], D_00429B10[];

#define M(o)       (*(s32 *)(D_00428F4C + (o)))
#define MP(o)      (D_00428F4C + (o))
#define M_ANIMCTX  M(0x0C)
#define M_FLAGS    M(0x174)
#define M_SEL      M(0x178)
#define M_ANIM     M(0x17C)
#define M_MODE     M(0x190)
#define M_STATE    M(0x198)
#define M_CURSOR   (*(s32 **)(D_00428F4C + 0x1B8))   /* current entry: 3 words {id, a, b} */
#define M_LISTHEAD (*(s32 **)(D_00428F4C + 0x1B4))
#define OBJ_A      MP(0x50)
#define OBJ_B      MP(0x78)
#define OBJ_C      MP(0xA0)

#define BTN_CONFIRM 0x4000
#define Beep(snd) func_00297FE0(0, (snd), 0x40, 0x40, 1)
#define StartAnim() func_002493C0(M_ANIMCTX, 0x3711, 0x3B2A, 0, M_ANIM)
/* screen idle: no fade running, widget C finished, confirm pressed */
#define UI_READY() (!ColorFade_IsFadingOut() && func_0026EB60(OBJ_C) && (D_003B0C34 & BTN_CONFIRM))

/* sets the entry mode from the flags of the current entry and starts the matching animation */
#define ApplyEntry() \
    do { \
        s32 *ent_ = M_CURSOR; \
        M_MODE = ent_[1] != 0 ? 2 : (ent_[2] != 0 ? 1 : 0); \
        func_003ECA78(M_MODE == 2 ? 0 : M_MODE); \
        StartAnim(); \
    } while (0)

void func_003EF038(u32 *leaveFlag) {
    s32 i, n;

    if (M_STATE == 0) {
        return;
    }
    switch (M_STATE) {
    case 0x15:
        M_FLAGS |= 8;
        M_ANIM = 7;
        M_STATE = M_STATE + 1;
        M_MODE = 0;
        StartAnim();
        M_STATE = 0x20;
        return;
    case 0x20:
        if (func_001018B8() == 5) {
            M_STATE = M_STATE + 1;
            return;
        }
        if (UI_READY()) {
            M_STATE = M_STATE + 1;
            Beep(1);
        }
        return;
    case 0x21:
        M_FLAGS ^= 8;
        M_STATE = 0;
        func_003ECA78(0);
        return;
    case 0x29:
        M_FLAGS |= 8;
        M_ANIM = 13;
        M_STATE = M_STATE + 1;
        M_MODE = 3;
        StartAnim();
        return;
    case 0x2A:
        if (func_001018B8() == 5) {
            M_STATE = M_STATE + 1;
        }
        if (UI_READY()) {
            M_STATE = 0x2B;
            Beep(1);
        }
        return;
    case 0x2B:
        M_FLAGS ^= 8;
        M_STATE = 0;
        return;
    case 0x3D:
        M_STATE = M_STATE + 1;
        M_MODE = 0;
        M_ANIM = 14;
        StartAnim();
        return;
    case 0x3E:
        if (func_001018B8() == 5) {
            M_STATE = M_STATE + 1;
        }
        return;
    case 0x3F:
        func_00243A80(0, 0, 0);
        *leaveFlag = 0;
        M_STATE = 0;
        return;

    case 0x51:
        if (M_FLAGS & 4) {
            M_ANIM = rand() % 3 + 45;
            M_MODE = 3;
            M_FLAGS |= 8;
        } else {
            M(0x1B8) = M(0x1B4);
            n = 2 * (M(0x188) + M(0x18C));
            i = 0;
            if (n > 0 && M(0x1B8) == 0) {
                /* no list */
            } else {
                if (n > 0) {
                    /* skip to the (2*count)-th terminator entry */
                    do {
                        do {
                            M_CURSOR = M_CURSOR + 3;
                        } while (*M_CURSOR != 0);
                        i++;
                    } while (i < 2 * (M(0x188) + M(0x18C)));
                }
                if (M(0x1B8) != 0 && M(0x188) + M(0x18C) > 0) {
                    M_CURSOR = M_CURSOR + 3;
                }
            }
            if (*M_CURSOR == 0) {
                M_STATE = 0x55;
                return;
            }
            M_FLAGS |= 8;
            func_0026EB78(OBJ_A, D_0042A258);
        }
        func_0026EB78(OBJ_B, D_0042A268);
        M_STATE = 0x56;
        return;
    case 0x52:
        if (M_FLAGS & 4) {
            M_STATE = 0x55;
            return;
        }
        if (M(0x1B8) == 0) {
            M_STATE = 0x55;
            return;
        }
        M_CURSOR = M_CURSOR + 3;
        M_STATE = M_STATE + 1;
        /* fall into 0x53 */
    case 0x53:
        if (M_FLAGS & 4) {
            StartAnim();
            M_STATE = M_STATE + 1;
            return;
        }
        if (M(0x1B8) == 0 || *M_CURSOR == 0) {
            M_STATE = 0x55;
            return;
        }
        M_ANIM = *M_CURSOR;
        ApplyEntry();
        M_STATE = M_STATE + 1;
        return;
    case 0x54:
        if (func_001018B8() == 5 || UI_READY()) {
            EftShotFx_Update_2494A0();
            M_STATE = 0x52;
            if (UI_READY()) {
                Beep(1);
            }
        }
        return;
    case 0x55:
        M_FLAGS |= 1;
        M_FLAGS |= 2;
        M(0x19C) = 15;
        *(s32 *)(D_003876A4 + 0x1C) = 0x3E;
        M_STATE = 0;
        return;
    case 0x56:
        if (func_0026EB70(OBJ_B) & 0x200) {
            M_STATE = 0x53;
        }
        return;

    case 0x65:
        if (M_FLAGS & 4) {
            M_STATE = 0x69;
            return;
        }
        M(0x1B8) = M(0x1B4);
        n = 2 * *(s32 *)(D_003876A4 + 0x484) + 1;
        i = 0;
        if (!(n > 0 && M(0x1B8) == 0)) {
            if (n > 0) {
                do {
                    do {
                        M_CURSOR = M_CURSOR + 3;
                    } while (*M_CURSOR != 0);
                    i++;
                } while (i < 2 * *(s32 *)(D_003876A4 + 0x484) + 1);
            }
            if (M(0x1B8) != 0) {
                M_CURSOR = M_CURSOR + 3;
            }
        }
        if (*M_CURSOR == 0) {
            M_STATE = 0x6A;
            return;
        }
        M_FLAGS |= 8;
        func_0026EB78(OBJ_A, D_0042A258);
        M_STATE = 0x6B;
        func_0026EB78(OBJ_B, D_0042A268);
        return;
    case 0x66:
        if (M(0x1B8) == 0) {
            M_STATE = 0x69;
            return;
        }
        M_CURSOR = M_CURSOR + 3;
        M_STATE = M_STATE + 1;
        /* fall into 0x67 */
    case 0x67:
        if (M(0x1B8) == 0 || *M_CURSOR == 0) {
            M_STATE = 0x69;
            return;
        }
        M_ANIM = *M_CURSOR;
        ApplyEntry();
        M_STATE = M_STATE + 1;
        return;
    case 0x68:
        if (func_001018B8() == 5 || UI_READY()) {
            EftShotFx_Update_2494A0();
            M_STATE = 0x66;
            if (UI_READY()) {
                Beep(1);
            }
        }
        return;
    case 0x69:
        if (!(M_FLAGS & 4)) {
            if (!(M_FLAGS & 0x20)) {
                func_0026EB78(OBJ_B, D_0042A280);
            }
            func_0026EB78(OBJ_A, D_0042A290);
        }
        M_STATE = M_STATE + 1;
        return;
    case 0x6A:
        if (M_FLAGS & 0x20) {
            M_STATE = 0x8D;
        } else {
            M_STATE = 0;
            M_FLAGS &= ~8;
        }
        return;
    case 0x6B:
        if (func_0026EB70(OBJ_B) & 0x200) {
            M_STATE = 0x67;
        }
        return;

    case 0x8D:
        M_ANIM = 44;
        M_STATE = M_STATE + 1;
        M_MODE = 0;
        StartAnim();
        return;
    case 0x8E:
        if (func_001018B8() == 5 || UI_READY()) {
            EftShotFx_Update_2494A0();
            M_STATE = M_STATE + 1;
            func_0026EB78(OBJ_A, D_0042A150);
            if (UI_READY()) {
                Beep(1);
            }
        }
        return;
    case 0x8F:
        func_0026EB78(OBJ_C, D_0042A2A0);
        M_STATE = M_STATE + 1;
        func_00297FE0(2, 8, 0x40, 0x40, 1);
        return;
    case 0x90:
    case 0x92:
        if (func_0026EB70(OBJ_C) & 0x200) {
            M_STATE = M_STATE + 1;
        }
        return;
    case 0x91:
        if (UI_READY()) {
            M_STATE = M_STATE + 1;
            func_0026EB78(OBJ_C, D_0042A2B0);
            Beep(1);
        }
        return;
    case 0x93:
        func_0026EB78(OBJ_B, D_0042A280);
        func_0026EB78(OBJ_A, D_00429B10);
        M_FLAGS &= ~8;
        func_00298460(0x233, 1, 1);
        M_STATE = 0;
        M_FLAGS &= ~0x20;
        return;

    case 0xA1:
        M_STATE = M_STATE + 1;
        /* fall into 0xA2 */
    case 0xA2:
        if (func_0026EB70(OBJ_A) & 0x200) {
            M_ANIM = 2;
            M_STATE = M_STATE + 1;
            M_MODE = 3;
            StartAnim();
            M_FLAGS |= 8;
        }
        return;
    case 0xA3:
        if (func_001018B8() == 5 || UI_READY()) {
            M_STATE = M_STATE + 1;
            if (UI_READY()) {
                Beep(1);
            }
        }
        return;
    case 0xA4:
        M_ANIM = 2 * M_SEL + 4;
        M_MODE = 3;
        StartAnim();
        M_FLAGS ^= 8;
        M_STATE = 0;
        return;
    case 0xB5:
        M_STATE = M_STATE + 1;
        /* fall into 0xB6 */
    case 0xB6:
        if (func_0026EB70(OBJ_A) & 0x200) {
            M_ANIM = 2 * M_SEL + 3;
            M_STATE = M_STATE + 1;
            M_MODE = 0;
            StartAnim();
        }
        return;
    case 0xB7:
        M_STATE = 0;
        return;
    default:
        return;
    }
}

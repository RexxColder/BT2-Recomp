#include "common.h"

extern u32 D_003B0C34 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_00425138[];

s32 rand(void);
s32 func_001018B8(void);
void func_00101890(void);
void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_003D1928(s32 idx, s32 *o1, s32 *o2, s32 *o3);
s32 func_003D83D0(u8 *arg0);
s32 func_003D8458(u8 *arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0026EAE0(u8 *arg0, s32 arg1);
void func_0026EB78(u8 *arg0, u8 *arg1);
void EftShotFx_Update_2494A0(void);

#define W(o) (*(s32 *)(b + (o)))
#define STATE W(0x3310)
#define FLAGS W(0x2BC)
#define ANIM W(0x2C0)
#define ANIM_FROM_TABLE W(0x2CC)
#define SKIP_FX() func_00297FE0(0, 1, 0x40, 0x40, 1)
#define PAD_SKIP (D_003B0C34 & 0x4000)

/* character id (u16 at 0x333E + 32 * id) of the table entry at u16 table `off`, entry `slot` */
static u32 CharIdAt(u8 *b, s32 off, s32 slot) {
    return *(u16 *)(b + 0x333E + 32 * *(u16 *)(b + off + slot * 2));
}

/* common tail of states 1..10: pad skip jumps to the end state 13 */
static void SkipToEnd(u8 *b) {
    if (PAD_SKIP != 0 && (FLAGS & 0x200) != 0) {
        STATE = 13;
        SKIP_FX();
    }
}

/* wait for the animation (1018B8 == 5), then advance */
static void WaitAnim(u8 *b) {
    if (func_001018B8() == 5) {
        STATE = STATE + 1;
    }
}

/* 0x003D3338: guide character animation state machine (b = menu object, state at +0x3310) */
void func_003D3338(u8 *b) {
    s32 anim[2];
    s32 state = STATE;

    if (state == 0) {
        return;
    }
    anim[0] = 0x3507;
    anim[1] = 0x3920;
    switch (state) {
    case 1:
        FLAGS = FLAGS | 8;
        if ((*(u32 *)(D_003876A4 + 0x18) & 0x20) != 0) {
            STATE = 5;
            return;
        }
        if (func_003D83D0(b) != 0) {
            ANIM = 0x10;
            ANIM_FROM_TABLE = 1;
            func_002493C0(0, anim[0], anim[1], 0, 0x10);
        } else if (func_003D8458(b) != 0) {
            ANIM = 0xE;
            ANIM_FROM_TABLE = 1;
            func_002493C0(0, anim[0], anim[1], 0, 0xE);
        } else {
            ANIM_FROM_TABLE = 1;
            ANIM = W(0x3320) * 2 + 8;
            func_002493C0(0, anim[0], anim[1], 0, ANIM);
        }
        STATE = STATE + 1;
        SkipToEnd(b);
        return;
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
        WaitAnim(b);
        SkipToEnd(b);
        return;
    case 3:
        if (func_003D83D0(b) != 0) {
            ANIM = ANIM + 2;
        } else {
            ANIM = ANIM + 1;
        }
        ANIM_FROM_TABLE = 1;
        func_002493C0(0, anim[0], anim[1], 0, ANIM);
        STATE = STATE + 1;
        SkipToEnd(b);
        return;
    case 5:
        func_003D1928(CharIdAt(b, 0x353E, W(0x3324) * 8), &anim[0], &anim[1], &ANIM);
        ANIM_FROM_TABLE = 1;
        func_002493C0(0, anim[0], anim[1], 0, ANIM);
        STATE = STATE + 1;
        SkipToEnd(b);
        return;
    case 7:
        ANIM_FROM_TABLE = 1;
        func_003D1928(CharIdAt(b, 0x3540, W(0x3324) * 8), &anim[0], &anim[1], &ANIM);
        func_002493C0(0, anim[0], anim[1], 0, ANIM + 1);
        STATE = STATE + 1;
        SkipToEnd(b);
        return;
    case 9:
        if (func_003D83D0(b) != 0) {
            ANIM = 0x13;
            ANIM_FROM_TABLE = 1;
            func_002493C0(0, anim[0], anim[1], 0, 0x13);
        } else if (func_003D8458(b) != 0) {
            ANIM_FROM_TABLE = 0;
            ANIM = rand() % 3 + 0x18;
            func_002493C0(0, 0x3681, 0x3A9A, 0, ANIM);
        } else {
            ANIM_FROM_TABLE = 1;
            ANIM = rand() % 7 + 0x14;
            func_002493C0(0, anim[0], anim[1], 0, ANIM);
        }
        STATE = STATE + 1;
        SkipToEnd(b);
        return;
    case 11:
        STATE = state + 1;
        SkipToEnd(b);
        return;
    case 12:
        W(0x3308) = W(0x3308) - 1;
        if (W(0x3308) == -1) {
            STATE = state + 1;
        }
        SkipToEnd(b);
        return;
    case 13:
        W(0x3308) = 0;
        ANIM = -1;
        STATE = 0;
        FLAGS = (FLAGS & ~8) | 2;
        *(u32 *)(D_003876A4 + 0x18) |= 0x20;
        return;

    case 51:
        FLAGS = FLAGS & ~8;
        ANIM = 2;
        ANIM_FROM_TABLE = 1;
        func_002493C0(0, anim[0], anim[1], 0, 2);
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 53;
            SKIP_FX();
        }
        return;
    case 52:
        WaitAnim(b);
        if (PAD_SKIP != 0) {
            STATE = 53;
            SKIP_FX();
        }
        return;
    case 53:
        ANIM_FROM_TABLE = 0;
        ANIM = rand() & 1;
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 55;
            SKIP_FX();
        }
        return;
    case 54:
        WaitAnim(b);
        if (PAD_SKIP != 0) {
            STATE = 55;
            SKIP_FX();
        }
        return;
    case 55:
        func_0026EAE0(b + 0x30, 0x3C);
        STATE = 101;
        return;

    case 101:
        FLAGS = (FLAGS & ~8) | 0x100;
        if (func_003D8458(b) != 0) {
            ANIM_FROM_TABLE = 0;
            ANIM = 0x10;
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, 0x10);
        } else if (func_003D83D0(b) != 0) {
            ANIM_FROM_TABLE = 0;
            ANIM = 0x13;
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, 0x13);
        } else if (W(0x3320) == 0) {
            s32 mode = *(s32 *)(D_003876A4 + 0x90);

            if (mode == 1) {
                ANIM = 4;
                ANIM_FROM_TABLE = 0;
            } else if (mode == 0) {
                ANIM = 2;
                ANIM_FROM_TABLE = 0;
            } else if (mode < 2) {
                ANIM_FROM_TABLE = 0;
            } else if (mode < 4) {
                ANIM = 6;
                ANIM_FROM_TABLE = 0;
            } else {
                ANIM_FROM_TABLE = 0;
            }
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        } else {
            ANIM_FROM_TABLE = 0;
            ANIM = W(0x3320) * 3 + 7;
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        }
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 103;
            SKIP_FX();
        }
        return;
    case 102:
        if (func_001018B8() == 5) {
            STATE = STATE + 1;
        } else if (PAD_SKIP != 0) {
            STATE = STATE + 1;
            SKIP_FX();
        }
        return;
    case 103:
        if (W(0x3320) == 0) {
            s32 prev = ANIM;

            ANIM = prev + 1;
            if (*(s32 *)(D_003876A4 + 0x90) == 3) {
                ANIM = prev + 2;
            }
            ANIM_FROM_TABLE = 0;
        } else {
            ANIM = ANIM + (rand() & 1) + 1;
            ANIM_FROM_TABLE = 0;
        }
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        STATE = STATE + 1;
        return;
    case 104:
        if (func_001018B8() == 5) {
            STATE = 0;
            FLAGS = FLAGS & ~0x100;
        }
        if (PAD_SKIP != 0) {
            STATE = 0;
            SKIP_FX();
            EftShotFx_Update_2494A0();
            FLAGS = FLAGS & ~0x100;
            ANIM = -1;
        }
        return;

    case 151:
        ANIM = 6;
        ANIM_FROM_TABLE = 1;
        FLAGS = FLAGS | 8;
        func_002493C0(0, anim[0], anim[1], 0, 6);
        STATE = STATE + 1;
        return;
    case 152:
    case 154:
        WaitAnim(b);
        return;
    case 153:
        func_003D1928(CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)), &anim[0], &anim[1], &ANIM);
        ANIM_FROM_TABLE = 1;
        func_002493C0(0, anim[0], anim[1], 0, ANIM + 1);
        STATE = STATE + 1;
        return;
    case 155: {
        u32 flags = FLAGS;

        ANIM = -1;
        FLAGS = flags & ~8;
        if ((flags & 0x10) != 0) {
            FLAGS = (flags & ~8) ^ 0x10;
        }
        STATE = 0;
        if ((FLAGS & 0x4000) == 0) {
            func_0026EB78(b + 0x148, D_00425138);
            func_0026EB78(b + 0xA8, D_00425138);
            func_0026EAE0(b + 0xF8, 0x3C);
            func_0026EAE0(b + 0x30, 0x3C);
        }
        return;
    }

    case 251:
        FLAGS = FLAGS & ~8;
        if (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) {
            ANIM_FROM_TABLE = 0;
            ANIM = 0x1E;
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, 0x1E);
        } else {
            ANIM = 0x1C;
            ANIM_FROM_TABLE = 1;
            func_002493C0(0, anim[0], anim[1], 0, 0x1C);
        }
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 253;
            SKIP_FX();
        }
        return;
    case 252:
        WaitAnim(b);
        if (PAD_SKIP != 0) {
            STATE = 253;
            SKIP_FX();
        }
        return;
    case 253:
        if (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) {
            STATE = 258;
            ANIM = ANIM + 1;
        } else {
            ANIM = 0x1B;
            STATE = state + 1;
        }
        ANIM_FROM_TABLE = 0;
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        if (PAD_SKIP != 0) {
            STATE = (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) ? 258 : 255;
            SKIP_FX();
        }
        return;
    case 254:
    case 256:
    case 304:
        if (func_001018B8() == 5) {
            STATE = STATE + 1;
        } else if (PAD_SKIP != 0) {
            STATE = STATE + 1;
            SKIP_FX();
        }
        return;
    case 255:
        ANIM = ANIM + 1;
        ANIM_FROM_TABLE = 0;
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 257;
            SKIP_FX();
        }
        return;
    case 257:
    case 305:
        ANIM_FROM_TABLE = 0;
        ANIM = ANIM + 1;
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, ANIM);
        STATE = STATE + 1;
        return;
    case 258:
        if (PAD_SKIP != 0) {
            SKIP_FX();
        } else if (func_001018B8() != 5) {
            return;
        }
        STATE = 0;
        W(0x3308) = 0;
        return;

    case 301:
        FLAGS = FLAGS & ~8;
        if (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) {
            ANIM_FROM_TABLE = 0;
            ANIM = 0x1E;
            func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, 0x1E);
        } else {
            ANIM = 0x1C;
            ANIM_FROM_TABLE = 1;
            func_002493C0(0, anim[0], anim[1], 0, 0x1C);
        }
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) ? 307 : 303;
            SKIP_FX();
        }
        return;
    case 302:
        if (func_001018B8() == 5) {
            if (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) {
                STATE = 307;
            } else {
                STATE = STATE + 1;
            }
        } else if (PAD_SKIP != 0) {
            if (CharIdAt(b, 0x353E, W(0x3324) * 8 + W(0x2C8)) == 0x2E) {
                STATE = 307;
            } else {
                STATE = STATE + 1;
            }
            SKIP_FX();
        }
        return;
    case 303:
        ANIM = 0x1B;
        ANIM_FROM_TABLE = 0;
        func_002493C0(W(0x1C), 0x3681, 0x3A9A, 0, 0x1B);
        STATE = STATE + 1;
        if (PAD_SKIP != 0) {
            STATE = 305;
            SKIP_FX();
        }
        return;
    case 306:
        if (PAD_SKIP != 0) {
            SKIP_FX();
        } else if (func_001018B8() != 5) {
            return;
        }
        STATE = 0;
        W(0x3308) = 0;
        return;
    default:
        func_00101890();
        return;
    }
}

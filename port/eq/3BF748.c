#include "common.h"

extern u8 *D_00421C94 __attribute__((section(".data")));  /* memory-card flow object */
extern u8 *D_00387F2C __attribute__((section(".data")));  /* save data */
extern u8 *D_003876A4 __attribute__((section(".data")));  /* player data */
extern u8 D_003B0AA0[] __attribute__((section(".data"))); /* memory-card port state */
extern u8 D_003B0B00[] __attribute__((section(".data"))); /* pad state */

extern s32 McCard_Checksum();
extern s32 McCard_CreateSave();
extern s32 McCard_Format();
extern s32 McCard_GetInfo();
extern s32 McCard_IsFatalError();
extern void McCard_Probe();
extern s32 McCard_WriteSave();
extern void func_00288348();
extern s32 func_00289C98();
extern s32 func_0028A578();
extern s32 func_0028A790();
extern void func_00297FE0();
extern s32 func_00298528();
extern s32 func_0029C1E8();
extern void func_0029C550();
extern s32 func_0029C640();
extern s32 func_0029C7C0();
extern s32 func_0029C800();
extern void func_0029C820();
extern s32 func_0029C830();

#define M (D_00421C94)
#define MW(off) (*(s32 *)(M + (off)))
#define CODE MW(0x1C)        /* message code shown by func_0029C800 */
#define STATE MW(0x20)
#define TIMER MW(0x24)
#define SAVE_BUF (M + 0x28)  /* 16 KiB-save work buffer passed to the card routines */
#define SLOT MW(0x520)
#define ASYNC MW(0x528)      /* >0 busy, 0 idle, <0 failed */
#define FLAGS MW(0x52C)
#define RESULT52 MW(0x530)

#define CARD_RESULT (*(s32 *)(D_003B0AA0 + 8))   /* last card result, < 0 on error */
#define CARD_TYPE (*(s32 *)(D_003B0AA0 + 12))
#define CARD_FREE (*(s32 *)(D_003B0AA0 + 16))
#define CARD_FORMATTED (*(s32 *)(D_003B0AA0 + 20))
#define CARD_NEEDED (*(s32 *)(D_003B0AA0 + 28))
#define PAD_PRESS (*(s32 *)(D_003B0B00 + 0x134))
#define PLAYER_FLAGS (*(s32 *)(D_003876A4 + 24))

#define REDRAW(arg) func_00297FE0(0, (arg), 0x40, 0x40, 1)

static void GoState(s32 state, s32 timer) {
    STATE = state;
    TIMER = timer;
}

/* The card went bad: show the error for 3 seconds in state 4. */
static void CardError(void) {
    GoState(4, 180);
}

/* No pending async result: either start a new one or flag the failure. min is the lowest ASYNC treated as "idle". */
static void AsyncIdleOrFail(s32 min) {
    if (ASYNC >= min) {
        ASYNC = func_0029C640(0);
        TIMER = 12;
    } else {
        func_0029C820(1);
        STATE = 22;
        ASYNC = 0;
    }
}

/* Message states that wait for a confirm/cancel press and then go to state 22. */
static void WaitConfirm(s32 code) {
    CODE = code;
    if (PAD_PRESS & 0x4008) {
        REDRAW(1);
        func_0029C820(1);
        STATE = 22;
    }
}

/* Poll the card info while the timer runs; err is the state taken on a fatal error. Returns after the first check. */
static void PollInfo(s32 code, s32 err) {
    CODE = code;
    if (McCard_GetInfo(0) == 0) {
        return;
    }
    if (TIMER > 0) {
        return;
    }
    if (McCard_IsFatalError(CARD_RESULT)) {
        GoState(err, 180);
    }
}

/* 0x003BF748: memory-card save/load flow, one state per call (STATE selects). */
s32 func_003BF748(void) {
    s32 r;

    if (STATE == 0) {
        return 0;
    }

    switch ((u32)(STATE - 4)) {
    case 0:  /* state 4 */
        func_0029C7C0(0);
        WaitConfirm(5);
        break;
    case 1:  /* state 5 */
        func_0029C7C0(0);
        WaitConfirm(16);
        break;
    case 2:  /* state 6 */
        break;
    case 3:  /* state 7 */
        func_0029C7C0(0);
        CODE = 34;
        if (func_0028A578(0, 1) == 0) {
            if (McCard_IsFatalError(CARD_RESULT)) {
                CardError();
            }
        } else {
            GoState(13, 120);
        }
        break;
    case 4:  /* state 8 */
        func_0029C7C0(0);
        func_0029C550(1);
        STATE = 9;
        break;
    case 5:  /* state 9 */
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() != 0) {
            STATE = 0;
            FLAGS |= 1;
            FLAGS |= 2;
            RESULT52 = 15;
        }
        break;
    case 6:  /* state 10 */
        func_0029C7C0(1);
        CODE = 28;
        if (ASYNC > 0) {
            if (--TIMER < 0) {
                GoState(11, 120);
                ASYNC = 0;
                func_00288348();
            }
        } else {
            AsyncIdleOrFail(0);
        }
        break;
    case 7:  /* state 11 */
        func_0029C7C0(0);
        if (--TIMER >= 0) {
            CODE = 34;
            if (McCard_GetInfo(0) == 0) {
                break;
            }
            if (TIMER > 0) {
                break;
            }
            if (CARD_TYPE != 2) {
                CardError();
            } else if (McCard_IsFatalError(CARD_RESULT)) {
                CardError();
            } else if (CARD_RESULT != 0) {
                if (PLAYER_FLAGS & 4) {
                    PLAYER_FLAGS ^= 4;
                } else {
                    McCard_Probe(0);
                    if (McCard_IsFatalError(CARD_RESULT)) {
                        CardError();
                    } else {
                        STATE = 21;
                        func_0029C820(1);
                    }
                }
            } else if (CARD_FORMATTED == 0) {
                STATE = 17;
                func_0029C820(1);
            }
        } else {
            CODE = 34;
            if (func_00289C98(0, SAVE_BUF) == 0) {
                if (CARD_TYPE != 2) {
                    CardError();
                } else if (CARD_FORMATTED == 0) {
                    STATE = 17;
                    func_0029C820(1);
                } else if (McCard_IsFatalError(CARD_RESULT)) {
                    CardError();
                } else if (CARD_RESULT < 0) {
                    if (CARD_FREE < 75) {
                        GoState(5, 180);
                    } else {
                        STATE = 7;
                    }
                }
            } else {
                func_00288348();
                STATE = 23;
            }
        }
        break;
    case 8:  /* state 12 */
        func_0029C7C0(1);
        CODE = 21;
        McCard_Probe(0);
        if (McCard_IsFatalError(CARD_RESULT)) {
            CardError();
            ASYNC = 0;
        } else if (ASYNC > 0) {
            if (--TIMER < 0) {
                GoState(14, 120);
                ASYNC = 0;
            }
        } else {
            AsyncIdleOrFail(0);
        }
        break;
    case 9:  /* state 13 */
        func_0029C7C0(0);
        if (--TIMER >= 0) {
            PollInfo(29, 16);
        } else {
            CODE = 29;
            if (McCard_CreateSave(0, SAVE_BUF) != 0) {
                STATE = 14;
            } else if (CARD_RESULT < 0) {
                GoState(16, 180);
            }
        }
        break;
    case 10:  /* state 14: write the save */
        func_0029C7C0(0);
        if (--TIMER >= 0) {
            PollInfo(29, 16);
        } else {
            CODE = 29;
            McCard_Checksum(D_00387F2C, 0x4000, 1);
            if (McCard_WriteSave(0, D_00387F2C, 0x4000, SAVE_BUF) != 0) {
                REDRAW(6);
                GoState(15, 180);
            } else if (CARD_RESULT < 0) {
                GoState(16, 180);
            }
        }
        break;
    case 11: /* state 15 */
        func_0029C7C0(0);
        PLAYER_FLAGS &= ~1;
        CODE = 30;
        if (PAD_PRESS & 0x4008) {
            REDRAW(1);
            STATE = 8;
        }
        break;
    case 12: /* state 16 */
        func_0029C7C0(0);
        WaitConfirm(31);
        break;
    case 13: /* state 17 */
        func_0029C7C0(1);
        CODE = 13;
        McCard_Probe(0);
        if (McCard_IsFatalError(CARD_RESULT)) {
            func_0029C7C0(0);
            CODE = 5;
            GoState(4, 180);
            ASYNC = 0;
        } else if (ASYNC > 0) {
            if (--TIMER < 0) {
                GoState(18, 120);
                ASYNC = 0;
            }
        } else {
            AsyncIdleOrFail(0);
        }
        break;
    case 14: /* state 18 */
        func_0029C7C0(0);
        if (--TIMER >= 0) {
            PollInfo(12, 20);
        } else {
            CODE = 12;
            if (McCard_Format(0) != 0) {
                GoState(19, 180);
            } else if (CARD_RESULT < 0) {
                GoState(20, 180);
            }
        }
        break;
    case 15: /* state 19 */
        func_0029C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(CARD_RESULT)) {
            GoState(4, 180);
            ASYNC = 0;
        } else if (--TIMER >= 0) {
            CODE = 14;
        } else {
            GoState(13, 120);
        }
        break;
    case 16: /* state 20 */
        func_0029C7C0(0);
        WaitConfirm(15);
        break;
    case 17: /* state 21 */
        func_0029C7C0(1);
        CODE = 24;
        if (ASYNC > 0) {
            if (--TIMER < 0) {
                GoState(11, 120);
                ASYNC = 0;
                McCard_Probe(0);
            }
        } else {
            AsyncIdleOrFail(-1);
        }
        break;
    case 18: /* state 22 */
        func_0029C7C0(1);
        CODE = 47;
        if (ASYNC > 0) {
            if (--TIMER < 0) {
                STATE = 8;
                ASYNC = 0;
            }
        } else if (ASYNC >= -1) {
            AsyncIdleOrFail(-1);
        } else {
            GoState(10, 120);
            ASYNC = 0;
            func_00288348();
        }
        break;
    case 19: /* state 23 */
        func_0029C7C0(0);
        CODE = 34;
        r = func_0028A790(0, SAVE_BUF);
        if (r == 0) {
            if (CARD_TYPE != 2) {
                CardError();
            } else if (CARD_FORMATTED == 0) {
                STATE = 17;
                func_0029C820(1);
            } else if (McCard_IsFatalError(CARD_RESULT)) {
                CardError();
            }
        } else if (CARD_NEEDED <= 0) {
            GoState(12, 120);
            func_0029C820(1);
        } else if (CARD_FREE < CARD_NEEDED) {
            GoState(5, 180);
        } else {
            GoState(24, 120);
            func_0029C820(1);
        }
        break;
    case 20: /* state 24 */
        func_0029C7C0(1);
        CODE = 21;
        McCard_Probe(0);
        if (McCard_IsFatalError(CARD_RESULT)) {
            CardError();
            ASYNC = 0;
        } else if (ASYNC > 0) {
            if (--TIMER < 0) {
                GoState(13, 120);
                ASYNC = 0;
            }
        } else {
            AsyncIdleOrFail(0);
        }
        break;
    case 21: /* state 25 */
        func_0029C7C0(1);
        CODE = 38;
        if (ASYNC > 0) {
            if (--TIMER < 0) {
                func_00298528(D_00387F2C + 7644 + SLOT * 34, M);
                FLAGS |= 0x40;
                STATE = 26;
                ASYNC = 0;
            }
        } else if (ASYNC >= 0) {
            AsyncIdleOrFail(0);
        } else {
            STATE = 26;
            ASYNC = 0;
        }
        break;
    case 22: /* state 26 */
        func_0029C7C0(0);
        func_0029C550(1);
        STATE = 27;
        break;
    case 23: /* state 27 */
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() != 0) {
            STATE = 0;
        }
        break;
    default:
        break;
    }

    func_0029C800(CODE);
    return func_0029C1E8(1);
}

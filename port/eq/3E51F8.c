#include "common.h"

/* Menu overlay: memory-card save/load dialog state machine, one step per frame.
 * dlg->state (0x110) is the current step, dlg->timer (0x118) a countdown, dlg->answer (0x114)
 * the player's choice from the message box (>0 confirm, 0 pending, <0 cancel),
 * dlg->msg (0x10C) the text id shown. The switch is dense by state (2..0x21). */

extern u8 *D_004279CC;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern s32 D_003B0C34;
extern u8 gMcCardPort[];
extern int Port_Autosave(void);

s32 func_0029C1E8();
void func_0029C7C0(s32 arg0);
void func_0029C550(s32 arg0);
s32 func_0029C640(s32 arg0);
void func_0029C820(s32 arg0);
s32 func_0029C830(void);
void func_0029C800(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00289C98(s32 port, u8 *buf);
s32 func_0028A578(s32 arg0, s32 arg1);
s32 func_0028A790(s32 port, u8 *buf);
void func_00288348(void);
void func_0024B4C8(void);
void func_00102360(void);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_003E4B10(void);
void func_0026EB78(u8 *obj, const char *name);
s32 McCard_GetInfo();
s32 McCard_IsFatalError();
s32 McCard_Probe();
s32 McCard_ReadFile();
s32 McCard_Checksum();
s32 McCard_WriteSave();
s32 McCard_CreateSave();
s32 McCard_Format();

#define W(p, off) (*(s32 *)((p) + (off)))
#define DLG(off) W(D_004279CC, off)
#define MSG DLG(0x10C)
#define STATE DLG(0x110)
#define ANSWER DLG(0x114)
#define TIMER DLG(0x118)
#define BUF (D_004279CC + 0x120)     /* 0x4000-byte save image */
#define BUF_END (D_004279CC + 0x4120)
#define SYS_FLAGS (*(u32 *)(D_003876A4 + 0x18))
#define MC_FLAGS W(gMcCardPort, 0x0)
#define MC_STATUS W(gMcCardPort, 0x8)
#define MC_TYPE W(gMcCardPort, 0xC)
#define MC_FREE W(gMcCardPort, 0x10)
#define MC_FORMATTED W(gMcCardPort, 0x14)
#define MC_NEEDED W(gMcCardPort, 0x1C)
#define PAD_OK_OR_BACK (D_003B0C34 & 0x4008)

#define GO(s, t) (STATE = (s), TIMER = (t))
#define GO_NOCARD() GO(2, 180)
#define ERR_AFTER_CREATE() GO(22, 180)

s32 func_003E51F8(void) {
    s32 saved;
    s32 v;

    if (DLG(0x110) == 0) {
        return -1;
    }
    MSG = -1;
    switch (STATE) {
    case 2:
        func_0029C7C0(0);
        MSG = 5;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            if (DLG(0xD0) & 8) {
                STATE = 29;
                ANSWER = 0;
                func_0029C820(1);
            } else {
                func_0029C820(1);
                STATE = DLG(0xDC) ? 30 : 29;
            }
        }
        break;
    case 3:
        func_0029C7C0(0);
        MSG = 7;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            func_0029C820(1);
            STATE = 30;
        }
        SYS_FLAGS &= ~0x400;
        break;
    case 4:
        func_0029C7C0(0);
        MSG = 16;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 5:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 34;
            if (func_00289C98(0, BUF_END)) {
                TIMER = 120;
                STATE = 9;
            } else if (MC_TYPE != 2) {
                GO_NOCARD();
            } else if (McCard_IsFatalError(MC_STATUS)) {
                GO_NOCARD();
            } else if (MC_STATUS < 0) {
                STATE = 7;
            }
        } else {
            MSG = 34;
            if (McCard_GetInfo(0) && TIMER <= 0) {
                if (MC_TYPE != 2) {
                    GO_NOCARD();
                } else if (McCard_IsFatalError(MC_STATUS)) {
                    GO_NOCARD();
                }
            }
        }
        break;
    case 7:
        func_0029C7C0(0);
        MSG = 34;
        if (func_0028A578(0, 1)) {
            GO(MC_STATUS == 1 ? 12 : 3, 180);
        } else if (McCard_IsFatalError(MC_STATUS)) {
            GO(2, 180);
        }
        break;
    case 8:
        func_0029C7C0(0);
        MSG = 34;
        if (func_0028A578(0, 1)) {
            GO(19, 120);
        } else if (McCard_IsFatalError(MC_STATUS)) {
            GO(2, 180);
        }
        break;
    case 9:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 8;
            if (McCard_ReadFile(0, BUF, 0x4000, BUF_END)) {
                if (MC_FLAGS & 1) {
                    GO(12, 180);
                } else if (McCard_Checksum(BUF, 0x4000, 0)) {
                    GO(12, 180);
                } else {
                    __builtin_memcpy(D_00387F2C, BUF, 0x4000);
                    func_0024B4C8();
                    saved = W(D_003876A4, 40);
                    func_00102360();
                    W(D_003876A4, 40) = saved;
                    STATE = 10;
                    TIMER = 180;
                }
            } else if (MC_STATUS < 0) {
                GO(11, 180);
            }
        } else {
            MSG = 8;
            if (McCard_GetInfo(0)) {
                if (TIMER <= 0) {
                    if (McCard_IsFatalError(MC_STATUS)) {
                        GO(11, 180);
                    }
                }
            }
        }
        break;
    case 10:
        func_0029C7C0(0);
        SYS_FLAGS &= ~1;
        SYS_FLAGS |= 0x800;
        MSG = 10;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            STATE = 14;
        } else {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 14;
            }
        }
        break;
    case 11:
        func_0029C7C0(0);
        MSG = 9;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            func_0029C820(1);
            STATE = 30;
        }
        break;
    case 12:
        func_0029C7C0(0);
        MSG = 25;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            func_0029C820(1);
            STATE = 30;
        }
        break;
    case 13:
        func_0029C7C0(1);
        func_0029C550(0);
        MSG = 4;
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 5;
                TIMER = 120;
                ANSWER = 0;
                func_00288348();
            }
        } else if (ANSWER == 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            func_0029C820(1);
            STATE = 30;
            ANSWER = 0;
        }
        break;
    case 14:
        func_0029C7C0(0);
        func_0029C550(1);
        func_0029C640(0);
        STATE = 15;
        break;
    case 15:
        func_0029C640(0);
        if (DLG(0xD0) & 4) {
            DLG(0xD0) ^= 4;
        }
        if (func_0029C830()) {
            if (DLG(0xD0) & 2) {
                func_00243A80(0, 0, 0);
                STATE = 0;
            } else {
                DLG(0x11C) = 1;
                STATE = 0;
                func_0026EB78(D_004279CC + 0x3C, "fr_saveload_out");
                func_003E4B10();
            }
        }
        break;
    case 16:
        func_0029C7C0(1);
        func_0029C550(0);
        DLG(0x11C) = 0;
        MSG = 28;
        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 17;
                TIMER = 120;
                ANSWER = 0;
                func_00288348();
            }
        } else if (ANSWER == 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            func_0029C820(1);
            STATE = 29;
            ANSWER = 0;
        }
        break;
    case 17:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 34;
            if (func_00289C98(0, BUF_END)) {
                func_00288348();
                STATE = 31;
            } else if (MC_TYPE != 2) {
                GO_NOCARD();
            } else if (MC_FORMATTED == 0) {
                STATE = 23;
                func_0029C820(1);
            } else if (McCard_IsFatalError(MC_STATUS)) {
                GO_NOCARD();
            } else if (MC_STATUS < 0) {
                if (MC_FREE >= 75) {
                    STATE = 8;
                } else {
                    GO(4, 180);
                }
            }
        } else {
            MSG = 34;
            if (McCard_GetInfo(0) && TIMER <= 0) {
                if (MC_TYPE != 2) {
                    GO_NOCARD();
                } else if (McCard_IsFatalError(MC_STATUS)) {
                    GO_NOCARD();
                } else if (MC_STATUS == 0) {
                    if (MC_FORMATTED == 0) {
                        STATE = 23;
                        func_0029C820(1);
                    }
                } else if (SYS_FLAGS & 4) {
                    SYS_FLAGS ^= 4;
                } else {
                    McCard_Probe(0);
                    if (McCard_IsFatalError(MC_STATUS)) {
                        GO_NOCARD();
                    } else {
                        STATE = 27;
                        func_0029C820(1);
                        SYS_FLAGS &= ~0x400;
                    }
                }
            }
        }
        break;
    case 18:
        func_0029C7C0(1);
        MSG = 21;
        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
        McCard_Probe(0);
        if (McCard_IsFatalError(MC_STATUS)) {
            GO(2, 180);
            ANSWER = 0;
        } else if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                GO(20, 120);
                ANSWER = 0;
            }
        } else if (ANSWER == 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 19:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 18;
            if (McCard_CreateSave(0, BUF_END)) {
                STATE = 20;
            } else if (MC_STATUS < 0) {
                ERR_AFTER_CREATE();
            }
        } else {
            MSG = 18;
            if (McCard_GetInfo(0) && TIMER <= 0 && McCard_IsFatalError(MC_STATUS)) {
                ERR_AFTER_CREATE();
            }
        }
        break;
    case 20:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 29;
            if (!McCard_WriteSave(0, D_00387F2C, 0x4000, BUF_END)) {
                if (MC_STATUS < 0) {
                    ERR_AFTER_CREATE();
                }
            } else {
                GO(21, 180);
            }
        } else {
            MSG = 29;
            if (McCard_GetInfo(0) && TIMER <= 0 && McCard_IsFatalError(MC_STATUS)) {
                ERR_AFTER_CREATE();
            }
        }
        break;
    case 21:
        func_0029C7C0(0);
        SYS_FLAGS |= 0x400;
        SYS_FLAGS &= ~1;
        MSG = 30;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            STATE = 14;
        } else {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 14;
            }
        }
        break;
    case 22:
        func_0029C7C0(0);
        MSG = 31;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 23:
        func_0029C7C0(1);
        MSG = 13;
        McCard_Probe(0);
        if (McCard_IsFatalError(MC_STATUS)) {
            func_0029C7C0(0);
            MSG = 5;
            STATE = 2;
            TIMER = 180;
            ANSWER = 0;
        } else if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                GO(24, 120);
                ANSWER = 0;
            }
        } else if (ANSWER == 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 24:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 12;
            if (McCard_Format(0)) {
                GO(25, 180);
            } else if (MC_STATUS < 0) {
                GO(26, 180);
            }
        } else {
            MSG = 12;
            if (McCard_GetInfo(0) && TIMER <= 0 && McCard_IsFatalError(MC_STATUS)) {
                GO(26, 180);
            }
        }
        break;
    case 25:
        func_0029C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(MC_STATUS)) {
            STATE = 2;
            TIMER = 180;
            ANSWER = 0;
        } else {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 19;
                TIMER = 120;
            } else {
                MSG = 14;
            }
        }
        break;
    case 26:
        func_0029C7C0(0);
        MSG = 15;
        if (PAD_OK_OR_BACK) {
            func_00297FE0(0, 1, 64, 64, 1);
            STATE = 29;
            ANSWER = 0;
            func_0029C820(1);
        }
        break;
    case 27:
        func_0029C7C0(1);
        MSG = 24;
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 17;
                TIMER = 120;
                ANSWER = 0;
                McCard_Probe(0);
            }
        } else if (ANSWER >= -1) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 28:
        func_0029C7C0(1);
        func_0029C550(0);
        DLG(0x11C) = 0;
        MSG = 37;
        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 17;
                TIMER = 120;
                ANSWER = 0;
                func_00288348();
            }
        } else if (ANSWER >= 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            ANSWER = 0;
            func_0029C820(1);
            STATE = 29;
        }
        break;
    case 29:
        func_0029C7C0(1);
        MSG = 47;
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 14;
                ANSWER = 0;
            }
        } else if (ANSWER >= -1) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            v = 16;
            if ((DLG(0xD0) & 4) == 0) {
                v = 28;
            }
            STATE = v;
            TIMER = 120;
            ANSWER = 0;
            func_00288348();
        }
        break;
    case 30:
        func_0029C7C0(1);
        MSG = 48;
        if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                STATE = 14;
                ANSWER = 0;
            }
        } else if (ANSWER >= -1) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            STATE = 13;
            TIMER = 120;
            ANSWER = 0;
            func_00288348();
        }
        break;
    case 31:
        func_0029C7C0(0);
        MSG = 34;
        if (!func_0028A790(0, BUF_END)) {
            if (MC_TYPE == 2) {
                if (MC_FORMATTED == 0) {
                    STATE = 23;
                    func_0029C820(1);
                } else if (McCard_IsFatalError(MC_STATUS)) {
                    GO_NOCARD();
                }
            } else {
                GO_NOCARD();
            }
        } else if (MC_NEEDED > 0) {
            if (MC_FREE < MC_NEEDED) {
                GO(4, 180);
            } else {
                GO(32, 120);
                func_0029C820(1);
            }
        } else {
            GO(18, 120);
            func_0029C820(1);
        }
        break;
    case 32:
        func_0029C7C0(1);
        MSG = 21;
        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
        McCard_Probe(0);
        if (McCard_IsFatalError(MC_STATUS)) {
            GO(2, 180);
            ANSWER = 0;
        } else if (ANSWER > 0) {
            TIMER -= 1;
            if (TIMER < 0) {
                GO(33, 120);
                ANSWER = 0;
            }
        } else if (ANSWER == 0) {
            ANSWER = func_0029C640(0);
            TIMER = 12;
        } else {
            func_0029C820(1);
            STATE = 29;
            ANSWER = 0;
        }
        break;
    case 33:
        func_0029C7C0(0);
        TIMER -= 1;
        if (TIMER < 0) {
            MSG = 29;
            if (McCard_CreateSave(0, BUF_END)) {
                STATE = 20;
            } else if (MC_STATUS < 0) {
                ERR_AFTER_CREATE();
            }
        } else {
            MSG = 29;
            if (McCard_GetInfo(0) && TIMER <= 0 && McCard_IsFatalError(MC_STATUS)) {
                ERR_AFTER_CREATE();
            }
        }
        break;
    default:
        break;
    }
    func_0029C800(MSG);
    return func_0029C1E8(1);
}

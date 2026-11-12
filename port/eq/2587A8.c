#include "common.h"

extern s32 *D_00387A00;
extern s32 *D_003876A4;
extern s32 D_00387F2C;
extern s32 D_003B0C34;
extern s32 gMcCardPort[];

extern void func_0029C7C0(s32 a0);
extern void func_0029C550(s32 a0);
extern void func_0029C820(s32 a0);
extern void func_0029C7E0(s32 a0);
extern void func_0029C810(s32 a0);
extern s32 func_0029C640(s32 a0);
extern s32 func_0029C830(void);
extern void func_0029C800(s32 a0);
extern s32 func_0029C1E8(s32 a0);
extern void func_00288348(void);
extern s32 func_0028A578(s32 a0, s32 a1);
extern s32 func_00289C98(s32 a0, s32 *buf);
extern s32 func_0028A790(s32 a0, s32 *buf);
extern void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 McCard_GetInfo(s32 port);
extern s32 McCard_IsFatalError(s32 status);
extern void McCard_Probe(s32 port);
extern s32 McCard_Format(s32 port);
extern s32 McCard_CreateSave(s32 port, s32 *buf);
extern s32 McCard_WriteSave(s32 port, s32 data, s32 size, s32 *buf);

/* the memory-card flow object: [3] flags, [4] counter, [5] state, [6] timer, [7] message code, [8] result, [9..] buffer */
#define CUR D_00387A00
#define PORT_STATUS gMcCardPort[2]
#define PORT_MODE gMcCardPort[3]
#define PORT_SLOTS gMcCardPort[5]
#define PORT_FREE gMcCardPort[4]
#define PORT_NEED gMcCardPort[7]

/* go to state s, timer 120 */
#define GO_STATE(s) \
    do { \
        CUR[5] = (s); \
        CUR[6] = 120; \
        goto tail; \
    } while (0)
/* same, and clear the result */
#define GO_STATE_CLR(s) \
    do { \
        CUR[5] = (s); \
        CUR[6] = 120; \
        CUR[8] = 0; \
        goto tail; \
    } while (0)

/* Memory-card save/load flow: one step of the state machine per call. */
s32 func_002587A8(void) {
    s32 t;
    s32 code;
    s32 st = CUR[5];

    if (st == 0) {
        return 0;
    }
    switch (st) {
    case 1:
        func_0029C7C0(0);
        CUR[7] = 5;
        if (!(D_003B0C34 & 0x4008)) {
            goto tail;
        }
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        CUR[5] = 0x15;
        func_0029C820(1);
        CUR[8] = 0;
        goto tail;
    case 2:
        func_0029C7C0(0);
        code = 7;
        goto show_msg;
    case 3:
        func_0029C7C0(0);
        code = 0x10;
        goto show_msg;
    case 5:
        func_0029C7C0(0);
        CUR[7] = 0x22;
        if (func_0028A578(0, 1) == 0) {
            if (!McCard_IsFatalError(gMcCardPort[2])) {
                goto tail;
            }
            GO_STATE(1);
        }
        GO_STATE(0xC);
    case 6:
        func_0029C7C0(0);
        func_0029C550(1);
        CUR[5] = 7;
        goto tail;
    case 7:
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() == 0) {
            goto tail;
        }
        CUR[5] = 0;
        CUR[3] |= 1;
        CUR[3] |= 2;
        CUR[4] = 0xF;
        goto tail;
    case 8:
        func_0029C550(0);
        func_0029C820(1);
        func_0029C7E0(1);
        func_0029C810(0);
        CUR[8] = 0;
        CUR[5] = 9;
        goto tail;
    case 9:
        func_0029C7C0(1);
        CUR[7] = 0x1C;
        t = CUR[8];
        if (t > 0) {
            CUR[6] = CUR[6] - 1;
            if (CUR[6] >= 0) {
                goto tail;
            }
            code = 10;
            goto wait_done;
        }
        goto result_check;
    case 10:
        func_0029C7C0(0);
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            CUR[7] = 0x22;
            if (func_00289C98(0, CUR + 9) != 0) {
                func_00288348();
                CUR[5] = 0x16;
                goto tail;
            }
            if (PORT_MODE != 2) {
                GO_STATE(1);
            }
            if (PORT_SLOTS == 0) {
                code = 0x10;
                goto set_state_wait;
            }
            if (McCard_IsFatalError(PORT_STATUS)) {
                GO_STATE(1);
            }
            if (PORT_STATUS >= 0) {
                goto tail;
            }
            if (PORT_FREE < 0x4B) {
                GO_STATE(3);
            }
            CUR[5] = 5;
            goto tail;
        }
        CUR[7] = 0x22;
        if (McCard_GetInfo(0) == 0) {
            goto tail;
        }
        if (CUR[6] > 0) {
            goto tail;
        }
        if (PORT_MODE != 2) {
            CUR[5] = 1;
            CUR[6] = 120;
            goto tail;
        }
        if (McCard_IsFatalError(PORT_STATUS)) {
            GO_STATE(1);
        }
        if (PORT_STATUS == 0) {
            if (PORT_SLOTS != 0) {
                goto tail;
            }
            code = 0x10;
            goto set_state_wait;
        }
        if (D_003876A4[6] & 4) {
            D_003876A4[6] = D_003876A4[6] ^ 4;
            goto tail;
        }
        McCard_Probe(0);
        if (McCard_IsFatalError(PORT_STATUS)) {
            GO_STATE(1);
        }
        code = 0x14;
        goto set_state_wait;
    case 11:
        func_0029C7C0(1);
        CUR[7] = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(gMcCardPort[2])) {
            GO_STATE_CLR(1);
        }
        t = CUR[8];
        if (t <= 0) {
            goto result_check_21;
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] >= 0) {
            goto tail;
        }
        GO_STATE_CLR(0xD);
    case 12:
        func_0029C7C0(0);
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            CUR[7] = 0x1D;
            if (McCard_CreateSave(0, CUR + 9)) {
                CUR[5] = 0xD;
                goto tail;
            }
            if (gMcCardPort[2] >= 0) {
                goto tail;
            }
            GO_STATE(0xF);
        }
        CUR[7] = 0x1D;
        if (McCard_GetInfo(0) == 0) {
            goto tail;
        }
        if (CUR[6] > 0) {
            goto tail;
        }
        if (!McCard_IsFatalError(gMcCardPort[2])) {
            goto tail;
        }
        GO_STATE(0xF);
    case 13:
        func_0029C7C0(0);
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            CUR[7] = 0x1D;
            if (McCard_WriteSave(0, D_00387F2C, 0x4000, CUR + 9)) {
                GO_STATE(0xE);
            }
            if (gMcCardPort[2] >= 0) {
                goto tail;
            }
            GO_STATE(0xF);
        }
        CUR[7] = 0x1D;
        if (McCard_GetInfo(0) == 0) {
            goto tail;
        }
        if (CUR[6] > 0) {
            goto tail;
        }
        if (!McCard_IsFatalError(gMcCardPort[2])) {
            goto tail;
        }
        GO_STATE(0xF);
    case 14:
        func_0029C7C0(0);
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            CUR[5] = 6;
            goto tail;
        }
        CUR[7] = 0x1E;
        goto tail;
    case 15:
        func_0029C7C0(0);
        code = 0x1F;
        goto show_msg;
    case 16:
        func_0029C7C0(1);
        CUR[7] = 0xD;
        McCard_Probe(0);
        if (McCard_IsFatalError(gMcCardPort[2])) {
            func_0029C7C0(0);
            CUR[7] = 5;
            CUR[5] = 1;
            CUR[6] = 120;
            CUR[8] = 0;
            goto tail;
        }
        t = CUR[8];
        if (t <= 0) {
            goto result_check;
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] >= 0) {
            goto tail;
        }
        GO_STATE_CLR(0x11);
    case 17:
        func_0029C7C0(0);
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            CUR[7] = 0xC;
            if (McCard_Format(0)) {
                GO_STATE(0x12);
            }
            if (gMcCardPort[2] >= 0) {
                goto tail;
            }
            GO_STATE(0x13);
        }
        CUR[7] = 0xC;
        if (McCard_GetInfo(0) == 0) {
            goto tail;
        }
        if (CUR[6] > 0) {
            goto tail;
        }
        if (!McCard_IsFatalError(gMcCardPort[2])) {
            goto tail;
        }
        GO_STATE(0x13);
    case 18:
        func_0029C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(gMcCardPort[2])) {
            GO_STATE_CLR(1);
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] < 0) {
            GO_STATE(0xC);
        }
        CUR[7] = 0xE;
        goto tail;
    case 19:
        func_0029C7C0(0);
        code = 0xF;
        goto show_msg;
    case 20:
        func_0029C7C0(1);
        CUR[7] = 0x18;
        t = CUR[8];
        if (t <= 0) {
            if (t < -1) {
                goto fail_result;
            }
            goto read_result;
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] >= 0) {
            goto tail;
        }
        CUR[5] = 10;
        CUR[6] = 120;
        CUR[8] = 0;
        McCard_Probe(0);
        goto tail;
    case 21:
        func_0029C7C0(1);
        CUR[7] = 0x2F;
        t = CUR[8];
        if (t > 0) {
            CUR[5] = 6;
            CUR[8] = 0;
            goto tail;
        }
        if (t >= 0) {
            goto read_result;
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] >= 0) {
            goto tail;
        }
        func_0029C820(1);
        code = 9;
        goto wait_done;
    case 22:
        func_0029C7C0(0);
        CUR[7] = 0x22;
        if (func_0028A790(0, CUR + 9) == 0) {
            if (PORT_MODE != 2) {
                GO_STATE(1);
            }
            if (PORT_SLOTS == 0) {
                code = 0x10;
                goto set_state_wait;
            }
            if (!McCard_IsFatalError(PORT_STATUS)) {
                goto tail;
            }
            GO_STATE(1);
        }
        if (PORT_NEED <= 0) {
            code = 0xB;
            goto set_state_timer;
        }
        if (PORT_FREE < PORT_NEED) {
            GO_STATE(3);
        }
        code = 0x17;
        goto set_state_timer;
    case 23:
        func_0029C7C0(1);
        CUR[7] = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(gMcCardPort[2])) {
            GO_STATE_CLR(1);
        }
        t = CUR[8];
        if (t <= 0) {
            goto result_check_21;
        }
        CUR[6] = CUR[6] - 1;
        if (CUR[6] >= 0) {
            goto tail;
        }
        GO_STATE_CLR(0xC);
    default:
        goto tail;
    }

    /* message code + optional overlay then state 0x15 */
show_msg:
    CUR[7] = code;
    if (!(D_003B0C34 & 0x4008)) {
        goto tail;
    }
    func_00297FE0(0, 1, 0x40, 0x40, 1);
    func_0029C820(1);
    CUR[5] = 0x15;
    goto tail;

    /* state change, then func_0029C820(1) */
set_state_wait:
    CUR[5] = code;
    func_0029C820(1);
    goto tail;

    /* state change with timer 120, then func_0029C820(1) */
set_state_timer:
    CUR[5] = code;
    CUR[6] = 120;
    func_0029C820(1);
    goto tail;

    /* end of the wait: new state, timer 120, result cleared, then func_00288348 */
wait_done:
    CUR[5] = code;
    CUR[6] = 120;
    CUR[8] = 0;
    func_00288348();
    goto tail;

    /* result == 0 reads the new result, result < 0 is a failure */
result_check:
    if (t >= 0) {
        goto read_result;
    }
fail_result:
    func_0029C820(1);
    CUR[5] = 0x15;
    CUR[8] = 0;
    goto tail;
result_check_21:
    if (t >= 0) {
        goto read_result;
    }
    func_0029C820(1);
    CUR[5] = 0x15;
    CUR[8] = 0;
    goto tail;
read_result:
    CUR[8] = func_0029C640(0);
    CUR[6] = 12;

tail:
    func_0029C800(CUR[7]);
    return func_0029C1E8(1);
}

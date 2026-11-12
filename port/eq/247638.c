#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern u8 *D_00387958;
extern u8 *D_00387F2C;
extern u8 D_003B0B00[];
extern u8 D_003745B0[];
extern u8 D_00387968[];

extern s32 func_0026EB70(u8 *p);
extern s32 func_0026EB60(u8 *p);
extern void func_0026EB78(u8 *p, u8 *name);
extern void func_0026EAE0(u8 *p, s32 n);
extern s32 func_001018B8(void);
extern void EftShotFx_Update_2494A0(void);
extern s32 func_002493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_00298460(s32 a0, s32 a1, s32 a2);
extern void func_00251088();
extern void func_00243A80(s32 a0, s32 a1, s32 a2);

#define PAD() W(D_003B0B00, 0x134)

/* Shop-like menu state machine on D_00387958[0x1288] (state), button bits from PAD(). */
void func_00247638(s32 *arg0) {
    switch (W(D_00387958, 0x1288)) {
    case 0:
        break;
    case 1:
        if (func_0026EB70(D_00387958 + 0x28) & 8) {
            W(D_00387958, 0x1248) = 0;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
        }
        break;
    case 2:
        if (!(func_0026EB60(D_00387958 + 0x28) && (PAD() & 0x4000))) {
            if (func_001018B8() != 5) {
                return;
            }
        }
        func_0026EB78(D_00387958 + 0x28, D_003745B0);
        EftShotFx_Update_2494A0();
        W(D_00387958, 0x1248) = -1;
        if (PAD() & 0x4000) {
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        {
            s32 v = 5;

            if (!(W(D_00387958, 0x122C) & 4)) {
                if (*(s16 *)(D_00387F2C + 0x24DE) == 0) {
                    v = 0x14;
                }
            }
            W(D_00387958, 0x1288) = v;
        }
        func_0026EAE0(D_00387958 + 0x50, 0x3C);
        break;
    case 5:
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            W(D_00387958, 0x122C) |= 0x200;
        }
        if (func_0026EB70(D_00387958 + 0x28) & 8) {
            W(D_00387958, 0x1248) = 4;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = 0;
        }
        break;
    case 10:
        W(D_00387958, 0x1248) = -1;
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            W(D_00387958, 0x1248) = 5;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = 0;
            W(D_00387958, 0x122C) ^= 0x100;
            W(D_00387958, 0x122C) &= ~0x80;
        }
        break;
    case 20:
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            W(D_00387958, 0x122C) &= ~0x200;
        }
        if (func_0026EB70(D_00387958 + 0x28) & 8) {
            W(D_00387958, 0x1248) = 1;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
        }
        break;
    case 21:
        if (!(PAD() & 0x4000)) {
            return;
        }
        if (func_0026EB60(D_00387958 + 0x28)) {
            W(D_00387958, 0x1248) = 2;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        break;
    case 22:
        if (!(PAD() & 0x4000)) {
            return;
        }
        if (func_0026EB60(D_00387958 + 0x28)) {
            W(D_00387958, 0x1248) = 3;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            func_00298460(0x16B, W(*(u8 **)(D_00387958 + 0x1250), 0x4420), 1);
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
        }
        break;
    case 23:
        if (!((PAD() & 0x4000) && func_0026EB60(D_00387958 + 0x28))) {
            if (func_001018B8() != 5) {
                return;
            }
        }
        if (PAD() & 0x4000) {
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        W(D_00387958, 0x122C) |= 0x200;
        W(D_00387958, 0x1288) = 0;
        break;
    case 30:
        W(D_00387958, 0x1248) = -1;
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            W(D_00387958, 0x122C) &= ~0x200;
        }
        if (func_0026EB70(D_00387958 + 0x28) & 8) {
            W(D_00387958, 0x1248) = 13;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
        }
        break;
    case 31:
        if (!((PAD() & 0x5000) && func_0026EB60(D_00387958 + 0x28))) {
            if (func_001018B8() != 5) {
                return;
            }
        }
        if (PAD() & 0x5000) {
            EftShotFx_Update_2494A0();
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        W(D_00387958, 0x122C) |= 2;
        func_0026EB78(D_00387958 + 0x28, D_00387968);
        W(D_00387958, 0x1288) = 0x46;
        break;
    case 40:
        if (!(PAD() & 0x9000)) {
            return;
        }
        func_00251088();
        func_00297FE0(0, 2, 0x40, 0x40, 1);
        W(D_00387958, 0x1288) = W(D_00387958, 0x1288) + 1;
        break;
    case 41:
        W(D_00387958, 0x1288) = 0;
        break;
    case 50:
        W(D_00387958, 0x1248) = -1;
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            W(D_00387958, 0x1248) = (W(D_00387958, 0x122C) & 0x10) ? 10 : 6;
            func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
            W(D_00387958, 0x1288) = 0;
            W(D_00387958, 0x122C) ^= 0x100;
            if (W(D_00387958, 0x122C) & 0x10) {
                W(D_00387958, 0x122C) |= 0x400;
            } else {
                W(D_00387958, 0x122C) &= ~0x400;
            }
        }
        break;
    case 60: {
        s32 fl = W(D_00387958, 0x122C);
        s32 v;

        if (fl & 0x80) {
            v = (fl & 0x10) ? 12 : 8;
        } else {
            v = (fl & 0x10) ? 10 : 6;
        }
        W(D_00387958, 0x1248) = v;
        func_002493C0(W(D_00387958, 0xAC), 0x36CE, 0x3AE7, 0, W(D_00387958, 0x1248));
        W(D_00387958, 0x1288) = 0;
        break;
    }
    case 70:
        if (func_0026EB70(D_00387958 + 0x28) & 0x200) {
            *arg0 = 0;
            func_00243A80(0, 0, 0);
            W(D_00387958, 0x1288) = 0;
        }
        break;
    default:
        break;
    }
}

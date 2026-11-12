#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_002EFAB8(void *fmt, s32 arg1, s32 arg2);
u32 sceSifAllocIopHeap(u32 size);
void func_002FCFE8(void);
s32 func_002FCC58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FCE58(u32 a0, u32 a1, u32 a2);
void func_002FCE68(u32 a0, u32 a1, u32 a2);
s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4);
void func_00306850(void);
void func_00306AA8(void);
void func_003025A0(void);
void func_00301A98(void);
extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));
extern s32 D_0035D238 __attribute__((section(".data")));
extern s32 D_0035D23C __attribute__((section(".data")));
extern s32 D_0035D240 __attribute__((section(".data")));
extern s32 D_0035D244 __attribute__((section(".data")));
extern s32 D_0035D26C __attribute__((section(".data")));
extern s32 D_0035D270 __attribute__((section(".data")));
extern s32 D_0035D274 __attribute__((section(".data")));
extern s32 D_0035D278 __attribute__((section(".data")));
extern s32 D_0035FCC0 __attribute__((section(".data")));
extern s32 D_0035FCC4 __attribute__((section(".data")));
extern u8 D_0035FCC8[] __attribute__((section(".data")));
extern u8 D_0037F0F0[] __attribute__((section(".data")));
extern u8 D_0037F228[] __attribute__((section(".data")));
extern u8 D_0037F270[] __attribute__((section(".data")));
extern u8 D_0037F298[] __attribute__((section(".data")));

/* 0x00302278: Init del sistema de sonido (contador D_0035D26C). Si D_0035D228 == 1 y D_0035D220 <= 0 no hace
 * nada (ni incrementa). La primera vez: func_00306850, func_00306AA8, func_002FCFE8, func_003025A0,
 * func_00301A98; limpia D_0035FCC8 (0x8D0), D_0035FCC4 = 0x880, D_0035D270 = (D_0035FCC8 + 0x40) & ~0x3F;
 * si D_0035D274 == 0 reserva 0x8D0 en el IOP (falla -> printf y cuelga); printf de control;
 * D_0035D278 = (iop + 0x40) & ~0x3F; D_0035FCC0 = func_002FCC58(1, ee, iop, 0x880) (0 -> cuelga);
 * callbacks 0x00301EF0 / 0x00301F50 (direcciones PS2, sin C nativo); si D_0035D23C == 0:
 * D_0035D244 = D_0035D220, D_0035D238 = D_0035D220 * 0x400 + 0x40, D_0035D23C = alloc IOP (falla -> cuelga) +
 * printf de control. Después D_0035D240 = (D_0035D23C + 0x3F) & ~0x3F y RPC 0xA con
 * {D_0035D244, D_0035D240, D_0035D238}. Al final D_0035D26C++. (El lw de D_0035C278 a $a1 no se usa.) */
void func_00302278(void) {
    s32 sp[4];

    if (D_0035D228 == 1 && D_0035D220 <= 0) {
        return;
    }
    if (D_0035D26C == 0) {
        func_00306850();
        func_00306AA8();
        func_002FCFE8();
        func_003025A0();
        func_00301A98();
        memset(D_0035FCC8, 0, 0x8D0);
        D_0035FCC4 = 0x880;
        D_0035D270 = (s32)(((u32)D_0035FCC8 + 0x40) & ~0x3Fu);
        if (D_0035D274 == 0) {
            D_0035D274 = (s32)sceSifAllocIopHeap(0x8D0);
            if (D_0035D274 == 0) {
                func_002EFAB8(D_0037F228, 0x8D0, 0);
                for (;;) {
                }
            }
        }
        func_002EFAB8(D_0037F0F0, 0x8D0, D_0035D274);
        D_0035D278 = (D_0035D274 + 0x40) & ~0x3F;
        D_0035FCC0 = func_002FCC58(1, D_0035D270, D_0035D278, D_0035FCC4);
        if (D_0035FCC0 == 0) {
            func_002EFAB8(D_0037F270, 0, 0);
            for (;;) {
            }
        }
        func_002FCE58((u32)D_0035FCC0, 0x00301EF0u, 0);
        func_002FCE68((u32)D_0035FCC0, 0x00301F50u, 0);
        if (D_0035D23C == 0) {
            D_0035D244 = D_0035D220;
            D_0035D238 = (D_0035D220 << 10) + 0x40;
            D_0035D23C = (s32)sceSifAllocIopHeap(D_0035D238);
            if (D_0035D23C == 0) {
                func_002EFAB8(D_0037F298, D_0035D238, 0);
                for (;;) {
                }
            }
            func_002EFAB8(D_0037F0F0, D_0035D238, D_0035D23C);
        }
        D_0035D240 = (D_0035D23C + 0x3F) & ~0x3F;
        sp[0] = D_0035D244;
        sp[1] = D_0035D240;
        sp[2] = D_0035D238;
        func_002FD150((u8 *)0xA, sp, 3, NULL, 0);
    }
    D_0035D26C += 1;
}

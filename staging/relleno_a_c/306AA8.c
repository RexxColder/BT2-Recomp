#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_002FCFE8(void);
void func_002EFAB8(void *fmt, s32 arg1);
u32 sceSifAllocIopHeap(u32 size);
s32 func_002FCC58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FCE58(u32 a0, u32 a1, u32 a2);
void func_002FCE68(u32 a0, u32 a1, u32 a2);
s32 func_002FD150(u8 *arg0, s32 *arg1, s32 arg2, s32 *arg3, s32 arg4);
extern s32 D_003658EC __attribute__((section(".data")));
extern s32 D_003658F0 __attribute__((section(".data")));
extern s32 D_003658F4 __attribute__((section(".data")));
extern s32 D_003658F8 __attribute__((section(".data")));
extern s32 D_00365B80 __attribute__((section(".data")));
extern s32 D_00365B84 __attribute__((section(".data")));
extern u8 D_00365B88[] __attribute__((section(".data")));
extern u8 D_0037FA88[] __attribute__((section(".data")));
extern u8 D_0037FAB8[] __attribute__((section(".data")));

/* 0x00306AA8: Init con contador (D_003658EC) del cliente de sonido: la primera vez limpia D_00365B88 (0x8D0),
 * bind (func_002FCFE8), buffer EE alineado a 64 = (D_00365B88 + 0x40) & ~0x3F -> D_003658F0, tamaño 0x880 ->
 * D_00365B84; si D_003658F4 == 0 reserva 0x8D0 en el heap del IOP (falla -> printf y cuelga, como el original);
 * D_003658F8 = (iop + 0x40) & ~0x3F; D_00365B80 = func_002FCC58(0, ee, iop, 0x880) (0 -> printf y cuelga);
 * registra los callbacks 0x003068E0 y 0x00306980 (direcciones PS2: no tienen C nativo, el jmp de
 * full_patch_range las lleva al código que corresponda) y manda el RPC 3 sin datos. */
void func_00306AA8(void) {
    if (D_003658EC == 0) {
        memset(D_00365B88, 0, 0x8D0);
        func_002FCFE8();
        D_00365B84 = 0x880;
        D_003658F0 = (s32)(((u32)D_00365B88 + 0x40) & ~0x3Fu);
        if (D_003658F4 == 0) {
            D_003658F4 = (s32)sceSifAllocIopHeap(0x8D0);
            if (D_003658F4 == 0) {
                func_002EFAB8(D_0037FA88, 0);
                for (;;) {
                }
            }
        }
        D_003658F8 = (D_003658F4 + 0x40) & ~0x3F;
        D_00365B80 = func_002FCC58(0, D_003658F0, D_003658F8, D_00365B84);
        if (D_00365B80 == 0) {
            func_002EFAB8(D_0037FAB8, 0);
            for (;;) {
            }
        }
        func_002FCE58((u32)D_00365B80, 0x003068E0u, 0);
        func_002FCE68((u32)D_00365B80, 0x00306980u, 0);
        func_002FD150((u8 *)3, NULL, 0, NULL, 0);
    }
    D_003658EC += 1;
}

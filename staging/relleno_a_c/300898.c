#include "common.h"

void func_003007A0(s32 arg0);
void func_003007B8(s32 arg0);
void func_003007D0(s32 arg0, s32 arg1);
void func_00300888(void);
void *memset(void *dst, s32 c, u32 n);
extern s32 D_00357108 __attribute__((section(".data")));
extern u8 D_00357110[] __attribute__((section(".data")));

/* 0x00300898: inicialización con contador. Bajo el par func_003007A0/func_003007B8 (guardan/restauran estado en un
 * buffer de 16 bytes de la pila, como 2FFA38): la primera vez limpia D_00357110 (0x4700 bytes), llama a
 * func_00300888 y func_003007D0(0, 0); siempre incrementa D_00357108. (El lw de D_003570F0 del delay slot del
 * primer jal no se usa.) */
void func_00300898(void) {
    s32 sp[4];

    func_003007A0((s32)sp);
    if (D_00357108 == 0) {
        memset(D_00357110, 0, 0x4700);
        func_00300888();
        func_003007D0(0, 0);
    }
    D_00357108 += 1;
    func_003007B8((s32)sp);
}

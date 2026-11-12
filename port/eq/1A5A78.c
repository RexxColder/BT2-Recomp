#include "common.h"

void func_001E70B0(f32 f0, s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);

/* asm: a0=arg0+0x18 a1=[+0x1C] a2=0 a3=0 t0=flag t1=arg0+0x30 t2=[+0x20] t3=[+0x80] f12=[+0x74] */
void func_001A5A78(u8 *arg0) {
    s32 temp;
    s32 flag;

    temp = *(s32 *)(arg0 + 0x1C);
    if (temp != 0 && *(s32 *)(arg0 + 0x20) != 0) {
        flag = (*(u16 *)(arg0 + 0x88) & 0x10) != 0;
        func_001E70B0(*(f32 *)(arg0 + 0x74), (s32)(arg0 + 0x18), temp, 0, 0, flag, (s32)(arg0 + 0x30),
                      *(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x80));
    }
}

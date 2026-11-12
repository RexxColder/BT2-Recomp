#include "common.h"

/* 0x00281F50: memset(a0, 0, 0x190); func_00281F00(a0); D_00387B00 = a0. */
extern s32 D_00387B00;
void func_00281F00(s32 arg0);

void func_00281F50(void *a0) {
    memset(a0, 0, 0x190);
    func_00281F00((s32)a0);
    D_00387B00 = (s32)a0;
}

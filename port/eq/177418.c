#include "common.h"

s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
void EftTexSet_Load32(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);
extern s32 D_00387E94;

void func_00177418(void) {
    s32 temp;
    s32 dst;
    s32 p;

    temp = D_00387E94;
    if (temp == 0) {
        D_00387E94 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x3F70);
        memset((void *)D_00387E94, 0, 0x3F70);
        temp = D_00387E94;
    }
    dst = temp + 0x3D48;
    p = func_00126460(0x1C);
    EftTexSet_Load32(dst, p);
}

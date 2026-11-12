#include "common.h"

void BtlLoad_EndStageSwap(void);
void func_002BD250(s32 arg0, s32 arg1);

void func_002BC698(s32 arg0) {
    s32 i = 0;

    while (i < 10) {
        i++;
        func_002BD250(arg0, 1);
        BtlLoad_EndStageSwap();
        func_002BD250(arg0, 0);
        if (*(s32 *)(arg0 + 0x60) != 1) {
            break;
        }
    }
}

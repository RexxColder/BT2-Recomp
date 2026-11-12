#include "common.h"

void BtlTask_SetDead(s32 arg0);
void FlashShapePool_Term(s32 arg0);
void func_001A5A78(s32 arg0);
s32 func_001A5B18(s32 arg0);
void func_001A5B60(s32 arg0);
void func_001A5E48(s32 arg0);

void func_001A5920(s32 arg0) {
    s32 temp_s0;

    temp_s0 = *(s32 *) (arg0 + 0x38);
    if (*(u8 *) (arg0 + 1) == 0) {
        func_001A5A78(temp_s0);
        func_001A5B60(temp_s0);
        *(u8 *) (arg0 + 1) = 1;
    }
    if (func_001A5B18(temp_s0) == 0) {
        FlashShapePool_Term(temp_s0 + 0x18);
    }
    func_001A5E48(temp_s0);
    if (*(u16 *) (temp_s0 + 0x88) == 4) {
        BtlTask_SetDead(arg0);
    }
}

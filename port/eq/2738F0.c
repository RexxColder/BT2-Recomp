#include "common.h"

void func_002720B8(s32 arg0);
void func_00272E90(void);
void func_0028BB60(s32 arg0);
extern s32 D_003876A0;
extern u8 D_00387ABD;

void func_002738F0(s32 arg0) {
    s32 temp_s0;
    s32 temp_a0;

    temp_s0 = D_003876A0;
    func_002720B8(arg0);
    if (*(s32 *)(temp_s0 + 8) != 0) {
        func_0028BB60(*(s32 *)(temp_s0 + 8));
        *(s32 *)(temp_s0 + 8) = 0;
    }
    if (D_00387ABD != 1) {
        temp_a0 = *(s32 *)(temp_s0 + 4);
        if (temp_a0 != 0) {
            func_0028BB60(temp_a0);
            *(s32 *)(temp_s0 + 4) = 0;
        }
        func_00272E90();
        return;
    }
    *(s32 *)(temp_s0 + 4) = 0;
}

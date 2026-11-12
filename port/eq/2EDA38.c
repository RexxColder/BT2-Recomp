#include "common.h"

void func_002EA050(u8 *arg0);
void func_002ED660(u8 *arg0, s32 arg1, u32 arg2);
void func_002ED758(u8 *arg0);
void func_002FFF90(s32 arg0);
void func_00300720(s32 arg0, s32 arg1);
extern u8 D_0037C420[] __attribute__((section(".data")));

void func_002EDA38(u8 *arg0, s32 arg1, u32 arg2) {
    s32 temp_s0;

    if ((arg0 != NULL) && (arg1 <= 0)) {
        if (arg2 <= 0x10000U) {
            temp_s0 = *(s32 *)(arg0 + 0x94);
            func_002FFF90(temp_s0);
            func_002ED660(arg0, arg1, arg2);
            func_00300720(temp_s0, 1);
            func_002ED758(arg0);
            return;
        }
        func_002EA050(D_0037C420);
        return;
    }
    func_002EA050(D_0037C420);
}

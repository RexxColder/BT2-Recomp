#include "common.h"

void func_002ED220(s32 arg0);
void func_002F0078(void);
void func_002DA708(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00393E50[] __attribute__((section(".data")));

/* 0x002BD9E0: func_002ED220(arg0) (a0 passes through), func_002F0078(), func_002DA708(&D_00393E50, 0, 7); returns 0. */
s32 func_002BD9E0(s32 arg0) {
    func_002ED220(arg0);
    func_002F0078();
    func_002DA708((s32)D_00393E50, 0, 7);
    return 0;
}

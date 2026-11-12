#include "common.h"

void func_002EA2F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
void func_002EC198(void *arg0);
void func_002F1BC0(s32 arg0);
void func_002F1E48(s32 arg0);
void *memset(void *s, int c, unsigned int n);

void func_002EBB38(u8 *arg0) {
    s32 temp_s0;

    func_002EA2F0(3, 0, arg0, -1, -1);
    if (arg0 != NULL) {
        if (*(s8 *)(arg0 + 1) == 2) {
            func_002EC198(arg0);
        }
        temp_s0 = *(s32 *)(arg0 + 4);
        if (temp_s0 != 0) {
            *(u8 *)(arg0 + 0) = 0;
            *(s32 *)(arg0 + 4) = 0;
            func_002F1E48(temp_s0);
            func_002F1BC0(temp_s0);
        }
        memset(arg0, 0, 0x48);
        func_002EA2F0(3, 1, arg0, -1, -1);
    }
}

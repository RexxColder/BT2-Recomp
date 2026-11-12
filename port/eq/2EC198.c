#include "common.h"

void func_002E93C0(void);
void func_002E93D8(void);
void func_002EA050(void *arg0);
void func_002EA2F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
void func_002EBA98(void *arg0);
s32 func_002F1F78(s32 arg0);
void func_002F21A0(s32 arg0);
extern u8 D_0037BF38[];
extern u8 D_0037BF60[];

s32 func_002EC198(void *arg0) {
    s32 temp_a0;
    s8 temp_v1;

    func_002EA2F0(5, 0, arg0, -1, -1);
    if (arg0 == NULL) {
        func_002EA050(D_0037BF38);
        return -3;
    }
    temp_v1 = *(s8 *)((u8 *)arg0 + 1);
    if (temp_v1 != 1) {
        if (temp_v1 != 3) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 4);
            if (temp_a0 == 0) {
                func_002EA050(D_0037BF60);
                return -1;
            }
            func_002F21A0(temp_a0);
            func_002E93C0();
            *(s32 *)((u8 *)arg0 + 0x24) = func_002F1F78(*(s32 *)((u8 *)arg0 + 4)) - *(s32 *)((u8 *)arg0 + 0x18);
            func_002EBA98(arg0);
            *(s8 *)((u8 *)arg0 + 1) = 1;
            func_002E93D8();
            func_002EA2F0(5, 1, arg0, -1, -1);
            goto block_11;
        }
        *(s8 *)((u8 *)arg0 + 1) = 1;
        goto block_11;
    }
block_11:
    return *(s32 *)((u8 *)arg0 + 0x18);
}

#include "common.h"

void func_002E93C0();
void func_002E93D8();
void func_002EA050(void *arg0);
void func_002EA2F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
s32 func_002EBC78(void *arg0, s32 arg1, void *arg2);
void **func_00304760(s32 arg0, s32 arg1, s32 arg2);
void func_0030A430(s32 arg0, s32 arg1);
extern s32 D_003672D8 __attribute__((section(".data")));
extern u8 D_0037BE50 __attribute__((section(".data")));
extern u8 D_0037BE78 __attribute__((section(".data")));
extern u8 D_0037BEA8 __attribute__((section(".data")));
extern u8 D_0037BED0 __attribute__((section(".data")));

s32 func_002EBF28(void *arg0, s32 arg1, s32 arg2) {
    void *var_a0;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 var_v0;
    s8 temp_a0;
    void **temp_a0_2;
    void **temp_v0;

    func_002EA2F0(4, 0, arg0, arg1, arg2);
    if (arg0 == 0) {
        var_a0 = &D_0037BE50;
        goto block_8;
    }
    if (arg1 < 0) {
        var_a0 = &D_0037BE78;
        goto block_8;
    }
    if (arg2 != 0) {
        temp_a0 = *(s8 *)((u8 *)arg0 + 1);
        var_v0 = 0;
        if (temp_a0 != 2) {
            func_002E93C0(temp_a0);
            if (*(void ***)((u8 *)arg0 + 8) != 0) {
                func_002EA050(&D_0037BED0);
                func_002E93D8();
                return -1;
            }
            temp_s2 = arg1 << 0xB;
            func_002E93D8();
            temp_v0 = func_00304760(arg2, temp_s2, 0);
            var_v0 = -2;
            if (temp_v0 != 0) {
                func_002E93C0();
                *(s32 *)((u8 *)arg0 + 0x28) = arg2;
                *(void ***)((u8 *)arg0 + 8) = temp_v0;
                *(s32 *)((u8 *)arg0 + 0x2C) = temp_s2;
                if (D_003672D8 == 1) {
                    func_0030A430(arg2, temp_s2);
                }
                func_002E93D8();
                temp_v0_2 = func_002EBC78(arg0, arg1, *(void ***)((u8 *)arg0 + 8));
                if (temp_v0_2 <= 0) {
                    func_002E93C0();
                    temp_a0_2 = *(void ***)((u8 *)arg0 + 8);
                    if (temp_a0_2 != 0) {
                        (*(void (**)(void *))((u8 *)*temp_a0_2 + 0xC))(temp_a0_2);
                        *(void ***)((u8 *)arg0 + 8) = 0;
                    }
                    func_002E93D8();
                }
                *(u8 *)((u8 *)arg0 + 2) = 0;
                func_002EA2F0(4, 1, arg0, arg1, arg2);
                var_v0 = temp_v0_2;
            }
            return var_v0;
        }
        return var_v0;
    }
    var_a0 = &D_0037BEA8;
block_8:
    func_002EA050(var_a0);
    return -3;
}

#include "common.h"

void Mtx_StoreIdentity(void *arg0);
void func_00128C58(f32 farg0, void *arg1, void *arg2);
void func_00129BD0(void *arg1, void *arg2, f32 farg0);
void func_00129C38(void *arg0, void *arg1, s32 arg2);
void func_0018D298(f32 farg0, void *arg1, void *arg2, void *arg3, void *arg4);
extern s32 D_003877B8;

void func_0018E200(u8 *arg0, u8 *arg1) {
    s64 sp[2];
    s64 sp10[8];
    s64 sp50[3];
    u8 *temp_s1;
    u8 *temp_s3;
    u8 *var_s0;

    sp[1] = *(s64 *)(arg1 + 8);
    sp[0] = *(s64 *)(arg1 + 0);
    if ((D_003877B8 != 0) && (arg0 != NULL)) {
        temp_s1 = *(u8 **)(arg0 + 0x38);
        if (temp_s1 != NULL) {
            temp_s3 = temp_s1 + 0x10;
            if (*(u16 *)(temp_s1 + 0x56) & 2) {
                func_00129C38(temp_s3, sp, D_003877B8);
                Mtx_StoreIdentity(sp10);
                func_00128C58(*(f32 *)(temp_s1 + 0x30), sp10, sp10);
                var_s0 = *(u8 **)(temp_s1 + 0x158);
                if (var_s0 != NULL) {
                    do {
                        func_00129BD0(sp50, temp_s1 + 0x20, -1.0f);
                        func_0018D298(*(f32 *)(temp_s1 + 0x30), var_s0, sp10, temp_s3, sp50);
                        var_s0 = *(u8 **)(var_s0 + 0xF4);
                    } while (var_s0 != NULL);
                }
            }
        }
    }
}

#include "common.h"

void Rand_Range(void *arg0, void *arg1);
void func_002B74F8(s32 arg0, s32 arg1);
s32 func_002B8280(s32 arg0);
void func_002BACC8(s32 arg0);
void func_002BAD68(s32 arg0, s32 arg1);
void func_002BB0F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FFF90(s32 arg0);
extern u8 D_00379D20[];

void func_002BB180(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_002B8280((s32)arg0);
    if (temp_v0 != 1) {
        Rand_Range(D_00379D20, arg1);
        return;
    }
    func_002B74F8((s32)arg0, (s32)arg1);
    func_002FFF90(*(s32 *)((u8 *)arg0 + 0x48));
    func_002BB0F8((s32)arg0, (s32)arg1, arg2, arg3);
    func_002BAD68((s32)arg0, 1);
    func_002BACC8((s32)arg0);
    *(s32 *)((u8 *)arg0 + 0x2E4) = 3;
    *(s32 *)((u8 *)arg0 + 0x2F4) = arg2;
    *(s32 *)((u8 *)arg0 + 0x2F8) = arg3;
    *(s32 *)((u8 *)arg0 + 0x2DC) = temp_v0;
    if (*(s32 *)((u8 *)arg0 + 0x2E0) == 0) {
        *(s32 *)((u8 *)arg0 + 0x2E8) = temp_v0;
    }
}

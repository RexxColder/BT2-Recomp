#include "common.h"

s32 func_00276B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003126C8(s32 arg0, s32 arg1);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_00276C40(s32 arg0, s32 arg1, s32 arg2) {
    u8 *stage;
    s64 flags;

    stage = gBtlStage;
    if (stage != 0) {
        flags = *(s64 *)(D_003876A0 + 0x4D8);
        if ((flags & 0x2000) == 0) {
            if (*(s32 *)(stage + 4) != 0) {
                if (func_00276B00(arg0, arg1, arg2, (s32)stage) < 0) {
                    func_003126C8(arg1, (s32)D_002C3630);
                    func_003126C8(arg2, (s32)D_002C3630);
                }
                return 1;
            }
        }
    }
    func_003126C8(arg1, (s32)D_002C3630);
    func_003126C8(arg2, (s32)D_002C3630);
    return -1;
}

#include "common.h"

void FlashShapePool_Term(void *arg0);
void func_00147FB8(s32 arg0);
void func_0014EEF8(s32 arg0, void *arg1);
void *func_001F3758(void *arg0);

void func_00170CE0(void *arg0) {
    u8 *obj;
    u8 *temp_s0;
    u8 *temp_s1;

    obj = func_001F3758(arg0);
    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s1 = *(u8 **)(temp_s0 + 0xB0);
    func_0014EEF8(*(s32 *)(obj + 0x38), temp_s0 + 0xB4);
    if (*(s32 *)(*(u8 **)(temp_s1 + 0x20) + 0x4) != 0) {
        func_00147FB8(*(s32 *)temp_s1);
    }
    FlashShapePool_Term(temp_s0 + 0xABC);
}

#include "common.h"

void func_001E04C8(s32 arg0, s32 arg1, f32 farg0);

void func_001E09D0(u8 *arg0) {
    if (*(u8 *)(arg0 + 0x21E5) != 0) {
        func_001E04C8((s32)arg0, *(s32 *)(arg0 + 0x21E8), *(f32 *)(arg0 + 0x21E0));
    }
}

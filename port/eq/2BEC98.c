#include "common.h"

void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
void func_002D1C08(s32 arg0, s32 arg1, s32 arg2);
extern void func_002BECD8(void);

void func_002BEC98(s32 arg0) {
    func_002D1C08(arg0, (s32)func_002BECD8, 2);
    func_002D05E8(arg0, 0xF, 2);
}

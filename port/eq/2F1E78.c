#include "common.h"

void func_002F21A0(s32 arg0);
void func_002F1DD8(s32 arg0);
void func_0030A5F0(void);

void func_002F1E78(s32 arg0) {
    func_002F21A0(arg0);
    func_002F1DD8(arg0);
    while (*(s8 *)((u8 *)arg0 + 0x49) != 0) {
        func_0030A5F0();
    }
}

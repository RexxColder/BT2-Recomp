#include "common.h"

void func_002F3378(s32 arg0);
void func_002F3390(s32 arg0, s32 arg1);

void func_002F2138(s32 arg0) {
    func_002F3378(arg0);
    if ((*(s32 *)((u8 *)arg0 + 0) & 0xFFFF00) == 0x10200) {
        *(s8 *)((u8 *)arg0 + 0x48) = 1;
        if (*(s8 *)((u8 *)arg0 + 0x47) == 1) {
            *(s8 *)((u8 *)arg0 + 0x47) = 0;
        }
    } else {
        *(s8 *)((u8 *)arg0 + 1) = 1;
    }
    func_002F3390(0x10200, 1);
}

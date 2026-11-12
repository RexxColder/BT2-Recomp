#include "common.h"

void func_002BA1C8(void *arg0);
void func_002BA378(void *arg0);

void func_002BA128(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x17C) != 0 && *(s32 *)((u8 *)arg0 + 0x194) != 1) {
        func_002BA1C8(arg0);
        func_002BA378(arg0);
    }
}

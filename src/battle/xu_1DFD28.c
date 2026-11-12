#include "common.h"

/* Forwards arg0 and the byte arg1 & 0xFF, with the word at +0x21C0 of arg0 in between. */
void func_001DFCA0(s32 arg0, s32 arg1, s32 arg2);

void func_001DFD28(void *arg0, s32 arg1) {
    func_001DFCA0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x21C0), arg1 & 0xFF);
}

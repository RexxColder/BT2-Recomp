#include "common.h"

extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_002C8920(s32 arg0, s32 arg1);
s32 func_002C8AD8(s32 arg0, s32 arg1);
void func_002D1C18(s32 arg0, s32 arg1, s32 arg2);

/* 0x002C9540: one-shot setup of the record at arg0+0xE48 (flag word, 0 = not yet). Copies a
 * 32-byte block from +0xDF4 to a frame buffer, runs two probes (func_002C8920, and func_002C8AD8
 * only when the first returned 0; a zero result clears frame word 0x18), calls func_002D1C18 on
 * the frame's two out-words, copies the buffer to +0xE4C, then stores flag 1, the difference of
 * the first out-word against +0xD6C+0x24 and the second out-word. */
void func_002C9540(u8 *arg0) {
    u8 *s1 = arg0 + 0xE48;
    u8 *s2 = arg0 + 0xD6C;
    u32 buf[20];
    u8 *sp = (u8 *)buf;

    if (*(s32 *)s1 != 0) {
        return;
    }

    memcpy(sp, arg0 + 0xDF4, 0x20);
    if (func_002C8920((s32)arg0, 3) == 0) {
        if (func_002C8AD8((s32)arg0, 3) == 0) {
            *(s32 *)(sp + 0x18) = 0;
        }
    }

    func_002D1C18((s32)sp, (s32)(sp + 0x20), (s32)(sp + 0x24));
    memcpy(arg0 + 0xE4C, sp, 0x20);

    *(s32 *)s1 = 1;
    *(s32 *)(s1 + 0x24) = *(s32 *)(sp + 0x20) - *(s32 *)(s2 + 0x24);
    *(s32 *)(s1 + 0x28) = *(s32 *)(sp + 0x24);
}

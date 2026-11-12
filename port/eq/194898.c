#include "common.h"

void func_001929C0(u8 *arg0, u8 *arg1, s64 arg2, s64 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_00194898(u8 *arg0, u8 *arg1) {
    u8 *s1;
    u8 *base;
    u8 *dst;
    u8 *src;
    s64 t2;
    s64 t3;

    s1 = *(u8 **)(arg0 + 0x38);
    memset(s1, 0, 0x1F0);
    base = s1 + 0x10;
    dst = base;
    src = arg1;
    do {
        t2 = *(s64 *)(src + 0x08);
        t3 = *(s64 *)(src + 0x10);
        *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
        *(s64 *)(dst + 0x08) = t2;
        *(s64 *)(dst + 0x10) = t3;
        *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
        src += 0x20;
        dst += 0x20;
    } while (src != arg1 + 0x40);
    *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
    *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
    func_001929C0(s1, base, t2, t3);
}

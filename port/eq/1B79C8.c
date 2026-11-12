#include "m2c_macros.h"

void func_001B79C8(void *arg0, void *arg1) {
    u8 *dst = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *src = (u8 *)arg1;
    u8 *end = src + 0x80;

    do {
        *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
        *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
        *(s64 *)(dst + 0x10) = *(s64 *)(src + 0x10);
        *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
        src += 0x20;
        dst += 0x20;
    } while (src != end);
}

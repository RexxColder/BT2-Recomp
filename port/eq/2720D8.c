#include "common.h"

void func_002720D8(u8 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    f32 a = farg0;
    f32 b = farg1;
    f32 c = farg2;
    f32 na = -a;
    f32 nb = -b;
    f32 nc = -c;

    *(f32 *)(arg0 + 0xE4) = b;
    *(f32 *)(arg0 + 0xF0) = a;
    *(f32 *)(arg0 + 0x10) = a;
    *(f32 *)(arg0 + 0x100) = na;
    *(f32 *)(arg0 + 0x14) = b;
    *(f32 *)(arg0 + 0x18) = c;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(f32 *)(arg0 + 0x90) = a;
    *(f32 *)(arg0 + 0x94) = b;
    *(f32 *)(arg0 + 0x98) = c;
    *(f32 *)(arg0 + 0x9C) = 1.0f;
    *(f32 *)(arg0 + 0xA0) = na;
    *(f32 *)(arg0 + 0xA4) = b;
    *(f32 *)(arg0 + 0xA8) = c;
    *(f32 *)(arg0 + 0xAC) = 1.0f;
    *(f32 *)(arg0 + 0xB0) = a;
    *(f32 *)(arg0 + 0xB4) = nb;
    *(f32 *)(arg0 + 0xB8) = c;
    *(f32 *)(arg0 + 0xBC) = 1.0f;
    *(f32 *)(arg0 + 0xC0) = na;
    *(f32 *)(arg0 + 0xC4) = nb;
    *(f32 *)(arg0 + 0xC8) = c;
    *(f32 *)(arg0 + 0xCC) = 1.0f;
    *(f32 *)(arg0 + 0xD0) = a;
    *(f32 *)(arg0 + 0xD4) = b;
    *(f32 *)(arg0 + 0xD8) = nc;
    *(f32 *)(arg0 + 0xDC) = 1.0f;
    *(f32 *)(arg0 + 0xE0) = na;
    *(f32 *)(arg0 + 0xE8) = nc;
    *(f32 *)(arg0 + 0xEC) = 1.0f;
    *(f32 *)(arg0 + 0xF4) = nb;
    *(f32 *)(arg0 + 0xF8) = nc;
    *(f32 *)(arg0 + 0xFC) = 1.0f;
    *(f32 *)(arg0 + 0x104) = nb;
    *(f32 *)(arg0 + 0x10C) = 1.0f;
    *(f32 *)(arg0 + 0x108) = nc;
}

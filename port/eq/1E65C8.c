#include "common.h"

extern f32 D_003434A8[16];

f32 *func_001E65C8(f32 *out, u8 *base, u32 idx) {
    u64 bits = *(u64 *)(base + (idx & 0xFF) * 16);
    f32 *entry;

    out[0] = D_003434A8[(bits >> 26) & 0xF];
    bits = *(u64 *)(base + (idx & 0xFF) * 16);
    entry = &D_003434A8[(bits >> 30) & 0xF];
    out[3] = 1.0f;
    out[1] = *entry;
    out[2] = 0.0f;
    return entry;
}

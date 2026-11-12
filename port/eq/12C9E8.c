#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

u8 *func_0012B9B0(void);
s32 func_0012BB50(u8 *arg0, s32 arg1, u8 *arg2);
void func_0012D868(u8 *out, u8 *a, u8 *b, s32 n, u8 *c, u8 *d);

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* Clips a polygon against 5 planes, then queues it as a triangle fan of GIF packets (0x80 bytes each):
   vertex j uses screen xyz sp[0x10*j], uv sp[0x90 + 0x10*j] and colour floats obj[0x120 + 0x10*j]. */
void func_0012C9E8(u8 *obj, u8 *arg1, u64 *tex, s32 base, s32 zbits) {
    /* real frame reaches sp+0x110: uv at sp+0x90+0x10*j, j<8 */
    u8 sp[0x120] __attribute__((aligned(16)));
    u64 m = 0xFF000000FFFFFFFFull;
    u64 zmask = (u64)(zbits & 0xFFFFFF) << 32;
    u8 *tbl;
    s32 n = 3;
    s32 i;
    s32 j;
    s32 key;
    u8 *pkt;
    u8 *ent;
    u8 *prev;
    u8 *vA;
    u8 *vB;
    u8 *vC;
    u8 *cB;
    u8 *cC;
    u8 *uB;
    u8 *uC;

    tbl = func_0012B9B0();
    for (i = 0; i < 5; i++) {
        n = func_0012BB50(tbl, n, obj);
        tbl += 0x10;
    }
    if (n == 0) {
        return;
    }
    func_0012D868(sp, arg1, obj, n, sp + 0x90, obj + 0x90);

    for (j = 2; j < n; j++) {
        vA = sp;
        vB = sp + 0x10 * (j - 1);
        vC = sp + 0x10 * j;
        cB = obj + 0x120 + 0x10 * (j - 1);
        cC = obj + 0x120 + 0x10 * j;
        uB = sp + 0x90 + 0x10 * (j - 1);
        uC = sp + 0x90 + 0x10 * j;

        if (*(s32 *)(vA + 8) > 0xFFFFFF) {
            *(s32 *)(vA + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vB + 8) > 0xFFFFFF) {
            *(s32 *)(vB + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vC + 8) > 0xFFFFFF) {
            *(s32 *)(vC + 8) = 0xFFFFFF;
        }

        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x80;
        *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
        *(u64 *)(pkt + 0x20) = 0x5B;
        *(u64 *)(pkt + 0x00) = 0xA0000007ull;
        *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
        pkt[0x30] = f2u(*(f32 *)(obj + 0x120));
        pkt[0x31] = f2u(*(f32 *)(obj + 0x124));
        pkt[0x32] = f2u(*(f32 *)(obj + 0x128));
        pkt[0x33] = f2u(*(f32 *)(obj + 0x12C));
        *(f32 *)(pkt + 0x34) = *(f32 *)(sp + 0x98);
        pkt[0x48] = f2u(*(f32 *)(cB + 0x0));
        pkt[0x49] = f2u(*(f32 *)(cB + 0x4));
        pkt[0x4A] = f2u(*(f32 *)(cB + 0x8));
        pkt[0x4B] = f2u(*(f32 *)(cB + 0xC));
        *(f32 *)(pkt + 0x4C) = *(f32 *)(uB + 0x8);
        pkt[0x60] = f2u(*(f32 *)(cC + 0x0));
        pkt[0x61] = f2u(*(f32 *)(cC + 0x4));
        pkt[0x62] = f2u(*(f32 *)(cC + 0x8));
        pkt[0x63] = f2u(*(f32 *)(cC + 0xC));
        *(f32 *)(pkt + 0x64) = *(f32 *)(uC + 0x8);
        *(u16 *)(pkt + 0x40) = *(u16 *)(vA + 0);
        *(u16 *)(pkt + 0x42) = *(u16 *)(vA + 4);
        *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | zmask;
        pkt[0x47] = 0xFF;
        *(u16 *)(pkt + 0x58) = *(u16 *)(vB + 0);
        *(u16 *)(pkt + 0x5A) = *(u16 *)(vB + 4);
        *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & m) | zmask;
        pkt[0x5F] = 0xFF;
        *(u16 *)(pkt + 0x70) = *(u16 *)(vC + 0);
        *(u16 *)(pkt + 0x72) = *(u16 *)(vC + 4);
        *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | zmask;
        pkt[0x77] = 0xFF;
        *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0x90);
        *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0x94);
        *(f32 *)(pkt + 0x50) = *(f32 *)(uB + 0x0);
        *(f32 *)(pkt + 0x54) = *(f32 *)(uB + 0x4);
        *(f32 *)(pkt + 0x68) = *(f32 *)(uC + 0x0);
        *(f32 *)(pkt + 0x6C) = *(f32 *)(uC + 0x4);
        *(u64 *)(pkt + 0x28) = *tex;
        if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 12C9E8 %llx ret %p", (unsigned long long)*(u64 *)(pkt + 0x28), __builtin_return_address(0)); /* TEMP TEX0 */

        key = (*(s32 *)(vA + 8) + *(s32 *)(vB + 8) + *(s32 *)(vC + 8)) / 3;
        key >>= 8;
        if (key < 0) {
            ent = D_00387AE0 + (base << 3);
        } else if (key < 0x1000) {
            ent = D_00387AE0 + ((key * 2 + base) << 3);
        } else {
            ent = D_00387AE0 + (base << 3) + 0xFFF0;
        }
        prev = *(u8 **)(ent + 4);
        *(u8 **)(prev + 4) = pkt;
        *(u8 **)(ent + 4) = pkt;
    }
}

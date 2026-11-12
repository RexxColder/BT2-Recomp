#include "common.h"
void *memcpy(void *dst, const void *src, unsigned long n);

extern u8 *D_0042311C __attribute__((section(".data")));
extern u8 D_00424DF0[] __attribute__((section(".data")));
extern u8 D_00424E00[] __attribute__((section(".data")));
extern u8 D_00424E10[] __attribute__((section(".data")));
extern u8 D_00424E20[] __attribute__((section(".data")));
extern u8 D_00424E38[] __attribute__((section(".data")));
extern u8 D_00424E48[] __attribute__((section(".data")));
extern u8 D_00424E58[] __attribute__((section(".data")));
extern u8 D_00424E70[] __attribute__((section(".data")));

void func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_002495A8(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249778(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249FB8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_0024A198(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
void func_00325830(u8 *a0, u8 *a1, s32 a2);
void func_0024A8A0(u8 *a0, s32 a1, s32 a2);
void func_0024AB10(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, u8 *t1);
void func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
void func_0026ED60(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, f32 f12, f32 f13);
void func_0026EA58(u8 *a0);
s32 func_0024C060(void);

/* 0x003CEA08: menu draw pass. Builds the name strings and rects on the stack, draws the guide/text
   window groups (and the bonus/amount block when the flags say so), then the background quad, and
   draws the four-part overlay at o+0x14 with the 0x28 stride. */
s32 func_003CEA08(void) {
    u8 *o;
    u8 *s2;
    u8 *ent;
    s32 x;
    s32 adj;
    s32 cnt;
    s32 i;
    u8 *amt;
    u8 buf[16];       /* sp+0x00 */
    s32 rect[4];      /* sp+0x10 .. sp+0x1F */
    u8 name[32];      /* sp+0x30 */
    u8 amounts[48];   /* sp+0x50 */
    u8 digits[16];    /* sp+0x80 */
    u8 blk[20];       /* sp+0x90 */

    o = D_0042311C;
    s2 = o + 0x8C;

    func_0026EBC0(s2, D_00424DF0, buf);
    func_002495A8(s2, buf, o + 0x144, 1);
    func_0026EBC0(s2, D_00424E00, buf);
    func_00249778(s2, buf, o + 0x148, 3);
    func_0026EBC0(s2, D_00424E10, buf);
    func_00249FB8(s2, buf, 0, 0, *(s32 *)(o + 0xC), *(s32 *)(o + 0x11C), 1);

    if (*(s32 *)(o + 0x118) & 0x40) {
        func_0026EBC0(s2, D_00424E20, buf);
        func_0024A198(s2, buf, 4, 0, *(s32 *)(o + 0x10), *(s32 *)(o + 0x130) + 1, 0, 306);

        ent = *(u8 **)(o + 0x140) + 48 * *(s32 *)(o + 0x130);
        x = *(s32 *)(ent + 8);
        adj = (x < 0) ? x + 3 : x;
        rect[1] = (adj >> 2) << 6;
        rect[3] = rect[1] + 64;
        rect[0] = (x - ((adj >> 2) << 2)) << 6;
        rect[2] = rect[0] + 64;

        func_0026EBC0(s2, D_00424E38, buf);
        func_0026EC48(s2, buf, (u8 *)rect);
    }

    if (*(s32 *)(o + 0x118) & 0xC) {
        amt = amounts;
        cnt = 0;
        do {
            cnt += 1;
            func_00325830(name, D_00424E48, 6 - (cnt - 1));
            func_0026EBC0(s2, name, amt);
            amt += 8;
        } while (cnt < 6);

        func_0024A8A0(digits, *(s32 *)(o + 0x134), 6);
        func_0024AB10(s2, amounts, 0, 0, *(s32 *)(o + 0x13C), digits);
    }

    o = D_0042311C;
    s2 = o + 0x14;
    memcpy(blk, D_00424E58, 20);
    func_0026EBC0(s2, D_00424E70, buf);
    func_0026ED60(s2, buf, blk, o + 0x12C, 0, -0.25f, 0.0f);

    i = 3;
    {
        s32 off = 0;
        do {
            i -= 1;
            func_0026EA58(D_0042311C + off + 0x14);
            off += 0x28;
        } while (i >= 0);
    }

    return func_0024C060();
}

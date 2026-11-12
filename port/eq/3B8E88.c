#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));
extern u8 D_00421A88[] __attribute__((section(".data")));
extern u8 D_00421A98[] __attribute__((section(".data")));
extern u8 D_00421AA8[] __attribute__((section(".data")));
extern u8 D_00421AC0[] __attribute__((section(".data")));
extern u8 D_00421AD8[] __attribute__((section(".data")));
extern u8 D_00421AE8[] __attribute__((section(".data")));
extern u8 D_00421B00[] __attribute__((section(".data")));
extern u8 D_00421B18[] __attribute__((section(".data")));
extern u8 D_00421B30[] __attribute__((section(".data")));
extern u8 D_00421B40[] __attribute__((section(".data")));

#define SPW(off) (*(s32 *)(sp + (off)))

s32 rand(void);
void func_277E70(u8 *a0, s32 a1, s32 a2);
void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_26EC48(u8 *a0, u8 *a1, u8 *a2);
void func_26EC78(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1, s32 t2, s32 t3);
void func_26EFC8(u8 *a0, u8 *a1, s32 a2);
void func_26EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_26EF38(u8 *a0, u8 *a1, f32 f12, f32 f13);
void func_26EA58(u8 *a0);
void func_325830(u8 *a0, u8 *a1, s32 a2);

void func_003B8E88(void) {
    u8 *obj;
    u8 *s4;
    u8 *fp;
    u8 sp[0x80];
    s32 cnt;
    s32 cur;
    s32 i;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 r;
    s32 t0v;
    f32 f;
    u8 *t0;
    u8 *t1;
    u8 *t2;
    u8 *t4;
    s32 v0;
    s32 v1;
    s32 a0v;
    s32 a3v;

    obj = D_004213B0;
    func_277E70(*(u8 **)(obj + 0x60), 0, 0x80);

    s4 = obj + 0x10;
    cnt = *(s32 *)(obj + 0x45B8) + 1;
    *(s32 *)(obj + 0x45B8) = cnt;
    if (cnt >= 8) {
        *(s32 *)(obj + 0x45B8) = 0;
        *(s32 *)(obj + 0xCC) ^= 0x40;
    }

    if (*(s32 *)(obj + 0xCC) & 0x40) {
        f = (f32)*(s32 *)(obj + 0x45B8);
        f = f * 0.125f;
        f = f * 0.19999993f;
        f = f + 0.9f;
        *(f32 *)(obj + 0x45BC) = f;
    } else {
        f = (f32)*(s32 *)(obj + 0x45B8);
        f = f * 0.125f;
        f = f * 0.19999993f;
        f = 1.0999999f - f;
        *(f32 *)(obj + 0x45BC) = f;
    }

    cur = 0;
    for (i = 0; i < 5; i++) {
        s32 *ctr = (s32 *)(obj + 0x4554 + 4 * i);
        *ctr -= 1;
        if (*ctr < 0) {
            s0 = 8;
            s3 = 8;
            r = rand();
            {
                s32 *slot = (s32 *)(obj + 0x452C + 4 * (2 * i + (r % 2)));
                *slot = (*slot == 0);
            }
            r = rand();
            *(s32 *)(obj + 0x4554 + 4 * i) = (r % 24) + 8;

            r = rand();
            f = (f32)r;
            f = f / 2147483520.0f;
            f = f * 0.29999998f;
            f = f + 0.59999996f;
            *(f32 *)(obj + 0x457C + 4 * i) = f;

            {
                s32 ra = rand();
                s1 = ra % 8;
                {
                    s32 rb = rand();
                    s32 base;
                    s32 rc;
                    s0 = (rb & 1) ? 8 : -8;
                    rc = rand();
                    base = s0;
                    s0 = (rc & 1) ? base + s1 : base - s1;
                    *(s32 *)(obj + cur + 0x4590) = s0;
                }
            }

            {
                s32 rd;
                s32 re;
                s32 rf;
                s32 base;
                rd = rand();
                s0 = rd % 8;
                re = rand();
                base = (re & 1) ? s3 : -8;
                rf = rand();
                s3 = (rf & 1) ? base + s0 : base - s0;
                *(s32 *)(obj + cur + 0x4594) = s3;
            }
        }

        cur += 8;

        {
            s32 cc = *(s32 *)(obj + 0x4554 + 4 * i);
            s32 tq = (cc + (cc < 0)) >> 1;
            s32 mq = (tq < 0 ? tq + 3 : tq) >> 2 << 2;
            *(s32 *)(obj + 0x4568 + 4 * i) = 3 - (tq - mq);
        }
    }

    /* after the reset loop: fill the work buffer */
    fp = sp + 0x10;
    SPW(0x10) = 0;
    SPW(0x14) = 0;
    SPW(0x18) = 0x40;
    SPW(0x1C) = 0x40;
    func_26EBC0(s4, D_00421A88, sp);
    func_26EC78(s4, sp, obj + 0x451C, obj + 0x4524, fp, 4, 2, 2);
    func_26EBC0(s4, D_00421A98, sp);
    func_26EC78(s4, sp, obj + 0x4520, obj + 0x4528, fp, 4, 2, 2);
    func_26EBC0(s4, D_00421AA8, sp);
    func_26EFC8(s4, sp, 0x80);
    func_26EBC0(s4, D_00421AC0, sp);
    func_26EFC8(s4, sp, 0x80);

    f = 1.0f - *(f32 *)(obj + 0x45BC);
    f = f * 32.0f;
    s3 = (s32)f;
    func_26EBC0(s4, D_00421A88, sp);
    func_26EFC8(s4, sp, 0x80);
    func_26EF38(s4, sp, *(f32 *)(obj + 0x45BC), *(f32 *)(obj + 0x45BC));
    func_26EEC8(s4, sp, s3, s3);
    func_26EBC0(s4, D_00421A98, sp);
    func_26EFC8(s4, sp, 0x80);
    func_26EF38(s4, sp, *(f32 *)(obj + 0x45BC), *(f32 *)(obj + 0x45BC));
    func_26EEC8(s4, sp, s3, s3);
    func_26EBC0(s4, D_00421AD8, sp);
    func_26EFC8(s4, sp, 0x80);
    func_26EBC0(s4, D_00421AE8, sp);
    func_26EFC8(s4, sp, 0x80);

    /* per-slot loop */
    for (i = 0; i < 5; i++) {
        s2 = 4 * i;
        s1 = 8 * i;
        t0 = obj;
        t2 = t0 + s2 + 0x4568;
        t0 = t0 + 12;
        t1 = t0 + s1 + 0x4520;
        a0v = *(s32 *)t1;
        t4 = t0 + s1 + 0x4524;
        v1 = *(s32 *)t2;
        v0 = ((v1 + (v1 < 0)) >> 1) << 1;
        v1 = v1 - v0;
        v1 = (v1 + a0v) << 5;
        SPW(0x10) = v1;
        v0 = *(s32 *)t2;
        a3v = *(s32 *)t4;
        v0 = (((v0 + (v0 < 0)) >> 1) + a3v) << 5;
        SPW(0x14) = v0;
        v1 = *(s32 *)t2;
        {
            s32 t3v = *(s32 *)t1;
            s32 w = ((v1 + (v1 < 0)) >> 1) << 1;
            s32 m = (v1 - w) << 5;
            s32 cand = m + 32;
            SPW(0x18) = (t3v == 0) ? cand : m;
        }
        {
            s32 w = (*(s32 *)t2 + (*(s32 *)t2 < 0)) >> 1;
            s32 m = w << 5;
            s32 cand = m + 32;
            SPW(0x1C) = (*(s32 *)t4 == 0) ? cand : m;
        }
        f = 1.0f - *(f32 *)(t0 + s2 + 0x4570);
        f = f * 32.0f;
        s3 = (s32)f;
        func_325830(sp + 0x30, D_00421B00, i + 1);
        func_26EBC0(s4, sp + 0x30, sp);
        func_26EFC8(s4, sp, 0x80);
        func_26EC48(s4, sp, fp);
        func_26EF38(s4, sp, *(f32 *)(obj + s2 + 0x4570 + 0xC), *(f32 *)(obj + s2 + 0x4570 + 0xC));
        func_26EEC8(s4, sp, *(s32 *)(obj + s1 + 0x4590) + s3, *(s32 *)(obj + s1 + 0x4594) + s3);
        if (*(s32 *)(obj + 0x4554 + s2) < 8) {
            func_26EFC8(s4, sp, 4);
        } else {
            func_26EFC8(s4, sp, 8);
        }
        func_325830(sp + 0x30, D_00421B18, i + 1);
        func_26EBC0(s4, sp + 0x30, sp);
        func_26EFC8(s4, sp, 0x80);
        func_26EC48(s4, sp, fp);
        func_26EF38(s4, sp, *(f32 *)(obj + s2 + 0x457C), *(f32 *)(obj + s2 + 0x457C));
        func_26EEC8(s4, sp, *(s32 *)(obj + s1 + 0x4590) + s3, *(s32 *)(obj + s1 + 0x4594) + s3);
        if (*(s32 *)(obj + 0x4554 + s2) < 8) {
            func_26EFC8(s4, sp, 4);
        } else {
            func_26EFC8(s4, sp, 8);
        }
    }

    s4 = obj + 0x38;
    SPW(0x10) = 0;
    SPW(0x14) = (*(s32 *)(obj + 0xD0)) << 5;
    SPW(0x18) = 0x200;
    SPW(0x1C) = ((*(s32 *)(obj + 0xD0)) << 5) + 0x20;
    func_26EBC0(s4, D_00421B30, sp);
    func_26EC48(s4, sp, fp);
    SPW(0x10) = 0;
    SPW(0x14) = 0x20;
    SPW(0x18) = 0x20;
    SPW(0x1C) = 0x40;
    func_26EBC0(s4, D_00421B40, sp);
    func_26EC48(s4, sp, fp);
    func_26EA58(obj + 0x10);
    func_26EA58(obj + 0x38);
}

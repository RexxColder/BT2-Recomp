#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));

s32 func_00211288(s32 arg0);
void memset(void *arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void func_001F5958(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00217488(s32 arg0);
s32 func_00202DC0(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 func_0023F960(s32 arg0);
s32 func_0023F498(s32 arg0);
s32 func_0023F9B0(s32 arg0);
s32 func_00203188(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
void BtlMember_AddHealth(s32 arg0, s32 arg1);
void func_00203810(s32 arg0, s32 arg1);
void func_0025DB98(s32 arg0);

void func_001F5FD8(s32 arg0) {
    u8 *obj;
    u8 *a510;
    u8 *a950;
    u8 *a960;
    u8 *gau;
    u8 *g2;
    u8 *gg;
    u64 *src;
    u64 *dst;
    s32 i;
    s32 r;
    s32 r2;
    s32 flags;
    s32 v1;
    s32 a0v;
    s32 t;
    s32 a1;
    s32 q;
    s32 pp;
    f32 fa;
    f32 fb;
    f32 qq;
    f32 pr;
    f32 dd;
    s32 ri;

    obj = (u8 *)func_00211288(arg0);
    a510 = obj + 0x510;
    a950 = obj + 0x950;
    a960 = obj + 0x960;
    memset(a510, 0, 0xE0);
    func_003126C8((s32)a510, (s32)a950);
    func_003126C8((s32)(obj + 0x520), (s32)a960);
    func_003126C8(*(s32 *)(obj + 0x1530) + 0x9A0, (s32)a950);
    func_003126C8(*(s32 *)(obj + 0x1530) + 0x9B0, (s32)a960);
    func_003126C8(*(s32 *)(obj + 0x1530) + 0x9C0, (s32)a950);
    *(f32 *)(obj + 0x5C4) = *(f32 *)(obj + 0x524);

    src = (u64 *)a510;
    dst = (u64 *)(obj + 0x5F0);
    for (i = 0; i < 28; i++) {
        dst[i] = src[i];
    }
    src = (u64 *)a510;
    dst = (u64 *)(obj + 0x6D0);
    for (i = 0; i < 28; i++) {
        dst[i] = src[i];
    }

    func_003126C8((s32)a950, (s32)D_002C3630);
    func_003126C8((s32)a960, (s32)D_002C3630);
    func_001F5958((s32)obj);
    func_002113C0((s32)obj, 3, 0x1000, 1);
    r = func_00217488((s32)obj);

    if (r < 0x2E) {
        return;
    }
    if (r < 0x32) {
        /* block A */
        *(s32 *)(s32)func_00202DC0((s32)obj) = *(s32 *)(*(s32 *)(obj + 0x1530) + 4);
        gau = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        t = *(s32 *)(gau + 4) - *(s32 *)(gau + 8);
        r2 = func_0023F960((s32)obj);
        *(s32 *)(gau + 8) = r2;
        *(s32 *)(gau + 4) = r2 + t;

        flags = func_0023F498((s32)obj);
        if (flags & 1) {
            fa = (f32)*(s32 *)gau;
            fb = (f32)*(s32 *)(gau + 4);
            qq = fa / fb;
            pr = fb * qq;
            ri = (s32)pr;
            dd = pr - (f32)ri;
            if (dd >= 0.5f) {
                if (dd > 0.5f || (ri & 1)) {
                    ri += 1;
                }
            } else if (dd <= -0.5f) {
                if (dd < -0.5f || (ri & 1)) {
                    ri -= 1;
                }
            }
            *(s32 *)gau = ri;
        }
        flags = func_0023F498((s32)obj);
        if (flags & 2) {
            *(s32 *)gau += 0x2710;
        }
        flags = func_0023F498((s32)obj);
        if (flags & 4) {
            *(s32 *)gau += 0x4E20;
        }
        flags = func_0023F498((s32)obj);
        if (flags & 8) {
            *(s32 *)(gau + 0xC) = *(s32 *)(gau + 0x10);
        }
        flags = func_0023F498((s32)obj);
        if (flags & 0x10) {
            *(u8 *)(gau + 0x28) = 0;
        }

        v1 = *(s32 *)gau;
        a0v = *(s32 *)(gau + 4);
        if (v1 <= 0) {
            *(s32 *)gau = 1;
            v1 = 1;
            a0v = *(s32 *)(gau + 4);
        }
        if (a0v < v1) {
            *(s32 *)gau = a0v;
        }

        gg = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        q = func_0023F9B0((s32)obj);
        *(s32 *)(gg + 0x18) = (s32)((u32)q * 100000u);
    } else if (r < 0x34) {
        /* block C */
        t = *(s32 *)(obj + 0x1184);
        if (t > 0) {
            q = func_00203188((s32)obj);
            *(s32 *)(obj + 0x1180) = q;
        }
        gau = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        func_002113C0((s32)obj, 1, 0x20000, 1);
        *(s32 *)(obj + 0x1188) = 0;

        gg = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        if (*(s32 *)(gg + 0x18) == 0) {
            g2 = (u8 *)BtlMember_GetActiveGauge((s32)obj);
            q = func_0023F9B0((s32)obj);
            *(s32 *)(g2 + 0x18) = (s32)((u32)q * 100000u);
        }

        gg = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        if (*(s32 *)(gg + 8) == 0) {
            g2 = (u8 *)BtlMember_GetActiveGauge((s32)obj);
            r2 = func_0023F960((s32)obj);
            *(s32 *)(g2 + 8) = r2;
        }

        if (func_00203C58((s32)obj, (s64)0x8000 << 20) != 0) {
            *(s32 *)(gau + 0x14) = *(s32 *)(gau + 0x18);
        }
        a1 = *(s32 *)(gau + 0x20);
        if (a1 > 0) {
            BtlMember_AddHealth((s32)obj, a1);
            *(s32 *)(gau + 0x20) = 0;
        }
        a1 = *(s32 *)(gau + 0x24);
        if (a1 > 0) {
            func_00203810((s32)obj, a1);
            *(s32 *)(gau + 0x24) = 0;
        }

        gg = (u8 *)BtlMember_GetActiveGauge((s32)obj);
        if (*(u8 *)(gg + 0x2C) != 0) {
            func_0025DB98(*(s32 *)(obj + 0x1530));
        }
    } else {
        return;
    }

    if (*(u8 *)(gau + 0x28) != 0) {
        pp = *(s32 *)(obj + 0x1530);
        *(s32 *)((u8 *)pp + 0xAF0) |= 0x10000000;
    }
}

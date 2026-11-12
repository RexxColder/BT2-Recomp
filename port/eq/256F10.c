#include "common.h"

extern u8 *D_003879F8;
extern u8 *D_003876A0;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;

void Res_RelocateOffsets(void *arg0, s32 arg1, s32 arg2);
void func_00249510(s32 arg0, s32 arg1);
s32 func_0024B210(s32 arg0);
void func_00298460(s32 arg0, s32 arg1, s32 arg2);
void func_002984E0(s32 arg0);
void func_0026EAE0(s32 arg0, s32 arg1);
u8 *func_0028BAA8(s32 arg0);
s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void *func_002AD630(void);
void *func_002AD4E0(void);
s32 func_002AD540(void);
void func_00256E60(void);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002492E0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
u64 func_0024B010(u8 *arg0, u8 *arg1, u8 *arg2, s32 *arg3, s32 arg4);
void func_0024B248(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00101438(s32 arg0);

/* base + (word offset at off, rounded down to 4), relocated through the slot; returns the relocated pointer */
static u8 *Reloc(u8 **slot, u8 *base, s32 off) {
    u8 *v = base + (*(u32 *)(base + off) >> 2 << 2);
    *slot = v;
    Res_RelocateOffsets(slot, (s32)v, (s32)v);
    return *slot;
}

void func_00256F10(s32 *arg0, s32 arg1) {
    u8 sp[0x30];
    u8 *slot = (u8 *)&sp[0x20];
    u8 *g;
    u8 *cfg;
    u8 *ee;
    u8 *s;
    s32 i;
    s32 r;

    *(s32 *)(sp + 0x20) = 0;
    g = func_0028BAA8(0x11C);
    D_003879F8 = g;
    __builtin_memset(g, 0, 0x11C);
    g = D_003879F8;
    if (*(s32 *)g == 0) {
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 0x10, 0, 1);
        do {
            r = func_00100D58(0, 0, 0);
            *(s32 *)D_003879F8 = r;
        } while (r == 0);
        g = D_003879F8;
    }
    *(u8 **)(D_003879F8 + 4) = func_002B24C8(*(u8 **)g, 0, 0);
    g = D_003879F8;
    *(u8 **)(g + 0x110) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x58) >> 2 << 2);
    g = D_003879F8;
    *(u8 **)(g + 0x108) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x40) >> 2 << 2) + 4;
    g = D_003879F8;
    *(u8 **)(g + 0x10C) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x44) >> 2 << 2) + 4;
    cfg = D_003876A0 + 0x480;
    ee = (u8 *)func_002AD630();

    if ((*(u32 *)cfg & 1) == 0) {
        func_00249510(1, -0x50);
        *arg0 = 0;
        *(s32 *)(D_003879F8 + 0xC0) = 0;
        *(s32 *)(D_003879F8 + 0xC8) = 0;
    } else {
        if (arg1 != 0) {
            func_00249510(10, -0x50);
        } else {
            func_00249510(0, -0x50);
        }
        g = D_003879F8;
        *(u32 *)(g + 0xA4) |= 0x400;
        if ((*(u32 *)(D_003876A0 + 0xD8) & 2) != 0) {
            if ((*(u32 *)(cfg + 4) & 0x10000) == 0) {
                *(u32 *)(D_003879F8 + 0xA4) |= 0x1000;
            }
        }
        if ((*(u32 *)(cfg + 4) & 0x10000) != 0) {
            s32 left = 1;
            u8 *src = ee + 0x18;
            *(u32 *)(D_003879F8 + 0xA4) |= 0x800;
            g = D_003879F8;
            do {
                s32 id = *(s32 *)src;
                if (id >= 0) {
                    s32 skip = 0;
                    if (*(s32 *)(*(u8 **)(g + 0x108) + id * 0x30 + 0x10) == 1) {
                        if (*(s16 *)(D_00387F2C + id * 4 + 0x1F32) != 0) {
                            skip = 1;
                        }
                    }
                    if (!skip) {
                        s32 cnt = *(s32 *)(g + 0xB4);
                        *(s32 *)(g + 0xCC + cnt * 4) = id;
                        *(s32 *)(g + 0xB4) = cnt + 1;
                        id = *(s32 *)src;
                        g = D_003879F8;
                        if ((u32)(id - 0x186) < 0x19) {
                            u8 *gc = D_00387F2C;
                            if (*(s16 *)(gc + id * 4 + 0x1F32) == 0) {
                                *(u32 *)(gc + 8) |= 4;
                                g = D_003879F8;
                            }
                        }
                    }
                }
                left--;
                src += 4;
            } while (left >= 0);
        } else {
            g = D_003879F8;
        }
        if (*(s32 *)(cfg + 0x48) != 0) {
            u8 *g2;
            s32 cnt;
            *(u32 *)(g + 0xA4) |= 0x800;
            g2 = D_003879F8;
            cnt = *(s32 *)(g2 + 0xB4);
            *(s32 *)(g2 + 0xCC + cnt * 4) = *(s32 *)(cfg + 0x48) + 0x163;
            *(s32 *)(g2 + 0xB4) = cnt + 1;
            g = D_003879F8;
        }
        if ((*(u32 *)(g + 0xA4) & 0x1000) != 0) {
            *(s32 *)(g + 0xC0) = 0;
            *(s32 *)(D_003879F8 + 0xC8) = 0;
        } else {
            u32 flags;
            f32 sc;
            u8 *gb;
            *(s32 *)(g + 0xC8) = *(s32 *)(ee + 0x14);
            flags = *(u32 *)(cfg + 4);
            gb = D_003876A4;
            sc = (f32)*(s32 *)(gb + 0x3C);
            g = D_003879F8;
            if ((flags & 1) != 0) {
                sc = sc * *(f32 *)(*(u8 **)(g + 0x110) + 0xC);
            } else if ((flags & 8) != 0) {
                sc = sc * *(f32 *)(*(u8 **)(g + 0x110) + 8);
            } else if ((flags & 4) != 0) {
                g = D_003879F8;
                sc = sc * *(f32 *)(*(u8 **)(g + 0x110) + 4);
            }
            sc = sc * *(f32 *)(*(u8 **)(g + 0x110) + *(s32 *)(gb + 0x38) * 4 + 0x10);
            *(s32 *)(g + 0xC0) = (s32)sc;
        }
    }

    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0xC);
    *(u8 **)(D_003879F8 + 0x40) = s;
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x14);
    g = D_003879F8;
    if ((*(u32 *)(g + 0xA4) & 0x400) != 0) {
        *(s32 *)(g + 0x44) = *(s32 *)(s + 0x10);
    } else {
        *(s32 *)(g + 0x44) = *(s32 *)(s + 0x10) + 0x40;
    }
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x18);
    *(s32 *)(D_003879F8 + 0x48) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x38);
    *(s32 *)(D_003879F8 + 0x4C) = *(s32 *)(s + 0x10);
    *(s32 *)(D_003879F8 + 0x50) = *(s32 *)(s + 0x10) + 0x40;
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x34);
    *(s32 *)(D_003879F8 + 0x7C) = *(s32 *)(s + 0x10);
    *(s32 *)(D_003879F8 + 0x58) = *(s32 *)(s + 0x10) + 0x40;
    *(s32 *)(D_003879F8 + 0x5C) = *(s32 *)(s + 0x10) + 0x80;
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x1C);
    *(s32 *)(D_003879F8 + 0x54) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x30);
    *(s32 *)(D_003879F8 + 0x60) = *(s32 *)(s + 0x10);
    *(s32 *)(D_003879F8 + 0x64) = *(s32 *)(s + 0x10) + 0x40;
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x10);
    *(s32 *)(D_003879F8 + 0x68) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x28);
    *(s32 *)(D_003879F8 + 0x6C) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x24);
    *(s32 *)(D_003879F8 + 0x80) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x8);
    *(s32 *)(D_003879F8 + 0x74) = *(s32 *)(s + 0x10);
    g = D_003879F8;
    s = Reloc(&slot, *(u8 **)(g + 4), 0x20);
    *(s32 *)(D_003879F8 + 0x90) = *(s32 *)(s + 0x10);
    *(s32 *)(D_003879F8 + 0x78) = *(s32 *)(s + 0x10) + 0x40;

    g = D_003879F8;
    func_0026E7F0((s32)(g + 0x18), (s32)(*(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 4) >> 2 << 2)), (s32)(g + 0x44));
    func_0026EAE0((s32)(g + 0x18), 0x3C);
    g = D_003879F8;
    *(u8 **)(g + 0x104) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x54) >> 2 << 2) + 4;
    g = D_003879F8;
    *(s32 *)(g + 0x100) = *(s32 *)(*(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x54) >> 2 << 2));
    g = D_003879F8;
    *(u8 **)(g + 8) = func_002B24C8(*(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x3C) >> 2 << 2), 0, 0);
    for (i = 0; i < 0x86; i++) {
        u8 *tbl = *(u8 **)(D_003879F8 + 8);
        Reloc(&slot, tbl, i * 4 + 4);
        /* Reloc adds base + word at off: tbl + (tbl[i*4+4] >> 2 << 2) */
    }
    g = D_003879F8;
    *(u8 **)(g + 0xC) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x48) >> 2 << 2);
    g = D_003879F8;
    *(u8 **)(g + 0x10) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x4C) >> 2 << 2);
    g = D_003879F8;
    *(u8 **)(g + 0x14) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x50) >> 2 << 2);
    g = D_003879F8;
    *(u8 **)(g + 0x114) = *(u8 **)(g + 4) + (*(u32 *)(*(u8 **)(g + 4) + 0x2C) >> 2 << 2);
    *(void **)(g + 0x118) = func_002AD4E0();
    g = D_003879F8;
    *(s32 *)(g + 0xB8) = func_002AD540();
    func_00256E60();
    g = D_003879F8;
    i = 0;
    if (*(s32 *)(g + 0xB8) > 0) {
        do {
            s32 idx = func_002492E0(*(s32 *)(*(u8 **)(g + 0x118) + i * 16 + 8), *(s32 *)(g + 0x100), *(s32 **)(g + 0x104), 1);
            s32 off = idx * 34;
            s32 bit = 4 << i;
            func_0024B010(*(u8 **)(g + 0x108), *(u8 **)(g + 0x10C), D_00387F2C + off + 0x1408, (s32 *)sp, 0x14);
            *(s32 *)(D_003879F8 + 0xD8 + i * 8) = func_0024B210((s32)sp);
            g = D_003879F8;
            func_0024B248(*(u8 **)(g + 0x108), D_00387F2C + off + 0x1408, *(u8 **)(g + 0x110), *(s32 *)(g + 0xC0));
            g = D_003879F8;
            func_0024B010(*(u8 **)(g + 0x108), *(u8 **)(g + 0x10C), D_00387F2C + off + 0x1408, (s32 *)sp, 0x14);
            *(s32 *)(D_003879F8 + 0xDC + i * 8) = func_0024B210((s32)sp);
            g = D_003879F8;
            i++;
            if (*(s32 *)(g + 0xD8 + (i - 1) * 8) < *(s32 *)(g + 0xDC + (i - 1) * 8)) {
                *(u32 *)(g + 0xA4) |= bit;
                g = D_003879F8;
            }
        } while (i < *(s32 *)(g + 0xB8));
    }
    for (i = 0; i < 3;) {
        s32 n = *(s32 *)(g + 0xB4);
        s32 id = *(s32 *)(g + 0xCC + i * 4);
        i++;
        if (i - 1 < n) {
            func_00298460(id, *(s32 *)(*(u8 **)(g + 0x108) + id * 0x30 + 0x10), 1);
            g = D_003879F8;
        }
    }
    func_002984E0(*(s32 *)(g + 0xC8));
    func_00101438(0x3E21);
}

#include "common.h"

extern u8 *D_003879A0;
extern u8 *D_003876A4;
extern u8 *D_003876A0;
extern u8 *D_003876AC;
extern char D_00374A88[];

extern u8 *func_0028BAA8(s32 size);
extern u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
extern void Res_RelocateOffsets(u8 **cur, u8 *a1, u8 *a2);
extern void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
extern void func_0026EAE0(u8 *arg0, s32 arg1);
extern void func_0026EB78(u8 *dst, const char *s);
extern void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
extern void func_00250BF0(u8 *arg0);
extern void func_0029BB88(u8 *arg0, u8 *arg1);
extern void func_00248068(u8 *arg0);
extern s32 func_0024ACB8(u8 *arg0, s32 arg1);
extern void func_0024CD30(s32 arg0);
extern void func_0024C380(s32 arg0);
extern u8 *func_0024C148(void);
extern void func_0024B010(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 a4);
extern s32 func_0024B210(u8 *arg0);
extern void func_0024CC48(void);

/* Loads the "edit/shop/..." screen resources (archive index `idx`) into a freshly allocated screen state
 * M = *D_003879A0 (13156 bytes). M+4 = resource pack, whose header words give 4-byte aligned offsets. */
#define M D_003879A0
#define S D_003876A4
#define MW(off) (*(s32 *)(M + (off)))
#define MP(off) (*(u8 **)(M + (off)))
#define HDR (*(u8 **)(M + 4))
/* aligned pointer to header section `off` */
#define SECT(off) (HDR + (*(u32 *)(HDR + (off)) >> 2 << 2))
/* relocate section `off`; its first resource pointer ends in sp0 */
#define LOAD(off) do { u8 *sect_ = SECT(off); sp0 = sect_; Res_RelocateOffsets(&sp0, sect_, sect_); } while (0)
#define R0(o) (*(s32 *)(sp0 + (o)))

s32 func_0024CF78(s32 idx)
{
    u8 *sp0 = 0;
    u8 *m;
    s32 i;
    s32 v;

    D_003879A0 = func_0028BAA8(0x3364);
    __builtin_memset(M, 0, 0x3364);
    {
        u8 *base = D_003876AC;
        *(u8 **)M = base + (*(u32 *)(base + 4 * idx) >> 2 << 2);
    }
    MP(4) = func_002B24C8(*(u8 **)M, 0, 0);

    LOAD(0x48);
    MP(0xC4) = sp0;
    LOAD(0x40);
    MW(0xD0) = R0(0x10);
    MW(0xD4) = R0(0x10) + 0x40;
    LOAD(0x30);
    MW(0xE8) = R0(0x10);
    LOAD(0x3C);
    MW(0xF0) = R0(0x10) + 0x40;
    LOAD(0x28);
    MW(0x108) = R0(0x10);
    MW(0x110) = R0(0x10) + 0x40;
    LOAD(0x2C);
    MW(0x104) = R0(0x10);
    MW(0x10C) = R0(0x10);
    LOAD(0x08);
    MW(0x100) = R0(0x10);
    MW(0xFC) = R0(0x10) + 0x40;
    LOAD(0x0C);
    MW(0x114) = R0(0x10);
    LOAD(0x24);
    MW(0x118) = R0(0x10);
    LOAD(0x1C);
    MW(0x11C) = R0(0x10);
    MW(0x128) = R0(0x10) + 0x40;
    LOAD(0x18);
    MW(0x124) = R0(0x10);
    LOAD(0x34);
    MW(0xEC) = R0(0x10);
    MW(0x1B0) = R0(0x10);
    LOAD(0x20);
    MW(0x120) = R0(0x10);
    MW(0x12C) = R0(0x10) + 0x40;
    LOAD(0x50);
    MW(0xDC) = R0(0x10);
    LOAD(0x4C);
    MW(0xC8) = R0(0x10);

    m = M + 0x4C;
    func_0026E7F0(m, HDR + (*(u32 *)(HDR + 4) >> 2 << 2), M + 0xC8);
    func_0026EAE0(m, 0x3C);
    if ((*(s32 *)(S + 0x48C) & 0xC) || *(s32 *)(S + 0x1C) == 0x37 || *(s32 *)(S + 0x1C) == 0x29) {
        func_0026EB78(M + 0x4C, D_00374A88);
    }

    LOAD(0x60);
    MW(0x130) = R0(0x10);
    MW(0x138) = R0(0x10) + 0x40;
    MW(0x134) = R0(0x10) + 0x80;
    MW(0x13C) = R0(0x10) + 0xC0;
    m = M + 0x24;
    func_0026E7F0(m, HDR + (*(u32 *)(HDR + 0x64) >> 2 << 2), M + 0x130);
    func_0026EAE0(m, 0x3C);

    if (*(s32 *)(S + 0x1C) != 0x37 && *(s32 *)(S + 0x1C) != 0x29) {
        LOAD(0xB4);
        MW(0x148) = R0(0x10);
        MW(0x140) = R0(0x10) + 0x40;
        LOAD(0xAC);
        MW(0x144) = R0(0x10);
        LOAD(0xA8);
        MW(0x16C) = R0(0x10);
        MW(0x170) = R0(0x10) + 0x40;
        MW(0x168) = R0(0x10) + 0x80;
        m = M + 0x74;
        func_0026E7F0(m, HDR + (*(u32 *)(HDR + 0xB0) >> 2 << 2), M + 0x140);
        if (!(*(s32 *)(S + 0x48C) & 0xC)) {
            func_0026EAE0(m, 0x3C);
        }
    }

    LOAD(0x94);
    MW(0x190) = R0(0x10);
    LOAD(0x80);
    if (*(s32 *)(S + 0x1C) == 0x29) {
        MW(0x1B8) = 0;
        v = R0(0x10);
    } else {
        MW(0x1B8) = R0(0x10);
        v = R0(0x10) + 0x40;
    }
    MW(0x1B4) = v;
    LOAD(0x84);
    MW(0x1A0) = R0(0x10);
    LOAD(0x8C);
    MW(0x19C) = R0(0x10);
    LOAD(0x90);
    MW(0x1A8) = R0(0x10);
    LOAD(0x88);
    MW(0x1BC) = R0(0x10);
    m = M + 0x9C;
    func_0026E7F0(m, HDR + (*(u32 *)(HDR + 0x7C) >> 2 << 2), M + 0x190);
    if (*(s32 *)(S + 0x48C) & 8) {
        func_0026EAE0(m, 0x3C);
    }

    if (*(s32 *)(S + 0x1C) != 0x37 && *(s32 *)(S + 0x1C) != 0x29) {
        MP(0x10) = func_002B24C8(HDR + (*(u32 *)(HDR + 0xA4) >> 2 << 2), 0, 0);
        for (i = 0; i < 0x86; i++) {
            u8 *t = MP(0x10);
            u8 *p = t + (*(u32 *)(t + 4 * i + 4) >> 2 << 2);
            sp0 = p;
            Res_RelocateOffsets(&sp0, p, p);
        }
    }

    MP(0x1E8) = SECT(0x54) + 4;
    MW(0x1E4) = *(s32 *)SECT(0x54);
    func_00248708(M + 0x1F0, M + 0x1F4, M + 0x1E4, M + 0x1E8);
    MW(0x1E4) = MW(0x1F0);
    MP(0x1E8) = M + 0x1F4;
    MP(0x1EC) = M + 0x1A04;
    MW(0x3214) = MW(0x1E4) / 7;
    MP(0x14) = SECT(0x58);
    MP(0x18) = SECT(0x5C);
    MP(0x1C) = SECT(0x98);
    MP(0x20) = SECT(0x78);
    MP(0x3358) = SECT(0x44);
    MP(0x335C) = SECT(0x14);
    MP(0x3360) = SECT(0x38);
    MP(0x334C) = SECT(0x6C) + 4;
    MP(0x3350) = SECT(0x70) + 4;
    MW(0x3354) = *(s32 *)(D_003876A0 + 0x74);
    func_00250BF0(SECT(0x74));
    if (*(s32 *)(S + 0x1C) != 0x29) {
        func_0029BB88(SECT(0x68), MP(0x20));
    }
    if (*(s32 *)(S + 0x1C) != 0x37) {
        func_00248068(SECT(0x9C));
    }
    MP(8) = func_0028BAA8(0x17800);
    MP(0xC) = func_0028BAA8(0x20560);
    MW(0x3224) = 1;

    if (*(s32 *)(S + 0x1C) == 0x37) {
        MW(0x1C8) = *(s32 *)(S + 0x494) % 7;
        MW(0x1CC) = *(s32 *)(S + 0x494) / 7;
        if (*(s32 *)(S + 0x48C) & 0x20) {
            MW(0x1E0) = 2;
        } else {
            MW(0x1E0) = 1;
        }
    } else if (*(s32 *)(S + 0x1C) == 0x29) {
        MW(0x1C8) = *(s32 *)(S + 0x494) % 7;
        MW(0x1CC) = *(s32 *)(S + 0x494) / 7;
        MW(0x1E0) = 3;
    } else {
        if (func_0024ACB8(MP(0x1E8), *(s32 *)(S + 0x390)) == 0) {
            *(s32 *)(S + 0x390) = 0;
        }
        MW(0x1C8) = *(s32 *)(S + 0x390) % 7;
        MW(0x1CC) = *(s32 *)(S + 0x390) / 7;
        *(s32 *)(S + 0x3B8) = 0;
        *(s32 *)(S + 0x408) = 0;
        *(s32 *)(S + 0x430) = 0;
        func_0024CD30(0);
        MW(0x1E0) = 3;
    }

    func_0024C380(0);
    {
        u8 *c = func_0024C148();
        func_0024B010(MP(0x334C), MP(0x3350), c + 0x1408 + 34 * (MW(0x1C8) + 7 * MW(0x1CC)), M + 0x326C, 0x14);
    }
    MW(0x323C) = func_0024B210(M + 0x326C);
    {
        s32 cell = 7 * MW(0x1CC) + MW(0x1C8);
        u8 *tab = (*(s32 *)(S + 0x48C) & 2) ? MP(0x1EC) : MP(0x1E8);
        s32 ent = *(s32 *)(tab + 44 * cell);
        MW(0x3234) = *(s32 *)(MP(0x3354) + 16 * ent);
    }
    {
        s32 cell = 7 * MW(0x1CC) + MW(0x1C8);
        u8 *tab = (*(s32 *)(S + 0x48C) & 2) ? MP(0x1EC) : MP(0x1E8);
        s32 ent = *(s32 *)(tab + 44 * cell);
        MW(0x3238) = *(s32 *)(MP(0x3354) + 16 * ent + 4);
    }

    if (*(s32 *)(S + 0x48C) & 0xC) {
        MW(0x1DC) = *(s32 *)(S + 0x498);
        if (*(s32 *)(S + 0x48C) & 4) {
            u8 *c = func_0024C148();
            u8 *src = c + 0x1408 + 34 * (7 * MW(0x1CC) + MW(0x1C8));
            __builtin_memcpy(M + 0x3314, src, 28);
            *(u16 *)(M + 4 * MW(0x1DC) + 0x3314) = *(u16 *)(S + 0x49C);
            *(u16 *)(M + 4 * MW(0x1DC) + 0x3316) = 0;
            func_0024C380(1);
            func_0024B010(MP(0x334C), MP(0x3350), M + 0x3314, M + 0x328C, 0x14);
            func_0024CC48();
            MW(0x3228) = 6;
        } else {
            MW(0x3228) = 3;
        }
    } else if (*(s32 *)(S + 0x1C) == 0x37) {
        MW(0x3228) = 1;
    } else if (*(s32 *)(S + 0x1C) == 0x29) {
        MW(0x3228) = 7;
    }
    *(s32 *)(S + 0x48C) &= ~4;
    *(s32 *)(S + 0x48C) &= ~8;
    return *(s32 *)(S + 0x48C);
}

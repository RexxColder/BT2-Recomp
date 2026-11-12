#include "common.h"

s32 func_0028BAA8(s32 arg0);
s32 func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(void *arg0, s32 arg1, s32 arg2);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
void func_0026EAE0(s32 arg0, s32 arg1);
void func_00250BF0(s32 arg0);
s32 func_0024C148(void);
extern u8 *D_003879C0;
extern u8 *D_003876A4;
extern u8 *D_003876AC;

#define RES() (*(u8 **)(D_003879C0 + 4))
#define RES_AT(off) (RES() + (*(u32 *)(RES() + (off)) & ~3))
#define RELOC(off) (sp0 = RES_AT(off), Res_RelocateOffsets(&sp0, (s32)sp0, (s32)sp0))
#define FIELD(off) (*(s32 *)(sp0 + (off)))

s32 func_00251100(s32 idx) {
    u8 *sp0;
    u8 *st;
    u8 *ent;
    s32 i, cnt, hits;

    sp0 = NULL;
    st = (u8 *)func_0028BAA8(0x2E68);
    D_003879C0 = st;
    __builtin_memset(st, 0, 0x2E68);
    *(u8 **)(D_003879C0 + 0) = D_003876AC + (*(u32 *)(D_003876AC + idx * 4) & ~3);
    *(s32 *)(D_003879C0 + 4) = func_002B24C8(*(s32 *)(D_003879C0 + 0), 0, 0);
    sp0 = RES_AT(0x38);
    Res_RelocateOffsets(&sp0, (s32)sp0, (s32)sp0);
    *(u8 **)(D_003879C0 + 0x5C) = sp0;
    RELOC(0x14);
    *(s32 *)(D_003879C0 + 0x68) = FIELD(0x10);
    *(s32 *)(D_003879C0 + 0x6C) = FIELD(0x10) + 0x40;
    RELOC(0x18);
    *(s32 *)(D_003879C0 + 0x70) = FIELD(0x10);
    RELOC(0x1C);
    *(s32 *)(D_003879C0 + 0x60) = FIELD(0x10);
    RELOC(0x20);
    *(s32 *)(D_003879C0 + 0x74) = FIELD(0x10);
    RELOC(0x28);
    *(s32 *)(D_003879C0 + 0x64) = FIELD(0x10);
    func_0026E7F0((s32)(D_003879C0 + 0xC), (s32)RES_AT(0x10), (s32)(D_003879C0 + 0x60));
    func_0026EAE0((s32)(D_003879C0 + 0xC), 0x3C);
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x38) {
        RELOC(0x8);
        *(s32 *)(D_003879C0 + 0xA8) = FIELD(0x10);
    }
    RELOC(0x4);
    *(s32 *)(D_003879C0 + 0x8C) = FIELD(0x10);
    RELOC(0xC);
    *(s32 *)(D_003879C0 + 0x7C) = FIELD(0x10);
    *(s32 *)(D_003879C0 + 0x80) = FIELD(0x10) + 0x40;
    RELOC(0x40);
    *(s32 *)(D_003879C0 + 0x98) = FIELD(0x10);
    RELOC(0x5C);
    *(s32 *)(D_003879C0 + 0x78) = FIELD(0x10);
    RELOC(0x48);
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x38) {
        *(s32 *)(D_003879C0 + 0xA0) = FIELD(0x10);
        *(s32 *)(D_003879C0 + 0x9C) = 0;
    } else {
        *(s32 *)(D_003879C0 + 0xA0) = 0;
        *(s32 *)(D_003879C0 + 0x9C) = FIELD(0x10);
    }
    cnt = 0;
    hits = 0;
    RELOC(0x4C);
    *(s32 *)(D_003879C0 + 0x88) = FIELD(0x10);
    RELOC(0x54);
    *(s32 *)(D_003879C0 + 0x84) = FIELD(0x10);
    RELOC(0x58);
    *(s32 *)(D_003879C0 + 0x90) = FIELD(0x10);
    RELOC(0x50);
    *(s32 *)(D_003879C0 + 0xA4) = FIELD(0x10);
    func_0026E7F0((s32)(D_003879C0 + 0x34), (s32)RES_AT(0x44), (s32)(D_003879C0 + 0x78));
    func_0026EAE0((s32)(D_003879C0 + 0x34), 0x3C);
    *(u8 **)(D_003879C0 + 0x2E64) = RES_AT(0x3C);
    *(u8 **)(D_003879C0 + 0x2E60) = RES_AT(0x24);
    *(u8 **)(D_003879C0 + 0x8) = RES_AT(0x2C);
    *(u8 **)(D_003879C0 + 0x2E5C) = RES_AT(0x30) + 4;
    func_00250BF0((s32)RES_AT(0x34));
    st = D_003879C0;
    for (i = 0; i < 0x243; i++) {
        ent = *(u8 **)(st + 0x2E5C) + i * 0x30;
        if ((*(u32 *)ent & 0x41) == 0) {
            s32 grp = *(s32 *)(ent + 8);
            s32 *slot;
            u8 *info;

            cnt++;
            *(s32 *)(st + (grp * 0x243 + *(s32 *)(st + grp * 4 + 0xE4)) * 4 + 0xF8) = i;
            slot = (s32 *)(D_003879C0 + *(s32 *)(*(u8 **)(D_003879C0 + 0x2E5C) + i * 0x30 + 8) * 4 + 0xE4);
            *slot = *slot + 1;
            info = (u8 *)func_0024C148();
            st = D_003879C0;
            hits += *(u16 *)(info + 0x1F30 + i * 4) & 1;
        }
    }
    *(s32 *)(st + 0xDC) = (s32)((f32)hits / (f32)cnt * 100.0f);
    for (i = 0; i < 5; ) {
        s32 off = i * 4;
        i++;
        *(s32 *)(D_003879C0 + off + 0xB0) = 0;
        *(s32 *)(D_003879C0 + off + 0x2E34) = *(s32 *)(D_003879C0 + off + 0xB0);
        *(s32 *)(D_003879C0 + off + 0x2E48) =
            *(s32 *)(D_003879C0 + off + 0xB0) + ((*(s32 *)(D_003876A4 + 0x1C) != 0x38) ? 6 : 5);
    }
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x38) {
        *(s32 *)(D_003879C0 + 0xC8) = 2;
        if ((*(u32 *)(D_003876A4 + 0x48C) & 0x10) != 0) {
            *(s32 *)(D_003879C0 + 0xC4) = *(s32 *)(D_003876A4 + 0x4A0);
            *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0xB0) = *(s32 *)(D_003876A4 + 0x4A4);
            *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0x2E34) = *(s32 *)(D_003876A4 + 0x4A8);
            *(s32 *)(D_003879C0 + *(s32 *)(D_003879C0 + 0xC4) * 4 + 0x2E48) = *(s32 *)(D_003876A4 + 0x4AC);
            *(u32 *)(D_003876A4 + 0x48C) = *(u32 *)(D_003876A4 + 0x48C) ^ 0x10;
            return *(s32 *)(D_003876A4 + 0x48C);
        }
        return (s32)D_003879C0;
    }
    *(s32 *)(D_003879C0 + 0xC8) = 5;
    return 5;
}

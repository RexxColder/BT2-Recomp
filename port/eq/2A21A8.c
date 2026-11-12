#include "common.h"

extern u8 gFontStyle[] __attribute__((section(".data")));

u8 *func_002A2170(void);
s32 func_002A2AC8(s32 arg0);
f32 func_002A2AD0(f32 farg0);

/* Font_NewCmd (BT3 name): the command record at +0x00..+0x4C is filled from the arguments and the current
 * gFontStyle (raw offsets, as in the BT2 asm). The asm's coordinate passes call func_002A2AC8 on the fields
 * unless the matching flag bit is set; the scale at +0x14 goes through func_002A2AD0 unless flags & 2. */
u8 *Font_NewCmd(s32 arg, s32 digits, s32 x, s32 y, s32 homeX, s32 kind) {
    u8 *cmd;
    u8 *gs;
    s32 flags;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;

    gs = gFontStyle;
    cmd = func_002A2170();
    *(s32 *)(cmd + 0x4) = arg;
    *(u16 *)(cmd + 0x8) = (u16)x;
    *(u16 *)(cmd + 0xE) = (u16)digits;
    *(u16 *)(cmd + 0xC) = (u16)homeX;
    *(s32 *)(cmd + 0x0) = kind;
    *(u16 *)(cmd + 0xA) = (u16)y;
    *(f32 *)(cmd + 0x10) = *(f32 *)(gs + 0x0) * *(f32 *)(gs + 0x8);
    *(f32 *)(cmd + 0x14) = *(f32 *)(gs + 0x4) * *(f32 *)(gs + 0x8);
    *(u16 *)(cmd + 0x18) = *(u16 *)(gs + 0x10);
    *(u16 *)(cmd + 0x1A) = *(u16 *)(gs + 0x14);
    *(s32 *)(cmd + 0x1C) = *(s32 *)(gs + 0xC);
    *(s32 *)(cmd + 0x38) = *(s32 *)(gs + 0x18);
    *(s32 *)(cmd + 0x3C) = *(s32 *)(gs + 0x1C);
    *(u16 *)(cmd + 0x2C) = *(u16 *)(gs + 0x2C);
    *(u16 *)(cmd + 0x2E) = *(u16 *)(gs + 0x2E);
    *(u16 *)(cmd + 0x30) = *(u16 *)(gs + 0x30);
    *(u16 *)(cmd + 0x32) = *(u16 *)(gs + 0x32);
    *(s32 *)(cmd + 0x34) = *(s32 *)(gs + 0x34);
    flags = *(s32 *)(gs + 0x34);
    *(s32 *)(cmd + 0x20) = *(s32 *)(gs + 0x20);
    *(s32 *)(cmd + 0x24) = *(s32 *)(gs + 0x24);
    *(u16 *)(cmd + 0x28) = *(u16 *)(gs + 0x28);
    *(u16 *)(cmd + 0x2A) = *(u16 *)(gs + 0x2A);
    *(s32 *)(cmd + 0x40) = *(s32 *)(gs + 0x38);
    *(s32 *)(cmd + 0x44) = *(s32 *)(gs + 0x3C);
    *(s32 *)(cmd + 0x48) = -1;

    if ((flags & 1) == 0) {
        a = func_002A2AC8((s16)y);
        *(u16 *)(cmd + 0xA) = (u16)a;
        b = func_002A2AC8(*(u16 *)(cmd + 0x2E));
        *(u16 *)(cmd + 0x2E) = (u16)b;
        c = func_002A2AC8(*(u16 *)(cmd + 0x32));
        *(u16 *)(cmd + 0x32) = (u16)c;
    }
    if ((flags & 4) == 0) {
        d = func_002A2AC8(*(u16 *)(cmd + 0x1A));
        e = func_002A2AC8(*(u16 *)(cmd + 0x2A));
        *(u16 *)(cmd + 0x1A) = (u16)d;
        *(u16 *)(cmd + 0x2A) = (u16)e;
    }
    if ((flags & 2) == 0) {
        *(f32 *)(cmd + 0x14) = func_002A2AD0(*(f32 *)(cmd + 0x14));
    }
    return cmd;
}

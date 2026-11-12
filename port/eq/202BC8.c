#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_003858F4;

u8 *func_00211288(s32 a0);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void *memset(void *s, s32 c, u32 n);

void func_00202BC8(void) {
    u8 flags[0x40];
    u8 *p0;
    u8 *p1;
    s32 v;

    p0 = func_00211288(0);
    p1 = func_00211288(1);
    memset(flags, 0, 2);

    /* jtbl_0036F7C0: indices 0,1,2,9,10,14 set flags[0] (C38), 3..8,11..13 do not (C40) */
    v = W32(p0, 0xB48) - 0x12;
    if ((u32)v < 0xF) {
        switch (v) {
        case 0:
        case 1:
        case 2:
        case 9:
        case 10:
        case 14:
            flags[0] = 1;
            break;
        default:
            break;
        }
    }

    /* jtbl_0036F800: indices 0,1,2,9,10,14 set flags[1] (C70), 3..8,11..13 do not (C78) */
    v = W32(p1, 0xB48) - 0x12;
    if ((u32)v < 0xF) {
        switch (v) {
        case 0:
        case 1:
        case 2:
        case 9:
        case 10:
        case 14:
            flags[1] = 1;
            break;
        default:
            break;
        }
    }

    if (flags[0] == 0 || flags[1] == 0) {
        return;
    }

    func_002113C0(p0, 4, 0x800000, 0);
    func_002113C0(p1, 4, 0x800000, 0);
    func_002113C0(p0, 4, 0x4000000, 0);
    func_002113C0(p1, 4, 0x4000000, 0);
    func_002113C0(p0, 6, 1, 0);
    func_002113C0(p1, 6, 1, 0);
    memset(p0 + 0xB48, 0, 0x78);
    memset(p1 + 0xB48, 0, 0x78);
    memset(p0 + 0xA50, 0, 0x60);
    memset(p1 + 0xA50, 0, 0x60);
    memset(p0 + 0xAB0, 0, 0x14);
    memset(p1 + 0xAB0, 0, 0x14);
    W32(p0, 0xB48) = 0xF;
    W32(p1, 0xB48) = 0xF;
    F32(p0, 0xB60) = D_003858F4;
    F32(p1, 0xB60) = D_003858F4;
}

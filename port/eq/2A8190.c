#include "common.h"

s32 Gsc_GetInt(void);
s32 func_002A0010(s32 arg0);
void *func_002A3CC0(void);
void *func_002A4CF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                    s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15,
                    s32 arg16);

s32 func_002A8190(s32 arg0) {
    s32 aval;
    s32 bval;
    s32 cval;
    s32 dval;
    s32 wval;
    s32 hval;
    s32 hx;
    s32 hy;
    s32 t;
    s64 x;
    void *e;
    u8 *p;

    if (arg0 != 0) {
        return 1;
    }
    aval = Gsc_GetInt();
    if (aval >= 0) {
        bval = Gsc_GetInt();
        cval = Gsc_GetInt();
        dval = Gsc_GetInt();
        e = func_002A3CC0();
        x = *(s64 *)((u8 *)((dval * 0x40) + *(s32 *)((u8 *)e + 0x10)) + 0x30);
        hval = (s32)((u32)1 << (u32)((x >> 30) & 0xF));
        wval = (s32)((u32)1 << (u32)((x >> 26) & 0xF));
        p = (u8 *)func_002A4CF0(aval, 0xC, (s32)e, dval, bval, cval, bval + wval, cval + hval,
                                0x80, 0x80, 0x80, 0x80, 0, 0, wval, hval, 0);
        *(u8 *)(p + 0x18) = 0;
        if (func_002A0010(0x79) != 0) {
            *(u16 *)(p + 4) = (u16)bval;
            *(u16 *)(p + 0) = (u16)(bval - wval);
        }
        if (func_002A0010(0x78) != 0) {
            hx = (wval + ((u32)wval >> 31)) >> 1;
            hy = (hval + ((u32)hval >> 31)) >> 1;
            *(u16 *)(p + 0) = (u16)(bval - hx);
            *(u16 *)(p + 2) = (u16)(cval - hy);
            *(u16 *)(p + 4) = (u16)(bval + hx);
            *(u16 *)(p + 6) = (u16)(cval + hy);
        }
        if (func_002A0010(0x63) != 0) {
            *(u8 *)(p + 8) = (u8)Gsc_GetInt();
            *(u8 *)(p + 9) = (u8)Gsc_GetInt();
            *(u8 *)(p + 0xA) = (u8)Gsc_GetInt();
            *(u8 *)(p + 0xB) = (u8)Gsc_GetInt();
        }
        if (func_002A0010(0x77) != 0) {
            t = Gsc_GetInt();
            *(u16 *)(p + 4) = (u16)(*(u16 *)(p + 0) + t);
            t = Gsc_GetInt();
            *(u16 *)(p + 6) = (u16)(*(u16 *)(p + 2) + t);
        }
        if (func_002A0010(0x75) != 0) {
            *(u16 *)(p + 0xC) = (u16)Gsc_GetInt();
            *(u16 *)(p + 0xE) = (u16)Gsc_GetInt();
            t = Gsc_GetInt();
            *(u16 *)(p + 0x10) = (u16)(*(u16 *)(p + 0xC) + t);
            t = Gsc_GetInt();
            *(u16 *)(p + 0x12) = (u16)(*(u16 *)(p + 0xE) + t);
        }
        if (func_002A0010(0x70) != 0) {
            *(u8 *)(p + 0x19) = (u8)Gsc_GetInt();
        }
    }
    return 1;
}

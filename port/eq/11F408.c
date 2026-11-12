#include "common.h"

void func_0011FD48(u8 *arg0);
void func_00124098(u8 *arg0);
s32 func_00126058(u8 *arg0, s32 arg1, s32 arg2);
void func_0011FAE0(u8 *arg0, s32 arg1, s32 arg2);
void func_00121270(u8 *arg0);
void func_00121388(u8 *arg0);
void func_00121218(u8 *arg0, s32 arg1);

s32 func_0011F408(u8 *arg0, s32 arg1) {
    u8 *s0 = arg0;
    s32 idx = arg1 - 0xF6;

    if ((u32)idx >= 8) {
        return 0;
    }

    switch (idx) {
    case 0: /* 246 */
        if (func_00126058(s0, 0xF, 1) == 0) {
            func_0011FD48(s0);
            return 0;
        }
        func_00121218(s0, 0x2000);
        return 1;

    case 1: /* 247 */
        if (*(s32 *)(s0 + 0x11B0) != 0x47) {
            func_0011FD48(s0);
            return 0;
        }
        func_00121388(s0);
        return 1;

    case 2: /* 248 */
        if (*(s32 *)(s0 + 0x11B0) != 0x47) {
            func_0011FD48(s0);
            return 0;
        }
        func_00121388(s0);
        func_00121218(s0, 0x100);
        return 1;

    case 3: /* 249 */
        if (*(s32 *)(s0 + 0x11B0) == 0x48) {
            func_00121270(s0);
            return 1;
        }
        func_0011FD48(s0);
        return 0;

    case 4: /* 250 */
        if (*(u8 *)(s0 + 0x10A0) != 0 && (*(u32 *)(s0 + 0x110C) & 0x20) == 0) {
            func_0011FD48(s0);
            func_00124098(s0);
            if (func_00126058(s0, 0, 4) == 0) {
                func_0011FAE0(s0, 125, 0);
            }
            func_0011FAE0(s0, 221, 0);
            return 1;
        }
        if (*(s32 *)(s0 + 0xBE4) <= 0) {
            return 1;
        }
        if (!(*(f32 *)(s0 + 0x1030) < 50.0f)) {
            return 1;
        }
        func_0011FD48(s0);
        if (*(u8 *)(s0 + 0x10A0) != 0) {
            func_0011FAE0(s0, 250, 0);
        } else {
            func_0011FAE0(s0, 252, 0);
        }
        return 1;

    case 5: /* 251 */
        if (*(u8 *)(s0 + 0x10A0) != 0 && (*(u32 *)(s0 + 0x110C) & 0x20) == 0) {
            func_0011FD48(s0);
            func_00124098(s0);
            if (func_00126058(s0, 0, 4) == 0) {
                func_0011FAE0(s0, 125, 0);
            }
            func_0011FAE0(s0, 221, 0);
            return 1;
        }
        if (*(s32 *)(s0 + 0xBE4) <= 0) {
            return 1;
        }
        if (!(*(f32 *)(s0 + 0x1030) < 50.0f)) {
            return 1;
        }
        func_0011FD48(s0);
        if (*(u8 *)(s0 + 0x10A0) != 0) {
            func_0011FAE0(s0, 251, 0);
        } else {
            func_0011FAE0(s0, 253, 0);
        }
        return 1;

    case 6: /* 252 */
        if (*(u8 *)(s0 + 0x10A0) != 0) {
            func_0011FD48(s0);
            func_00124098(s0);
            if ((*(u32 *)(s0 + 0x110C) & 0x20) != 0) {
                func_0011FAE0(s0, 250, 0);
                return 1;
            }
            if (func_00126058(s0, 0, 4) == 0) {
                func_0011FAE0(s0, 125, 0);
            }
            func_0011FAE0(s0, 221, 0);
            return 1;
        }
        if (*(s32 *)(s0 + 0xBE4) <= 0) {
            return 1;
        }
        if (!(*(f32 *)(s0 + 0x1030) < 50.0f)) {
            return 1;
        }
        func_0011FD48(s0);
        func_0011FAE0(s0, 252, 0);
        return 1;

    case 7: /* 253 */
        if (*(u8 *)(s0 + 0x10A0) != 0) {
            func_0011FD48(s0);
            func_00124098(s0);
            if ((*(u32 *)(s0 + 0x110C) & 0x20) != 0) {
                func_0011FAE0(s0, 251, 0);
                return 1;
            }
            if (func_00126058(s0, 0, 4) == 0) {
                func_0011FAE0(s0, 125, 0);
            }
            func_0011FAE0(s0, 221, 0);
            return 1;
        }
        if (*(s32 *)(s0 + 0xBE4) <= 0) {
            return 1;
        }
        if (!(*(f32 *)(s0 + 0x1030) < 50.0f)) {
            return 1;
        }
        func_0011FD48(s0);
        func_0011FAE0(s0, 253, 0);
        return 1;
    }
    return 0;
}

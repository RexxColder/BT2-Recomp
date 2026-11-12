#include "common.h"

void func_00101438(s32 arg0);
s32 func_0020C870(void);
void func_00247CC0(void);
void func_00277E28(void);
void func_00277E50(void);
s32 func_00284E08(s32 arg0);
void func_00284E68(f32 farg0, s32 arg0, s32 arg1);
void func_00298158(s32 arg0);
s32 func_0029F6F8(s32 arg0);
void func_002A4ED8(void);
s32 func_002ACF10(s32 arg0);
extern u8 D_003B2654[] __attribute__((section(".data")));

s32 func_002A9E30(void) {
    u8 *g;
    s32 state;
    s32 v0;

    g = D_003B2654;
    state = *(s32 *)(g + 0x50);
    if (state == 1) {
        if (func_00284E08(0) != 0) {
            *(s32 *)(g + 0x50) = 2;
        }
        return 0;
    }
    if (state >= 2) {
        if (state == 2) {
            return 1;
        }
        return 0;
    }
    if (state != 0) {
        return 0;
    }
    if (func_002ACF10(state) == 0) {
        if (func_0020C870() != 0) {
            *(s32 *)(g + 0x5C + 8) = *(s32 *)(g + 0x1C);
            *(s32 *)(g + 0x5C + 4) = 4;
            g[0x3B8 + 4] = 1;
            func_00284E68(1.0f, 0, 0);
            *(s32 *)(g + 0x50) = 1;
            return 0;
        }
        if (*(s32 *)(g + 0x10) == 0) {
            return 0;
        }
        v0 = *(s32 *)(g + 0x5C + 4);
        if (v0 == 5) {
            if (func_0029F6F8(*(s32 *)(g + 0x10)) == 0) {
                func_00284E68(1.0f, 0, 0);
                *(s32 *)(g + 0x50) = 1;
            }
            return 0;
        }
        if (v0 == 7) {
            if (func_0029F6F8(*(s32 *)(g + 0x10)) == 0) {
                *(s32 *)(g + 0x10) = 0;
                func_00101438(0x3E2C);
                func_00277E28();
                func_00298158(1);
                func_00247CC0();
                func_00277E50();
                func_00298158(0);
                func_00284E68(1.0f, 0, 1);
                func_002A4ED8();
            }
            return 0;
        }
        if (func_0029F6F8(*(s32 *)(g + 0x10)) == 0) {
            *(s32 *)(g + 0x10) = 0;
        }
        return 0;
    }
    func_00284E68(1.0f, 0, 0);
    *(s32 *)(g + 0x50) = 1;
    return 0;
}

#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387A40;
extern s32 gPauseMenuWhich;

s32 PauseMenu_GetMenu(s32 arg0);
s32 func_00107860(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00107850(s32 arg0);
s32 func_001081A0(s32 arg0);
u8 *func_00108060();
void func_00101798(void);
void func_00101E40(s32 arg0, s32 arg1);
void func_00105B70(s32 arg0, s32 arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001066E8: pause-menu input handler. arg1 == 0 is the "menu toggle" request,
 * which only runs when bit 0x100 of the 64-bit flags at D_003876A0+0x4D8 is set.
 * Returns 0 when the toggle was consumed, 1 otherwise (0 only from the toggle paths). */
s32 func_001066E8(s32 arg0, s32 arg1)
{
    void (*fn)(s32, s32);
    s32 menu;
    u8 *item;
    s32 kind;

    if (arg1 == 0 && (*(u64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
        return 0;
    }

    gPauseMenuWhich = arg1;
    menu = PauseMenu_GetMenu(arg1);

    if ((u32)(*(s32 *)(D_003876A0 + 0xB8) - 7) < 2) {
        fn = func_00101E40;
    } else {
        func_001081A0(*(s32 *)(*(u8 **)D_00387A40 + arg0 * 99712 + 0x5C));
        fn = func_00105B70;
    }

    if (func_00107860(arg1, 0, menu, arg0)) {
        *(u64 *)(D_003876A0 + 0x4D8) ^= 0x100;
        func_00101798();
        return 0;
    }

    func_00107850(menu);
    item = func_00108060(0, menu);
    if (item == NULL) {
        return 1;
    }

    func_00297FE0(0, 1, 64, 64, 1);
    kind = *(s32 *)(item + 4);
    switch (kind) {
    case 0xD:
    case 0x17:
        fn(8, 0x8000);
        return 1;
    case 0xE:
        return 1;
    case 0xF:
        fn(8, 32);
        return 1;
    case 0x10:
        fn(8, 256);
        return 1;
    case 0x11:
        fn(8, 16);
        return 1;
    case 0x12:
        fn(8, 512);
        return 1;
    case 0x13:
        fn(8, 2048);
        return 1;
    case 0x14:
        fn(8, 1024);
        return 1;
    case 0x15:
        fn(8, 4096);
        return 1;
    case 0x16:
        fn(8, 0x4000);
        return 1;
    case 0x18:
        if (arg0 == 0) {
            fn(8, 64);
        } else {
            fn(8, 128);
        }
        return 1;
    default:
        return 1;
    }
}

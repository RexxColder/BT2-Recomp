#include "common.h"

extern void func_002DA708(u8 *arg0, s32 arg1, s32 arg2);
extern void func_002DCA58(u8 *arg0);
extern void func_002DCD90(u8 *arg0);
extern void func_002DCDA8(u8 *arg0);
extern void func_002DCDD0(u8 *arg0);
extern u8 func_002DA9D0[];

u8 *func_002DCCF0(u8 *obj) {
    func_002DA708(obj, 0, 0x40);
    *(s32 *)(obj + 0x0) = 2;
    func_002DCA58(obj + 0x4);
    *(s32 *)(obj + 0x10) = 2;
    func_002DCD90(obj + 0x18);
    func_002DCDA8(obj + 0x28);
    func_002DCDA8(obj + 0x48);
    func_002DCDA8(obj + 0x68);
    func_002DCDA8(obj + 0x88);
    func_002DCDD0(obj + 0xA8);
    *(s32 *)(obj + 0xD0) = 0;
    *(s32 *)(obj + 0xD8) = 0;
    *(s32 *)(obj + 0xDC) = 0;
    *(u8 **)(obj + 0xD4) = func_002DA9D0;
    *(s32 *)(obj + 0xE0) = 0;
    *(s32 *)(obj + 0xE4) = 0;
    *(s32 *)(obj + 0xE8) = 0;
    return obj;
}

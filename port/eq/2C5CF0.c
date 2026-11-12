#include "common.h"

extern s32 func_002D07B0(u8 *arg0, s32 arg1);
extern s32 func_002C5E98(u8 *arg0);
extern void func_002C5D88(u8 *arg0);
extern void func_002C5DF8(u8 *arg0);
extern s32 func_002C6250(u8 *arg0);
extern void func_002C5EB0(u8 *arg0);
extern void func_002C6138(u8 *arg0);

s32 func_002C5CF0(u8 *obj) {
    s32 ret;

    if (func_002D07B0(obj, 5) == 0) {
        return 0;
    }
    if (func_002C5E98(obj) == 1) {
        return 0;
    }
    func_002C5D88(obj);
    if (*(s32 *)(obj + 0x48) == 2) {
        func_002C5DF8(obj);
    }
    ret = func_002C6250(obj);
    func_002C5EB0(obj);
    func_002C6138(obj);
    return ret;
}

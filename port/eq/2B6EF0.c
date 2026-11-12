#include "common.h"

extern void func_002BD380(s32 arg0);
extern void func_002B7138(u8 *arg0);
extern void func_002B6D10(u8 *arg0);
extern void func_002B7570(u8 *arg0, s32 arg1);
extern void func_002B7C20(u8 *arg0, s32 arg1, s32 arg2);
extern void func_002B7C28(u8 *arg0, s32 arg1, s32 arg2);

void func_002B6EF0(u8 *obj, s32 arg1, s32 arg2, s32 arg3) {
    func_002BD380(1);
    *(s32 *)(obj + 0x1BC) = *(s32 *)(obj + 0x1C0);
    func_002B7138(obj);
    func_002B6D10(obj);
    func_002BD380(0);
    func_002B7570(obj, arg1);
    func_002B7C20(obj, arg2, arg3);
    func_002B7C28(obj, arg2, arg3);
}

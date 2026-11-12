#include "m2c_macros.h"

void func_002BD380(s32);
void func_002B7138(void *);
void func_002B6D10(void *);
void func_002B7570(void *, M2C_UNK);
void func_002B7C20(void *, M2C_UNK, M2C_UNK);
void func_002B7C28(void *, M2C_UNK, M2C_UNK);


/* Copies +0x1C0 into +0x1BC, runs the per-object update calls (func_002B7138, func_002B6D10, func_002B7570), then func_002B7C20 and func_002B7C28 with arg2, arg3 */
void func_002B6EF0(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    func_002BD380(1);
    M2C_FIELD(arg0, s32 *, 0x1BC) = (s32) M2C_FIELD(arg0, s32 *, 0x1C0);
    func_002B7138(arg0);
    func_002B6D10(arg0);
    func_002BD380(0);
    func_002B7570(arg0, arg1);
    func_002B7C20(arg0, arg2, arg3);
    func_002B7C28(arg0, arg2, arg3);
}

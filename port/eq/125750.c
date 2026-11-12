#include "common.h"

s32 func_00124A00(u8 *arg0);
void func_00124AF0(u8 *arg0);
void func_00124D98(u8 *arg0);
void func_00124E18(u8 *arg0);
void func_00124F90(u8 *arg0);
void func_00125048(u8 *arg0);
void func_001251B0(u8 *arg0);
void func_00125248(u8 *arg0);
void func_00125488(u8 *arg0);
void func_00125580(u8 *arg0);
void func_001255F0(u8 *arg0);

/* 0x00125750(p): v = func_00124A00(p); p->+0x10A0 = (u8)v; if v == 0 return; else run the nine stages
 * func_00124AF0 .. func_00125580 on p and tail-call func_001255F0(p). */
void func_00125750(u8 *arg0) {
    u8 *p = arg0;
    s32 v;

    v = func_00124A00(arg0);
    *(u8 *)(p + 0x10A0) = (u8)v;
    if (v == 0) {
        return;
    }
    func_00124AF0(arg0);
    func_00124D98(arg0);
    func_00124E18(arg0);
    func_00124F90(arg0);
    func_00125048(arg0);
    func_001251B0(arg0);
    func_00125248(arg0);
    func_00125488(arg0);
    func_00125580(arg0);
    func_001255F0(arg0);
}

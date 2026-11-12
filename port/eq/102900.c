#include "common.h"

/* 0x00102900: p = D_003876A0; memset(p, 0, 0x70); func_00101BF0(); func_00297A30(); func_002A85B0();
   p = D_003876A0; func_00104C10(p->+0xD4, p->+0x2AC, p->+0x47C); func_00104E60(); func_002998D8(); tail func_00102568(). */
extern u8 D_003876A0[];
void func_00101BF0(void);
void func_00297A30(void);
void func_002A85B0(void);
void func_00104C10(s32 arg0, s32 arg1, s32 arg2);
void func_00104E60();
void func_002998D8(void);
void func_00102568(void);

void func_00102900(void) {
    u8 *p;

    p = *(u8 **)D_003876A0;
    memset(p, 0, 0x70);
    func_00101BF0();
    func_00297A30();
    func_002A85B0();
    p = *(u8 **)D_003876A0;
    func_00104C10(*(s32 *)(p + 0xD4), *(s32 *)(p + 0x2AC), *(s32 *)(p + 0x47C));
    func_00104E60();
    func_002998D8();
    func_00102568();
}

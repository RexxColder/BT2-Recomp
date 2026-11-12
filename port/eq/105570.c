#include "common.h"

s32 func_00105500(s32 arg0, s32 arg1, s32 arg2);
void func_00101700(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00101A38(s32 arg0);
void PauseMenu_Reset(void);
void func_0010ACE0(void);
void func_00105F30(s32 arg0);
extern u8 *D_003876A0;
extern u8 *D_003876B4;
extern u8 D_0033F418[] __attribute__((section(".data")));
extern u8 D_0033F4A8[] __attribute__((section(".data")));
extern u8 D_0033F538[] __attribute__((section(".data")));

s32 func_00105570(void) {
    u8 *p;
    u32 a0v;
    s32 v0;
    s32 idx;
    s32 table;

    func_00101700(0);
    func_00101700(1);
    memset(D_003876B4, 0, 0x114);
    *(s32 *)(D_003876B4 + 0x108) = ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) ? 2 : 1;
    a0v = *(u32 *)(D_003876A0 + 0xB8);
    p = D_003876B4;
    if (a0v < 6U) {
        if (a0v >= 4U || a0v == 1U) {
            *(s32 *)p = 2;
            v0 = (s32)D_0033F4A8;
        } else {
            v0 = (s32)D_0033F418;
        }
    } else if (a0v == 6U) {
        *(s32 *)p = 3;
        v0 = (s32)D_0033F538;
    } else {
        v0 = (s32)D_0033F418;
    }
    *(s32 *)(p + 0x104) = v0;
    if (a0v > 6U) {
        func_00101A38((s32)a0v);
    } else {
        func_00101A38((s32)p);
    }
    PauseMenu_Reset();
    func_0010ACE0();
    func_00105F30((s32)(D_003876A0 + 0x4B8));
    idx = *(s32 *)p;
    table = *(s32 *)(p + 0x104);
    return func_00105500(*(s32 *)(table + idx * 0x14), idx, table);
}

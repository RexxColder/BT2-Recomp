#include "m2c_macros.h"

extern u8 D_00393E50[] __attribute__((section(".data")));
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002BDCE0(void);
s32 func_002D07B0(void *arg0, s32 arg1);
void func_002D3098(void *arg0);
s32 func_002D31B8(void *arg0, s32 arg1);
void func_002D31C0(void *arg0, void *arg1);
void func_002D31D8(void *arg0, void *arg1);
void func_002D31F0(void *arg0, void *arg1);
void func_002D3208(void *arg0, void *arg1);
s32 func_002D3220(void *arg0, s32 arg1);
void func_002D87E8(s32 arg0);

/* Builds the object at arg1 from the template D_00393E50 (28 bytes at +8), then runs the sub-object setup
 * at arg0 + 0x1020 with the values of seven calls to func_002D07B0 on arg0. */
s32 Obj_InitFromTemplate(void *arg0, u8 *arg1) {
    s64 tab[8];
    u8 *sub;
    s32 r;

    if (*(s32 *)(D_00393E50 + 0x8) == 0 || *(s32 *)(D_00393E50 + 0x18) == 0) {
        return func_002C2FF0(0, 0xFF000C06);
    }

    for (r = 0; r < 7; r++) {
        *(u32 *)(arg1 + 8 + r * 4) = *(u32 *)(D_00393E50 + r * 4);
    }
    *(s32 *)(arg1 + 0x44) = -1;
    *(s32 *)(arg1 + 0x4C) = 0;
    *(s32 *)(arg1 + 0x00) = 0;
    *(s32 *)(arg1 + 0x04) = 0;
    *(s32 *)(arg1 + 0x24) = -1;
    *(s32 *)(arg1 + 0x2C) = 0;
    *(s32 *)(arg1 + 0x30) = 0;
    *(s32 *)(arg1 + 0x34) = 0;
    *(s32 *)(arg1 + 0x38) = 0;
    *(s32 *)(arg1 + 0x40) = 0;
    *(s32 *)(arg1 + 0x28) = 1;
    *(void **)(arg1 + 0x3C) = (void *)func_002BDCE0;
    *(s32 *)(arg1 + 0x48) = 0;

    sub = (u8 *)arg0 + 0x1020;

    r = func_002D07B0(arg0, 0x3F);
    tab[0] = r;
    tab[1] = 1000000;
    r = func_002D07B0(arg0, 0x40);
    tab[2] = r;
    tab[3] = 1000000;
    r = func_002D07B0(arg0, 0x41);
    tab[4] = r;
    tab[5] = 1000000;
    r = func_002D07B0(arg0, 0x42);
    tab[6] = r;
    tab[7] = 1000000;
    func_002D3098(sub);

    r = func_002D07B0(arg0, 0x48);
    func_002D31B8(sub, r);
    func_002D31C0(sub, &tab[0]);
    func_002D31D8(sub, &tab[2]);
    func_002D31F0(sub, &tab[4]);
    func_002D3208(sub, &tab[6]);

    r = func_002D07B0(arg0, 0x3E);
    func_002D3220(sub, r);

    r = func_002D07B0(arg0, 0x3D);
    func_002D87E8(r);
    return 0;
}

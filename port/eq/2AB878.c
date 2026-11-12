#include "common.h"

s32 func_0028BAA8();
s32 func_00100CB8();
void func_001012D0();
void func_00297A30();
void func_002A85D0();
void func_00261B18();
void func_002738B8();
void func_0025B9F8();
void func_00261D30(s32 arg0);
void func_0025E2D0(s32 arg0);
void func_00280CD8();
void func_0025A400();
void func_00278C80();
void Gsc_InitDefault(void *arg0);
void func_002A3310();
void func_002AC9E0();
void func_00284AC8();
void func_002ACEE0();
void func_00259378(s32 arg0, s32 arg1);
void func_0028BB60(s32 arg0);
void func_002AB130();
extern u8 *D_003876A0;
extern u8 D_00344C98 __attribute__((section(".data")));
extern s32 D_003B2690 __attribute__((section(".data")));

void func_002AB878(void) {
    u8 *s1;
    s32 s0;
    s32 v0;

    s1 = D_003876A0;
    *(s64 *)(s1 + 0x4D8) &= ~0x8000;
    *(s64 *)(s1 + 0x4D8) &= ~0x100;
    *(s64 *)(s1 + 0x4D8) &= ~0x800;
    *(s64 *)(s1 + 0x4D8) &= ~0x1000;
    *(s64 *)(s1 + 0x4D8) &= ~0x2000;
    *(s64 *)(s1 + 0x4D8) &= ~0x200;
    *(s64 *)(s1 + 0x4D8) &= ~0x400;
    *(s64 *)(s1 + 0x4D8) &= ~0x1;
    *(s64 *)(s1 + 0x4D8) &= ~0x2;

    *(s32 *)(s1 + 0xC) = func_0028BAA8(0x74800, D_003876A0, -0x101, -0x801, -0x1001, -0x2001, -0x201, -0x401);
    *(s32 *)(s1 + 0x14) = func_0028BAA8(0x32000);
    func_001012D0();
    func_00297A30();
    func_002A85D0();
    func_00261B18();
    func_002738B8();
    func_0025B9F8();
    func_00261D30(2);
    func_0025E2D0(2);
    func_00280CD8();
    func_0025A400();
    func_00278C80();
    Gsc_InitDefault(&D_00344C98);
    func_002A3310();
    func_002AC9E0();
    func_00284AC8();
    *(s32 *)(s1 + 0x24) = func_00100CB8(0x33CB);
    func_002ACEE0();
    s0 = (((D_003B2690 ^ 1) == 0) ? 0x768 : 0x767);
    *(s32 *)(s1 + 0x28) = func_0028BAA8(0x7D000);
    v0 = func_00100CB8(s0);
    func_00259378(v0, *(s32 *)(s1 + 0x28));
    func_0028BB60(v0);
    func_002AB130();
}

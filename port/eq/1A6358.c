#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 func_00129C28(s32 arg0, s32 arg1);
void Vec3_Normalize(s32 arg0, s32 arg1);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern s32 *gEftTrail;
extern u8 D_00342688[];

void func_001A6358(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    u8 sp[0x220];
    u8 *p;
    u8 *cur;
    s32 i;

    memset(sp, 0, 0x220);
    *(s32 *)(sp + 0x1B0) = 0x14;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        *(s32 *)(sp + 0x1B0) = 0xF;
    }
    func_00129C28((s32)(sp + 0x40), arg0);
    i = 0;
    if (*(s32 *)(sp + 0x1B0) > 0) {
        p = sp + 0x70;
        do {
            cur = p;
            p += 0x10;
            i += 1;
            func_00129C28((s32)cur, arg0);
        } while (i < *(s32 *)(sp + 0x1B0));
    }
    func_00129C28((s32)(sp + 0x50), arg1);
    Vec3_Normalize((s32)(sp + 0x50), (s32)(sp + 0x50));
    *(s32 *)(sp + 0x1B8) = 4;
    *(s32 *)(sp + 0x1B4) = 0;
    *(f32 *)(sp + 0xC) = farg0;
    *(f32 *)(sp + 0x10) = farg1;
    *(f32 *)(sp + 0x14) = farg2;
    *(f32 *)(sp + 0x18) = farg3;
    *(s32 *)(sp + 0x24) = arg2;
    *(s32 *)(sp + 0x30) = arg3;
    *(s32 *)(sp + 0x0) = (s32)((u8 *)gEftTrail + 8);
    BtlTaskList_AddTail(*gEftTrail, (s32)D_00342688, (s32)sp);
}

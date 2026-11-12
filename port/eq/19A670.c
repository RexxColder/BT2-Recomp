#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftGlow_Begin(s32 arg0, s32 arg1);
void EftAura_CommandAlt(s32 arg0, s32 arg1);
extern s32 D_003877E4;
extern u8 D_003420C0[] __attribute__((section(".data")));
extern u8 *gEftGlow;

s32 func_0019A670(s32 arg0, s32 unused1, s32 unused2, s32 arg3) {
    s32 s1;
    s32 loc;
    s32 v;
    u8 *ent;
    u8 *t;

    s1 = arg0 * 4;
    ent = *(u8 **)(*(u8 **)(gEftGlow + 0x6F0) + s1);
    if (ent != NULL) {
        t = *(u8 **)(ent + 0x38);
        EftGlow_Begin((s32)t, (s32)(t + 0x4C));
    } else {
        loc = arg0;
        v = BtlTaskList_AddTail(D_003877E4, (s32)D_003420C0, (s32)&loc, arg3);
        if (v == 0) {
            return 0;
        }
        *(s32 *)(*(u8 **)(gEftGlow + 0x6F0) + s1) = v;
    }
    EftAura_CommandAlt(arg0, 0);
    return 1;
}

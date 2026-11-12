#include "common.h"

s32 BtlStage_FindZoneNear(s32 arg0, s32 arg1);
void StgCol_InitSegCtx(u8 *arg0, s32 arg1);
void func_0011DF50(s32 arg0, s32 arg1, s32 arg2, u8 *arg3);
void func_00273268(void);
void func_003126C8(u8 *arg0, u8 *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s32 D_003876F0;
extern s32 D_003876F4;
extern u8 D_003885A0[] __attribute__((section(".data")));
extern u8 D_003885F0[] __attribute__((section(".data")));

s32 func_0011E1C8(s32 arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_v1;

    memset(D_003885A0, 0, 0x50);
    func_00273268();
    temp_s2 = BtlStage_FindZoneNear(-1, arg0);
    temp_s1 = BtlStage_FindZoneNear(-1, arg0 + 0x10);
    StgCol_InitSegCtx(D_003885F0, arg0);
    D_003876F0 = 0;
    D_003876F4 = 0;
    func_0011DF50(temp_s2, temp_s2, temp_s1, D_003885F0);
    var_v0 = 0;
    if (*(u8 *)(D_003885F0 + 0xC8) != 0) {
        *(s8 *)(D_003885A0 + 0) = 1;
        func_003126C8(D_003885A0 + 0x10, D_003885F0 + 0x90);
        temp_v1 = D_003885F0 + 0xA0;
        temp_a0 = D_003885A0 + 0x20;
        var_v0 = 1;
        *(s64 *)(temp_a0 + 0x18) = *(s64 *)(temp_v1 + 0x18);
        *(s32 *)(D_003885A0 + 0x40) = *(s32 *)(D_003885F0 + 0xC4);
        *(s64 *)(D_003885A0 + 0x20) = *(s64 *)(D_003885F0 + 0xA0);
        *(s64 *)(temp_a0 + 8) = *(s64 *)(temp_v1 + 8);
        *(s64 *)(temp_a0 + 0x10) = *(s64 *)(temp_v1 + 0x10);
    }
    return var_v0;
}

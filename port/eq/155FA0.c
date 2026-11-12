#include "common.h"

s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlScene_GetPackEntry(s32 arg0, s32 arg1);
void BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load32(s32 arg0, s32 arg1);
void func_00148000(s32 arg0);
void func_0014E258(s32 arg0, s32 arg1);
void func_001EC288(s32 arg0, s32 arg1);
void func_001EC308(s32 arg0, s32 arg1);
void func_001EC368(s32 arg0, s32 arg1);
void func_001EC370(s32 arg0, s32 arg1);

void func_00155FA0(u8 *arg0, u8 *arg1) {
    u8 *s0;
    s32 v;
    s32 var_v0;
    s32 var_a1;

    s0 = *(u8 **)(arg0 + 0x38);

    func_00148000(0x1E90);
    memset(s0, 0, 0x1E90);
    *(s32 *)(s0 + 0x1E80) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x80);
    memset((void *)*(s32 *)(s0 + 0x1E80), 0, 0x80);
    *(s32 *)(s0 + 0x1E84) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x208);
    memset((void *)*(s32 *)(s0 + 0x1E84), 0, 0x208);

    v = *(s32 *)(*(u8 **)(arg1 + 0x20));
    if (v == 0x6A) {
        var_v0 = BtlScene_GetPackEntry(*(s32 *)(arg1 + 0x1C), 0x2D);
        var_a1 = 0x2E;
    } else if (v == 0x6B) {
        var_v0 = BtlScene_GetPackEntry(*(s32 *)(arg1 + 0x1C), 0x2A);
        var_a1 = 0x2B;
    } else {
        goto common;
    }
    *(s32 *)(s0 + 0x1E88) = var_v0;
    *(s32 *)(s0 + 0x1E8C) = BtlScene_GetPackEntry(*(s32 *)(arg1 + 0x1C), var_a1);

common:
    EftTexSet_Load32(*(s32 *)(s0 + 0x1E84), *(s32 *)(s0 + 0x1E8C));
    func_001EC288(*(s32 *)(s0 + 0x1E80), *(s32 *)(s0 + 0x1E88));
    func_001EC308(*(s32 *)(s0 + 0x1E80), *(s32 *)(s0 + 0x1E84));
    func_001EC368(*(s32 *)(s0 + 0x1E80), 1);
    func_001EC370(*(s32 *)(s0 + 0x1E80), 0);
    func_0014E258((s32)arg1, (s32)s0);
    BtlTask_CreateChildList((s32)arg0, 2, 0xAC0);
}

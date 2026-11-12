#include "common.h"

s32 BtlStage_IsReady(u8 *arg0);
void Dma_AddScissor(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ObjGs_AddDefaultEnv(void);
void func_00268710(void);
void func_002690C0(s32 arg0, u32 arg1, u8 *arg2);
void func_00271370(void);
s32 func_00276D80(void);
void func_0029EF08(s32 arg0);
void func_0029EF80(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 *D_00387A44;

void func_00269848(u8 *arg0, u8 *arg1) {
    u32 var_a1;
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0xE90);
    if (BtlStage_IsReady(arg0) == 0) {
        return;
    }
    if (func_00276D80() == 1) {
        return;
    }
    if (temp_s0 == NULL) {
        return;
    }
    if (*(u32 *)(temp_s0 + 0x10) == 0) {
        return;
    }
    Dma_AddScissor(*(s32 *)(arg1 + 0x200), *(s32 *)(arg1 + 0x204), *(s32 *)(arg1 + 0x208), *(s32 *)(arg1 + 0x20C));
    ObjGs_AddDefaultEnv();
    var_a1 = *(u32 *)(temp_s0 + 0x10);
    if (var_a1 >= 0x90U) {
        var_a1 = 0x8F;
        *(u32 *)(temp_s0 + 0x10) = 0x8FU;
    }
    func_002690C0(*(s32 *)(temp_s0 + (*(u8 *)(D_00387A44 + 0xE550) * 4)), var_a1, temp_s0 + 0xC0);
    func_00268710();
    func_0029EF80(arg1, temp_s0 + 0x40, temp_s0 + 0x30);
    func_0029EF08(*(s32 *)(temp_s0 + (*(u8 *)(D_00387A44 + 0xE550) * 4)));
    func_00271370();
}

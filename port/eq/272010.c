#include "common.h"

void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_00271FD8(void);
void func_002727B8(void);
void func_00276430(s32 arg0);
void func_0028D340(s32 arg0);
extern u8 *gBtlStage;

void func_00272010(u8 *arg0, s32 arg1) {
    gBtlStage = arg0;
    *(s32 *)(arg0 + 0x5C) = arg1;
    Res_RelocateOffsets((s32)(gBtlStage + 0x58), arg1,
                        *(s32 *)(gBtlStage + 0x5C) + *(s32 *)(gBtlStage + 0x54) * 4);
    func_0028D340(*(s32 *)(gBtlStage + 0x5C));
    *(s32 *)(gBtlStage + 0x8) = 0;
    func_00276430((s32)gBtlStage);
    func_002727B8();
    func_00271FD8();
}

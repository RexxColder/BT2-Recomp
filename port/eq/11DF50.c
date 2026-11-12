#include "common.h"

extern u8 *gBtlStage;
extern s32 D_003876F0;
extern s32 D_003876F4;

s32 ColBox_ClipRay(void *a0, void *a1, void *a2);
s32 ColBox_ContainsPoint(void *a0, void *a1);
s32 ColBox_Overlaps(void *a0, void *a1);
void StgCol_ClipSegToZone(void *a0, s32 a1, s32 a2, s32 a3, void *t0, void *t1, void *t2);
s32 StgCol_FirstBit(s64 a0);
void func_0011CB00(void);
s32 func_0011CB18(void *a0, u8 *a1, void *a2, u8 *a3, void *t0);
void func_0011DCA8(void *a0, s32 a1);
s32 func_002745F8(s32 a0);
void func_0011D978(void);
void func_0011DF50(s32 arg0, s32 arg1, s32 arg2, u8 *arg3);

void func_0011DF50(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s64 sp[4];
    s64 sp20[4];
    s64 sp40[4];
    s64 sp60[2];
    u8 *temp_s3;
    u8 *var_s0;
    s32 temp_v1;
    s32 temp_v0;
    s32 var_s1;
    s32 fp;

    temp_s3 = (u8 *)((arg0 << 6) + (*(s32 *)((u8 *)gBtlStage + 0x5C) + (*(s32 *)((u8 *)gBtlStage + 0x3C) * 4)));
    temp_v1 = *(s32 *)temp_s3;
    if (!(temp_v1 & 1)) {
        *(s32 *)temp_s3 = temp_v1 | 1;
        fp = ((arg2 ^ arg0) == 0);
        D_003876F4 += 1;
        func_0011DCA8(sp20, arg0);
        if (ColBox_Overlaps(sp20, arg3 + 0x40) != 0) {
            if (ColBox_ClipRay(sp20, arg3 + 0x60, sp60) != 0) {
                StgCol_ClipSegToZone(sp40, arg0, arg1, arg2, arg3, sp20, sp60);
                func_0011CB00();
                if (func_0011CB18(sp, temp_s3, sp40, arg3, (void *)func_0011D978) == 0) {
                    D_003876F0 += 1;
                    if (arg2 != arg0) {
                        var_s1 = 0;
                        if (*(s32 *)(temp_s3 + 8) > 0) {
                            var_s0 = (u8 *)(*(s32 *)((u8 *)gBtlStage + 0x5C) + (*(s32 *)(temp_s3 + 0xC) << 2));
                            do {
                                func_0011DCA8(sp20, *(s32 *)var_s0);
                                if (ColBox_ContainsPoint(sp20, sp60) != 0) {
                                    func_0011DF50(*(s32 *)var_s0, arg1, arg2, arg3);
                                }
                                var_s1 += 1;
                                var_s0 += 4;
                            } while (var_s1 < *(s32 *)(temp_s3 + 8));
                        }
                    }
                } else {
                    temp_v0 = StgCol_FirstBit(sp[2]);
                    if (temp_v0 >= 0) {
                        if (func_002745F8(temp_v0) == 0) {
                            *(s32 *)(arg3 + 0xC4) = temp_v0;
                        }
                    }
                }
            }
        }
    }
}

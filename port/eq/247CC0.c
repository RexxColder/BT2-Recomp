#include "common.h"

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_00101498(void);
void func_00101890(void);
void func_002437E8(void);
void func_002438E8(void);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_00243E38(s32 arg0);
void func_00244590(void);
void func_00244600(void);
void func_00244708(void);
void func_00246860(s32 arg0);
void func_00247638(s32 arg0);
void func_00250DC0(s32 arg0, s32 arg1);
void func_0026EA58(s32 arg0);
void func_002711A0(void);
void func_00271240(void);
void func_0028B090(void);
void func_0028B218(void);
void func_0028BCB0(void);
void func_0028BCE8(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_00297A60(s32 arg0, s32 arg1);
void func_00297EC8(void);
void func_00298158(s32 arg0);
extern u8 *D_003876A4;
extern u8 *D_00387958;

s32 func_00247CC0(void) {
    s32 sp[4];
    s32 temp_v0;

    sp[0] = 1;
    func_0028BCB0();
    func_00297A60(0x33E8, 0);
    func_00243E38(0);
    func_0028B218();
    func_00243968(0, 0, 0);
loop_1:
    func_002711A0();
    func_0028B090();
    func_0028BDA0();
    func_00297978();
    func_002438E8();
    func_00244600();
    if (*(s32 *)(D_00387958 + 0x1288) != 0) {
        func_00247638((s32)sp);
    }
    func_00244708();
    BattleSetup_Finish();
    func_0026EA58((s32)(D_00387958 + 0x78));
    temp_v0 = *(s32 *)(D_00387958 + 0x1220);
    func_00250DC0(*(s32 *)(D_00387958 + ((((temp_v0 << 8) + *(s32 *)(D_00387958 + temp_v0 * 4 + 0x1F0)) * 4)) + 0x210), (s32)D_00387958);
    func_002437E8();
    func_00271240();
    if ((ColorFade_IsFadingOut() != 0) && (*(s32 *)(D_00387958 + 0x122C) & 2)) {
        func_00101890();
        if (sp[0] == 0) {
            func_00101498();
        }
        goto loop_1;
    }
    if (ColorFade_IsOutDone() == 0) {
block_11:
        if (*(s32 *)(D_00387958 + 0x1288) == 0) {
            func_00246860((s32)sp);
        }
        goto loop_1;
    }
    if (!(*(s32 *)(D_00387958 + 0x122C) & 2)) {
        goto block_11;
    }
    func_00244590();
    func_0028B218();
    func_00297EC8();
    func_0028BCE8();
    if (*(s32 *)(D_003876A4 + 0x1C) != 5) {
        func_00298158(1);
    }
    return sp[0];
}

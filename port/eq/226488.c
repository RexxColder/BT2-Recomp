#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlObjAnim_MaskToNode(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001F9D10(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void func_00211418(s32 arg0, s32 arg1);

void func_00226488(s32 arg0) {
    BattleSide_SetChara(arg0, 0x87);
    func_0020FC38(arg0, 0x2E);
    *(s32 *) (arg0 + 0xA14) = 0x2D;
    *(s32 *) (arg0 + 0xA10) = *(s32 *) (arg0 + 0xA10) + 1;
    func_00211418(arg0, 0x10000);
    func_001F9D10(arg0, 0x89);
    *(s32 *) (arg0 + 0xA20) = BtlObjAnim_MaskToNode(BtlObjAnim_QueryEvent(*(s32 *) (arg0 + 0x1530), 4, 1, 3));
    func_00206958(arg0, 0x80000);
}

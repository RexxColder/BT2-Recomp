#include "common.h"

void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_0020FC38(u8 *arg0, s32 arg1);
void func_00211418(void *obj, s32 mask);
void func_001F9D10(s32 a0, s32 a1);
s32 BtlObjAnim_QueryEvent(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 BtlObjAnim_MaskToNode();
extern s32 func_00206958();

s32 func_00226A28(u8 *obj) {
    s32 ev;

    BattleSide_SetChara(obj, 0x99);
    func_0020FC38(obj, 0x2E);
    func_00211418(obj, 0x10000);
    func_001F9D10((s32)obj, 0x9B);
    ev = BtlObjAnim_QueryEvent(*(u8 **)(obj + 0x1530), 4, 1, 3);
    *(s32 *)(obj + 0xA20) = BtlObjAnim_MaskToNode(ev);
    return func_00206958(obj, 0x80000);
}

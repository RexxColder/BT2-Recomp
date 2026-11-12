#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

s32 BtlObjAnim_MaskToNode(s32);                     /* extern */
s32 BtlObjAnim_QueryEvent(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_001F9D10(void *, M2C_UNK);             /* extern */
M2C_UNK func_00206958(void *, M2C_UNK);             /* extern */
M2C_UNK func_0020FC38(void *, M2C_UNK);             /* extern */
M2C_UNK func_00211418(void *, M2C_UNK);             /* extern */

// Sets up a battle side: BattleSide_SetChara(arg0,0x99), func_0020FC38 0x2E, func_00211418 flag 0x10000, func_001F9D10 0x9B, stores anim node into 0xA20.
void func_00226A28(void *arg0) {
    BattleSide_SetChara(arg0, 0x99);
    func_0020FC38(arg0, 0x2E);
    func_00211418(arg0, 0x10000);
    func_001F9D10(arg0, 0x9B);
    M2C_FIELD(arg0, s32 *, 0xA20) = BtlObjAnim_MaskToNode(BtlObjAnim_QueryEvent(M2C_FIELD(arg0, s32 *, 0x1530), 4, 1, 3));
    func_00206958(arg0, 0x80000);
}

/*
 * BtlCharApi_ObjQuery24D610 (BT3 btl_char_api.c, same code).
 */
#include "common.h"
#include "battle/btl_char_api.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern BtlCharApiObj *BtlObjVis_GetView_207EA0(s32 objId);
extern s32 BtlObjAnim_QueryEvent(BtlCharApiObj *obj, u64 arg1, s32 arg2, s32 arg3);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* BtlObjAnim_QueryEvent(obj, arg1, 0, arg2) on the object. */
s32 BtlCharApi_ObjQuery24D610(s32 objId, s32 arg1, s32 arg2) {
    BtlCharApiObj *obj = BtlObjVis_GetView_207EA0(objId);

    if (obj != NULL) {
        return BtlObjAnim_QueryEvent(obj, arg1, 0, arg2);
    }
    return 0;
}

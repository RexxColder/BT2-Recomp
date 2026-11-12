/*
 * Fighter attribute accessors (BT3 btl_char_api.c, same code): BtlCharApi_ObjGetAttrValue, BtlCharApi_ObjGetAttrKind.
 */
#include "common.h"
#include "battle/btl_char_api.h"
#include "battle/battle.h"
#include "sys/math3d.h"

extern BtlCharApiObj *BtlObjVis_GetView_207EA0(s32 objId);
extern s32 BtlObjAnim_GetEventArg(BtlCharApiObj *obj, u64 mask);
extern s32 BtlObjAnim_MaskToNode(s32 bits);

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* OR of the values of the object's attribute words that have a bit of mask. */
s32 BtlCharApi_ObjGetAttrValue(s32 objId, u64 mask) {
    BtlCharApiObj *obj = BtlObjVis_GetView_207EA0(objId);

    if (obj != NULL) {
        return BtlObjAnim_GetEventArg(obj, mask);
    }
    return 0;
}
/* The same value mapped to a kind code by BtlObjAnim_MaskToNode, 0 when there is none. */
s32 BtlCharApi_ObjGetAttrKind(s32 objId, u64 mask) {
    BtlCharApiObj *obj = BtlObjVis_GetView_207EA0(objId);
    s32 bits;
    s32 kind;

    if (obj != NULL) {
        bits = BtlObjAnim_GetEventArg(obj, mask);
        kind = 0;
        if (bits != 0) {
            kind = BtlObjAnim_MaskToNode(bits);
        }
        return kind;
    }
    return 0;
}

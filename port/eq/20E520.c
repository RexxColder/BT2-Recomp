#include "m2c_macros.h"

void *memset(void *dst, s32 c, u32 n);
s32 func_00211270(void);
void *func_00211288(s32 arg0);
s32 func_0023F430(void *obj);
s32 BtlObjXf_Update(void *obj);
void *BtlMember_GetActiveGauge(void *obj);
s32 func_0020A658(s32 idx);
s32 func_00210DD8(void *obj);
s32 BtlParam_IsTypeSetB(void *obj);
void func_002113C0(void *obj, s32 a1, s32 a2, s32 a3);

void func_0020E520(void) {
    u8 buf[0x10];
    u8 *p = buf;
    s32 i;
    void *obj;
    void *g;
    f32 ratio;

    memset(buf, 0, 2);
    for (i = 0; i < func_00211270(); i++) {
        obj = func_00211288(i);
        if (func_0023F430(obj) & 0x80) {
            p++;
            continue;
        }
        if (M2C_FIELD(obj, s32 *, 0xAF0) > 0) {
            p++;
            continue;
        }
        if (BtlObjXf_Update(obj) == 0x41) {
            *p = 1;
        }
        BtlMember_GetActiveGauge(obj); /* GUESS arg: a0 left by BtlObjXf_Update, result unused */
        g = BtlMember_GetActiveGauge(obj);
        ratio = (f32)M2C_FIELD(g, s32 *, 0xC) / (f32)M2C_FIELD(g, s32 *, 0x10);
        if (0.5f <= ratio) {
            *p = 1;
        }
        p++;
    }
    for (i = 0; i < func_00211270(); i++) {
        if (func_0020A658(i) == 0) {
            obj = func_00211288(i);
            func_002113C0(obj, 0, 0x2000, 0);
            if (buf[func_00210DD8(obj)] != 0) {
                if (BtlParam_IsTypeSetB(obj)) {
                    func_002113C0(obj, 0, 0x2000, 1);
                }
            }
        }
    }
}

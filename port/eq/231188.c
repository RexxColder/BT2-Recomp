#include "common.h"

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

s32 BtlObjAnim_QueryEvent(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
void func_001F9D10(s32 arg0, s32 arg1);
s32 func_00241050(s32 arg0, s32 arg1);

void func_00231188(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    s32 r;
    f32 f0;
    f32 f1;

    if (arg2 < func_00241050((s32)arg0, arg1)) {
        if (arg2 == 0) {
            *(s32 *)(arg0 + 0xA90) = 0;
            *(s32 *)(arg0 + 0xAA8) = 0;
            *(s32 *)(arg0 + 0xAAC) = 0;
        }
        func_001F9D10((s32)arg0, arg2 + (arg1 * 0x22) + 0xEF);
        temp_a0 = *(u8 **)(arg0 + 0x1530);
        if (*(u8 **)(temp_a0 + 0xBFC) != NULL) {
            *(s32 *)(arg0 + 0xA90) = *(s32 *)(arg0 + 0xA90) +
                BtlObjAnim_QueryEvent((s32)temp_a0, (s64)0x8000 << 18, 1, 2);
            temp_a0_2 = *(u8 **)(arg0 + 0x1530);
            if (BtlObjAnim_QueryEvent((s32)temp_a0_2, 0x20000, 1, 2) > 0) {
                *(s32 *)(arg0 + 0xAA8) = *(s32 *)(arg0 + 0xAA8) +
                    BtlObjAnim_QueryEvent((s32)temp_a0_2, 0x20000, 1, 0);
            } else {
                f1 = (f32)*(s32 *)(arg0 + 0xAA8);
                f0 = (f32)*(u16 *)(*(u8 **)(temp_a0_2 + 0xBFC) + 2);
                f0 = f0 + 1.0f;
                f1 = f1 + f0;
                CVT_W_S(r, f1);
                *(s32 *)(arg0 + 0xAA8) = r;
            }
            temp_a0_3 = *(u8 **)(arg0 + 0x1530);
            if (BtlObjAnim_QueryEvent((s32)temp_a0_3, 0x40000, 1, 2) > 0) {
                *(s32 *)(arg0 + 0xAAC) = *(s32 *)(arg0 + 0xAAC) +
                    BtlObjAnim_QueryEvent((s32)temp_a0_3, 0x40000, 1, 1);
                return;
            }
            f1 = (f32)*(s32 *)(arg0 + 0xAAC);
            f0 = (f32)*(u16 *)(*(u8 **)(temp_a0_3 + 0xBFC) + 2);
            f0 = f0 + 1.0f;
            f1 = f1 + f0;
            CVT_W_S(r, f1);
            *(s32 *)(arg0 + 0xAAC) = r;
        }
    }
}

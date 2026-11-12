#include "common.h"

s32 func_00191C30(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);

/* Blends the object's keyframe block (a2+56 -> 160-byte table) into the live copy at arg0+108: while the
 * time at +268 is below the end at +272, each field is interpolated between the two key sets by the
 * ratio t (func_00191C30 per field group) and the time advances by 1; otherwise the key set is copied. */
s32 func_00191C80(s32 a1, s32 a2) {
    f32 v3 = *(f32 *)(a1 + 268);
    f32 v4 = *(f32 *)(a1 + 272);
    s32 v5 = *(s32 *)(a2 + 56);
    s32 v6 = v5 + 40;
    s32 v17;
    s32 v18;
    f32 v19;
    f32 v16;
    s32 result;

    if (v4 > v3) {
        v16 = *(f32 *)(a1 + 276);
        if (v3 < v16) {
            v19 = v3 / v16;
            v17 = v5 + 244;
            v18 = v5 + 200;
        } else {
            v17 = v5 + 288;
            v18 = v5 + 244;
            v19 = (v3 - v16) / (v4 - v16);
        }
        func_00191C30(a1 + 108, v6, 3, *(f32 *)(v18 + 0), *(f32 *)(v17 + 0), v19);
        func_00191C30(a1 + 120, v6 + 12, 2, *(f32 *)(v18 + 4), *(f32 *)(v17 + 4), v19);
        func_00191C30(a1 + 128, v6 + 20, 3, *(f32 *)(v18 + 8), *(f32 *)(v17 + 8), v19);
        func_00191C30(a1 + 140, v6 + 32, 6, *(f32 *)(v18 + 12), *(f32 *)(v17 + 12), v19);
        func_00191C30(a1 + 164, v6 + 56, 6, *(f32 *)(v18 + 16), *(f32 *)(v17 + 16), v19);
        func_00191C30(a1 + 188, v6 + 80, 6, *(f32 *)(v18 + 20), *(f32 *)(v17 + 20), v19);
        func_00191C30(a1 + 212, v6 + 104, 2, *(f32 *)(v18 + 24), *(f32 *)(v17 + 24), v19);
        *(f32 *)(a1 + 220) = *(f32 *)(v6 + 112);
        func_00191C30(a1 + 224, v6 + 116, 1, *(f32 *)(v18 + 28), *(f32 *)(v17 + 28), v19);
        func_00191C30(a1 + 228, v6 + 120, 2, *(f32 *)(v18 + 32), *(f32 *)(v17 + 32), v19);
        func_00191C30(a1 + 236, v6 + 128, 2, *(f32 *)(v18 + 36), *(f32 *)(v17 + 36), v19);

        result = func_00191C30(a1 + 244, v6 + 136, 6, *(f32 *)(v18 + 40), *(f32 *)(v17 + 40), v19);
        *(f32 *)(a1 + 268) = *(f32 *)(a1 + 268) + 1.0f;
    } else {
        __builtin_memcpy((void *)(a1 + 108), (void *)v6, 160);
        result = v5 + 200;
    }
    return result;
}

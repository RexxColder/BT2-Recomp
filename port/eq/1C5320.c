#include "common.h"

extern f32 D_0038516C;

void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
s32 func_00129CD8(s32 arg0, s32 arg1);
s32 func_001C4F48(s32 arg0, s32 arg1);
void func_001C5130(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001C52A0(s32 arg0, s32 arg1);

/* Per-frame update of one emitter slot (arg2) for the source record arg0 at the anchor arg3: ramps the
 * slot's time 124 up to 1, otherwise counts elapsed frames against the distance, then advances the
 * spawn counter and emits through func_001C5130 (mode 0) or func_001C52A0 (mode 1). */
void func_001C5320(s32 a1, s32 a2, s32 a3, s32 a4) {
    u8 sp[0x10];
    s32 v9 = *(s32 *)(a3 + 80);
    s32 v11;
    s32 v14;
    s32 v15;
    s32 v16;
    s32 i;
    f32 v10;
    f32 v12;
    f32 v13;
    f32 v18;
    f32 v19;
    f32 v20;
    f32 v21;
    f32 v22;
    s32 v23;

    if ((v9 & 2) != 0) {
        v18 = *(f32 *)(a3 + 124) - (1.0f / *(f32 *)(a3 + 108));
        *(f32 *)(a3 + 124) = v18;
        if (v18 <= 0.0f) {
            *(f32 *)(a3 + 124) = 0.0f;
            *(s32 *)(a3 + 80) = v9 | 4;
            v9 = v9 | 4;
        }
    } else {
        v10 = *(f32 *)(a3 + 124);
        if (v10 < 1.0f) {
            v12 = v10 + D_0038516C;
            *(f32 *)(a3 + 124) = v12;
            if (v12 > 1.0f) {
                *(f32 *)(a3 + 124) = 1.0f;
            }
            v11 = *(u8 *)(a1 + 1);
        } else {
            v11 = *(u8 *)(a1 + 1);
        }

        if (v11 != 0) {
            *(s32 *)(a3 + 96) = *(s32 *)(a3 + 96) + 1;
            v14 = *(s32 *)(a3 + 96);
        } else {
            func_00129B58((s32)sp, a3 + 144, a4 + 16);
            v13 = __builtin_sqrtf(func_00129CD8((s32)sp, (s32)sp));
            *(f32 *)(a3 + 112) = v13;
            *(s32 *)(a3 + 96) = (s32)((v13 / 60.0f) + 4.0f);
            v14 = *(s32 *)(a3 + 96);
        }

        v15 = *(s32 *)(a3 + 92);
        if (v15 < v14) {
            *(s32 *)(a3 + 96) = v15;
            v14 = v15;
        }

        v16 = *(s32 *)(a3 + 100);
        if (v16 < v14) {
            for (i = v14 - v16; i != 0; i = i - 1) {
                if (func_001C4F48(a3, a4) == 0) {
                    v9 = *(s32 *)(a3 + 80);
                    goto emit;
                }
                *(s32 *)(a3 + 100) = *(s32 *)(a3 + 100) + 1;
            }
            v9 = *(s32 *)(a3 + 80);
        } else {
            v9 = *(s32 *)(a3 + 80);
        }
    }

emit:
    v19 = *(f32 *)(a3 + 124);
    *(f32 *)(a3 + 116) = (*(f32 *)(a1 + 4) * *(f32 *)(a4 + 12)) * v19;
    if ((v9 & 0x10) != 0) {
        v20 = *(f32 *)(a3 + 128);
        *(f32 *)(a3 + 120) = (*(f32 *)(a1 + 8) * *(f32 *)(a4 + 12)) * v19;
        v21 = v20 + *(f32 *)(a1 + 12);
        *(f32 *)(a3 + 128) = v21;
        if (v21 < 1.0f) {
            if (v21 > -1.0f) {
                v23 = *(u8 *)(a1 + 1);
                goto mode;
            }
            v22 = v21 + 1.0f;
        } else {
            v22 = v21 - 1.0f;
        }
        *(f32 *)(a3 + 128) = v22;
    }
    v23 = *(u8 *)(a1 + 1);

mode:
    if (v23 != 0) {
        if (v23 == 1 && (v9 & 2) == 0) {
            func_001C52A0(a1, a3);
        }
    } else {
        func_001C5130(a1, a2, a3, a4);
    }
}

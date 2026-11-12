#include "common.h"

void Vu0Screen_StoreMtx(void *arg0);
void func_00177D58(void *arg0, void *arg1);
void func_00178070(void *arg0, void *arg1, void *arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern u8 *D_00387E94;

/* 0x001778D8: frame = the screen matrix (Vu0Screen_StoreMtx) at +0, scratch matrix at +0x40. For each node of the list
 * at D_00387E94 +0x3F54 (linked by +0x4C) whose word +0x40 has bit 0: func_00177D58(scratch, node), then
 * func_00178070(scratch, frame, table + 16 * byte(+0x44), byte(+0x45), 255.0f, 255.0f, 255.0f, float(+0x38)). */
void func_001778D8(void) {
    u8 frame[0x80];
    u8 *g = D_00387E94;
    u8 *n;

    Vu0Screen_StoreMtx(frame);
    n = *(u8 **)(g + 0x3F54);
    if (n == NULL) {
        return;
    }
    do {
        if ((*(s32 *)(n + 0x40) & 1) != 0) {
            func_00177D58(frame + 0x40, n);
            func_00178070(frame + 0x40, frame, g + 0x3D48 + ((*(u8 *)(n + 0x44)) << 4), *(u8 *)(n + 0x45),
                          255.0f, 255.0f, 255.0f, *(f32 *)(n + 0x38));
        }
        n = *(u8 **)(n + 0x4C);
    } while (n != NULL);
}

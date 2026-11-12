#include "common.h"

extern f32 D_0038457C;
extern f32 D_00384580;
extern f32 D_00384584;
extern f32 D_00384588;
extern f32 D_0038458C;

f32 func_001488F8(void *arg0) {
    f32 f;
    void *p;
    s32 kind;
    s32 code;

    f = D_0038457C;
    p = *(void **)((u8 *)arg0 + 0x20);
    if (p != NULL) {
        kind = *(s32 *)((u8 *)p + 4);
        if (kind == 1) {
            if (*(s32 *)((u8 *)p + 8) == 4) {
                f = D_00384580;
            }
        } else if (kind == 2) {
            code = *(s32 *)((u8 *)p + 0);
            f = D_00384584;
            if (*(s32 *)((u8 *)p + 8) != 4) {
                f = D_00384588;
            }
            if (code == 0x85) {
                f = D_0038458C;
            }
            if (code == 0xB6) {
                f = 0.0f;
            }
        }
        code = *(s32 *)((u8 *)p + 0);
        if (code == 0x83) {
            f = 30.0f;
        }
    }
    return f;
}

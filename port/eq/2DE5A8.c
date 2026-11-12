#include "common.h"

s32 func_002DCE50(s32 arg0);

typedef s32 (*VFunc4)(s32, s32, s32, s32);
typedef void (*VFunc3)(s32, s32, s32);

s32 func_002DE5A8(u8 *arg0) {
    s32 sp[4];
    u8 *vt;

    vt = *(u8 **)arg0;
    ((VFunc4)(*(s32 *)(vt + 0x18)))((s32)arg0, 1, 0x7FFFFFFF, (s32)sp);
    vt = *(u8 **)arg0;
    ((VFunc3)(*(s32 *)(vt + 0x1C)))((s32)arg0, 1, (s32)sp);
    if (sp[1] >= 4) {
        return func_002DCE50(sp[0]);
    }
    return 0;
}

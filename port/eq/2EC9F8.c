#include "common.h"

/* 0x002EC9F8: e = (idx < 0x100) ? D_00366ED8[idx] : 0; if (idx >= 0x100 || !e) { func_002EA050(&D_0037C180, a1); return -3; }
   if (a1 < 0) { call &D_0037C1A8; return -3; } if (a1 < e->+8) return 0; call &D_0037C1A8; return -3. */
extern u8 D_00366ED8[];
extern u8 D_0037C180[];
extern u8 D_0037C1A8[];
s32 func_002EA050();

s32 func_002EC9F8(s32 a0, s32 a1) {
    u8 *e;

    e = NULL;
    if ((u32)a0 < 0x100) {
        e = *(u8 **)(D_00366ED8 + (a0 << 2));
    }
    if ((u32)a0 >= 0x100 || e == NULL) {
        func_002EA050((s32)D_0037C180, a1);
        return -3;
    }
    if (a1 < 0) {
        func_002EA050((s32)D_0037C1A8, a1);
        return -3;
    }
    if (a1 < *(s32 *)(e + 0x8)) {
        return 0;
    }
    func_002EA050((s32)D_0037C1A8, a1);
    return -3;
}

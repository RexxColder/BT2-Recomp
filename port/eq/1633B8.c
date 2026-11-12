#include "common.h"

extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern s32 func_00163088(s32 obj, u32 *arr, u32 mask);
extern s32 BtlCharApi_IsHidden(s32 arg0);
extern u32 D_0036E480[6];

/* Same record dispatch as func_00152608, but each pushed vector is lifted by 200.0 on its
   second lane (+4) when the owner character is hidden. */
s32 func_001633B8(u8 *obj, u8 *st, u32 flags) {
    u32 masks[6];
    s32 view = *(s32 *)(obj + 0);
    u8 *owner = *(u8 **)(obj + 0x20);
    s32 hidden;
    s32 i;
    u32 cur;

    for (i = 0; i < 6; i++) {
        masks[i] = D_0036E480[i];
    }
    hidden = BtlCharApi_IsHidden(view);
    if (flags & 0x80) {
        *(u32 *)(st + 0) |= 0x1000;
    }
    cur = *(u32 *)(st + 0);
    if (cur & 0x1000) {
        return cur & 0x1000;
    }

    if (*(u32 *)(owner + 0x30) & 4) {
        for (i = 0; i < 6; i++) {
            u32 bit = 1u << (i * 2);
            u8 *rec = st + i * 64;

            if (!(cur & bit)) {
                if (flags & masks[i]) {
                    *(u32 *)(st + 0) = cur | bit;
                    *(u32 *)(rec + 0x10) = *(u8 *)(*(u8 **)(obj + 0x20) + i + 0x38);
                    cur = *(u32 *)(st + 0);
                }
            }
            if (cur & bit) {
                func_00208DE8(view, rec + 0x20, *(s32 *)(rec + 0x10));
                if (hidden) {
                    *(f32 *)(rec + 0x24) = *(f32 *)(rec + 0x24) + 200.0f;
                }
                cur = *(u32 *)(st + 0);
            } else if (cur & 1) {
                func_00208DE8(view, rec + 0x20, *(s32 *)(st + 0x10));
                if (hidden) {
                    *(f32 *)(rec + 0x24) = *(f32 *)(rec + 0x24) + 200.0f;
                }
                cur = *(u32 *)(st + 0);
            }
            if (cur & (1u << (i * 2 + 1))) {
                func_00208DE8(view, rec + 0x40, *(s32 *)(rec + 0x30));
                if (hidden) {
                    *(f32 *)(rec + 0x44) = *(f32 *)(rec + 0x44) + 200.0f;
                }
            } else if (cur & 1) {
                func_00208DE8(view, rec + 0x40, *(s32 *)(st + 0x10));
                if (hidden) {
                    *(f32 *)(rec + 0x44) = *(f32 *)(rec + 0x44) + 200.0f;
                }
            }
            cur = *(u32 *)(st + 0);
        }
        return 0;
    }

    func_00163088(view, (u32 *)st, flags);
    if (!(*(u32 *)(*(u8 **)(obj + 0x20) + 0x30) & 8)) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        u32 bit = 1u << i;
        u8 *rec = st + 0x1A0 + i * 0x20;
        u8 *val = st + 0x190 + i * 0x20;
        u32 st1 = *(u32 *)(st + 4);

        if (st1 & bit) {
            func_00208DE8(view, rec, *(s32 *)val);
            if (hidden) {
                *(f32 *)(rec + 4) = *(f32 *)(rec + 4) + 200.0f;
            }
        } else {
            if (flags & masks[i]) {
                *(u32 *)(st + 4) = st1 | bit;
                *(u32 *)(st + 0) |= bit;
                *(u32 *)val = *(u8 *)(*(u8 **)(obj + 0x20) + i + 0x38);
                st1 = *(u32 *)(st + 4);
            }
            if (st1 & bit) {
                func_00208DE8(view, rec, *(s32 *)val);
                if (hidden) {
                    *(f32 *)(rec + 4) = *(f32 *)(rec + 4) + 200.0f;
                }
            } else if (st1 & 1) {
                func_00208DE8(view, rec, *(s32 *)(st + 0x190));
                if (hidden) {
                    *(f32 *)(rec + 4) = *(f32 *)(rec + 4) + 200.0f;
                }
            }
        }
        st1 = *(u32 *)(st + 4);
        if (st1 & bit) {
            func_00208DE8(view, rec, *(s32 *)val);
            if (hidden) {
                *(f32 *)(rec + 4) = *(f32 *)(rec + 4) + 200.0f;
            }
        } else if (st1 & 1) {
            func_00208DE8(view, rec, *(s32 *)(st + 0x190));
            if (hidden) {
                *(f32 *)(rec + 4) = *(f32 *)(rec + 4) + 200.0f;
            }
        }
    }
    return 0;
}

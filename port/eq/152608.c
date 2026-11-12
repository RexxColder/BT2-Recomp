#include "common.h"

extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern s32 func_00152328(s32 arg0, s32 *arg1, s32 arg2);
/* 8-byte aligned table in game memory: declared as one byte: clang assumes 16-byte alignment for extern arrays of >= 16 bytes (movaps fault) */
extern u8 D_0036E0D8;

/* Pushes the per-slot records of a state block through func_00208DE8: first a six-slot pass with
   2-bit groups (when the owner flag 4 is set), otherwise func_00152328 plus a six-slot pass over
   the second record table (owner flag 8). Returns the 0x1000 bit when it was already set. */
s32 func_00152608(u8 *obj, u8 *st, u32 flags) {
    u32 masks[6];
    s32 view = *(s32 *)(obj + 0);
    u8 *owner = *(u8 **)(obj + 0x20);
    s32 i;
    u32 cur;

    __builtin_memcpy(masks, &D_0036E0D8, sizeof(masks));
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
                cur = *(u32 *)(st + 0);
            } else if (cur & 1) {
                func_00208DE8(view, rec + 0x20, *(s32 *)(st + 0x10));
                cur = *(u32 *)(st + 0);
            }
            if (cur & (1u << (i * 2 + 1))) {
                func_00208DE8(view, rec + 0x40, *(s32 *)(rec + 0x30));
            } else if (cur & 1) {
                func_00208DE8(view, rec + 0x40, *(s32 *)(st + 0x10));
            }
            cur = *(u32 *)(st + 0);
        }
        return 0;
    }

    func_00152328(view, (s32 *)st, flags);
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
        } else {
            if (flags & masks[i]) {
                *(u32 *)(st + 4) = st1 | bit;
                *(u32 *)(st + 0) |= bit;
                *(u32 *)val = *(u8 *)(*(u8 **)(obj + 0x20) + i + 0x38);
                st1 = *(u32 *)(st + 4);
            }
            if (st1 & bit) {
                func_00208DE8(view, rec, *(s32 *)val);
            } else if (st1 & 1) {
                func_00208DE8(view, rec, *(s32 *)(st + 0x190));
            }
        }
        st1 = *(u32 *)(st + 4);
        if (st1 & bit) {
            func_00208DE8(view, rec, *(s32 *)val);
        } else if (st1 & 1) {
            func_00208DE8(view, rec, *(s32 *)(st + 0x190));
        }
    }
    return 0;
}

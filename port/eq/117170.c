#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
s32 BtlObjVis_GetView(s32 arg0);
s32 func_0010B078(void);
void func_00116908(s32 arg0, s32 arg1);
void func_00116D50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_0029D548(void);
void func_0029D580(s32 arg0);

extern u8 *D_003876A0;
extern u8 D_0036C9E0[] __attribute__((section(".data")));

/* 0x00117170: per-view draw of the current stage's objects. Two views (flag 2 of *(D_003876A0+0x4D8), else one)
 * are each handed to func_00116908 with their 0x110-byte block; the second call per view uses the three-word
 * table copied from D_0036C9E0 (sp+0..0x17). Skipped entirely when flag 0x100 is set. */
void func_00117170(void) {
    u8 sp[0x18];
    s32 base;
    s32 count;
    s32 k;
    s32 s1;
    s32 view;
    s32 flags;
    s32 flags2;
    s32 *pw;

    base = func_0010B078();
    memcpy(sp, D_0036C9E0, 0x18);

    flags = (s32)(*(s64 *)(D_003876A0 + 0x4D8));
    count = (flags & 2) ? 2 : 1;
    flags2 = (s32)(*(s64 *)(D_003876A0 + 0x4D8)) & 0x100;
    if (flags2 != 0) {
        return;
    }
    if (count == 0) {
        return;
    }

    s1 = base + 0x1130;
    for (k = 0; k < count; k++) {
        view = BtlObjVis_GetView(k);
        func_00116908(s1, view);
        s1 += 0x110;
        func_0029D548();
        func_0029D548();
        pw = (s32 *)(sp + 0xC + 8 * k);
        if (count == 1) {
            view = BtlObjVis_GetView(k);
            func_00116D50(base, k, view, LD32(sp, 0), LD32(sp, 4));
        } else {
            view = BtlObjVis_GetView(k);
            func_00116D50(base, k, view, pw[-1], pw[0]);
        }
        func_0029D580(1);
        func_0029D580(1);
    }
}

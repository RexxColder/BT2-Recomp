#include "common.h"

typedef struct { u64 lo, hi; } q128;

/* Object-build block passed to func_0018BA90 (0x60 bytes on the stack). */
typedef struct {
    s32 arg2;
    s32 arg3;
    s32 ctx;
    s32 pad;
    q128 v1;
    q128 v2;
    q128 v3;
    q128 v4;
    f32 f_second;
    f32 f_first;
    s32 desc3;
    s32 mode;
} ObjBuild;

s32 func_0018BA90(s32 arg0);
void func_0018BFD8(s32 arg0, s32 arg1);
void func_0018C020(s32 arg0, s32 arg1);
s32 func_0018C068(void *arg0);
s32 func_0018C0B0(u8 *arg0, s8 arg1);
void func_0018BB50(u8 *arg0, u8 *arg1);
void func_0018BDE0(s32 arg0, s32 arg1);
void func_0018BE48(s32 arg0, s32 arg1);
void func_0018BF08(u8 *arg0, f32 farg0);
s32 func_0018BB10(s32 arg0);
s32 func_0018BAD0(s32 arg0);
void func_00129C28(q128 *arg0, q128 *arg1);

s32 func_00150C68(s32 base, u8 *desc, s32 arg2, s32 arg3, s32 *objp, s32 flags, s32 mode,
                  q128 *src, f32 f_first, f32 f_second, q128 *src_a10, q128 *src_a11) {
    ObjBuild build;
    s32 result;

    if ((flags & 1) != 0 && *objp == 0) {
        build.arg2 = arg2;
        build.arg3 = arg3;
        build.ctx = base + 0x1AB8;
        build.desc3 = desc[3];
        build.mode = mode;
        build.f_first = f_first;
        build.f_second = f_second;
        /* 129C28 copies are the only writes to the four 16-byte slots (memsets were overwritten). */
        func_00129C28(&build.v4, src_a11);
        func_00129C28(&build.v1, src);
        func_00129C28(&build.v2, src);
        func_00129C28(&build.v3, src_a10);
        *objp = func_0018BA90((s32)&build);
        func_0018BFD8(*objp, desc[21]);
        func_0018C020(*objp, desc[4]);
        if ((desc[7] & 0x20) != 0) {
            func_0018C068((void *)*objp);
        }
        func_0018C0B0((u8 *)*objp, 1);
    }

    if (*objp == 0) {
        return flags & 8;
    }

    if ((flags & 8) != 0) {
        func_0018BB50((u8 *)*objp, (u8 *)src);
        func_0018BDE0(*objp, (s32)src);
        func_0018BE48(*objp, (s32)src_a10);
    }
    if ((flags & 0x20) != 0) {
        func_0018BF08((u8 *)*objp, f_second);
    }
    if ((flags & 4) != 0) {
        result = func_0018BB10(*objp);
        *objp = 0;
        return result;
    }
    if ((flags & 2) != 0) {
        return func_0018BAD0(*objp);
    }
    return 0;
}

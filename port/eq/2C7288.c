#include "common.h"

extern s32 func_002DE358();
extern s32 func_00305390();
extern s32 func_002DE398(s32 arg0, s32 arg1);
extern s32 func_002C71F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_002C7148(u8 *arg0, s32 arg1);
extern s32 func_002DE080(u8 *arg0, u8 *arg1);
extern s32 func_002C2FF0(u8 *arg0, s32 arg1);
extern s32 func_002D07B0(u8 *ctx, s32 idx);
extern s32 func_002DE370();
extern s32 func_002DCFE8(u32 arg0, s32 arg1, s32 arg2);
extern void func_002C75E0(u8 *arg0, s32 arg1, s32 arg2, s64 *arg3, s64 *arg4, s32 arg5);
extern void func_002C7870(void *arg0, void *arg1, s32 arg2);
extern void func_002C7BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_002C8170(u8 *arg0);
extern void func_002C8250(s32 arg0);
extern s32 func_002C83E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C7288(u8 *ctx, u8 *pair, s32 file, s32 flags, s32 *out) {
    u8 *st;
    u8 *info;
    s32 handle;
    s64 lo;
    s64 hi;
    s32 pos0;
    s32 len;
    s32 r;
    s32 mode;
    s32 limit;
    s32 want_hook;
    s32 hook;
    s32 hookArg;
    s32 hookB;
    s32 hookArgB;

    st = *(u8 **)(ctx + 0x1FC0);
    info = st + 0x8C;
    handle = *(s32 *)st;
    *(s32 *)(st + 0x1090) = 0;
    func_002DE358(handle, *(s32 *)(st + 0x108C), *(s32 *)(st + 0x1088));
    pos0 = func_00305390(file, 0, 1);
    *out = func_002DE398(handle, file);
    len = func_00305390(file, 0, 1) - pos0;
    r = func_002C71F0((s32)ctx, *out, len, 0xFF000F04);
    func_002C7148(ctx, len);
    if (r != 0) {
        return r;
    }
    if (*out == -2) {
        return 0;
    }
    r = func_002DE080((u8 *)handle, info);
    *out = r;
    if (r != 0) {
        return func_002C2FF0(ctx, 0xFF000F05);
    }
    want_hook = flags & 0x40;
    if (want_hook != 0) {
        if (*(s32 *)(ctx + 0x90C) > 0) {
            if (*(s32 *)(ctx + 0x90C) != *(s32 *)info) {
                *out = -2;
                return 0;
            }
            if (*(s32 *)(ctx + 0x910) != *(s32 *)(info + 4)) {
                *out = -2;
                return 0;
            }
        }
        hook = func_002D07B0(ctx, 0x5F);
        hookArg = func_002D07B0(ctx, 0x5F);
        s32 (*hookFn)(s32, s32, s32) = (s32 (*)(s32, s32, s32))(u32)hook;
        if (hook != 0 && hookFn(hookArg, *(s32 *)info, *(s32 *)(info + 4)) != 0) {
            *out = -2;
            return 0;
        }
    }
    mode = *(s32 *)(info + 0x18);
    if (mode == 1) {
        *(s32 *)(st + 0x174) = 0;
    } else if (*(s32 *)(ctx + 0x38) == 3) {
        if (*(s32 *)(st + 0x164) != 0) {
            limit = *(s32 *)(*(u8 **)(st + 0x164) + 0x70);
            if (mode == 2) {
                if (*(s32 *)(info + 0x14) < limit && limit < 0x200) {
                    *(s32 *)(st + 0x174) = 1;
                }
            } else if (mode == 3) {
                if (*(s32 *)(info + 0x14) >= limit) {
                    *(s32 *)(st + 0x174) = 1;
                }
            }
        }
    }
    func_002DE370(handle, 0, st + 0x1090);
    if (*(s32 *)(st + 0x10C) == *(s32 *)(info + 0x30)) {
        *(s32 *)(st + 0x110) = 0;
    } else {
        *(s32 *)(st + 0x10C) = *(s32 *)(info + 0x30);
        *(s32 *)(st + 0x110) = 1;
    }
    if (want_hook != 0) {
        hookB = func_002D07B0(ctx, 0x4D);
        hookArgB = func_002D07B0(ctx, 0x4E);
        if (hookB != 0) {
            r = func_002DCFE8(*(u32 *)pair, *(s32 *)(pair + 4), 1);
            if (r != 0) {
                s32 (*hookFnB)(s32, s32, s32) = (s32 (*)(s32, s32, s32))(u32)hookB;
                hookFnB(hookArgB, *(s32 *)pair, r - *(s32 *)pair + 4);
            }
        }
    }
    r = func_002DCFE8(*(u32 *)pair, *(s32 *)(pair + 4), 4);
    func_002C75E0(ctx, (s32)info, r, &lo, &hi, *(s32 *)(st + 0x110));
    *(s64 *)(st + 0x1120) = hi;
    if (((s64)flags & (s64)*(s32 *)(st + 0x78)) == 0) {
        return 0;
    }
    func_002C7870(ctx, info, *(s32 *)(st + 0x110));
    func_002C7BC8((s32)ctx, (s32)info, (s32)lo, *(s32 *)(st + 0x110));
    func_002C8170(ctx);
    func_002C8250((s32)ctx);
    return func_002C83E8(ctx, handle, (s32)info, (s32)pair);
}

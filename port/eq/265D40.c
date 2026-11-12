#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern void *D_003876A0;
extern s32 *D_00387A40;
extern s32 gBtlCamView;

s32 BtlStage_IsReady(void);
void func_00264320(f32 farg0, void *arg0, s32 arg1, void *arg2);

void func_00265D40(s32 arg0, s32 arg1, f32 farg0) {
    s32 *arr;
    u8 *elem, *a2;
    s32 s0, s1, s2b, t, a1v;

    if (!((*(s64 *)((u8 *)D_003876A0 + 0x4D8)) & 3) || BtlStage_IsReady() != 0) {
        s1 = 0;
        W(&D_00387A40[arg0], 0x38018) = gBtlCamView;
        arr = D_00387A40;
        if (arr[1] > 0) {
            s0 = 0;
            do {
                s1 += 1;
                elem = (u8 *)((s32)arr[0] + s0);
                s0 += 0x18580;
                a2 = elem + 0xAF0;
                W(a2, 0x90) = (s32)(a2 + (arg0 << 6) + 0x10);
                func_00264320(farg0, elem, arg1, a2);
                arr = D_00387A40;
            } while (s1 < arr[1]);
        }
        s1 = 0;
        arr = D_00387A40;
        if (arr[3] > 0) {
            s2b = arg0 << 6;
            s0 = 0;
            do {
                elem = (u8 *)((s32)arr[2] + s0);
                s0 += 0x1520;
                a2 = elem + 0xAF0;
                if (W(elem, 0xC) != 0) {
                    W(a2, 0x90) = (s32)(a2 + s2b + 0x10);
                    t = W(elem, 0x14);
                    a1v = (t != 1) ? -1 : 0x63;
                    func_00264320(0.0f, elem, a1v, a2);
                    arr = D_00387A40;
                }
                s1 += 1;
            } while (s1 < arr[3]);
        }
    }
}

#include "common.h"

extern f32 D_00384020;
extern f32 D_00384024;
extern f32 D_00384028;
extern f32 D_0038402C;

s32 func_0010B080(void);
s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113598(s32 arg0);
void func_00113600(f32 farg0, f32 farg1);
void func_00113620(s32 arg0, s32 arg1);
void func_00113980(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113A30(s32 arg0, s32 arg1);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0029D548(void);
void func_0029D580(s32 arg0);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);

/* Effect/emitter setup: copies the template block at P+0x00 to P+0x60 and P+0x120,
   seeds two random values, then sets up the two sub-emitters at P+0x180 and P+0x1E0. */
void func_00119B90(u8 *arg0, u8 *arg1, s32 arg2, u8 arg3, u8 arg4) {
    u8 *p = arg0;
    u8 *q = arg1;
    u8 *p1;
    u8 *p2;
    u8 *tbl;
    f32 buf[2];
    f32 f20;
    f32 f21;
    s32 v30;

    f21 = *(f32 *)(q + 0x28) * D_00384020 + D_00384024;
    tbl = (u8 *)func_0010B080();

    func_00114508((s32)p, 2, 0, 7);
    func_00113CB8((s32)p, 0, *(s32 *)(tbl + 12), 0);

    __builtin_memcpy(p + 0x60, p, 0x60);
    *(s32 *)(p + 0x60) = *(s32 *)(p + 0x60) | 0x80;
    *(u16 *)(p + 0x74) = 1;

    f20 = D_00384028;
    __builtin_memset(buf, 0, 8);
    buf[0] = (f32)rand() / f20;
    buf[1] = (f32)rand() / f20;
    func_00113A30((s32)(p + 0x60), (s32)buf);

    __builtin_memcpy(p + 0x120, p, 0x60);

    v30 = *(s32 *)(tbl + 12);
    p1 = p + 0x180;
    p2 = p + 0x1E0;
    if (arg2 >= 8) {
        func_00113CB8((s32)p1, 0, v30, (s16)arg2);
        func_00113B00((s32)p1, 16, 16);
        if (arg4 != 0) {
            __builtin_memcpy(p2, p1, 0x60);
            *(u16 *)(p + 0x1F4) = 16;
            func_00113B00((s32)p2, 0, -16);
        }
        f20 = 1.0f;
    } else {
        func_00113CB8((s32)p1, 0, v30, (s16)arg2);
        if (arg3 != 0) {
            *(s32 *)p1 = *(s32 *)p1 | 0x20;
        }
        f20 = D_0038402C;
    }

    func_00113598((s32)(q + 0x30));
    func_0029D548();
    func_00113600(f21, f21);
    BtlRec_CallFlagged((s32)p, 1, 4);
    func_0029D580(1);
    func_0029D548();
    func_00113600(f20, f20);
    func_00113620((s32)p1, 1);
    func_00113620((s32)p2, 1);
    func_0029D580(1);
    func_00113980((s32)p, 0x80, 0x80, 0x80, q[12], 7);
}

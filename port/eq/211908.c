#include "common.h"

void func_00312650(void *a0, void *a1, void *a2);
void func_00312680(f32 f12, void *a0, void *a1);
void func_00312638(void *a0, void *a1, void *a2);
void *func_00269A40(void *a0, s32 a1);
extern u8 *D_003876A0;
extern f32 D_00385A34;

void func_00211908(void *arg0) {
    u8 *s1;
    u8 *s2;
    u8 *v0;
    u8 *a1;
    u8 buf[0x20];
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;

    s1 = (u8 *)arg0;
    s2 = s1 + 0x910;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) != 0) {
        return;
    }
    f20 = D_00385A34;
    v0 = func_00269A40(*(void **)(s1 + 0x1530), 0x2F);
    f2 = *(f32 *)(v0 + 0x34);
    a1 = *(u8 **)(s1 + 0x1530);
    f0 = *(f32 *)(a1 + 0x9C4);
    f1 = *(f32 *)(s1 + 0x930);
    f0 = f0 - f2;
    f0 = f0 - f1;
    f0 = f0 * f20;
    f1 = f1 + f0;
    *(f32 *)(s1 + 0x930) = f1;
    func_00312650(buf + 0x10, a1 + 0x9C0, v0 + 0x30);
    func_00312650(buf, buf + 0x10, s2);
    func_00312680(f20, buf, buf);
    func_00312638(s2, s2, buf);
}

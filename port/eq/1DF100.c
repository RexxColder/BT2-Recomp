#include "common.h"

void func_00312650(void *a0, void *a1, void *a2);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312680(void *a0, void *a1, f32 farg0);

void EftBlade_Spline(void *arg0, u8 *arg1, f32 fparg0) {
    u8 buf[0x40];
    u8 *D;
    u8 *B;
    u8 *A;
    u8 *C;
    f32 t2;
    f32 t3;
    f32 t21;

    D = buf;
    B = buf + 0x10;
    A = buf + 0x20;
    C = buf + 0x30;

    t2 = fparg0 * fparg0;
    func_00312650(A, arg1 + 0x10, arg1);
    func_00312650(C, arg1 + 0x20, arg1 + 0x10);
    func_00312638(D, A, C);
    func_00312650(B, arg1 + 0x30, arg1 + 0x20);
    func_00312638(B, C, B);

    t3 = t2 * fparg0;
    func_00312680(D, D, 0.5f);
    func_00312680(B, B, 0.5f);

    t21 = t2 * 3.0f;
    func_00312680(A, arg1 + 0x10, ((t3 + t3) - t21) + 1.0f);
    func_00312680(D, D, (t3 - (t2 + t2)) + fparg0);
    func_00312680(B, B, t3 - t2);
    func_00312638(D, A, D);
    func_00312638(D, D, B);
    func_00312680(A, arg1 + 0x20, (t3 * -2.0f) + t21);
    func_00312638(arg0, A, D);
}

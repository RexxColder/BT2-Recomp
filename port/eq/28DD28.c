#include "common.h"

void Vec3_Copy(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 sceVu0InnerProduct(void *arg0, void *arg1);

/* Separating-axis test between two oriented boxes (0x190 bytes each, see include/battle/col_a.h):
 * half extents at +0x10, axes at +0x20 + 0x10*i, centre at +0. Returns 1 when no axis separates them. */
s32 ColObb_Overlaps(u8 *a, u8 *b) {
    f32 ha[4];
    f32 hb[4];
    f32 diff[4];
    f32 R[3][3];
    f32 absR[3][3];
    f32 d[3];
    f32 t;
    f32 rb;
    f32 sum;
    f32 ra;

    Vec3_Copy(ha, a + 0x10);
    Vec3_Copy(hb, b + 0x10);
    func_00312650(diff, a, b);

    R[0][0] = sceVu0InnerProduct(a + 0x20, b + 0x20);
    R[0][1] = sceVu0InnerProduct(a + 0x20, b + 0x30);
    R[0][2] = sceVu0InnerProduct(a + 0x20, b + 0x40);
    d[0] = sceVu0InnerProduct(a + 0x20, diff);
    absR[0][0] = __builtin_fabsf(R[0][0]);
    absR[0][1] = __builtin_fabsf(R[0][1]);
    absR[0][2] = __builtin_fabsf(R[0][2]);
    t = __builtin_fabsf(d[0]);
    rb = hb[0] * absR[0][0] + hb[1] * absR[0][1] + hb[2] * absR[0][2];
    sum = ha[0] + rb;
    if (t > sum) {
        return 0;
    }

    R[1][0] = sceVu0InnerProduct(a + 0x30, b + 0x20);
    R[1][1] = sceVu0InnerProduct(a + 0x30, b + 0x30);
    R[1][2] = sceVu0InnerProduct(a + 0x30, b + 0x40);
    d[1] = sceVu0InnerProduct(a + 0x30, diff);
    absR[1][0] = __builtin_fabsf(R[1][0]);
    absR[1][1] = __builtin_fabsf(R[1][1]);
    absR[1][2] = __builtin_fabsf(R[1][2]);
    t = __builtin_fabsf(d[1]);
    rb = hb[0] * absR[1][0] + hb[1] * absR[1][1] + hb[2] * absR[1][2];
    sum = ha[1] + rb;
    if (t > sum) {
        return 0;
    }

    R[2][0] = sceVu0InnerProduct(a + 0x40, b + 0x20);
    R[2][1] = sceVu0InnerProduct(a + 0x40, b + 0x30);
    R[2][2] = sceVu0InnerProduct(a + 0x40, b + 0x40);
    d[2] = sceVu0InnerProduct(a + 0x40, diff);
    absR[2][0] = __builtin_fabsf(R[2][0]);
    absR[2][1] = __builtin_fabsf(R[2][1]);
    absR[2][2] = __builtin_fabsf(R[2][2]);
    t = __builtin_fabsf(d[2]);
    rb = hb[0] * absR[2][0] + hb[1] * absR[2][1] + hb[2] * absR[2][2];
    sum = ha[2] + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(sceVu0InnerProduct(b + 0x20, diff));
    ra = ha[0] * absR[0][0] + ha[1] * absR[1][0] + ha[2] * absR[2][0];
    sum = ra + hb[0];
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(sceVu0InnerProduct(b + 0x30, diff));
    ra = ha[0] * absR[0][1] + ha[1] * absR[1][1] + ha[2] * absR[2][1];
    sum = ra + hb[1];
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(sceVu0InnerProduct(b + 0x40, diff));
    ra = ha[0] * absR[0][2] + ha[1] * absR[1][2] + ha[2] * absR[2][2];
    sum = ra + hb[2];
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[2] * R[1][0] - d[1] * R[2][0]);
    ra = ha[1] * absR[2][0] + ha[2] * absR[1][0];
    rb = hb[1] * absR[0][2] + hb[2] * absR[0][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[2] * R[1][1] - d[1] * R[2][1]);
    ra = ha[1] * absR[2][1] + ha[2] * absR[1][1];
    rb = hb[0] * absR[0][2] + hb[2] * absR[0][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[2] * R[1][2] - d[1] * R[2][2]);
    ra = ha[1] * absR[2][2] + ha[2] * absR[1][2];
    rb = hb[0] * absR[0][1] + hb[1] * absR[0][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[0] * R[2][0] - d[2] * R[0][0]);
    ra = ha[0] * absR[2][0] + ha[2] * absR[0][0];
    rb = hb[1] * absR[1][2] + hb[2] * absR[1][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[0] * R[2][1] - d[2] * R[0][1]);
    ra = ha[0] * absR[2][1] + ha[2] * absR[0][1];
    rb = hb[0] * absR[1][2] + hb[2] * absR[1][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[0] * R[2][2] - d[2] * R[0][2]);
    ra = ha[0] * absR[2][2] + ha[2] * absR[0][2];
    rb = hb[0] * absR[1][1] + hb[1] * absR[1][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[1] * R[0][0] - d[0] * R[1][0]);
    ra = ha[0] * absR[1][0] + ha[1] * absR[0][0];
    rb = hb[1] * absR[2][2] + hb[2] * absR[2][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[1] * R[0][1] - d[0] * R[1][1]);
    ra = ha[0] * absR[1][1] + ha[1] * absR[0][1];
    rb = hb[0] * absR[2][2] + hb[2] * absR[2][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }

    t = __builtin_fabsf(d[1] * R[0][2] - d[0] * R[1][2]);
    ra = ha[0] * absR[1][2] + ha[1] * absR[0][2];
    rb = hb[0] * absR[2][1] + hb[1] * absR[2][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    return 1;
}

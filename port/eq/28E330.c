#include "common.h"

extern f32 D_00387D88;
extern f32 D_00387104;
extern f32 D_00387108;
extern f32 D_0038710C;
extern f32 D_00387110;
extern f32 D_00387114;
extern f32 D_00387118;
extern f32 D_0038711C;
extern f32 D_00387120;
extern f32 D_00387124;
extern f32 D_00387128;
extern f32 D_0038712C;
extern f32 D_00387130;
extern f32 D_00387134;
extern f32 D_00387138;
extern f32 D_0038713C;
extern f32 D_00387140;
extern f32 D_00387144;
extern f32 D_00387148;
extern f32 D_0038714C;
extern f32 D_00387150;
extern f32 D_00387154;
extern f32 D_00387158;
extern f32 D_0038715C;
extern f32 D_00387160;
extern f32 D_00387164;
extern f32 D_00387168;
extern f32 D_0038716C;
extern f32 D_00387170;
extern f32 D_00387174;
extern f32 D_00387178;
extern f32 D_0038717C;
extern f32 D_00387180;
extern f32 D_00387184;

void func_00312650(u8 *out, u8 *a, u8 *b);
f32 sceVu0InnerProduct(u8 *a, u8 *b);
s32 Col_NearEq(f32 a, f32 b, f32 eps);
void sceVu0Normalize(f32 *out, f32 *in);
void Col_LineLineParams(f32 *s, f32 *t, u8 *pointC, u8 *dirA, u8 *pointD, u8 *dirB);

/* Edge-edge SAT axis k: num/den test, may return 0 (separated) or update the minimum depth. */
#define F(b, o) (*(f32 *)((b) + (o)))

#define EDGE_AXIS(k, eps, sqA, sqB, numExpr, bExpr, cqA, cqB, sepExpr) \
    do { \
        f32 num_ = __builtin_fabsf(numExpr); \
        f32 len_ = __builtin_sqrtf((sqA) * (sqA) + (sqB) * (sqB)); \
        f32 e_ = (eps); \
        s32 skip_ = Col_NearEq(__builtin_fabsf(bExpr), num_, e_); \
        skip_ |= Col_NearEq(len_, __builtin_sqrtf((cqA) * (cqA) + (cqB) * (cqB)), e_); \
        if (skip_ == 0) { \
            f32 q_; \
            if (len_ == 0.0f) { \
                len_ = e_; \
            } \
            q_ = ((sepExpr) - num_) / len_; \
            if (q_ != 0.0f) { \
                if (q_ < 0.0f) { \
                    return 0; \
                } \
                if (q_ < *depth) { \
                    *depth = q_; \
                    axis = (k); \
                } \
            } \
        } \
    } while (0)

/* Edge-edge contact for axis (6 + 3 * i + j): edge i of A against edge j of B.
 * ia/ib and ja/jb are the two other axes of A and B (increasing order). */
#define EDGE_CONTACT(i, ia, ib, j, ja, jb, sgnC0, sgnC4, sgnD0, sgnD4, tAx, facAa, facAb, constA, tBx, facBa, facBb, \
                     constB) \
    do { \
        s32 sC0_ = (sgnC0) ? 1 : -1; \
        s32 sC4_ = (sgnC4) ? 1 : -1; \
        s32 sD0_ = (sgnD0) ? 1 : -1; \
        s32 sD4_ = (sgnD4) ? 1 : -1; \
        f32 sA_[3]; \
        f32 sB_[3]; \
        f32 tA_ = (tAx); \
        f32 wAa_ = (facAa) * tA_; \
        f32 wAb_ = (facAb) * tA_; \
        f32 tB_; \
        f32 wBa_; \
        f32 wBb_; \
        f32 P1_[4]; \
        f32 P2_[4]; \
        f32 n_[4]; \
        f32 s_; \
        f32 t_; \
        u8 *dirA_ = boxA + 0x20 + (i) * 16; \
        u8 *dirB_ = boxB + 0x20 + (j) * 16; \
        s32 m_; \
        s32 c_; \
        sA_[ia] = (f32)sC0_; \
        sA_[ib] = (f32)sC4_; \
        sB_[ja] = (f32)sD0_; \
        sB_[jb] = (f32)sD4_; \
        if ((constA) < ((AE(ia) * sA_[ia]) * wAa_ + (AE(ib) * sA_[ib]) * wAb_)) { \
            for (c_ = 0; c_ < 3; c_++) { \
                f32 v_ = F(boxA, c_ * 4); \
                for (m_ = 0; m_ < 3; m_++) { \
                    if (m_ == (i)) { \
                        v_ = v_ + (-F(boxA, 0x20 + m_ * 16 + c_ * 4)) * AE(m_); \
                    } else { \
                        v_ = v_ + (F(boxA, 0x20 + m_ * 16 + c_ * 4) * AE(m_)) * sA_[m_]; \
                    } \
                } \
                P1_[c_] = v_; \
            } \
        } else { \
            for (c_ = 0; c_ < 3; c_++) { \
                f32 v_ = F(boxA, c_ * 4); \
                for (m_ = 0; m_ < 3; m_++) { \
                    if (m_ == (i)) { \
                        v_ = v_ + (-F(boxA, 0x20 + m_ * 16 + c_ * 4)) * AE(m_); \
                    } else { \
                        v_ = v_ + ((-F(boxA, 0x20 + m_ * 16 + c_ * 4)) * AE(m_)) * sA_[m_]; \
                    } \
                } \
                P1_[c_] = v_; \
            } \
        } \
        tB_ = (tBx); \
        wBa_ = (facBa) * tB_; \
        wBb_ = (facBb) * tB_; \
        if ((constB) < ((BE(ja) * sB_[ja]) * wBa_ + (BE(jb) * sB_[jb]) * wBb_)) { \
            for (c_ = 0; c_ < 3; c_++) { \
                f32 v_ = F(boxB, c_ * 4); \
                for (m_ = 0; m_ < 3; m_++) { \
                    if (m_ == (j)) { \
                        v_ = v_ + (-F(boxB, 0x20 + m_ * 16 + c_ * 4)) * BE(m_); \
                    } else { \
                        v_ = v_ + ((-F(boxB, 0x20 + m_ * 16 + c_ * 4)) * BE(m_)) * sB_[m_]; \
                    } \
                } \
                P2_[c_] = v_; \
            } \
        } else { \
            for (c_ = 0; c_ < 3; c_++) { \
                f32 v_ = F(boxB, c_ * 4); \
                for (m_ = 0; m_ < 3; m_++) { \
                    if (m_ == (j)) { \
                        v_ = v_ + (-F(boxB, 0x20 + m_ * 16 + c_ * 4)) * BE(m_); \
                    } else { \
                        v_ = v_ + (F(boxB, 0x20 + m_ * 16 + c_ * 4) * BE(m_)) * sB_[m_]; \
                    } \
                } \
                P2_[c_] = v_; \
            } \
        } \
        Col_LineLineParams(&s_, &t_, (u8 *)P1_, dirA_, (u8 *)P2_, dirB_); \
        point[0] = P1_[0] + F(dirA_, 0) * s_; \
        point[1] = P1_[1] + F(dirA_, 4) * s_; \
        point[2] = P1_[2] + F(dirA_, 8) * s_; \
        n_[0] = (P2_[0] + F(dirB_, 0) * t_) - point[0]; \
        n_[1] = (P2_[1] + F(dirB_, 4) * t_) - point[1]; \
        n_[2] = (P2_[2] + F(dirB_, 8) * t_) - point[2]; \
        sceVu0Normalize(normal, n_); \
        return 1; \
    } while (0)

/* 0x0028E330: OBB-OBB separating axis test (box = center +0, half extents +0x10, axes +0x20/+0x30/+0x40).
 * Returns 1 and fills normal (3 floats), point (3 floats) and *depth when boxes overlap, else 0. */
s32 func_0028E330(u8 *boxA, u8 *boxB, f32 *normal, f32 *point, f32 *depth) {
    f32 d[4];
    f32 R[9];
    f32 AR[9];
    f32 dA[3];
    f32 dB[3];
    f32 sep;
    s32 axis = -1;
    u8 *a0 = boxA + 0x20;
    u8 *a1 = boxA + 0x30;
    u8 *a2 = boxA + 0x40;
    u8 *b0 = boxB + 0x20;
    u8 *b1 = boxB + 0x30;
    u8 *b2 = boxB + 0x40;
#define AE(i) (*(f32 *)(boxA + 0x10 + (i) * 4))
#define BE(i) (*(f32 *)(boxB + 0x10 + (i) * 4))

    *depth = D_00387D88;
    func_00312650((u8 *)d, boxB, boxA);

    /* face axes of A */
    R[0] = sceVu0InnerProduct(a0, b0);
    R[1] = sceVu0InnerProduct(a0, b1);
    R[2] = sceVu0InnerProduct(a0, b2);
    dA[0] = sceVu0InnerProduct(a0, (u8 *)d);
    AR[0] = __builtin_fabsf(R[0]);
    AR[1] = __builtin_fabsf(R[1]);
    AR[2] = __builtin_fabsf(R[2]);
    sep = (AE(0) + ((BE(0) * AR[0] + BE(1) * AR[1]) + BE(2) * AR[2])) - __builtin_fabsf(dA[0]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 0;
    }

    R[3] = sceVu0InnerProduct(a1, b0);
    R[4] = sceVu0InnerProduct(a1, b1);
    R[5] = sceVu0InnerProduct(a1, b2);
    dA[1] = sceVu0InnerProduct(a1, (u8 *)d);
    AR[3] = __builtin_fabsf(R[3]);
    AR[4] = __builtin_fabsf(R[4]);
    AR[5] = __builtin_fabsf(R[5]);
    sep = (AE(1) + ((BE(0) * AR[3] + BE(1) * AR[4]) + BE(2) * AR[5])) - __builtin_fabsf(dA[1]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 1;
    }

    R[6] = sceVu0InnerProduct(a2, b0);
    R[7] = sceVu0InnerProduct(a2, b1);
    R[8] = sceVu0InnerProduct(a2, b2);
    dA[2] = sceVu0InnerProduct(a2, (u8 *)d);
    AR[6] = __builtin_fabsf(R[6]);
    AR[7] = __builtin_fabsf(R[7]);
    AR[8] = __builtin_fabsf(R[8]);
    sep = (AE(2) + ((BE(0) * AR[6] + BE(1) * AR[7]) + BE(2) * AR[8])) - __builtin_fabsf(dA[2]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 2;
    }

    /* face axes of B */
    dB[0] = sceVu0InnerProduct(b0, (u8 *)d);
    sep = (((AE(0) * AR[0] + AE(1) * AR[3]) + AE(2) * AR[6]) + BE(0)) - __builtin_fabsf(dB[0]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 3;
    }

    dB[1] = sceVu0InnerProduct(b1, (u8 *)d);
    sep = (((AE(0) * AR[1] + AE(1) * AR[4]) + AE(2) * AR[7]) + BE(1)) - __builtin_fabsf(dB[1]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 4;
    }

    dB[2] = sceVu0InnerProduct(b2, (u8 *)d);
    sep = (((AE(0) * AR[2] + AE(1) * AR[5]) + AE(2) * AR[8]) + BE(2)) - __builtin_fabsf(dB[2]);
    if (sep < 0.0f) {
        return 0;
    }
    if (sep < *depth) {
        *depth = sep;
        axis = 5;
    }

    /* edge-edge axes */
    EDGE_AXIS(6, D_00387104, R[2], R[1], dA[2] * R[3] - dA[1] * R[6], dB[1] * R[2] - dB[2] * R[1], R[2], R[1],
              (AE(1) * AR[6] + AE(2) * AR[3]) + (BE(1) * AR[2] + BE(2) * AR[1]));
    EDGE_AXIS(7, D_00387108, R[7], R[4], dA[2] * R[4] - dA[1] * R[7], dB[0] * R[2] - dB[2] * R[0], R[2], R[0],
              (AE(1) * AR[7] + AE(2) * AR[4]) + (BE(0) * AR[2] + BE(2) * AR[0]));
    EDGE_AXIS(8, D_0038710C, R[8], R[5], dA[2] * R[5] - dA[1] * R[8], dB[0] * R[1] - dB[1] * R[0], R[1], R[0],
              (AE(1) * AR[8] + AE(2) * AR[5]) + (BE(0) * AR[1] + BE(1) * AR[0]));
    EDGE_AXIS(9, D_00387110, R[6], R[0], dA[0] * R[6] - dA[2] * R[0], dB[1] * R[5] - dB[2] * R[4], R[5], R[4],
              (AE(0) * AR[6] + AE(2) * AR[0]) + (BE(1) * AR[5] + BE(2) * AR[4]));
    EDGE_AXIS(10, D_00387114, R[7], R[1], dA[0] * R[7] - dA[2] * R[1], dB[0] * R[5] - dB[2] * R[3], R[5], R[3],
              (AE(0) * AR[7] + AE(2) * AR[1]) + (BE(0) * AR[5] + BE(2) * AR[3]));
    EDGE_AXIS(11, D_00387118, R[8], R[2], dA[0] * R[8] - dA[2] * R[2], dB[0] * R[4] - dB[1] * R[3], R[4], R[3],
              (AE(0) * AR[8] + AE(2) * AR[2]) + (BE(0) * AR[4] + BE(1) * AR[3]));
    EDGE_AXIS(12, D_0038711C, R[3], R[0], dA[1] * R[0] - dA[0] * R[3], dB[1] * R[8] - dB[2] * R[7], R[8], R[7],
              (AE(0) * AR[3] + AE(1) * AR[0]) + (BE(1) * AR[8] + BE(2) * AR[7]));
    EDGE_AXIS(13, D_00387120, R[4], R[1], dA[1] * R[1] - dA[0] * R[4], dB[0] * R[8] - dB[2] * R[6], R[8], R[6],
              (AE(0) * AR[4] + AE(1) * AR[1]) + (BE(0) * AR[8] + BE(2) * AR[6]));
    EDGE_AXIS(14, D_00387124, R[5], R[2], dA[1] * R[2] - dA[0] * R[5], dB[0] * R[7] - dB[1] * R[6], R[7], R[6],
              (AE(0) * AR[5] + AE(1) * AR[2]) + (BE(0) * AR[7] + BE(1) * AR[6]));
    if (axis < 3) {
        /* contact on a face of A: reference face normal, incident point on B */
        s32 sg[3];
        f32 sf0, sf1, sf2;
        u8 *ax = boxA + 0x20 + axis * 16;

        sg[0] = (D_00387128 < R[axis * 3]) ? 1 : -1;
        sg[1] = (D_0038712C < R[axis * 3 + 1]) ? 1 : -1;
        sg[2] = (D_00387130 < R[axis * 3 + 2]) ? 1 : -1;
        sf0 = (f32)sg[0];
        sf1 = (f32)sg[1];
        sf2 = (f32)sg[2];
        if (0.0f < dA[axis]) {
            normal[0] = -F(ax, 0);
            normal[1] = -F(ax, 4);
            normal[2] = -F(ax, 8);
            point[0] = ((F(boxB, 0) - (sf0 * F(boxB, 0x20)) * BE(0)) - (sf1 * F(boxB, 0x30)) * BE(1)) -
                       (sf2 * F(boxB, 0x40)) * BE(2);
            point[1] = ((F(boxB, 4) - (sf0 * F(boxB, 0x24)) * BE(0)) - (sf1 * F(boxB, 0x34)) * BE(1)) -
                       (sf2 * F(boxB, 0x44)) * BE(2);
            point[2] = ((F(boxB, 8) - (sf0 * F(boxB, 0x28)) * BE(0)) - (sf1 * F(boxB, 0x38)) * BE(1)) -
                       (sf2 * F(boxB, 0x48)) * BE(2);
        } else {
            normal[0] = F(ax, 0);
            normal[1] = F(ax, 4);
            normal[2] = F(ax, 8);
            point[0] = ((F(boxB, 0) + (sf0 * F(boxB, 0x20)) * BE(0)) + (sf1 * F(boxB, 0x30)) * BE(1)) +
                       (sf2 * F(boxB, 0x40)) * BE(2);
            point[1] = ((F(boxB, 4) + (sf0 * F(boxB, 0x24)) * BE(0)) + (sf1 * F(boxB, 0x34)) * BE(1)) +
                       (sf2 * F(boxB, 0x44)) * BE(2);
            point[2] = ((F(boxB, 8) + (sf0 * F(boxB, 0x28)) * BE(0)) + (sf1 * F(boxB, 0x38)) * BE(1)) +
                       (sf2 * F(boxB, 0x48)) * BE(2);
        }
        return 1;
    }
    if (axis < 6) {
        /* contact on a face of B: reference face normal, incident point on A */
        s32 sg[3];
        f32 sf0, sf1, sf2;
        f32 dot;
        u8 *ax = boxB + axis * 16 - 0x10;

        sg[0] = (D_00387134 < R[axis - 3]) ? 1 : -1;
        sg[1] = (D_00387138 < R[axis]) ? 1 : -1;
        sg[2] = (D_0038713C < R[axis + 3]) ? 1 : -1;
        dot = sceVu0InnerProduct(ax, (u8 *)d);
        sf0 = (f32)sg[0];
        sf1 = (f32)sg[1];
        sf2 = (f32)sg[2];
        if (0.0f < dot) {
            normal[0] = -F(ax, 0);
            normal[1] = -F(ax, 4);
            normal[2] = -F(ax, 8);
            point[0] = ((F(boxA, 0) + (sf0 * F(boxA, 0x20)) * AE(0)) + (sf1 * F(boxA, 0x30)) * AE(1)) +
                       (sf2 * F(boxA, 0x40)) * AE(2);
            point[1] = ((F(boxA, 4) + (sf0 * F(boxA, 0x24)) * AE(0)) + (sf1 * F(boxA, 0x34)) * AE(1)) +
                       (sf2 * F(boxA, 0x44)) * AE(2);
            point[2] = ((F(boxA, 8) + (sf0 * F(boxA, 0x28)) * AE(0)) + (sf1 * F(boxA, 0x38)) * AE(1)) +
                       (sf2 * F(boxA, 0x48)) * AE(2);
        } else {
            normal[0] = F(ax, 0);
            normal[1] = F(ax, 4);
            normal[2] = F(ax, 8);
            point[0] = ((F(boxA, 0) - (sf0 * F(boxA, 0x20)) * AE(0)) - (sf1 * F(boxA, 0x30)) * AE(1)) -
                       (sf2 * F(boxA, 0x40)) * AE(2);
            point[1] = ((F(boxA, 4) - (sf0 * F(boxA, 0x24)) * AE(0)) - (sf1 * F(boxA, 0x34)) * AE(1)) -
                       (sf2 * F(boxA, 0x44)) * AE(2);
            point[2] = ((F(boxA, 8) - (sf0 * F(boxA, 0x28)) * AE(0)) - (sf1 * F(boxA, 0x38)) * AE(1)) -
                       (sf2 * F(boxA, 0x48)) * AE(2);
        }
        return 1;
    }
    switch (axis) {
    case 6:
        EDGE_CONTACT(0, 1, 2, 0, 1, 2, R[6] < 0.0f, 0.0f < R[3], R[2] < 0.0f, 0.0f < R[1],
                     (-R[6]) * dA[1] + R[3] * dA[2], -R[6], R[3], D_00387140,
                     (-R[2]) * dB[1] + R[1] * dB[2], -R[2], R[1], D_00387144);
    case 7:
        EDGE_CONTACT(0, 1, 2, 1, 0, 2, R[7] < 0.0f, 0.0f < R[4], 0.0f < R[2], R[0] < 0.0f,
                     (-R[7]) * dA[1] + R[4] * dA[2], -R[7], R[4], D_00387148,
                     R[2] * dB[0] - R[0] * dB[2], R[2], -R[0], D_0038714C);
    case 8:
        EDGE_CONTACT(0, 1, 2, 2, 0, 1, R[8] < 0.0f, 0.0f < R[5], R[1] < 0.0f, 0.0f < R[0],
                     (-R[8]) * dA[1] + R[5] * dA[2], -R[8], R[5], D_00387150,
                     (-R[1]) * dB[0] + R[0] * dB[1], -R[1], R[0], D_00387154);
    case 9:
        EDGE_CONTACT(1, 0, 2, 0, 1, 2, 0.0f < R[6], R[0] < 0.0f, R[5] < 0.0f, 0.0f < R[4],
                     R[6] * dA[0] - R[0] * dA[2], R[6], -R[0], D_00387158,
                     (-R[5]) * dB[1] + R[4] * dB[2], -R[5], R[4], D_0038715C);
    case 10:
        EDGE_CONTACT(1, 0, 2, 1, 0, 2, 0.0f < R[7], R[1] < 0.0f, 0.0f < R[5], R[3] < 0.0f,
                     R[7] * dA[0] - R[1] * dA[2], R[7], -R[1], D_00387160,
                     R[5] * dB[0] - R[3] * dB[2], R[5], -R[3], D_00387164);
    case 11:
        EDGE_CONTACT(1, 0, 2, 2, 0, 1, 0.0f < R[8], R[2] < 0.0f, R[4] < 0.0f, 0.0f < R[3],
                     R[8] * dA[0] - R[2] * dA[2], R[8], -R[2], D_00387168,
                     (-R[4]) * dB[0] + R[3] * dB[1], -R[4], R[3], D_0038716C);
    case 12:
        EDGE_CONTACT(2, 0, 1, 0, 1, 2, R[3] < 0.0f, 0.0f < R[0], R[8] < 0.0f, 0.0f < R[7],
                     (-R[3]) * dA[0] + R[0] * dA[1], -R[3], R[0], D_00387170,
                     (-R[8]) * dB[1] + R[7] * dB[2], -R[8], R[7], D_00387174);
    case 13:
        EDGE_CONTACT(2, 0, 1, 1, 0, 2, R[4] < 0.0f, 0.0f < R[1], 0.0f < R[8], R[6] < 0.0f,
                     (-R[4]) * dA[0] + R[1] * dA[1], -R[4], R[1], D_00387178,
                     R[8] * dB[0] - R[6] * dB[2], R[8], -R[6], D_0038717C);
    case 14:
        EDGE_CONTACT(2, 0, 1, 2, 0, 1, R[5] < 0.0f, 0.0f < R[2], R[7] < 0.0f, 0.0f < R[6],
                     (-R[5]) * dA[0] + R[2] * dA[1], -R[5], R[2], D_00387180,
                     (-R[7]) * dB[0] + R[6] * dB[1], -R[7], R[6], D_00387184);
    default:
        break;
    }
    return 1;
}
#undef AE
#undef BE

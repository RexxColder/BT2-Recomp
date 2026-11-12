/*
 * libvu0 del SDK (0x312418..0x313000): matematica de vectores/matrices del EE en C. Escrito a partir del desensamblado
 * de SLUS_214.41 (convencion de filas: dst.fila_i = suma_j a[i][j] * b.fila_j). Punteros del juego = u32.
 */
#include <math.h>
#include <stdint.h>
#include <string.h>

typedef uint32_t u32;
typedef int32_t s32;
#define P(a) ((float *)(uintptr_t)(a))

static s32 ftoi(float f, int shift) {
    double d = (double)f * (double)(1 << shift);
    if (d != d) return 0;
    if (d >= 2147483647.0) return 0x7FFFFFFF;
    if (d <= -2147483648.0) return (s32)0x80000000;
    return (s32)d;
}
static void rowmul(float *d, const float *v, const float *m) { /* d = v.x*m0 + v.y*m1 + v.z*m2 + v.w*m3 */
    float r[4]; int i;
    for (i = 0; i < 4; i++) r[i] = v[0] * m[i] + v[1] * m[4 + i] + v[2] * m[8 + i] + v[3] * m[12 + i];
    memcpy(d, r, 16);
}
static void mulm(float *d, const float *a1, const float *a2) { /* d.fila_i = a2.fila_i * a1 */
    float r[16]; int i;
    for (i = 0; i < 4; i++) rowmul(r + 4 * i, a2 + 4 * i, a1);
    memcpy(d, r, 64);
}
void sceVu0UnitMatrix(u32 m) { float *d = P(m); memset(d, 0, 64); d[0] = d[5] = d[10] = d[15] = 1.0f; }
void sceVu0CopyMatrix(u32 d, u32 s) { memmove(P(d), P(s), 64); }
void sceVu0TransMatrix(u32 d, u32 m, u32 tv) {
    float t[4], r[16]; memcpy(t, P(tv), 16); memcpy(r, P(m), 64);
    r[12] += t[0]; r[13] += t[1]; r[14] += t[2];
    memcpy(P(d), r, 64);
}
void sceVu0MulMatrix(u32 d, u32 a1, u32 a2) { mulm(P(d), P(a1), P(a2)); }
void sceVu0ApplyMatrix(u32 d, u32 m, u32 v) { float t[4]; memcpy(t, P(v), 16); rowmul(P(d), t, P(m)); }
float sceVu0InnerProduct(u32 a, u32 b) { float *x = P(a), *y = P(b); return x[0] * y[0] + x[1] * y[1] + x[2] * y[2]; }
void sceVu0Normalize(u32 d, u32 s) {
    float v[4], r[4], l; memcpy(v, P(s), 16);
    l = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    l = l != 0.0f ? 1.0f / l : 0.0f;
    r[0] = v[0] * l; r[1] = v[1] * l; r[2] = v[2] * l; r[3] = 0.0f;
    memcpy(P(d), r, 16);
}
void sceVu0InversMatrix(u32 d, u32 s) {
    float m[16], r[16], t[4]; memcpy(m, P(s), 64);
    memcpy(t, m + 12, 16);
    r[0] = m[0]; r[1] = m[4]; r[2] = m[8]; r[3] = 0;
    r[4] = m[1]; r[5] = m[5]; r[6] = m[9]; r[7] = 0;
    r[8] = m[2]; r[9] = m[6]; r[10] = m[10]; r[11] = 0;
    r[12] = -(t[0] * r[0] + t[1] * r[4] + t[2] * r[8]);
    r[13] = -(t[0] * r[1] + t[1] * r[5] + t[2] * r[9]);
    r[14] = -(t[0] * r[2] + t[1] * r[6] + t[2] * r[10]);
    r[15] = t[3];
    memcpy(P(d), r, 64);
}
static void rot(u32 d, u32 s, const float *M) { float r[16]; memcpy(r, P(s), 64); { int i; for (i = 0; i < 4; i++) rowmul(r + 4 * i, r + 4 * i, M); } memcpy(P(d), r, 64); }
void sceVu0RotMatrixZ(u32 d, u32 s, float a) { float c = cosf(a), sn = sinf(a), M[16] = { c, sn, 0, 0, -sn, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; rot(d, s, M); }
void sceVu0RotMatrixX(u32 d, u32 s, float a) { float c = cosf(a), sn = sinf(a), M[16] = { 1, 0, 0, 0, 0, c, sn, 0, 0, -sn, c, 0, 0, 0, 0, 1 }; rot(d, s, M); }
void sceVu0RotMatrixY(u32 d, u32 s, float a) { float c = cosf(a), sn = sinf(a), M[16] = { c, 0, -sn, 0, 0, 1, 0, 0, sn, 0, c, 0, 0, 0, 0, 1 }; rot(d, s, M); }
void sceVu0RotMatrix(u32 d, u32 s, u32 rv) {
    float *r = P(rv);
    sceVu0RotMatrixZ(d, s, r[2]); sceVu0RotMatrixY(d, d, r[1]); sceVu0RotMatrixX(d, d, r[0]);
}
void sceVu0ClampVector(u32 d, u32 s, float mn, float mx) {
    float v[4]; int i; memcpy(v, P(s), 16);
    for (i = 0; i < 4; i++) { if (v[i] < mn) v[i] = mn; if (v[i] > mx) v[i] = mx; }
    memcpy(P(d), v, 16);
}
void sceVu0InterVector(u32 d, u32 a, u32 b, float t) {
    float x[4], y[4], r[4]; int i; memcpy(x, P(a), 16); memcpy(y, P(b), 16);
    for (i = 0; i < 4; i++) r[i] = x[i] * t + y[i] * (1.0f - t);
    memcpy(P(d), r, 16);
}
void sceVu0InterVectorXYZ(u32 d, u32 a, u32 b, float t) {
    float x[4], y[4], r[4]; int i; memcpy(x, P(a), 16); memcpy(y, P(b), 16);
    for (i = 0; i < 3; i++) r[i] = x[i] * t + y[i] * (1.0f - t);
    r[3] = x[3];
    memcpy(P(d), r, 16);
}
void sceVu0NormalLightMatrix(u32 d, u32 l0, u32 l1, u32 l2) {
    float *m = P(d), t[4]; u32 ls[3] = { l0, l1, l2 }; int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) t[j] = P(ls[i])[j] * -1.0f;
        memcpy(m + 4 * i, t, 16);
        sceVu0Normalize((u32)(uintptr_t)(m + 4 * i), (u32)(uintptr_t)(m + 4 * i));
    }
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    { float r[16]; for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) r[4 * i + j] = m[4 * j + i]; memcpy(m, r, 64); }
}
void sceVu0ViewScreenMatrix(u32 d, float scrz, float ax, float ay, float cx, float cy, float zmin, float zmax, float nearz, float farz) {
    float *m = P(d), t[16], c0 = zmax - zmin, a = farz * nearz * c0, b = -zmax * nearz + zmin * farz, dv = farz - nearz;
    a /= dv; b /= dv;
    memset(m, 0, 64); m[0] = m[5] = scrz; m[10] = 0; m[15] = 0; m[11] = 1; m[14] = 1;
    memset(t, 0, 64); t[0] = ax; t[5] = ay; t[10] = a; t[12] = cx; t[13] = cy; t[14] = b; t[15] = 1;
    mulm(m, t, m);
}
static void rtp(s32 *o, const float *m, const float *v, int fl) {
    float r[4], q; int i;
    for (i = 0; i < 4; i++) r[i] = v[0] * m[i] + v[1] * m[4 + i] + v[2] * m[8 + i] + v[3] * m[12 + i];
    q = r[3] != 0.0f ? 1.0f / r[3] : 0.0f;
    r[0] *= q; r[1] *= q; r[2] *= q;
    o[0] = ftoi(r[0], 4); o[1] = ftoi(r[1], 4);
    o[2] = fl ? ftoi(r[2], 0) : ftoi(r[2], 4);
    o[3] = fl ? ftoi(r[3], 0) : ftoi(r[3], 4);
}
void sceVu0RotTransPers(u32 d, u32 m, u32 v, s32 fl) { rtp((s32 *)P(d), P(m), P(v), fl); }
void sceVu0RotTransPersN(u32 d, u32 m, u32 v, s32 n, s32 fl) { s32 i; for (i = 0; i < n; i++) rtp((s32 *)P(d) + 4 * i, P(m), P(v) + 4 * i, fl); }
void sceVu0DropShadowMatrix(u32 d, u32 lv, s32 mode, float px, float py, float pz) {
    float *m = P(d), *l = P(lv); (void)mode;
    /* proyeccion de sombras sobre un plano: aproximacion (no aparece hasta combate) */
    (void)l; (void)px; (void)py; (void)pz;
    sceVu0UnitMatrix(d);
}

/* ---- funciones de libvu0 sin nombre en el SDK de BT2 (0x312490..0x312FB0), leidas del desensamblado ---- */
void func_00312490(u32 d, u32 a, u32 b) {   /* OuterProduct: producto vectorial xyz, w = 0 */
    float x[4], y[4], r[4]; memcpy(x, P(a), 16); memcpy(y, P(b), 16);
    r[0] = x[1] * y[2] - x[2] * y[1]; r[1] = x[2] * y[0] - x[0] * y[2]; r[2] = x[0] * y[1] - x[1] * y[0]; r[3] = 0.0f;
    memcpy(P(d), r, 16);
}
void func_00312518(u32 d, u32 s) {   /* TransposeMatrix */
    float m[16], r[16]; int i, j; memcpy(m, P(s), 64);
    for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) r[4 * i + j] = m[4 * j + i];
    memcpy(P(d), r, 64);
}
void func_003125D0(u32 d, u32 s, float f) { float v[4], q = 1.0f / f; int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) v[i] *= q; memcpy(P(d), v, 16); }   /* DivVector */
void func_003125F0(u32 d, u32 s, float f) { float v[4], q = 1.0f / f; int i; memcpy(v, P(s), 16); for (i = 0; i < 3; i++) v[i] *= q; memcpy(P(d), v, 16); }   /* DivVectorXYZ */
static void vop3(u32 d, u32 a, u32 b, int op) { float x[4], y[4], r[4]; int i; memcpy(x, P(a), 16); memcpy(y, P(b), 16); for (i = 0; i < 4; i++) r[i] = op == 0 ? x[i] + y[i] : op == 1 ? x[i] - y[i] : x[i] * y[i]; memcpy(P(d), r, 16); }
void func_00312638(u32 d, u32 a, u32 b) { vop3(d, a, b, 0); }   /* AddVector */
void func_00312650(u32 d, u32 a, u32 b) { vop3(d, a, b, 1); }   /* SubVector */
void func_00312668(u32 d, u32 a, u32 b) { vop3(d, a, b, 2); }   /* MulVector */
void func_00312680(u32 d, u32 s, float f) { float v[4]; int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) v[i] *= f; memcpy(P(d), v, 16); }   /* ScaleVector */
void func_003126C8(u32 d, u32 s) { memmove(P(d), P(s), 16); }   /* CopyVector */
void func_00312700(u32 d, u32 s) { float v[4]; s32 *o = (s32 *)P(d); int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) o[i] = ftoi(v[i], 4); }   /* FTOI4 */
void func_00312710(u32 d, u32 s) { float v[4]; s32 *o = (s32 *)P(d); int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) o[i] = ftoi(v[i], 0); }   /* FTOI0 */
void func_00312720(u32 d, u32 s) { s32 v[4]; float *o = P(d); int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) o[i] = (float)v[i] / 16.0f; }   /* ITOF4 */
void func_00312730(u32 d, u32 s) { s32 v[4]; float *o = P(d); int i; memcpy(v, P(s), 16); for (i = 0; i < 4; i++) o[i] = (float)v[i]; }   /* ITOF0 */
void func_00312A50(u32 d, u32 pos, u32 zdir, u32 up) {   /* CameraMatrix: sceVu0CameraMatrix(m, p, zd, yd) */
    float sp[48] __attribute__((aligned(16)));
    u32 a = (u32)(uintptr_t)sp;
    sceVu0UnitMatrix(a);
    func_00312490(a + 0x40, up, zdir);
    sceVu0Normalize(a, a + 0x40);
    sceVu0Normalize(a + 0x20, zdir);
    func_00312490(a + 0x10, a + 0x20, a);
    sceVu0TransMatrix(a, a, pos);
    sceVu0InversMatrix(d, a);
}
void func_00312BC0(u32 d, u32 r0, u32 r1, u32 r2, u32 r3) { func_003126C8(d, r0); func_003126C8(d + 0x10, r1); func_003126C8(d + 0x20, r2); func_003126C8(d + 0x30, r3); }   /* SetMatrixRows */
void func_00312FB0(u32 d, u32 s, float f) { float v[4]; int i; memcpy(v, P(s), 16); for (i = 0; i < 3; i++) v[i] *= f; memcpy(P(d), v, 16); }   /* ScaleVectorXYZ */

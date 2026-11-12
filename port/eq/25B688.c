#include "common.h"

/* F2 (widescreen): el renderer estira el cuadro 512x448 al aspecto pedido; para que el 3D no se
   estire, la proyeccion abre el FOV horizontal por el mismo factor que el narrowing 2D
   (1333.333/aspect). Es el equivalente en BT2 del Port_WideFactor de BT3. */
extern int Port_IsWide(void);
extern int Port_AspectMilli(void);

void func_0025AFE0(void *a0, void *a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19, f32 f20, f32 f21);

void func_0025B688(void *arg0, void *arg1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19, f32 f20, f32 f21) {
    u8 *v0 = (u8 *)arg0;
    f32 *src = (f32 *)arg1;
    f32 f1v;
    f32 f0v;

    *(f32 *)(v0 + 0x210) = src[0];
    *(f32 *)(v0 + 0x214) = src[1];
    *(f32 *)(v0 + 0x218) = src[2];
    *(f32 *)(v0 + 0x21C) = src[3];
    *(f32 *)(v0 + 0x224) = f12;
    *(f32 *)(v0 + 0x230) = f15;
    *(f32 *)(v0 + 0x234) = f16;
    *(f32 *)(v0 + 0x238) = f17;
    *(f32 *)(v0 + 0x23C) = f18;
    *(f32 *)(v0 + 0x240) = f19;
    *(f32 *)(v0 + 0x244) = f20;
    *(f32 *)(v0 + 0x248) = f21;
    *(f32 *)(v0 + 0x228) = f13;
    *(f32 *)(v0 + 0x22C) = f14;
    if (1.0f < f13) {
        *(f32 *)(v0 + 0x228) = 1.0f;
        *(f32 *)(v0 + 0x22C) = f14 / f13;
    }
    f1v = *(f32 *)(v0 + 0x22C);
    if (1.0f < f1v) {
        f0v = *(f32 *)(v0 + 0x228);
        *(f32 *)(v0 + 0x22C) = 1.0f;
        *(f32 *)(v0 + 0x228) = f0v / f1v;
    }
    if (Port_IsWide()) {
        *(f32 *)(v0 + 0x228) *= 1333.333f / (float)Port_AspectMilli();
    }
    func_0025AFE0(arg0, arg1, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21);
}

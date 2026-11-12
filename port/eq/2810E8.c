#include "common.h"

void func_00284818(s32 arg0);
void func_00284530(s32 arg0, s32 arg1);
s32 func_0025AB48(s32 arg0);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
void func_00285028(s32 arg0, s32 arg1);
void func_00282640(s32 arg0, s32 arg1);
void func_0027BA08(void);
void func_0027BBA0(void);
s32 func_00126560(s32 arg0);
extern u8 *D_00387AFC;
extern u8 *D_003876A0;
extern u8 *gBtlCam;
extern s32 gBtlCamView;

void func_002810E8(void) {
    s32 sp[16];
    s32 B;
    s32 P;
    s32 C;
    s32 Q;
    s64 v3;
    s64 v2;
    f32 f0;
    f32 f1;

    B = (s32)D_00387AFC;
    if (*(u8 *)(B + 0x3CCA) != 0) {
        return;
    }
    if (*(u8 *)(B + 0x3CC0) != 0) {
        func_00284818(B + 0x2040);
    }
    P = (s32)D_003876A0;
    C = (s32)gBtlCam;
    v3 = *(s64 *)(P + 0x4D8);
    if ((v3 & 3) != 0) {
        if ((v3 & 2) != 0) {
            func_00284530(1, 0);
            func_00284530(1, 1);
        } else {
            func_00284530(0, *(s32 *)(*(s32 *)(C + 0x600) + 0x250));
        }
    }

L281164:
    if (*(u8 *)(B + 0x3CC1) == 0) {
        v3 = *(s64 *)(P + 0x4D8);
        goto L281270;
    }
    v3 = *(s64 *)(P + 0x4D8);
    if ((v3 & 3) == 0) {
        goto L281324;
    }
    if ((v3 & 2) == 0) {
        goto L281228;
    }
    if (func_0025AB48(P) == 0) {
        goto L2811C8;
    }

L28119C:
    sceVu0InversMatrix((s32)sp, gBtlCamView);
    f1 = *(f32 *)((u8 *)sp + 0x34);

L2811AC:
    f0 = *(f32 *)(B + 0x3CC4);
    if (f0 < f1) {
        func_00285028(0, 0);
    }
    goto L28126C;

L2811C8:
    Q = *(s32 *)(C + 0x600);
    if (*(s32 *)(Q + 0x258) != 0) {
        goto L2811E0;
    }
    f1 = *(f32 *)(Q + 0x274);
    goto L2811AC;

L2811E0:
    f1 = *(f32 *)(C + 0x274);
    f0 = *(f32 *)(B + 0x3CC4);
    if (f0 < f1) {
        func_00285028(1, 0);
    }
    f1 = *(f32 *)(B + 0x3CC4);
    f0 = *(f32 *)(C + 0x574);
    if (f1 < f0) {
        func_00285028(1, 1);
    }
    goto L28126C;

L281228:
    if (func_0025AB48(P) != 0) {
        goto L28119C;
    }
    Q = *(s32 *)(C + 0x600);
    f1 = *(f32 *)(B + 0x3CC4);
    f0 = *(f32 *)(Q + 0x274);
    if (f1 < f0) {
        func_00285028(0, 0);
    }
    goto L28126C;

L2812E0:
    if (func_0025AB48(P) == 0) {
        func_00282640(0, *(s32 *)(*(s32 *)(C + 0x600) + 0x250));
    } else {
        func_00282640(0, 0);
    }
    goto L281310;

L28126C:
    v3 = *(s64 *)(P + 0x4D8);

L281270:
    if ((v3 & 3) == 0) {
        goto L281324;
    }
    if ((v3 & 2) == 0) {
        goto L2812E0;
    }
    if (func_0025AB48(P) != 0) {
        func_00282640(0, 0);
        goto L281310;
    }
    Q = *(s32 *)(C + 0x600);
    if (*(s32 *)(Q + 0x258) != 0) {
        func_00282640(1, 0);
        func_00282640(1, 1);
    } else {
        func_00282640(0, *(s32 *)(Q + 0x250));
    }

L281310:
    func_0027BA08();
    func_0027BBA0();

L281324:
    v2 = *(s64 *)(P + 0x4D8);
    if ((v2 & ((s64)0x8000 << 22)) != 0) {
        goto L28134C;
    }
    if (func_00126560(P) == 0) {
        return;
    }

L28134C:
    func_00282640(0, 0);
}

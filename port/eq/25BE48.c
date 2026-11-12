#include "common.h"

void *memset(void *dst, int c, unsigned int n);
void func_0025BCD8(void);
void func_0025C6B8(void);
void func_0025CB50(f32 a0, f32 a1, f32 a2);
void func_0025CB70(f32 a0, f32 a1, f32 a2);
void func_0025CB90(f32 a0);
extern u8 *gBtlCam;
extern f32 D_00386E0C;

void func_0025BE48(void) {
    memset(gBtlCam, 0, 0x610);
    func_0025BCD8();
    *(s32 *)(gBtlCam + 0x600) = (s32)gBtlCam;
    func_0025C6B8();
    func_0025CB50(0.0f, -15.0f, 0.0f);
    func_0025CB70(0.0f, D_00386E0C, 0.0f);
    func_0025CB90(50.0f);
}

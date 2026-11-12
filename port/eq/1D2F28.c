#include "common.h"

void sceVu0TransposeMatrix(void *arg0, void *arg1);
void func_001D3288(void);
void func_001D4C30(void);
void func_001D52E8(void);
void func_001D5958(void);
void func_001D6088(void);
void func_001D6868(void);
void func_001D6E30(void);
void func_001D7598(void);
void func_001D7B50(void);
extern u8 *D_00387E9C;
extern u8 *gBtlCamView;

/* 0x001D2F28: when byte +0x1490 of D_00387E9C is set: transpose gBtlCamView into +0x1450, clear the floats
 * +0x1480, +0x1484, +0x1488, then run the eight stages func_001D3288 .. func_001D7598 and tail-call func_001D7B50. */
void func_001D2F28(void) {
    if (D_00387E9C[0x1490] == 0) {
        return;
    }
    sceVu0TransposeMatrix(D_00387E9C + 0x1450, gBtlCamView);
    *(f32 *)(D_00387E9C + 0x1480) = 0.0f;
    *(f32 *)(D_00387E9C + 0x1488) = 0.0f;
    *(f32 *)(D_00387E9C + 0x1484) = 0.0f;
    func_001D3288();
    func_001D4C30();
    func_001D52E8();
    func_001D5958();
    func_001D6088();
    func_001D6868();
    func_001D6E30();
    func_001D7598();
    func_001D7B50();
}

#include "common.h"

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00112B28(s32 arg0);
void func_0010CFE0(void);
void func_0010FAC0(s32 arg0);
void func_0010D3A0(s32 arg0);
void func_0010DD40(s32 arg0);
void func_0010EA90(s32 arg0);
s32 BtlObjVis_GetView(s32 arg0);
void func_0010FF18(s32 arg0, s32 arg1);
void func_00110258(s32 arg0);
void func_00110570(s32 arg0);
void func_001103F0(s32 arg0, s32 arg1);
void func_00110AD8(s32 arg0);

void func_00111008(void) {
    u8 *s2;
    s32 s0;

    s2 = (u8 *)func_0010B078();
    func_00112B28(*(s32 *)((u8 *)func_0010B080() + 8));
    func_0010CFE0();

    for (s0 = 0; s0 < 2; s0++) {
        if (*(s32 *)(s2 + 0x818 + 0x750 * s0) >= -0xFF) {
            func_0010FAC0(s0);
            func_0010D3A0(s0);
            func_0010DD40(s0);
            func_0010EA90(s0);
        }
    }

    for (s0 = 0; s0 < 2; s0++) {
        if (*(s32 *)(s2 + 0x818 + 0x750 * s0) >= -0xFF) {
            func_0010FF18(s0, BtlObjVis_GetView(s0));
        }
    }

    for (s0 = 0; s0 < 2; s0++) {
        if (*(s32 *)(s2 + 0x800 + 0x750 * s0) >= -0x7F) {
            func_00110258(s0);
            func_00110570(s0);
            func_001103F0(s0, BtlObjVis_GetView(s0));
            func_00110AD8(s0);
        }
    }
}

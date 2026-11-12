#include "common.h"

s32 Ot_Align64(s32 arg0);
extern u8 *D_0038790C;

s32 func_001EBFF0(void) {
    s32 var_s0;

    var_s0 = 0;
    if (*(s32 *)(D_0038790C + 0x68) & 2) {
        var_s0 = Ot_Align64(0xA000);
    }
    if (*(s32 *)(D_0038790C + 0x68) & 4) {
        var_s0 += Ot_Align64(0x1F4000);
    }
    if (*(s32 *)(D_0038790C + 0x68) & 8) {
        var_s0 += Ot_Align64(0x19000);
    }
    if (*(s32 *)(D_0038790C + 0x68) & 0x10) {
        var_s0 += Ot_Align64(0x400);
    }
    if (*(s32 *)(D_0038790C + 0x68) & 0x20) {
        var_s0 += Ot_Align64(0x400);
    }
    if (*(s32 *)(D_0038790C + 0x68) & 0x40) {
        var_s0 += Ot_Align64(0x400);
    }
    return var_s0;
}

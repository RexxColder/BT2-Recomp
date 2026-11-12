#include "common.h"

s32 Vu1Pkt_CallProg8(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 sceVu0CopyMatrix(s32 arg0, s32 arg1);

void Vu1Node_Draw(s32 arg0) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = arg0;
    for (;;) {
        if (*(s32 *) (var_s1 + 0xC) != 0) {
            temp_v0 = Vu1Pkt_CallProg8(var_s1);
            sceVu0CopyMatrix(temp_v0 + 0x50, var_s1 + 0x50);
            sceVu0CopyMatrix(temp_v0 + 0x10, var_s1 + 0x90);
            func_003126C8(temp_v0 + 0x90, var_s1 + 0xD0);
            func_003126C8(temp_v0 + 0xA0, var_s1 + 0xE0);
        }
        if (*(s32 *) (var_s1 + 8) != 0) {
            break;
        }
        var_s1 += *(s32 *) var_s1;
    }
}

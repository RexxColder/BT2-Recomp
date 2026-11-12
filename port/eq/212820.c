#include "common.h"

/* 0x00212820: puede actuar. Vacio de vida -> 0; con el flag 0/0x4000 -> 0; si no, (a0->+0xB74 < 1)
   (el asm hace beql ... lw v0, 0xB74 ; slti v0, v0, 1: la comparacion es sobre B74, no sobre el flag). */
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_00212820(s32 a0) {
    if (BtlMember_IsHealthEmpty_2127F8(a0) != 0) {
        return 0;
    }
    if (func_00211310(a0, 0, 0x4000) != 0) {
        return 0;
    }
    return *(s32 *)((u8 *)a0 + 0xB74) < 1;
}

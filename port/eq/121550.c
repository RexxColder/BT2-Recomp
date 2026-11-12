#include "common.h"

void func_003126C8(void *arg0, void *arg1);
void func_00123D58(u8 *arg0);
void func_00124500(u8 *arg0);
void func_001240F0(u8 *arg0);
void func_00124448(u8 *arg0);

/* 0x00121550(obj): s1 = obj + 0xFE0; mode = word s1+0x1C: 0 -> func_003126C8(obj+0x1070, obj+0x170); 1 -> when
 * byte obj+0x10A0 is set: func_003126C8(obj+0x1070, obj+0x10B0) and s1+0x94 -= 10.0f. Then func_00123D58(obj),
 * func_00124500(obj), func_001240F0(obj) and the tail call func_00124448(obj). */
void func_00121550(u8 *arg0) {
    u8 *s1 = arg0 + 0xFE0;
    s32 mode = *(s32 *)(s1 + 0x1C);

    if (mode == 0) {
        func_003126C8(arg0 + 0x1070, arg0 + 0x170);
    } else if (mode == 1) {
        if (arg0[0x10A0] != 0) {
            func_003126C8(arg0 + 0x1070, arg0 + 0x10B0);
            *(f32 *)(s1 + 0x94) = *(f32 *)(s1 + 0x94) - 10.0f;
        }
    }
    func_00123D58(arg0);
    func_00124500(arg0);
    func_001240F0(arg0);
    func_00124448(arg0);
}

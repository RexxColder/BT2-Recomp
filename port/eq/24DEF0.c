#include "common.h"

void func_00248150(s32 arg0);
void func_00250D90();
void func_0026E908(s32 arg0);
void func_0028BB60(s32 arg0);
void func_0029BD28(s32 arg0);
extern u8 *D_003876A4;
extern u8 *D_003879A0;

void func_0024DEF0(void) {
    s32 s0;
    s32 s1;
    s32 type;

    if (*(s32 *)(D_003876A4 + 0x1C) != 0x37) {
        func_00248150((s32)D_003876A4);
    }
    if (*(s32 *)(D_003876A4 + 0x1C) != 0x29) {
        func_0029BD28((s32)D_003876A4);
    }
    s0 = 0;
    func_00250D90();
    s1 = 0;
    do {
        type = *(s32 *)(D_003876A4 + 0x1C);
        if (type == 0x37 || type == 0x29) {
            if (s0 != 2) {
                func_0026E908((s32)(D_003879A0 + s1 + 0x24));
            }
        } else {
            func_0026E908((s32)(D_003879A0 + s1 + 0x24));
        }
        s0 += 1;
        s1 += 0x28;
    } while (s0 < 4);
    func_0028BB60(*(s32 *)(D_003879A0 + 0x10));
    func_0028BB60(*(s32 *)(D_003879A0 + 0x8));
    func_0028BB60(*(s32 *)(D_003879A0 + 0xC));
    func_0028BB60(*(s32 *)(D_003879A0 + 0x4));
    func_0028BB60((s32)D_003879A0);
}

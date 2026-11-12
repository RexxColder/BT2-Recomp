#include "common.h"

void func_00250D90(void);
void func_0026E908(s32 arg0);
void func_0028BB60(s32 arg0);
extern u8 *D_003879C0;

void func_00251890(void) {
    s32 n;
    s32 off;
    u8 *p;

    n = 1;
    off = 0;
    func_00250D90();
    do {
        n -= 1;
        p = D_003879C0 + off;
        off += 0x28;
        func_0026E908((s32)(p + 0xC));
    } while (n >= 0);
    func_0028BB60(*(s32 *)(D_003879C0 + 0x4));
    func_0028BB60((s32)D_003879C0);
}

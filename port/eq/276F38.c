#include "common.h"

extern u8 *D_003876A0;
void StgAmb_Update(void);
void func_00272890(void);
void func_002748B8(void);
void func_00276EA8(void);

void func_00276F38(void) {
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        func_00276EA8();
        func_002748B8();
        StgAmb_Update();
        func_00272890();
    }
}

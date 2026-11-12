#include "common.h"

void func_002E93C0();
void func_002E93D8();
void func_002F04B0(void *arg0);
void func_002F0EE0(void *arg0);
void func_002F1038(void *arg0);
void func_002F1188(void *arg0);

void func_002F0F90(void *arg0) {
    s8 v1;

    if (*(s32 *)((u8 *)arg0 + 0xA0) > 0) {
        func_002E93C0(arg0);
        func_002F1038(arg0);
        func_002E93D8();
    }
    v1 = *(s8 *)((u8 *)arg0 + 1);
    if (v1 == 2) {
        func_002F0EE0(arg0);
    } else if (v1 == 1) {
        func_002F04B0(arg0);
    }
    if (*(s32 *)((u8 *)arg0 + 0xA4) <= 0) {
        return;
    }
    func_002E93C0(arg0);
    func_002F1188(arg0);
    func_002E93D8();
}

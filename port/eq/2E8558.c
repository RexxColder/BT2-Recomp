#include "common.h"

void func_002E8408(void *arg0);
void func_002E8640(void *arg0);
void func_002E8920(void *arg0);
void func_002E9308(void *arg0);
void func_00308478(void *arg0);
void func_00308678(void *arg0);
void func_00309028(void *arg0);
void func_00309A90(void *arg0);

void func_002E8558(void *arg0) {
    s16 temp_v1;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x98);
    switch (temp_v1) {
    case 0:
        func_002E8408(arg0);
        break;
    case 10:
        func_00308678(arg0);
        break;
    case 2:
        func_002E8920(arg0);
        break;
    case 3:
        func_00309028(arg0);
        break;
    case 4:
        func_00309A90(arg0);
        break;
    case 1:
        func_002E9308(arg0);
        break;
    case 15:
        func_00308478(arg0);
        break;
    }
    if (*(s32 *)((u8 *)arg0 + 0xFC) != 0) {
        func_002E8640(arg0);
    }
}

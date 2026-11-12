#include "common.h"

void func_002E8DF0(void *arg0);
void func_002E8F68(void *arg0);
void func_002E9100(void *arg0);

void func_002E9308(void *arg0) {
    s16 temp_v1;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x9C);
    switch (temp_v1) {
    case 2:
        func_002E9100(arg0);
        return;
    case 1:
        func_002E8F68(arg0);
        return;
    case 0:
        func_002E8DF0(arg0);
        return;
    }
}

#include "common.h"

void func_002EA050(void *arg0);
void func_002F7D68(void *arg0);
void func_002F8190(void *arg0);
void func_002F8310(void *arg0);
void func_002F8410(void *arg0);
void func_002F8618(void *arg0);
void func_002F8960(void *arg0);
void func_002F89E0(void *arg0);
extern s32 D_0037D078 __attribute__((section(".data")));

void func_002F8AA8(u8 *arg0) {
    s8 temp_v1;

    if (arg0 == NULL) {
        func_002EA050((void *)&D_0037D078);
        return;
    }
    temp_v1 = *(s8 *)(arg0 + 1);
    switch (temp_v1) {
    case 3:
        func_002F8310(arg0);
        break;
    case 1:
        func_002F7D68(arg0);
        break;
    case 2:
        func_002F8190(arg0);
        break;
    case 4:
        func_002F8410(arg0);
        break;
    case 5:
        func_002F8618(arg0);
        break;
    }
    func_002F89E0(arg0);
    func_002F8960(arg0);
}

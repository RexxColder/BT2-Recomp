#include "common.h"

s32 func_001FD300(s32 arg0);
void func_001FD870(void);
s32 func_001FD940(s32 arg0);
void func_001FF648(s32 arg0);
void func_001FF818(s32 arg0);
void func_001FF9F0(s32 arg0);
void func_00202078(s32 arg0);
s32 func_00211270(void);
s32 func_00211288(s32 arg0);

/* los tres bucles recorren TODOS los luchadores (el asm compara antes de llamar); a FD940/FF818 les llega
   en a0 el indice final del bucle anterior, como en el original */
void func_00201F90(void) {
    s32 i;
    s32 v;

    for (i = 0; i < func_00211270(); i++) {
        func_001FD300(func_00211288(i));
    }
    if (func_001FD940(i) != 0) {
        return;
    }
    func_001FD870();
    for (i = 0; i < func_00211270(); i++) {
        v = func_00211288(i);
        func_00202078(v);
        func_001FF648(v);
    }
    func_001FF818(i);
    for (i = 0; i < func_00211270(); i++) {
        func_001FF9F0(func_00211288(i));
    }
}

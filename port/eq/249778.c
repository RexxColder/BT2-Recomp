#include "common.h"

void func_00247F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00248038(void);
void func_0026EC18(s32 arg0, s32 arg1, s32 arg2);
void func_0026EFC8(s32 arg0, s32 arg1, s32 arg2);
s32 rand(void);

void func_00249778(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_hi;
    s32 temp_hi_2;

    if (*arg1 >= 0) {
        func_00247F08(arg0, (s32)arg1, (s32)arg2, arg3);
        if (func_00248038() != 0) {
            temp_v0 = *arg2 + 1;
            temp_hi = temp_v0 % 6;
            *arg2 = temp_v0;
            if (temp_hi == 0) {
                temp_hi_2 = rand() % 3;
                if (temp_hi_2 == 1) {
                    func_0026EFC8(arg0, (s32)arg1, 4);
                    func_0026EC18(arg0, (s32)arg1, arg3 + 1);
                } else if (temp_hi_2 == 0) {
                    func_0026EFC8(arg0, (s32)arg1, 4);
                    func_0026EC18(arg0, (s32)arg1, arg3);
                } else if (temp_hi_2 == 2) {
                    func_0026EFC8(arg0, (s32)arg1, 8);
                    func_0026EC18(arg0, (s32)arg1, arg3);
                }
            }
        } else {
            func_0026EFC8(arg0, (s32)arg1, 4);
            func_0026EC18(arg0, (s32)arg1, arg3 + 1);
        }
    }
}

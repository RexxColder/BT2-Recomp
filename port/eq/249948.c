#include "common.h"

s32 func_00247F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00248038(void);
void func_0026EC18(s32 arg0, s32 arg1, s32 arg2);
void func_0026EFC8(s32 arg0, s32 arg1, s32 arg2);
s32 rand(s32 arg0);

void func_00249948(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 v;
    s32 rem;

    if (*arg1 >= 0) {
        func_00247F08(arg0, (s32)arg1, (s32)arg2, arg3);
        if (func_00248038() != 0) {
            v = *arg2 + 1;
            rem = v % 6;
            *arg2 = v;
            if (rem == 0) {
                rem = rand(0) % 3;
                switch (rem) {
                case 0:
                    func_0026EFC8(arg0, (s32)arg1, 4);
                    func_0026EC18(arg0, (s32)arg1, arg3);
                    break;
                case 1:
                    func_0026EFC8(arg0, (s32)arg1, 4);
                    func_0026EC18(arg0, (s32)arg1, arg3 + 1);
                    break;
                case 2:
                    func_0026EFC8(arg0, (s32)arg1, 8);
                    func_0026EC18(arg0, (s32)arg1, arg3);
                    break;
                }
            }
        } else {
            func_0026EFC8(arg0, (s32)arg1, 8);
        }
    }
}

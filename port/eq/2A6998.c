#include "common.h"

void EftAura_Command(s32 arg0, s32 arg1);
s32 Gsc_GetInt();
void func_001AA260(s32 arg0);
void func_001B56D8(s32 arg0, s32 arg1);
void func_001E7630(s32 arg0);
s32 func_002A0010(s32 arg0);

s32 func_002A6998(s32 arg0) {
    s32 t;
    s32 v;

    if (arg0 == 0) {
        if (func_002A0010(0x61) != 0) {
            t = Gsc_GetInt();
            EftAura_Command(t, 0);
            v = Gsc_GetInt();
            switch (v) {
            case 2:
                EftAura_Command(t, 4);
                break;
            case 1:
                EftAura_Command(t, 2);
                break;
            }
        }
        if (func_002A0010(0x6B) != 0) {
            func_001AA260(Gsc_GetInt());
        }
        if (func_002A0010(0x74) != 0) {
            func_001B56D8(Gsc_GetInt(), 0);
        }
        if (func_002A0010(0x54) != 0) {
            func_001E7630(Gsc_GetInt());
        }
        func_002A0010(0x66);
    }
    return 1;
}

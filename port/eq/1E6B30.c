#include "common.h"

/* 0x001E6B30 (a0 = object, s32 words). Word [2] selects: 0 -> switch on word [6] (cases 0..6, >=7 = case 0);
   1 -> func_001E09D0(word [17]); other -> return 1. Float block vec[0..3] comes from func_003126C8(vec, obj+0x30). */

extern f32 D_00385698;
extern f32 D_0038569C;
extern f32 D_003856A0;
extern f32 D_003856A4;

void func_003126C8(void *arg0, void *arg1);
s32 func_00126EC0(void);
s32 func_00126598(s32 arg0);
s32 func_001DFD28(s32 arg0, s32 arg1);
s32 func_001DFDE0(s32 arg0, void *arg1, s32 arg2);
void func_001E0048(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_001E09D0(s32 arg0);

s32 func_001E6B30(s32 *arg0) {
    f32 vec[4];
    s32 r;
    s32 n;
    s32 k;
    f32 ang;

    func_003126C8(vec, arg0 + 12);

    if (arg0[2] == 1) {
        return func_001E09D0(arg0[17]);
    }
    if (arg0[2] != 0) {
        return 1;
    }

    switch (arg0[6]) {
        case 1:
            if ((u32)arg0[8] < 2 && func_00126EC0() == 0) {
                r = func_00126598(arg0[8]);
                if (r == 0) {
                    return 0;
                }
            }
            return func_001DFD28(arg0[16], 1);

        case 2:
            n = arg0[9];
            if (n <= 0) {
                return n;
            }
            ang = vec[2];
            k = 0;
            do {
                func_001E0048(arg0[16], 0, vec[0], vec[1], (ang * 180.0f) / D_00385698);
                ang = ang + vec[3];
                if (D_00385698 <= ang) {
                    ang = ang - D_0038569C;
                }
                k = k + 1;
            } while (k < arg0[9]);
            return 0;

        case 3:
            if ((u32)arg0[8] < 2 && func_00126EC0() == 0) {
                r = func_00126598(arg0[8]);
                if (r == 0) {
                    return 0;
                }
            }
            n = arg0[9];
            if (n <= 0) {
                return n;
            }
            ang = vec[2];
            k = 0;
            do {
                func_001E0048(arg0[16], 1, vec[0], vec[1], (ang * 180.0f) / D_003856A0);
                ang = ang + vec[3];
                if (D_003856A0 <= ang) {
                    ang = ang - D_003856A4;
                }
                k = k + 1;
            } while (k < arg0[9]);
            return 0;

        case 4:
            return func_001DFDE0(arg0[16], vec, 0);

        case 5:
            if ((u32)arg0[8] < 2 && func_00126EC0() == 0) {
                if (func_00126598(arg0[8]) == 0) {
                    return 0;
                }
            }
            return func_001DFDE0(arg0[16], vec, 1);

        case 6:
            if ((u32)arg0[8] < 2 && func_00126EC0() == 0) {
                if (func_00126598(arg0[8]) == 0) {
                    return func_001DFD28(arg0[16], 0);
                }
            }
            return func_001DFD28(arg0[16], 1);

        default:
        case 0:
            return func_001DFD28(arg0[16], 0);
    }
}

#include "common.h"

extern u8 *D_003879D0;
extern u8 *D_003876A4;
extern s32 D_003876AC;
extern s32 D_00387F2C;

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_0024B010(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_0024B210(s32 arg0);
s32 func_00250978(s32 arg0);
void func_002539C8(s32 arg0);
void func_00243968(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0028BB60(s32 arg0);

void func_00255C98(void) {
    s32 sp[8];
    s32 s2;
    s32 s3;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = *(s32 *)(D_003879D0 + 0x15C);
    s2 = 1;
    if (!(temp_v1 & 0x80)) {
        *(s32 *)(D_003879D0 + 0x15C) = temp_v1 | 0x80;
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 0xE, 0, 1);
        func_00243A80(0, 0, 0);
    } else if (!(temp_v1 & 0x100)) {
        temp_v0 = func_00100D58(0, 0, 0);
        D_003876AC = temp_v0;
        if (temp_v0 != 0) {
            *(s32 *)(D_003879D0 + 0x15C) = *(s32 *)(D_003879D0 + 0x15C) | 0x100;
            *(s32 *)(D_003876A4 + 0x494) =
                *(s32 *)(D_003879D0 + 0x1A8 + (*(s32 *)(D_003879D0 + 0x168) * 0x14));
            s3 = *(s32 *)(D_003876A4 + 0x1C);
            *(s32 *)(D_003876A4 + 0x1C) = 0x37;
            do {
                switch (*(s32 *)(D_003876A4 + 0x1C)) {
                case 0x37:
                    if (func_00250978(1) != 0) {
                        *(s32 *)(D_003876A4 + 0x1C) = 0x38;
                    } else {
                        s2 = 0;
                    }
                    break;
                case 0x38:
                    func_002539C8(2);
                    *(s32 *)(D_003876A4 + 0x1C) = 0x37;
                    break;
                }
            } while (s2 != 0);
            func_0024B010(*(s32 *)(D_003879D0 + 0x288), *(s32 *)(D_003879D0 + 0x28C),
                          D_00387F2C + (*(s32 *)(D_003876A4 + 0x494) * 0x22) + 0x1408,
                          (s32)sp, 0x14);
            *(s32 *)(D_003879D0 + 0x1A4 + (*(s32 *)(D_003879D0 + 0x168) * 0x14)) =
                func_0024B210((s32)sp);
            *(s32 *)(D_003876A4 + 0x1C) = s3;
            *(s32 *)(D_003879D0 + 0x15C) = *(s32 *)(D_003879D0 + 0x15C) & ~0x40;
            *(s32 *)(D_003879D0 + 0x15C) = *(s32 *)(D_003879D0 + 0x15C) & ~0x80;
            *(s32 *)(D_003879D0 + 0x15C) = *(s32 *)(D_003879D0 + 0x15C) & ~0x100;
            func_00243968(0, 0, 0, (s32)D_003879D0);
            func_0028BB60(D_003876AC);
            D_003876AC = 0;
        }
    }
}

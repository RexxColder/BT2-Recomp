#include "common.h"

void func_00129680(s32 arg0, s32 arg1);
void func_001296E8(s32 arg0, s32 arg1, s32 arg2);
void func_00129920(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
f32 func_00129970(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_001299A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

u32 func_00129720(s32 unused0, s32 arg1, s32 arg2, s32 arg3) {
    u8 fr[0x280];   /* tamano de locales del original (antes 0x270) */
    s32 var_v0;
    s32 cnt;
    s32 s2;
    s32 s4;
    s32 temp_s4;
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s1;
    s32 o3;
    s32 oa;
    s32 ob;
    s32 oc;
    s32 *flags;
    s32 *a0p;
    s32 *s7p;
    f32 *v1f;
    f32 *s5f;
    s32 v;
    u32 temp_lo;

    var_v0 = 0;
    if (arg3 != 0) {
        func_001299A0((s32)(fr + 0x1B0), arg1, arg2, arg3);
        cnt = 0;
        flags = (s32 *)(fr + 0x240);
        if (arg3 > 0) {
            v1f = (f32 *)(fr + 0x1B0);
            a0p = flags;
            s2 = arg3;
            do {
                v = (*v1f < 0.0f) ? 1 : 0;
                v1f += 4;
                s2 -= 1;
                *a0p = v;
                cnt += v;
                a0p += 1;
            } while (s2 != 0);
        }
        var_v0 = arg3;
        if (cnt != 0) {
            var_v0 = 0;
            if (arg3 != cnt) {
                o3 = 0;
                s4 = 1;
                if (arg3 > 0) {
                    var_s1 = arg1;
                    s5f = (f32 *)(fr + 0x1B0);
                    s7p = flags;
                    s2 = arg3;
                    do {
                        temp_s4 = (s4 >= arg3) ? 0 : s4;
                        temp_a0 = *s7p;
                        s7p += 1;
                        temp_s0 = arg1 + (temp_s4 * 0x30);
                        if (temp_a0 == 0) {
                            oa = o3;
                            o3 += 0x30;
                            func_00129680((s32)(fr + oa), var_s1);
                            if (flags[temp_s4] != 0) {
                                ob = o3;
                                o3 += 0x30;
                                func_00129920(func_00129970(*s5f, arg2, var_s1, temp_s0),
                                              (s32)(fr + ob), temp_s0, var_s1);
                            }
                        } else if (flags[temp_s4] == 0) {
                            oc = o3;
                            o3 += 0x30;
                            func_00129920(func_00129970(*s5f, arg2, var_s1, temp_s0),
                                          (s32)(fr + oc), temp_s0, var_s1);
                        }
                        s2 -= 1;
                        s5f += 4;
                        var_s1 += 0x30;
                        s4 = temp_s4 + 1;
                    } while (s2 != 0);
                }
                temp_lo = (u32)o3 / 48U;
                func_001296E8(arg1, (s32)fr, (s32)temp_lo);
                var_v0 = (s32)temp_lo;
            }
        }
    }
    return (u32)var_v0;
}

#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FL(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_00385F78;
extern f32 D_00385F7C;
extern f32 D_00385F80;
extern f32 D_00385F84;
extern f32 D_00385F88;
extern f32 D_00385F8C;

s32 BtlObjXf_Update(void *arg0);
void BtlAnim_SetBlend(f32 farg0, void *arg1);
s32 BtlMember_HasKi(void *arg0, s32 arg1);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
s32 func_00203888(void *arg0, s32 arg1, s32 arg2);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(void *arg0);
s32 func_00212878(void);
void func_00212DD8(void *arg0, s32 arg1);
f32 func_00217360(void *arg0);
s32 func_00218540(f32 farg0, void *arg1);
s32 func_00218560(f32 farg0, void *arg1);
s32 func_00218838(void *arg0, s32 arg1);
s32 func_0023F410(void *arg0);
s32 func_0023F930(void *arg0, s32 arg1);

s32 func_00220D30(void *arg0) {
    f32 var_f12;
    s32 temp_v0;
    s32 var_v0;

    if (BtlObjXf_Update(arg0) == 0xEC) {
        if (!(func_00217360(arg0) < 2.0f)) {
            if (func_00218540(D_00385F78, arg0) != 0) {
                goto block_3;
            }
            goto block_8;
        }
block_3:
        if (func_00212878() != 0) {
            if (!(FL(W(arg0, 0x1530), 0xE64) < -10.0f)) {
                if (func_00211310(arg0, 0, 0x8000) != 0) {
                    goto block_22;
                }
block_8:
                if (func_00218560(D_00385F7C, arg0) == 0) {
                    if (func_00211310(arg0, 0, 0x100) != 0) {
                        func_002113C0(arg0, 0, 2, 1);
                        BtlAnim_SetBlend(D_00385F80, arg0);
                        return 0x20;
                    }
                    if (func_00211310(arg0, 0, 0x20) != 0) {
                        if (func_00212820(arg0) != 0) {
                            var_f12 = D_00385F84;
                            goto block_46;
                        }
                        goto block_37;
                    }
block_37:
                    if (func_00212878() != 0) {
                        if (func_00211310(arg0, 0, 0x40) != 0) {
                            var_v0 = 0x26;
                            if (func_00212820(arg0) == 0) {
                                goto block_40;
                            }
                            return var_v0;
                        }
                        goto block_40;
                    }
                    goto block_40;
                }
                if (!(W(W(arg0, 0x1530), 0xED0) & 0x40)) {
                    if (func_00218838(arg0, 1) != 0) {
                        goto block_16;
                    }
                    if (func_00212820(arg0) != 0) {
                        if (func_00211310(arg0, 1, 0x80000) != 0) {
                            return 0xA9;
                        }
                        if (BtlPad_Test48(arg0, 8) == 0) {
                            return 0xA9;
                        }
                        return 0x2A;
                    }
                    return 0xA9;
                }
                return (func_00212820(arg0) == 0) ? 0xA9 : 0x9B;
            }
            goto block_16;
        }
block_16:
        if (func_00212820(arg0) != 0) {
            if (func_00211310(arg0, 1, 0x80000) == 0) {
                if (BtlPad_Test48(arg0, 8) == 0) {
                    goto block_22;
                }
                return !(func_0023F410(arg0) & 0x1000) ? 0x29 : 0x27;
            }
            goto block_22;
        }
block_22:
        func_00212DD8(arg0, 0);
        return 0xA7;
    }
block_40:
    if (W(arg0, 0x8CC) >= 0x10) {
        if (BtlPad_Test4C(arg0, 2) != 0) {
            if (func_00212820(arg0) != 0) {
                if (BtlPad_Test48(arg0, 0xD) != 0) {
                    if (BtlMember_HasKi(arg0, 0x2710) != 0) {
                        func_00203888(arg0, 0x2710, 0);
                        func_002113C0(arg0, 0, 2, 1);
                        var_f12 = D_00385F88;
block_46:
                        BtlAnim_SetBlend(var_f12, arg0);
                        return 0x26;
                    }
                    goto block_47;
                }
block_47:
                if (BtlPad_Test48(arg0, 0xC) != 0) {
                    func_002113C0(arg0, 0, 2, 1);
                    BtlAnim_SetBlend(D_00385F8C, arg0);
                    temp_v0 = func_0023F930(arg0, 0);
                    var_v0 = 0x68;
                    if (temp_v0 != 2) {
                        if (temp_v0 >= 3) {
                            var_v0 = 0x67;
                            if (temp_v0 != 3) {
                                goto block_55;
                            }
                            return var_v0;
                        }
                        if (temp_v0 >= 0) {
                            return 0x66;
                        }
                        goto block_55;
                    }
                    return var_v0;
                }
                goto block_55;
            }
            goto block_55;
        }
        goto block_55;
    }
block_55:
    var_v0 = -1;
    return var_v0;
}

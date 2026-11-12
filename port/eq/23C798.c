#include "common.h"

extern f32 D_00386C34;
extern f32 D_00386C38;
extern f32 fabsf(f32 x);
s32 func_00212820();
s32 BtlPad_TestStep();
s32 func_00211310();
f32 func_00210A98();
s32 func_00217518();
s32 func_00218128();
s32 BtlPad_Test48();
s32 BtlPad_Test4C();
f32 func_00207E80();
f32 func_00207E88();
s32 func_0023F420();
s32 func_0023F8F8();
s32 func_00240438();
s32 BtlMember_HasKi();
s32 func_00218758();
s32 func_00217488();
s32 func_0023F948();
s32 func_0023F930();
u8 *BtlMember_GetActiveGauge(u8 *arg0);

s32 func_0023C798(u8 *arg0, u32 arg1) {
    s32 s1, v0, v1;
    f32 f20, f0;

    if (!func_00212820(arg0)) return -1;

    if ((arg1 & 1) && BtlPad_TestStep(arg0, 0)) {
        if (!func_00211310(arg0, 0, 1)) return 0x49;
        f0 = func_00210A98(arg0);
        if (D_00386C34 < fabsf(f0)) return func_00217518(0x41, 0x49);
        return 0x49;
    }
    if ((arg1 & 2) && BtlPad_TestStep(arg0, 1)) {
        s1 = 0;
        if (func_00218128(arg0, 8) && BtlPad_Test48(arg0, 7)) {
            s1 = func_00211310(arg0, 1, 1) != 0;
        }
        if (!BtlPad_Test48(arg0, 8)) {
            if (*(s32 *)(arg0 + 0x998) < 6) return s1 ? 0x54 : 0x4E;
            return s1 ? 0x55 : 0x4F;
        }
        f20 = fabsf(func_00207E80(arg0));
        f0 = fabsf(func_00207E88(arg0));
        if (f0 < f20) {
            f0 = func_00207E80(arg0);
            if (f0 < 0.0f) return s1 ? 0x50 : 0x4A;
            return s1 ? 0x51 : 0x4B;
        }
        f0 = func_00207E88(arg0);
        if (f0 < 0.0f) return s1 ? 0x52 : 0x4C;
        return s1 ? 0x53 : 0x4D;
    }
    if (arg1 & 0x400) {
        if ((func_0023F420(arg0) & 0x20000) && func_00211310(arg0, 1, 1) && BtlPad_Test4C(arg0, 1)) {
            if (BtlPad_Test48(arg0, 0xE)) return 0x74;
            if (BtlPad_Test48(arg0, 0xF)) return 0x75;
        }
    }
    if ((arg1 & 4) && BtlPad_TestStep(arg0, 2)) {
        if (func_00211310(arg0, 1, 1) && BtlPad_Test48(arg0, 0xC) && (func_0023F420(arg0) & 0x8000)) {
            /* skip to next block */
        } else if (!(*(s32 *)(arg0 + 0xA10) < func_0023F8F8(arg0))) {
            /* skip */
        } else {
            v0 = func_00240438(arg0, 0);
            if (BtlMember_HasKi(arg0, v0)) {
                if (!func_00211310(arg0, 0, 1)) return 0x87;
                f0 = func_00210A98(arg0);
                if (D_00386C38 < fabsf(f0)) return func_00217518(0x41, 0x87);
                return 0x87;
            }
        }
    }
    if ((arg1 & 8) && BtlPad_TestStep(arg0, 3)) {
        if (func_00211310(arg0, 1, 1) && BtlPad_Test48(arg0, 0xC) && (func_0023F420(arg0) & 0x8000)) {
            /* skip */
        } else if (!(*(s32 *)(arg0 + 0xA10) < func_0023F8F8(arg0))) {
            /* skip */
        } else if (func_00218758(arg0)) {
            v0 = func_00240438(arg0, 3);
            if (BtlMember_HasKi(arg0, v0)) {
                if (func_00211310(arg0, 0, 1)) func_00210A98(arg0);
                return 0x88;
            }
        }
    }
    if (arg1 & 0x10) {
        if ((func_0023F420(arg0) & 2) && BtlPad_Test4C(arg0, 1) && BtlPad_Test48(arg0, 0xC)) {
            if (func_00217488(arg0) != 0x17) return 0x56;
            v1 = func_0023F948(arg0, 1);
            if (v1 == 0) return 0x56;
            if (v1 == 1) return func_00217518(0x1B, 0x56);
        }
    }
    if (arg1 & 0x20) {
        if ((func_0023F420(arg0) & 4) && BtlPad_Test4C(arg0, 1) && BtlPad_Test48(arg0, 0xD)) {
            if (func_00217488(arg0) != 0x17) return 0x57;
            v1 = func_0023F948(arg0, 2);
            if (v1 == 0) return 0x57;
            if (v1 == 1) return func_00217518(0x1B, 0x57);
        }
    }
    if ((arg1 & 0x40) && func_00211310(arg0, 1, 1)) {
        if (BtlPad_Test48(arg0, 0xC)) {
            if ((func_0023F420(arg0) & 0x8000) && BtlPad_Test4C(arg0, 1)) {
                if (!BtlPad_Test48(arg0, 7)) return 0x82;
            }
            if (BtlPad_Test4C(arg0, 3)) return 0x7E;
        }
    }
    if (!(arg1 & 0x380)) return -1;
    s1 = -1;
    if (BtlPad_Test4C(arg0, 2)) {
        if (!BtlPad_Test48(arg0, 8)) {
            if (arg1 & 0x100) s1 = 1;
            if (arg1 & 0x80) s1 = 0;
        }
    }
    if (arg1 & 0x200) s1 = 2;
    if (s1 < 0) return -1;
    v1 = func_0023F930(arg0, s1);
    if (v1 == 2) return 0x68;
    if (v1 < 3) {
        if (v1 == 1) return 0x66;
    } else {
        if (v1 == 3) return 0x67;
        if (v1 == 4) return 0x1B;
    }
    return -1;
}

#include "common.h"

#define OBJ_B(o) (*(s8 *)(obj + (o)))
#define OBJ_W(o) (*(s32 *)(obj + (o)))
#define OBJ_U(o) (*(u32 *)(obj + (o)))
#define VT(s, off) (*(void **)((u8 *)(*(s)) + (off)))

extern s32 D_00353F88 __attribute__((section(".data")));
extern s32 D_00354EC0 __attribute__((section(".data")));
extern s32 D_003553C0 __attribute__((section(".data")));
extern s8 D_003553C4 __attribute__((section(".data")));

s32 func_002FA020(s32 arg0);
void func_002F3378(void);
void func_002F3390(void);
void func_002F22D8(void);
void func_002F9DC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
s32 func_002F9E30(s32 a0, s32 a1, s32 a2);
void func_003061A8(void *a0, s32 a1, void *a2, void *a3);

void func_002F22F0(u8 *obj) {
    s32 sp[6];
    void **s4;
    s32 s0;
    s32 v1;
    s32 a1;
    s32 t;
    s32 q;
    s32 w;
    u32 v;
    s32 c;
    s32 a3;
    s32 d;
    s32 r;
    s32 r2;
    s32 sh;
    u32 x;

    s4 =*(void ***)(obj + 4);
    s0 = func_002FA020(OBJ_W(8));
    func_002F3378();

    if (OBJ_B(2) == 1) {
        if (s0 != 1) {
            if (s0 == 3) {
                OBJ_B(2) = 0;
                func_002F3390();
                ((void (*)(void *, s32, void *))VT(s4, 0x1C))(s4, 0, obj + 0x24);
                OBJ_W(0x24) = 0;
                OBJ_W(0x28) = 0;
                c = OBJ_W(0x4C);
                if (D_00353F88 >= 0) {
                    if (c >= D_00353F88) {
                        OBJ_B(1) = 4;
                    } else if (c <= 0x7FFFFFFE) {
                        OBJ_W(0x4C) = c + 1;
                    }
                } else if (c <= 0x7FFFFFFE) {
                    OBJ_W(0x4C) = c + 1;
                }
            } else {
                func_002F3390();
            }
        } else {
            OBJ_B(2) = 0;
            func_002F3390();
            t = (s32)((u32)OBJ_W(0x20) << 11);
            func_003061A8(obj + 0x24, t, sp, &sp[4]);
            ((void (*)(void *, s32, void *))VT(s4, 0x20))(s4, 1, sp);
            ((void (*)(void *, s32, void *))VT(s4, 0x1C))(s4, 0, &sp[4]);
            a1 = OBJ_W(0x30);
            v1 = OBJ_W(0x58) + OBJ_W(0x20);
            OBJ_U(0x34) = OBJ_U(0x34) + (u32)t;
            OBJ_W(0x24) = 0;
            OBJ_W(0x58) = v1;
            OBJ_W(0x28) = 0;
            s0 = OBJ_W(0x14);
            if (v1 == a1) {
                void *fn = *(void **)(obj + 0x38);
                if (fn != NULL) {
                    ((void (*)(s32, s32))fn)(OBJ_W(0x3C), a1);
                }
            }
            v = OBJ_U(0x5C);
            if (OBJ_W(0x58) < s0 && (((OBJ_U(0x34) >> 11) < v) || (v > 0xFFFFEu))) {
                OBJ_W(0x4C) = 0;
            } else {
                OBJ_B(1) = 3;
                OBJ_W(0x4C) = 0;
            }
        }
    }

    if (OBJ_B(1) != 4) {
        if (OBJ_B(2) == 0) {
            OBJ_W(0x24) = 0;
            OBJ_B(2) = 1;
            OBJ_W(0x28) = 0;
            func_002F3390();
            if (OBJ_B(0x44) == 1) {
                OBJ_B(2) = 0;
            } else if (OBJ_B(0x48) == 1) {
                OBJ_B(2) = 0;
            } else if (OBJ_W(0x14) == 0) {
                OBJ_B(2) = 0;
                OBJ_B(1) = 3;
                OBJ_W(0x20) = 0;
            } else if (s4 != NULL) {
                if (*s4 != NULL) {
                    r = ((s32 (*)(void *, s32))VT(s4, 0x24))(s4, 0);
                    if ((s32)((u32)OBJ_W(0x40) - (u32)r) < OBJ_W(0x1C)) {
                        ((void (*)(void *, s32, s32, void *))VT(s4, 0x18))(s4, 0, OBJ_W(0x18), &sp[4]);
                        a3 = OBJ_W(0x58);
                        a1 = OBJ_W(0x30) - a3;
                        v1 = sp[5];
                        q = ((v1 < 0) ? (v1 + 0x7FF) : v1) >> 11;
                        s0 = (q >= a1) ? a1 : q;
                        d = OBJ_W(0x14) - a3;
                        s0 = (s0 >= d) ? d : s0;
                        t = OBJ_W(0x2C);
                        s0 = (s0 >= t) ? t : s0;
                        func_002F9DC8(OBJ_W(8), OBJ_W(0xC) + a3, 0, a3, t);
                        if (D_00354EC0 == 1) {
                            D_003553C0 = D_00354EC0;
                            if (OBJ_B(3) == D_00354EC0) {
                                D_003553C4 = 0;
                            } else {
                                D_003553C4 = (s8)D_00354EC0;
                            }
                        }
                        v = OBJ_U(0x5C);
                        if (v != 0xFFFFF) {
                            x = OBJ_U(0x34);
                            sh = ((s32)x < 0 ? (s32)x + 0x7FF : (s32)x) >> 11;
                            w = (s32)(v - (u32)sh);
                            s0 = (s0 >= w) ? w : s0;
                        }
                        r2 = func_002F9E30(OBJ_W(8), s0, sp[4]);
                        OBJ_W(0x28) = sp[5];
                        OBJ_W(0x24) = sp[4];
                        OBJ_W(0x20) = r2;
                        if (r2 <= 0) {
                            ((void (*)(void *, s32, void *))VT(s4, 0x1C))(s4, 0, obj + 0x24);
                            OBJ_W(0x24) = 0;
                            OBJ_W(0x28) = 0;
                            OBJ_B(2) = 0;
                            if (func_002FA020(OBJ_W(8)) == 3) {
                                c = OBJ_W(0x4C);
                                if (D_00353F88 >= 0) {
                                    if (c >= D_00353F88) {
                                        OBJ_B(1) = 4;
                                    } else if (c <= 0x7FFFFFFE) {
                                        OBJ_W(0x4C) = c + 1;
                                    }
                                } else if (c <= 0x7FFFFFFE) {
                                    OBJ_W(0x4C) = c + 1;
                                }
                            }
                        }
                    } else {
                        OBJ_B(2) = 0;
                    }
                } else {
                    OBJ_B(2) = 0;
                    func_002F22D8();
                }
            } else {
                OBJ_B(2) = 0;
                func_002F22D8();
            }
        }
    }
}

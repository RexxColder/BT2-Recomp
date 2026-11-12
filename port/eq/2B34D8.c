#include "common.h"

void func_002B2D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_002B2E48(s32 arg0, s32 arg1, s32 arg2);
s32 func_002B2F98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002B2FC8(void);
s32 func_002B4B08(s32 arg0, s32 arg1);
s32 func_002B3260(s32 arg0, s32 arg1, s32 arg2);
s32 func_002B3370(s32 arg0, s32 arg1, s32 arg2);
s32 func_002B3C30(s32 arg0);
void func_002B4CB0(s32 arg0);
void func_002B2DF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002B2F48(s32 arg0);
void func_002C5588(s32 arg0, s32 arg1, s32 arg2);
void func_002BD988(s32 arg0);
void func_002CBE08(s32 arg0);
s32 func_002CDF40(s32 arg0, s32 arg1);
void func_002B6700(s32 arg0);
s32 func_002C30A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002B29F8(s32 arg0, s32 arg1);
void func_002B3C68(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002B6818();
s32 Rand_Range(s32 arg0);

extern s32 D_0038BAC8, D_0038BACC, D_0038BAD0, D_0038BAD4, D_0038BAD8, D_0038BADC, D_0038BAE0, D_0038BAE4, D_0038BAE8;
extern s32 D_003452F0[];
extern s32 D_00345318[];
extern s32 D_00345334;
extern u8 D_00345218[], D_00345260[], D_003452A8[];
extern u8 D_00377E40[], D_00377E60[], D_00377E80[], D_00377EB0[], D_00377ED8[];

s32 func_002B34D8(u8 *obj, u8 *arg) {
    s32 cfg[20];
    s32 buf50[4];
    s32 buf60[16];
    s32 out_a0, out_a4, out_a8;
    s32 out_ac, out_b0, out_b4, out_b8;
    s32 mode, c0, c4, c8, d4;
    s32 rBC, rCC, rD0, rD8, rDC;
    s32 big, r1, r3, s1, s2, hnd, ptr;
    s32 mod;

    mode = *(s32 *)(arg + 0);
    c0 = *(s32 *)(arg + 0x10);
    c4 = *(s32 *)(arg + 8);
    c8 = *(s32 *)(arg + 0xC);
    func_002B2D10((s32)arg, (s32)&D_0038BACC, (s32)&D_0038BAD0, (s32)&D_0038BAD4, (s32)&D_0038BAD8,
                  (s32)&D_0038BAE8, (s32)&D_0038BAE4);
    func_002B2E48((s32)arg, (s32)&D_0038BADC, (s32)&D_0038BAE0);
    func_002B2F98((s32)arg, (s32)&out_a0, (s32)&out_a4, (s32)&out_a8);
    d4 = func_002B2FC8();
    rBC = func_002B4B08((s32)obj, D_0038BAD0 + D_0038BAD4 + D_0038BAD8 + 0x40);
    big = func_002B4B08((s32)obj, D_0038BACC + 0x40);
    r1 = func_002B3260((s32)obj, (s32)arg, (s32)buf50);
    r3 = func_002B3370((s32)obj, (s32)arg, (s32)buf60);
    if (func_002B3C30(mode) == 1) {
        s2 = func_002B4B08((s32)obj, D_0038BAE8);
        s1 = func_002B4B08((s32)obj, D_0038BAE4);
    } else {
        s2 = 0;
        s1 = 0;
    }
    rDC = func_002B4B08((s32)obj, 0x800);
    rCC = func_002B4B08((s32)obj, out_a0);
    rD0 = func_002B4B08((s32)obj, out_a4);
    ptr = func_002B4B08((s32)obj, out_a8);
    rD8 = func_002B4B08((s32)obj, d4);
    if (rBC == 0 || big == 0 || r1 != 0 || r3 != 0 || rCC == 0 || rD0 == 0 || rDC == 0 || rD8 == 0 || ptr == 0) {
        Rand_Range((s32)D_00377E40);
        func_002B4CB0((s32)obj);
        return 0;
    }
    if (func_002B3C30(mode) == 1 && (s2 == 0 || s1 == 0)) {
        Rand_Range((s32)D_00377E60);
        func_002B4CB0((s32)obj);
        return 0;
    }
    D_0038BAC8 = (big + 0x3F) & -0x40;
    func_002B2DF8((s32)arg, (s32)&out_ac, (s32)&out_b0, (s32)&out_b4, (s32)&out_b8);
    D_00345318[6] = s1;
    D_003452F0[0] = out_b4;
    D_003452F0[8] = 0;
    D_003452F0[1] = out_b8;
    D_00345318[2] = s2;
    D_003452F0[5] = out_ac;
    D_003452F0[6] = out_b0;
    D_003452F0[2] = out_ac;
    D_003452F0[3] = out_b0;
    D_003452F0[4] = 0;
    D_003452F0[7] = c0;
    if (mode == 2) {
        __builtin_memcpy(cfg, D_00345260, 0x44);
        *(s32 *)(obj + 0x1C4) = D_0038BAC8;
        *(s32 *)(obj + 0x1CC) = 0x800;
        *(s32 *)(obj + 0x1C8) = D_0038BACC - 0x800;
    } else if (mode == 1 || mode == 3) {
        __builtin_memcpy(cfg, mode == 1 ? D_00345218 : D_003452A8, 0x44);
        *(s32 *)(obj + 0x1C4) = D_0038BAC8;
        *(s32 *)(obj + 0x1C8) = D_0038BACC - D_00345334;
        *(s32 *)(obj + 0x1CC) = D_00345334;
    }
    cfg[10] = D_00345334;
    if (D_0038BAD0 != 0) {
        mod = D_0038BAD0 % D_00345334;
        D_0038BAD0 = D_0038BAD0 - mod;
    }
    cfg[14] = func_002B2F48(*(s32 *)(arg + 0x24));
    cfg[1] = rBC;
    cfg[2] = D_0038BAD0;
    cfg[3] = D_0038BAD4;
    cfg[4] = D_0038BAD8;
    cfg[11] = c0;
    cfg[12] = c4;
    cfg[13] = c8;
    cfg[15] = rCC;
    cfg[16] = out_a0;
    func_002C5588((s32)D_003452F0, (s32)buf50, (s32)buf60);
    if (mode == 1) {
        func_002BD988((s32)D_00345318);
    }
    func_002CBE08(1);
    hnd = func_002CDF40((s32)cfg, 0);
    if (hnd == 0) {
        func_002B6700(-0x131);
        Rand_Range((s32)D_00377E80);
        return 0;
    }
    if (func_002C30A0(hnd, (s32)func_002B6818, (s32)obj) != 0) {
        func_002B6700(-0x12F);
        Rand_Range((s32)D_00377EB0);
        return 0;
    }
    *(s32 *)(obj + 0x2D0) = func_002B29F8(rD0, out_a4);
    if (*(s32 *)(obj + 0x2D0) == 0) {
        Rand_Range((s32)D_00377ED8);
        return 0;
    }
    *(s32 *)(obj + 0x1A4) = rD8;
    *(s32 *)(obj + 0x1A8) = d4;
    func_002B3C68((s32)obj, rDC, 0x800, 0x40);
    *(s32 *)(obj + 0x2D4) = 0;
    return hnd;
}

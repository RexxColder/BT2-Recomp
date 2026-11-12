#include "common.h"

extern u8 *D_00387F2C;
extern s32 func_002A3E38();
extern void func_002A4098();
extern void func_002A3EA8();
extern u8 *func_002A3E48();
extern s32 func_002A0010();
extern void func_0025B8A8();
extern s32 func_0025B950();
extern void func_001017F0();
extern void func_00261970();
extern void func_001F4308();
extern void func_001AA260();
extern void func_001B56D8();
extern void func_001A0B50();
extern void func_001E7630();
extern void func_001F4398();
extern void func_001F4428();
extern void func_001F4610();
extern void func_001F44A0();
extern void func_001AA220();
extern void func_001A0B90();
extern void func_001F46F8();
extern void func_002612B8();
extern u8 *func_002A3DB8();
extern u8 *func_002A4E38();
extern void func_002611E8();
extern void func_001018E8();
extern void func_001019D8();
extern void func_00297FE0();
extern void func_00261A48();
extern void func_002615F0();
extern void func_002A3D90(s32 arg0, s32 arg1, f32 farg0);
extern s32 func_001018B8();

s32 func_002A4F50(s32 mode, u8 *st) {
    s32 cur;
    s32 again;
    s32 n;
    s32 a;
    s32 b;
    u8 *e;
    u8 *fx;
    f32 t;
    s32 id;

    if (mode == 1) {
        n = func_002A3E38();
        if (n <= 0) {
            return 0;
        }
        func_002A4098(n - 1);
        return 0;
    }
    if (mode == 0) {
        __builtin_memset(st, 0, 0x1C);
        *(s32 *)(st + 0x18) = -1;
        a = Gsc_GetInt();
        func_0025B8A8(a, func_002A0010(0x53) == 0);
        return func_002A0010(0x77) == 0;
    }
    if (mode != 2) {
        return 0;
    }

    cur = Gsc_GetCurrentTime();
    do {
        again = 0;
        if (Gsc_FindOptionN(106, (s8)st[0])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                BtlFacade_ShakeCamera_25B990(Gsc_GetFloat());
                st[0]++;
            }
        }
        if (Gsc_FindOptionN(109, (s8)st[1])) {
            if (cur >= Gsc_GetInt() * 10) {
                n = func_002A3E38();
                if (n > 0) {
                    func_002A4098(n - 1);
                }
                func_002A3EA8(n, 0);
                e = func_002A3E48();
                *(s32 *)(st + 0x10) = 0;
                *(s32 *)(st + 0x18) = -1;
                *(s32 *)(st + 0x14) = 0;
                if (*(s32 *)(e + 8) >= 0) {
                    id = *(s32 *)(e + 8);
                    *(s32 *)(st + 0x18) = id;
                    func_001017F0((*(u32 *)(D_00387F2C + 0x1008) & 1) ? id + 0x13F6 : id, 0);
                    if ((s8)e[7] >= 0 && (s8)e[6] >= 0) {
                        func_00261970((u16)(s8)e[7], (s8)e[6]);
                    }
                    if ((s8)e[4] >= 0 && (s8)e[5] >= 0) {
                        func_00261970((u16)(s8)e[4], (s8)e[5]);
                    }
                }
                again = 1;
                st[1]++;
            }
        }
        if (Gsc_FindOptionN(101, (s8)st[2])) {
            if (cur >= Gsc_GetInt() * 10) {
                a = Gsc_GetInt();
                b = Gsc_GetInt();
                switch (a) {
                case -2:
                    func_001F4308(b, 1);
                    break;
                case -1:
                    func_001F4308(b, 0);
                    break;
                case 0:
                    EftAura_Command(b, 0);
                    n = Gsc_GetInt();
                    if (n == 1) {
                        EftAura_Command(b, 2);
                    } else if (n == 2) {
                        EftAura_Command(b, 4);
                    }
                    break;
                case 1:
                    func_001AA260(b);
                    break;
                case 2:
                    func_001B56D8(b, 0);
                    break;
                case 3:
                    func_001A0B50(b);
                    break;
                case 4:
                    func_001E7630(b);
                    break;
                case 5:
                    func_001F4398(b);
                    break;
                case 6:
                    func_001F4428(b);
                    break;
                case 7:
                    func_001F4610();
                    break;
                case 8:
                    func_001F44A0(b);
                    break;
                default:
                    break;
                }
                again = 1;
                st[2]++;
            }
        }
        if (Gsc_FindOptionN(69, (s8)st[3])) {
            if (cur >= Gsc_GetInt() * 10) {
                a = Gsc_GetInt();
                b = Gsc_GetInt();
                switch (a) {
                case 0:
                    EftAura_Command(b, 7);
                    break;
                case 1:
                    func_001AA220();
                    break;
                case 2:
                    func_001B56D8(b, 1);
                    break;
                case 3:
                    func_001A0B90();
                    break;
                case 4:
                    BtlFacade_PulseCtrl10D(b); /* asm: a0 = s0 (b) */
                    break;
                case 5:
                    func_001F4398(b);
                    break;
                case 6:
                    func_001F4428(b);
                    break;
                case 7:
                    func_001F46F8();
                    break;
                default:
                    break;
                }
                again = 1;
                st[3]++;
            }
        }
        if (Gsc_FindOptionN(115, (s8)st[4])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                a = (u16)Gsc_GetInt();
                b = Gsc_GetInt();
                func_002612B8(a, b);
                st[4]++;
            }
        }
        if (Gsc_FindOptionN(102, (s8)st[5])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                func_002A3DB8(32)[24] = 0;
                fx = func_002A4E38(31, 14, 0, 0, 512, 448, 255, 255, 255, 0, 0);
                t = Gsc_GetFloat();
                *(s32 *)(fx + 0x20) = 2;
                *(u16 *)(fx + 0x24) = (s32)(t * 300.0f);
                st[5]++;
            }
        }
        if (Gsc_FindOptionN(70, (s8)st[6])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                func_002A3DB8(31)[24] = 0;
                fx = func_002A4E38(32, 14, 0, 0, 512, 448, 255, 255, 255, 0, 0);
                t = Gsc_GetFloat();
                *(s32 *)(fx + 0x20) = 1;
                *(u16 *)(fx + 0x24) = (s32)(t * 300.0f);
                st[6]++;
            }
        }
        if (Gsc_FindOptionN(99, (s8)st[7])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                a = (u16)Gsc_GetInt();
                b = Gsc_GetInt();
                func_002611E8(a, b);
                st[7]++;
            }
        }
        if (Gsc_FindOptionN(118, (s8)st[9])) {
            n = Gsc_GetInt() - 10;
            if (n < 0) {
                n = 0;
            }
            if (cur >= n * 10) {
                again = 1;
                func_001018E8(Gsc_GetInt(), 0);
                st[9]++;
            }
        }
        if (Gsc_FindOptionN(86, (s8)st[10])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                func_001019D8();
                st[10]++;
            }
        }
        if (Gsc_FindOptionN(120, (s8)st[8])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                func_00297FE0(1, Gsc_GetInt(), 64, 64, 0);
                st[8]++;
            }
        }
        if (Gsc_FindOptionN(121, (s8)st[12])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                a = (u16)Gsc_GetInt();
                b = Gsc_GetInt();
                func_00261A48(a, b);
                st[12]++;
            }
        }
        if (Gsc_FindOptionN(122, (s8)st[13])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                a = (u16)Gsc_GetInt();
                func_002615F0(a, 0);
                func_002615F0(a, Gsc_GetInt());
                st[13]++;
            }
        }
        if (Gsc_FindOptionN(112, (s8)st[14])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                st[14]++;
            }
        }
        if (Gsc_FindOptionN(80, (s8)st[15])) {
            if (cur >= Gsc_GetInt() * 10) {
                again = 1;
                st[15]++;
            }
        }
        if (Gsc_FindOptionN(103, (s8)st[11]) && cur >= Gsc_GetInt() * 10) {
            again = 1;
            a = Gsc_GetInt();
            func_002A3D90(a, 1, Gsc_GetFloat());
            st[11]++;
        }
    } while (again);

    if (*(s32 *)(st + 0x18) < 0) {
        return func_0025B950() != 0;
    }
    if (func_001018B8() == 3) {
        *(s32 *)(st + 0x14) = 1;
        return func_0025B950() != 0;
    }
    n = *(s32 *)(st + 0x10);
    if (*(s32 *)(st + 0x14) != 0 && n >= 600) {
        a = func_002A3E38();
        if (a > 0) {
            func_002A4098(a - 1);
        }
        *(s32 *)(st + 0x10) = 0;
        *(s32 *)(st + 0x18) = -1;
        n = 0;
    }
    *(s32 *)(st + 0x10) = n + 10;
    return func_0025B950() != 0;
}

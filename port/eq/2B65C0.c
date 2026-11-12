#include "common.h"

u8 *func_002B61E0(u8 *arg0);
void func_002B45D8(u8 *arg0);
void func_002BD250(s32 arg0, s32 arg1);
void func_002BC600(void);
void func_002BC418(void);
void func_002BC318(void);
void func_002BC3C8(void);
void func_002BC370(void);
void func_002B93B8(void);
void func_00300918(void);
void func_002B67F8(void);
void func_002ED3B0(void);
void func_002BD488(void);
void func_00305490(void);
void func_00303CC8(void);
void func_003046E0(void);
void func_002B7780(void);
void func_002BC228(void);
extern s32 D_00345340 __attribute__((section(".data")));

void func_002B65C0(u8 *arg0) {
    u8 *s0;
    u8 *temp;
    s32 s1;
    s32 s2;
    s32 v;

    temp = func_002B61E0(arg0);
    v = D_00345340 - 1;
    D_00345340 = v;
    if (v == 0) {
        s0 = temp + 0x6C;
        s2 = 0;
        s1 = 7;
        do {
            if (*(s32 *)s0 == 1) {
                s2 += 1;
                func_002B45D8(s0);
            }
            s1 -= 1;
            s0 += 0x304;
        } while (s1 >= 0);
        if (s2 == 0) {
            func_002BD250(0, 1);
            func_002BC600();
            func_002BD250(0, 0);
        }
        func_002BC418();
        func_002BC318();
        func_002BC3C8();
        func_002BC370();
        func_002B93B8();
        func_00300918();
        func_002B67F8();
        func_002ED3B0();
        func_002BD488();
        func_00305490();
        func_00303CC8();
        func_003046E0();
        func_002B7780();
        func_002BC228();
    }
}

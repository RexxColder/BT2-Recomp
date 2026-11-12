#include "common.h"

void func_002F4068(void);
void func_002EFD68();
void func_0030A528();
void func_002F1830();
void func_00300918();
void func_002E93C0();
void func_003074A0(s32 arg0, s32 arg1);
void func_00307B38();
void func_002F0130();
void func_002E9FF0();
void func_00303CC8();
void func_003046E0();
void func_00305490();
void func_002E93D8();
void func_002E9390();
void func_003070D0(s32 arg0);
void func_002F3E60(s32 arg0);
extern s32 D_0034AEC0 __attribute__((section(".data")));
extern s32 D_0034AEC8 __attribute__((section(".data")));
extern s32 D_0034AED4 __attribute__((section(".data")));
extern s8 D_0034AEE0[] __attribute__((section(".data")));
extern s32 D_003553DC __attribute__((section(".data")));
extern u8 D_0037C2B0[] __attribute__((section(".data")));

void func_002ED3B0(void) {
    s32 temp_v0;
    s32 s1;
    s8 *s0;

    temp_v0 = D_0034AEC0 - 1;
    D_0034AEC0 = temp_v0;
    if (temp_v0 != 0) {
        return;
    }

    D_003553DC = 0;
    func_002F4068();
    func_002EFD68();
    func_0030A528();
    func_002F1830();
    func_00300918();
    func_002E93C0();
    func_003074A0(2, 1);
    func_003074A0(4, D_0034AED4);
    func_003074A0(5, D_0034AEC8);
    func_00307B38();
    func_002F0130();
    func_002E9FF0();
    func_00303CC8();
    func_003046E0();
    func_00305490();
    func_002E93D8();
    func_002E9390();
    D_003553DC = 1;

    s1 = 0xF;
    s0 = D_0034AEE0;
    do {
        if (*s0 != 0) {
            func_003070D0((s32)D_0037C2B0);
            func_002F3E60((s32)s0);
        }
        s1 -= 1;
        s0 += 0xC8;
    } while (s1 >= 0);
}

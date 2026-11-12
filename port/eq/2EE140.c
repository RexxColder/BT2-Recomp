#include "common.h"

void func_002EE3A0(s32 arg0);
void func_002EE3F0(void);
s32 func_002EE408(s32 arg0);
s32 func_002EE8A8(void);
void func_002EF868(void);
u8 *func_003079F8(void);
void func_0032EAA0(void);
extern s32 D_0034BBA4 __attribute__((section(".data")));
extern s32 D_0034BBB4 __attribute__((section(".data")));
extern s64 D_0034BBE0 __attribute__((section(".data")));
extern s32 D_0034BC10 __attribute__((section(".data")));
extern s64 D_0034BC58 __attribute__((section(".data")));
extern s64 D_0034BC60 __attribute__((section(".data")));
extern s32 D_0034BC88 __attribute__((section(".data")));

void func_002EE140(void) {
    u8 *s0;
    s32 r;

    if (D_0034BC58 == 0) {
        do {
            D_0034BBE0 += 1;
            D_0034BBB4 = 1;
            s0 = func_003079F8();
            D_0034BBB4 = 0;
            if (D_0034BBA4 == 1) {
                D_0034BBA4 = 0;
                func_002EE3F0();
            }
            if (s0 == NULL) {
                if (func_002EE8A8() == 1) {
                    r = func_002EE408(D_0034BC10);
                    if (r == D_0034BC10) {
                        func_002EE3A0(D_0034BC10);
                    }
                }
                if (D_0034BBA4 != 1) {
                    func_002EF868();
                    D_0034BC88 = 1;
                }
                func_002EE3F0();
            }
        } while (D_0034BC58 == 0);
    }
    D_0034BC60 = 1;
    func_0032EAA0();
}

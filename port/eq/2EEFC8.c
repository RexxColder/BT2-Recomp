#include "common.h"

void func_002EE408(s32 arg0);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0);
extern s32 D_0034BBF8 __attribute__((section(".data")));
extern s64 D_0034BC18 __attribute__((section(".data")));
extern s64 D_0034BC20 __attribute__((section(".data")));

void func_002EEFC8(void) {
    if (D_0034BC20 == 0) {
        do {
            D_0034BC18 = 1;
            func_0032EAF0(D_0034BBF8, 1);
            func_0032EB90(D_0034BBF8);
            func_002EE408(D_0034BBF8);
        } while (D_0034BC20 == 0);
    }
    D_0034BC20 = 0;
    D_0034BC18 = 0;
    D_0034BBF8 = 0;
}

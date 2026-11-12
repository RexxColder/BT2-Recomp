#include "common.h"

void func_002EE350();
s32 func_002EE8A8(void);
void func_0030A800(void);
extern s32 D_0034AED8 __attribute__((section(".data")));
extern s32 D_0034BBA8 __attribute__((section(".data")));
extern s32 D_0034BBAC __attribute__((section(".data")));
extern s32 D_0034BBB0 __attribute__((section(".data")));
extern s64 D_0034BBF0 __attribute__((section(".data")));
extern s32 D_0034BBFC __attribute__((section(".data")));
extern s32 D_0034BC00 __attribute__((section(".data")));
extern s32 D_0034BC04 __attribute__((section(".data")));
extern s32 D_0034BC7C __attribute__((section(".data")));
extern s32 (*D_0034BC80)(s32) __attribute__((section(".data")));
extern s32 gFileReq __attribute__((section(".data")));

s32 func_002EF0D8(s32 arg0) {
    s32 temp_v0;

    D_0034AED8 += 1;
    if (D_0034BC7C == 0) {
        D_0034BC7C = 1;
        if (gFileReq > 0) {
            if (D_0034BBA8 != 1) {
                func_002EE350(D_0034BC00, (s32)&D_0034BC7C);
            }
            if (D_0034BBB0 != 1) {
                func_002EE350(D_0034BC04);
            }
            temp_v0 = func_002EE8A8();
            if (temp_v0 == 1 && D_0034BBAC != temp_v0) {
                func_002EE350(D_0034BBFC);
            }
            D_0034BBF0 += 1;
        }
        func_0030A800();
        D_0034BC7C = 0;
    }
    if (D_0034BC80 == NULL) {
        return 0;
    }
    return D_0034BC80(arg0);
}

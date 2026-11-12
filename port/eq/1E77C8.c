#include "common.h"

void func_0020C9B0(s32 arg0, s32 arg1);
void func_002822C8(s32 arg0, s32 arg1, f32 farg0);
void func_0020CB20(void);
void func_001329A0(s32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_0027BCC0(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4);
void FlashShapePool_Term(s32 arg0);
extern f32 D_003856A8;
extern f32 D_003856AC;

void func_001E77C8(void *arg0) {
    s32 sp[4];
    u8 *obj;
    u8 *s1;
    s32 s2;
    f32 f23;
    f32 f21;
    f32 f20;
    f32 f22;

    obj = *(u8 **)((u8 *)arg0 + 0x38);
    f20 = 10.0f;
    f22 = 50.0f;
    f23 = D_003856A8;
    s1 = obj + 0x88;
    s2 = 1;

    func_0020C9B0(*(s32 *)(obj + 0x68), 0);
    f21 = D_003856AC;
    func_002822C8(1, 1, 0.0f);
    func_0020CB20();
    func_001329A0(1);
    func_00208DE8(*(s32 *)(obj + 0x68), (s32)sp, 3);
    func_0027BCC0(*(s32 *)(obj + 0x68), (s32)sp, f23, f20, f22, f20, f21);
    func_0027BCC0(*(s32 *)(obj + 0x68), (s32)sp, f23, f20, f22, f20, f21);

    do {
        s1 += 4;
        s2 -= 1;
        FlashShapePool_Term((s32)(s1 - 4));
    } while (s2 >= 0);
}

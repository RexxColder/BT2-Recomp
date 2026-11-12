#include "common.h"

extern u8 D_0037B188[] __attribute__((section(".data")));

typedef s32 (*VtFnA)(void *arg0, s32 arg1, s32 arg2, s32 *arg3);
typedef s32 (*VtFnB)(void *arg0, s32 arg1, s32 *arg2);
typedef void (*FnPtrS)(s32 arg0, s32 arg1);

void *memcpy(void *arg0, void *arg1, u32 arg2);
void func_002E33B8(void *arg0, void *arg1, s32 arg2);

void func_002E3240(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 fr[8];
    s32 *sp = fr;
    s32 *sp10 = fr + 4;
    s32 s3, s4;
    void **s1;
    u8 *var;
    FnPtrS fn;

    s3 = *(s32 *)(arg0 + 0x580);
    s4 = (s3 * 12) + 0x110;
    s1 = *(void ***)(arg0 + s4 + 0xC);
    if (s1 != NULL) {
        (*(VtFnA *)((u8 *)*s1 + 0x18))(s1, 0, arg2, sp);
        memcpy((void *)sp[0], arg1, sp[1]);
        (*(VtFnB *)((u8 *)*s1 + 0x20))(s1, 1, sp);
        var = arg0 + s4;
        if (sp[1] < arg2) {
            (*(VtFnA *)((u8 *)*s1 + 0x18))(s1, 0, arg2 - sp[1], sp10);
            memcpy((void *)sp10[0], arg1 + sp[1], sp10[1]);
            (*(VtFnB *)((u8 *)*s1 + 0x20))(s1, 1, sp10);
            var = arg0 + s4;
        }
        fn = *(FnPtrS *)(var + 0x10);
        if (fn != NULL) {
            fn(*(s32 *)(var + 0x14), s3);
        }
    }
    if (s3 == 3) {
        if (*(s32 *)(arg0 + 0x14C) != 0) {
            if (*(s32 *)(arg0 + 0x524) != 0) {
                func_002E33B8(arg0, D_0037B188, 8);
            }
            func_002E33B8(arg0, arg1, arg2);
        }
    }
}

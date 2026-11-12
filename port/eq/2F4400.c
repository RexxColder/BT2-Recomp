#include "common.h"

void func_002E93C0(u8 *arg0);
void func_002E93D8(void);
void func_002EFE08(s32 arg0, s32 arg1);
void func_002EFE20(s32 arg0, s32 arg1);
void func_003031A8(s32 arg0, s32 arg1);
void func_002F0480(s32 arg0);
void func_003080A0(void *arg0);

/* 0x002F4400(obj): func_002E93C0(obj); func_002EFE08 and func_002EFE20 on word +0xC with 0; func_003031A8 on it with 1;
 * func_002F0480(word +4). When byte +2 is 2 and the pointer at +0x14 is set: it is cleared and its vtable entry at
 * +0xC is called with it. Then func_003080A0 on the pointer at +0x74 when set; byte +0xAC = 0; word +0x14 = 0;
 * byte +1 = 0; func_002E93D8(). */
void func_002F4400(u8 *arg0) {
    void *p;
    void *q;
    void (*fn)(void *);

    func_002E93C0(arg0);
    func_002EFE08(*(s32 *)(arg0 + 0xC), 0);
    func_002EFE20(*(s32 *)(arg0 + 0xC), 0);
    func_003031A8(*(s32 *)(arg0 + 0xC), 1);
    func_002F0480(*(s32 *)(arg0 + 4));
    if ((s8)arg0[2] == 2) {
        p = *(void **)(arg0 + 0x14);
        if (p != NULL) {
            *(void **)(arg0 + 0x14) = NULL;
            fn = *(void (**)(void *))((u8 *)(*(void **)p) + 0xC);
            fn(p);
        }
    }
    q = *(void **)(arg0 + 0x74);
    if (q != NULL) {
        func_003080A0(q);
    }
    arg0[0xAC] = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    arg0[1] = 0;
    func_002E93D8();
}

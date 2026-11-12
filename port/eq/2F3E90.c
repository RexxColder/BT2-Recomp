#include "common.h"

#define VCALL(obj) do { u8 *_vt = *(u8 **)(obj); ((void (*)(u8 *))(*(void **)(_vt + 0xC)))(obj); } while (0)

void func_002EA050(u8 *arg0);
void func_002F3DE8(u8 *arg0);
void func_002F3E10(u8 *arg0);
void func_002F3E38(u8 *arg0);
void func_002F44D0(u8 *arg0);
void func_002EFDA0(u8 *arg0);
void func_002F0328(u8 *arg0);
void func_002F2220(u8 *arg0, s32 arg1, s32 arg2);
void func_002F1BC0(u8 *arg0);
void func_002FFB40(u8 *arg0);
void func_002E93C0();
void func_00307EA8(u8 *arg0);
void func_002E93D8();
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_0037C768 __attribute__((section(".data")));

void func_002F3E90(u8 *arg0) {
    u8 *t;
    u8 *s0;
    u8 *s2;
    s32 s3;

    if (arg0 == NULL) {
        func_002EA050(&D_0037C768);
        return;
    }
    func_002F3DE8(arg0);
    func_002F3E10(arg0);
    func_002F3E38(arg0);
    if (*(s8 *)arg0 == 1) {
        func_002F44D0(arg0);
    }
    t = *(u8 **)(arg0 + 0xC);
    if (t != NULL) {
        *(s32 *)(arg0 + 0xC) = 0;
        func_002EFDA0(t);
    }
    t = *(u8 **)(arg0 + 0x4);
    if (t != NULL) {
        *(s32 *)(arg0 + 0x4) = 0;
        func_002F0328(t);
    }
    s0 = *(u8 **)(arg0 + 0x8);
    if (s0 != NULL) {
        *(s32 *)(arg0 + 0x8) = 0;
        func_002F2220(s0, 0, 0);
        func_002F1BC0(s0);
    }
    t = *(u8 **)(arg0 + 0x94);
    if (t != NULL) {
        *(s32 *)(arg0 + 0x94) = 0;
        func_002FFB40(t);
    }
    func_002E93C0();
    t = *(u8 **)(arg0 + 0x10);
    if (t != NULL) {
        *(s32 *)(arg0 + 0x10) = 0;
        VCALL(t);
    }

    s3 = 0;
    if (*(s8 *)(arg0 + 0x3) > 0) {
        s2 = arg0 + 0x80;
        s0 = arg0 + 0x78;
        do {
            t = *(u8 **)(s0 - 0x60);
            if (t != NULL) {
                *(s32 *)(s0 - 0x60) = 0;
                VCALL(t);
            }
            t = *(u8 **)s0;
            if (t != NULL) {
                *(s32 *)s0 = 0;
                VCALL(t);
            }
            t = *(u8 **)s2;
            if (t != NULL) {
                *(s32 *)s2 = 0;
                VCALL(t);
            }
            s3 += 1;
            s2 += 4;
            s0 += 4;
        } while (s3 < *(s8 *)(arg0 + 0x3));
    }

    t = *(u8 **)(arg0 + 0x74);
    if (t != NULL) {
        *(s32 *)(arg0 + 0x74) = 0;
        func_00307EA8(t);
    }
    memset(arg0, 0, 0xC8);
    *(u8 *)arg0 = 0;
    func_002E93D8();
}

#include "common.h"

void func_002E93C0();
void func_002E93D8(void);
void func_002EFE08(s32 arg0, s32 arg1);
void func_002EFE20(s32 arg0, s32 arg1);
void func_002F0480(s32 arg0);
void func_002F1F10(s32 arg0, s32 arg1);
void func_002F2000(s32 arg0);
void func_002F21A0(s32 arg0);
void func_002F4130(void *arg0, void *arg1);

void func_002F8620(void *arg0) {
    void *temp_a0_2;
    void *temp_a0_3;
    u8 *vt;
    void (*fn)(void *);
    s32 var_s2;
    void **var_s0;

    func_002E93C0(arg0);
    func_002EFE08(*(s32 *)((u8 *)arg0 + 0xC), 0);
    func_002EFE20(*(s32 *)((u8 *)arg0 + 0xC), 0);
    func_002F0480(*(s32 *)((u8 *)arg0 + 4));
    func_002E93D8();
    if (*(s32 *)((u8 *)arg0 + 8) != 0) {
        func_002F21A0(*(s32 *)((u8 *)arg0 + 8));
        temp_a0_2 = *(void **)((u8 *)arg0 + 0x14);
        vt = *(u8 **)temp_a0_2;
        fn = *(void (**)(void *))(vt + 0x14);
        fn(temp_a0_2);
    }
    var_s2 = 0;
    func_002E93C0(arg0);
    if (*(s8 *)((u8 *)arg0 + 3) > 0) {
        var_s0 = (void **)((u8 *)arg0 + 0x18);
        do {
            temp_a0_3 = *var_s0;
            var_s0 += 1;
            var_s2 += 1;
            vt = *(u8 **)temp_a0_3;
            fn = *(void (**)(void *))(vt + 0x14);
            fn(temp_a0_3);
        } while (var_s2 < *(s8 *)((u8 *)arg0 + 3));
    }
    if (*(s32 *)((u8 *)arg0 + 8) != 0) {
        func_002F1F10(*(s32 *)((u8 *)arg0 + 8), 0);
        func_002F2000(*(s32 *)((u8 *)arg0 + 8));
    }
    func_002F4130(arg0, *(void **)((u8 *)arg0 + 0x14));
    func_002E93D8();
}

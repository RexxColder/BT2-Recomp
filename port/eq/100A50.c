#include "common.h"

extern u8 D_003B0530[] __attribute__((section(".data")));
extern u8 D_003B0548[] __attribute__((section(".data")));
extern u8 D_00387680[] __attribute__((section(".data")));
extern u8 D_0036C350[] __attribute__((section(".data")));
extern s32 D_00387F00[];
extern s32 D_00387F08;
extern s32 D_00387F1C;
extern s32 gStgPanBlur;

void *memset(void *arg0, s32 arg1, s32 arg2);
u8 *malloc(s32 arg0);
s32 func_0028BAA8(s32 arg0);
void func_002ED220(void);
void func_002EE8E0(s32 arg0);
void func_002EE8C8(s32 arg0, s32 arg1);
void func_001006D8(void);
void func_00100700(void);
void func_002F3408(u8 *arg0);
void func_002F3508(u8 *arg0);
s32 func_002F39D8(s32 arg0, s32 arg1, s32 arg2);
void func_002F5620(s32 arg0, s32 arg1);
void func_002F5858(s32 arg0, s32 arg1);
void sceGsSyncVCallback(s32 arg0);

void func_00100A50(void) {
    s32 *s2;
    s32 *s0;
    s32 s1;
    s32 t;
    s32 a0v;

    s2 = D_00387F00;
    memset(D_003B0530, 0, 0x14);
    *(s32 *)D_003B0530 = (s32)D_00387680;
    func_002F3408(D_003B0530);
    memset(D_003B0548, 0, 0x10);
    *(s32 *)D_003B0548 = (s32)D_0036C350;
    *(s32 *)(D_003B0548 + 4) = 0x10;
    s1 = 1;
    *(s32 *)(D_003B0548 + 0xC) = 0x190;
    *(s32 *)(D_003B0548 + 8) = (s32)malloc(0x190);
    func_002F3508(D_003B0548);
    func_002ED220();
    func_002EE8E0(0);
    sceGsSyncVCallback((s32)func_001006D8);
    func_002EE8C8((s32)func_00100700, 0);

    t = func_002F39D8(2, func_0028BAA8(0x659E4), 0x659E4);
    gStgPanBlur = t;
    func_002F5858(t, 0x28);
    t = func_002F39D8(2, func_0028BAA8(0x299E4), 0x299E4);
    D_00387F1C = t;
    func_002F5858(t, 0x14);
    t = func_002F39D8(2, func_0028BAA8(0x301E4), 0x301E4);
    D_00387F08 = t;
    func_002F5858(t, 0x28);
    do {
        s1 -= 1;
        t = func_002F39D8(2, func_0028BAA8(0x301E4), 0x301E4);
        *s2 = t;
        func_002F5858(t, 0x28);
        s2 += 1;
    } while (s1 >= 0);

    s0 = D_00387F00;
    s1 = 1;
    func_002F5620(gStgPanBlur, 0x1E);
    func_002F5620(D_00387F1C, 0x1E);
    func_002F5620(D_00387F08, 0x1E);
    a0v = D_00387F00[0];
    do {
        s0 += 1;
        s1 -= 1;
        func_002F5620(a0v, 0x1E);
        if (s1 < 0) {
            break;
        }
        a0v = *s0;
    } while (1);
}

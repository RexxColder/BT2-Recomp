#include "common.h"

extern u8 D_003B0530[];
extern u8 D_003B0548[];
extern u8 D_00387680[];
extern u8 D_0036C350[];
extern u8 D_0036C360[];
extern s32 D_00387F00[];
extern s32 D_00387F08;
extern s32 D_00387F10;
extern s32 D_00387F14;
extern s32 D_00387F1C;
extern s32 D_00387F20;
extern s32 gStgPanBlur;

void *memset(void *arg0, s32 arg1, s32 arg2);
u8 *malloc(s32 arg0);
void func_001006D8(void);
void func_00100700(void);
void func_002F3408(s32 arg0);
void func_002F3508(s32 arg0);
void func_002ED220(void);
void func_002EE8E0(s32 arg0);
void sceGsSyncVCallback(s32 arg0);
void func_002EE8C8(s32 arg0, s32 arg1);
s32 func_0028BAA8(s32 arg0);
s32 func_002EA588(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002EAFA8(s32 arg0);
void func_002EF218(void);
s32 func_002F39D8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F5858(s32 arg0, s32 arg1);
void func_002F5620(s32 arg0, s32 arg1);

void func_00100708(void) {
    s32 *s0;
    s32 r;
    s32 i;
    s32 a;

    memset(D_003B0530, 0, 0x14);
    *(s32 *)(D_003B0530 + 0) = (s32)D_00387680;
    func_002F3408((s32)D_003B0530);

    memset(D_003B0548, 0, 0x10);
    *(s32 *)(D_003B0548 + 0) = (s32)D_0036C350;
    *(s32 *)(D_003B0548 + 4) = 0x10;
    *(s32 *)(D_003B0548 + 0xC) = 0x190;
    *(s32 *)(D_003B0548 + 8) = (s32)malloc(0x190);
    func_002F3508((s32)D_003B0548);

    func_002ED220();
    func_002EE8E0(0);
    sceGsSyncVCallback((s32)func_001006D8);
    func_002EE8C8((s32)func_00100700, 0);

    r = func_0028BAA8(0x6880);
    D_00387F20 = 0;
    D_00387F10 = r;
    func_002EA588(0, (s32)D_0036C360, 0, r);
    while (func_002EAFA8(D_00387F20) != 3) {
        func_002EF218();
    }

    s0 = D_00387F00;
    D_00387F14 = func_0028BAA8(0xFD04);
    r = func_0028BAA8(0x659E4);
    r = func_002F39D8(2, r, 0x659E4);
    gStgPanBlur = r;
    func_002F5858(r, 0x28);

    r = func_0028BAA8(0x299E4);
    r = func_002F39D8(2, r, 0x299E4);
    D_00387F1C = r;
    func_002F5858(r, 0x14);

    r = func_0028BAA8(0x301E4);
    r = func_002F39D8(2, r, 0x301E4);
    D_00387F08 = r;
    func_002F5858(r, 0x28);

    for (i = 0; i < 2; i++) {
        r = func_0028BAA8(0x301E4);
        r = func_002F39D8(2, r, 0x301E4);
        *s0 = r;
        s0++;
        func_002F5858(r, 0x28);
    }

    func_002F5620(gStgPanBlur, 0x1E);
    func_002F5620(D_00387F1C, 0x1E);
    func_002F5620(D_00387F08, 0x1E);

    s0 = D_00387F00;
    a = *s0;
    for (i = 0; i < 2; i++) {
        s0++;
        func_002F5620(a, 0x1E);
        if (i == 0) {
            a = *s0;
        }
    }
}

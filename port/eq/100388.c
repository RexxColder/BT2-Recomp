#include "common.h"

extern u8 D_0036C1A8[] __attribute__((section(".data")));
extern u8 D_0036C1C8[] __attribute__((section(".data")));
extern u8 D_0036C1E8[] __attribute__((section(".data")));
extern u8 D_0036C200[] __attribute__((section(".data")));
extern u8 D_0036C220[] __attribute__((section(".data")));
extern u8 D_0036C240[] __attribute__((section(".data")));
extern u8 D_0036C258[] __attribute__((section(".data")));
extern u8 D_0036C278[] __attribute__((section(".data")));
extern u8 D_0036C290[] __attribute__((section(".data")));
extern u8 D_0036C2B0[] __attribute__((section(".data")));
extern u8 D_0036C2D0[] __attribute__((section(".data")));
extern u8 D_0036C2F0[] __attribute__((section(".data")));
extern u8 D_0036C310[] __attribute__((section(".data")));
extern u8 D_0036C330[] __attribute__((section(".data")));
extern u8 *D_003876A4;

void func_00321E50(void);
void sceSifInitRpc(s32 arg0);
void sceCdInit(s32 arg0);
void sceCdMmode(s32 arg0);
s32 sceSifRebootIop(void *arg0);
s32 sceSifSyncIop(void);
void func_00100258(void);
void sceFsReset(void);
s32 func_00337C28(void *arg0, s32 arg1, s32 arg2);
void sceSifInitIopHeap(void *arg0);
s32 sceChk01(void *arg0);
void Dma_InitController(void);
void sceGsResetPath(void);
void sceGsResetGraph(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00270FF0(void);
s32 func_0032EB50(void);
void func_0032EAF0(s32 arg0, s32 arg1);
void func_0028BA70(void);
void func_0028AFA0(void);
void func_00298438(void);
void func_00297908(void);
void func_0028BCF8(void);
void McCard_Init(void);
void func_00100708(void);
void Gfx_SyncField(void);
void func_00271078(void);
s64 GetTimerSystemTime(void);
void func_00325370(s64 arg0);
void func_001021E8(void);
void func_00297A60(s32 arg0, s32 arg1);
void Overlay_Load(s32 arg0);
void func_3B7FA8(s32 arg0);
void func_002A8A38(s32 arg0, s32 arg1);
void func_00103000(s32 arg0, s32 arg1);

s32 func_00100388(void) {
    u8 sp[0x10];
    s32 v0;
    s32 a1;

    func_00321E50();
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(2);
    do {
    } while (sceSifRebootIop(D_0036C1A8) == 0);
    do {
    } while (sceSifSyncIop() == 0);
    func_00100258();
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(2);
    sceFsReset();
    do {
    } while (func_00337C28(D_0036C1C8, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C1E8, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C200, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C220, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C240, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C258, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C278, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C290, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C2B0, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C2D0, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C2F0, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C310, 0, 0) < 0);
    do {
    } while (func_00337C28(D_0036C330, 0, 0) < 0);
    sceSifInitIopHeap(D_0036C330);
    sceChk01(sp);
    Dma_InitController();
    sceGsResetPath();
    sceGsResetGraph(0, 1, 2, 1);
    func_00270FF0();
    func_0032EAF0(func_0032EB50(), 2);
    func_0028BA70();
    func_0028AFA0();
    func_00298438();
    func_00297908();
    func_0028BCF8();
    McCard_Init();
    func_00100708();
    func_00100258();
    Gfx_SyncField();

    if (sceChk01(sp) < 0) {
        return 0;
    }
    if (*(s32 *)sp != 0) {
        return 0;
    }
    func_00271078();
    func_00325370((s64)(GetTimerSystemTime() << 32) >> 32);
    func_001021E8();
    func_00297A60(0x543, 0);
    for (;;) {
        Overlay_Load(0);
        func_3B7FA8(0);
        v0 = *(s32 *)(D_003876A4 + 0x18);
        a1 = v0 ^ 0x200;
        if (v0 & 0x200) {
            *(s32 *)(D_003876A4 + 0x18) = a1;
            func_002A8A38(0, a1);
        } else {
            func_00103000(0, a1);
        }
    }
}

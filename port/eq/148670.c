#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
extern u8 D_00340264[] __attribute__((section(".data")));

u8 *func_00148530(s32 a0, s32 a1);
f32 func_001488F8(u8 *s0);
f32 func_00148008(s32 a0, s32 a1);
s32 func_00126560(void);
s32 func_001F42A0(void);
void EftTechEvt_Start(u8 *s0, s32 a1, s32 a2);
void BtlTaskList_AddTail(void *list, void *cls, void *init);
void bt2_fightlog_note(const char *fmt, ...);

void func_00148670(u8 *s1) {
    u8 *s0;
    u8 *p1;
    u8 *p2;
    u8 *s2;
    u8 *s3;
    s32 v;
    f32 f20;
    f32 g;

    s0 = func_00148530(*(s32 *)(s1 + 0), *(s32 *)(s1 + 4));
    if (s0 == NULL) {
        return;
    }
    p1 = *(u8 **)(s0 + 0x20);
    v = *(s32 *)p1;
    s2 = *(u8 **)(D_00340264 + v * 12);
    /* B10 log temporal: tipo de efecto de tecnica pedido y su clase */
    bt2_fightlog_note("B10 SHOT-PIDE obj %d slot %d tipo %d clase %p", *(s32 *)(s1 + 0), *(s32 *)(s1 + 4), v, s2);
    if (s2 == NULL) {
        return;
    }
    s3 = *(u8 **)(s0 + 0x28);
    memcpy(s0, s1, 0x1C);
    p2 = *(u8 **)(s0 + 0x24);
    *(s32 *)p2 = (s32)(*(f32 *)(s1 + 0x10) * 30.0f);
    *(f32 *)(p2 + 0x4) = *(f32 *)(s1 + 0xC);
    *(f32 *)(p2 + 0x8) = *(f32 *)(s1 + 0x14);
    *(f32 *)(p2 + 0x10) = *(f32 *)(s1 + 0x18);
    p1 = *(u8 **)(s0 + 0x20);
    *(f32 *)(p1 + 0x18) = *(f32 *)(s1 + 0x18);
    if (*(s32 *)(p1 + 0x4) == 0) {
        *(s32 *)p2 = 0x3C;
    }
    *(s32 *)(s0 + 0x40) = 0;

    g = func_001488F8(s0);
    f20 = g;
    func_00148008(*(s32 *)(s1 + 0), *(s32 *)(s1 + 4));
    if (func_00126560() != 0) {
        *(s32 *)s0 = func_001F42A0();
    }
    v = (s32)f20;
    p2 = *(u8 **)(s0 + 0x24);
    EftTechEvt_Start(s0, v, *(s32 *)p2);
    BtlTaskList_AddTail(*(void **)(s3 + 0x24), s2, s0);
}

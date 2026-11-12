#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern u8 D_00342A10[] __attribute__((section(".data")));
extern f32 D_00385190;
extern f32 D_00385194;
extern void *D_003878AC;

s32 rand(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00129C28(void *arg0, void *arg1);
void BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);

void func_001C8380(void *arg0, void *arg1, void *arg2) {
    u8 buf[0xC0];
    u8 *s0 = buf + 0x30;

    *(s64 *)(buf + 0x00) = *(s64 *)((u8 *)arg0 + 0x00);
    *(s64 *)(buf + 0x08) = *(s64 *)((u8 *)arg0 + 0x08);
    *(s64 *)(buf + 0x10) = *(s64 *)((u8 *)arg1 + 0x00);
    *(s64 *)(buf + 0x18) = *(s64 *)((u8 *)arg1 + 0x08);
    *(s64 *)(buf + 0x20) = *(s64 *)((u8 *)arg2 + 0x00);
    *(s64 *)(buf + 0x28) = *(s64 *)((u8 *)arg2 + 0x08);
    memset(s0, 0, 0x60);
    W(s0, 0) = 0;
    F(buf, 0x70) = (((f32)rand()) / D_00385190) * 3.5f + 2.5f;
    F(buf, 0x74) = 2.0f * (((f32)rand()) / D_00385190) + 1.0f;
    F(buf, 0x78) = (((f32)rand()) / D_00385190) * D_00385194;
    W(buf, 0x7C) = 5;
    W(buf, 0x80) = 0;
    func_00129C28(buf + 0x50, buf + 0x10);
    func_00129C28(buf + 0x40, buf + 0x20);
    func_00129C28(buf + 0x60, buf + 0x00);
    F(buf, 0x5C) = 1.0f;
    BtlTaskList_AddTail(W(D_003878AC, 0x208), D_00342A10, s0);
}

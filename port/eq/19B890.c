#include "common.h"

void func_0019BB28(s32 arg0);
void func_0019BEE8(s32 arg0);
s32 func_0019BDF0(s32 arg0);
s32 func_0019C0C0(s32 arg0);
void func_0019BE78(s32 arg0);
void func_0019C128(s32 arg0);
void func_0019C060(s32 arg0);
void func_0019BD50(s32 arg0);
void func_0019C170(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129C38(s32 arg0, s32 arg1);

void func_0019B890(s32 arg0) {
    u8 sp[0x30];
    u8 *self;
    u8 *P;
    u8 *s3;
    s32 ret;
    s32 tt;

    self = (u8 *)arg0;
    P = (u8 *)*(s32 *)(self + 0x38);
    s3 = P;
    switch (*(u8 *)(self + 1)) {
    case 0:
        func_0019BB28((s32)self);
        func_0019BEE8((s32)self);
        s3 = (u8 *)*(s32 *)(self + 0x38);
        *(u8 *)(self + 1) = (u8)(*(u8 *)(self + 1) + 1);
        break;
    case 1:
        *(u8 *)(self + 1) = 2;
        break;
    case 2:
        func_0019BDF0((s32)self);
        ret = func_0019C0C0((s32)self);
        if (ret == 0) {
            *(u16 *)(P + 0x88) = (u16)(*(u16 *)(P + 0x88) | 2);
            tt = *(u16 *)(P + 0x88);
        } else {
            tt = ret;
        }
        if ((tt & 2) != 0) {
            if (ret != 0) {
                func_0019BE78((s32)self);
                func_0019C128((s32)self);
            }
            *(u8 *)(self + 1) = (u8)(*(u8 *)(self + 1) + 1);
        }
        s3 = (u8 *)*(s32 *)(self + 0x38);
        break;
    default:
        break;
    }

    func_00208DE8(*(s32 *)(s3 + 0x80), (s32)sp, 0x15);
    func_00208DE8(*(s32 *)(s3 + 0x80), (s32)(sp + 0x10), 0x14);
    Vec3_Sub((s32)(sp + 0x20), (s32)sp, (s32)(sp + 0x10));
    Vec3_Normalize((s32)(sp + 0x20), (s32)(sp + 0x20));
    func_00129C38((s32)(s3 + 0x60), (s32)(sp + 0x20));
    func_00129C38((s32)(s3 + 0x40), (s32)sp);
    func_00208DE8(*(s32 *)(s3 + 0x80), (s32)sp, 0x23);
    func_00208DE8(*(s32 *)(s3 + 0x80), (s32)(sp + 0x10), 0x22);
    Vec3_Sub((s32)(sp + 0x20), (s32)sp, (s32)(sp + 0x10));
    Vec3_Normalize((s32)(sp + 0x20), (s32)(sp + 0x20));
    func_00129C38((s32)(s3 + 0x70), (s32)(sp + 0x20));
    func_00129C38((s32)(s3 + 0x50), (s32)sp);
    func_0019C060((s32)self);
    func_0019BD50((s32)self);
    func_0019C0C0((s32)self);
    func_0019BDF0((s32)self);
    if ((*(u16 *)(P + 0x88) & 4) != 0) {
        func_0019C170((s32)self, *(s32 *)(P + 0x80));
        BtlTask_SetDead((s32)self);
    }
}

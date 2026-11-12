#include "common.h"

s32 func_002CBE18(s32 arg0);
void func_002CB748(s32 arg0);
void func_002CBA48(s32 arg0);
void func_002CB948(s32 arg0);
void func_002CC9A0(s32 arg0);
s32 func_002DDF60(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DDF68(s32 arg0, s32 arg1, s32 arg2);
void sceMpegGetPicture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void sceMpegGetPictureRAW8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002CC630(s32 arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u8 *s2;
    u8 *s3;
    s32 s6;
    s32 v0;
    s32 v1;
    s32 a2;
    s32 a3;

    if (func_002CBE18((s32)arg3) == 0) {
        return func_002DDF60(arg0, arg1, (s32)arg2);
    }
    s2 = *(u8 **)(arg3 + 0x1FC0);
    s6 = func_002DDF68(arg0, arg1, (s32)arg2);
    s3 = s2 + 0x1128;
    func_002CBA48((s32)(s2 + 0x1198));
    func_002CB748((s32)(s2 + 0x1198));
    *(s32 *)(s3 + 0x14) = 1;
    v1 = *(s32 *)(s2 + 4 + 0xC);
    v0 = *(s32 *)(s2 + 4 + 0x8);
    a3 = v1 < 0;
    a2 = ((v0 < 0 ? v0 + 0xF : v0) >> 4) * ((v1 < 0 ? v1 + 0xF : v1) >> 4);
    if (*(s32 *)(arg3 + 0x38) == 2) {
        sceMpegGetPicture((s32)(s2 + 0x1150), *(s32 *)(arg2 + 0x20), a2, a3);
    } else {
        sceMpegGetPictureRAW8((s32)(s2 + 0x1150), *(s32 *)(arg2 + 0x20), a2, a3);
    }
    *(s32 *)(s3 + 0x14) = 0;
    func_002CB948((s32)(s3 + 0x70));
    func_002CC9A0((s32)arg3);
    return (*(s32 *)(s3 + 0x18) == 0) ? s6 : -3;
}

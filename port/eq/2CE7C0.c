#include "common.h"

extern void *D_00346E60;

s32 func_002CEC20(u8 *obj, u8 *out);
void func_002C2308(u8 *arg0);
void func_002BFB70(u8 *obj);
s32 func_002C5860(u8 *obj, u8 *out, s32 size);
s32 func_002CE5A0(u8 *obj);
s32 func_002DA3A8(u8 *dst, u8 *src, s32 size);
u8 *func_002CE080(u8 *req, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 code);
void func_002C58E8(u8 *obj, u8 *buf, s32 arg2);
s32 func_002CEC90(u8 *obj, s32 arg1, s32 arg2);
s32 func_002CED10(u8 *obj);
s32 func_002C30A0(u8 *obj, s32 arg1, s32 arg2);
void func_002D1920(u8 *obj, s32 arg1);
void func_002D19A8(u8 *obj, s32 arg1, s32 arg2, s32 arg3);
void func_002D18B0(u8 *obj, s32 arg1);
void func_002CCC80(u8 *obj, s32 arg1);
void func_002CF818(u8 *obj, u8 *arg1);
void func_002D01C0(u8 *obj, s32 arg1);
void func_002D00C8(u8 *obj, s32 arg1);
void func_002D0138(u8 *obj, s32 arg1, s32 arg2);
void func_002D0230(u8 *obj, s32 arg1);
void func_002CF240(u8 *obj, s32 arg1, s32 arg2);

/* Clones the object described by `src` into a freshly created one, re-applying its optional parts. Returns 0 or an error. */
s32 func_002CE7C0(u8 *src) {
    u8 req[0x44];
    u8 info[0x20];
    u8 name[0x190];
    u8 buf[0x40];
    s32 hasInfo;
    s32 infoVal = 0;
    s32 p0;
    s32 p0b;
    s32 p1;
    s32 p2;
    s32 p2b;
    s32 p3;
    s32 p4;
    s32 effCnt;
    s32 owner;
    s32 ownerA = 0;
    s32 ownerB = 0;
    s32 ownerC = 0;
    s32 ownerD = 0;
    s32 ownerE = 0;
    s32 tailPtr;
    s32 tailLen;
    u8 vec[12];
    u8 *ownerObj;
    u8 *obj;
    s32 sz;
    s32 r;
    s32 hook;

    __builtin_memcpy(req, src, 0x44);
    hasInfo = *(s32 *)(src + 0xA2C);
    if (hasInfo != 0) {
        func_002CEC20(src, info);
        infoVal = *(s32 *)(info + 0x14);
    }
    func_002C2308(src + 0x78);
    func_002BFB70(src);
    p0 = *(s32 *)(src + 0x9F8);
    p0b = *(s32 *)(src + 0x9FC);
    __builtin_memcpy(vec, src + 0x12E0, 12);
    ownerObj = *(u8 **)(src + 0x36B0);
    p2 = *(s32 *)(src + 0x1014);
    p3 = *(s32 *)(src + 0xD40);
    p1 = *(s32 *)(src + 0x1004);
    p2b = *(s32 *)(src + 0x1018);
    p4 = *(s32 *)(src + 0xD48);
    effCnt = *(s32 *)(src + 0xFDC);
    if (ownerObj != NULL) {
        ownerA = *(s32 *)(ownerObj + 0xDD0);
        ownerB = *(s32 *)(ownerObj + 0xDC4);
        ownerC = *(s32 *)(ownerObj + 0xDC8);
        ownerD = *(s32 *)(ownerObj + 0xDCC);
        ownerE = *(s32 *)(ownerObj + 0xDD4);
    }
    tailLen = *(s32 *)(src + 0x13C0) << 4;
    tailPtr = *(s32 *)(src + 0x13BC);
    sz = func_002C5860(src, buf, 0x40);
    r = func_002CE5A0(src);
    if (r != 0) {
        return r;
    }
    func_002DA3A8(name, src + 0xB9C, 0x190);
    obj = func_002CE080(req, 0);
    if (obj == NULL) {
        return func_002C2FF0(0, 0xFF000202);
    }
    func_002DA3A8(obj + 0xA0C, name, 0x190);
    func_002DA3A8(obj + 0xB9C, name, 0x190);
    func_002C58E8(obj, buf, sz);
    if (hasInfo != 0) {
        r = func_002CEC20(obj, info);
        if (r != 0) {
            return r;
        }
        r = func_002CEC90(obj, infoVal, *(s32 *)(info + 0x14));
        if (r != 0) {
            return r;
        }
        func_002CED10(obj);
    }
    if (p0 != 0) {
        func_002C30A0(obj, p0, p0b);
    }
    if (p3 != 0) {
        func_002D1920(obj, p3);
    }
    if (p1 != 0) {
        func_002D19A8(obj, p1, p2, p2b);
    }
    if (p4 != 0) {
        func_002D18B0(obj, p4);
    }
    if (effCnt != 1000) {
        func_002CCC80(obj, effCnt);
    }
    if (*(s32 *)vec != 0) {
        __builtin_memcpy(obj + 0x12E0, vec, 12);
        hook = (s32)D_00346E60;
        if (hook != 0) {
            s32 (*fn)(u8 *) = (s32 (*)(u8 *))(u32)hook;
            fn(vec);
        }
    }
    if (ownerObj != NULL) {
        func_002CF818(obj, ownerObj);
        func_002D01C0(obj, ownerA);
        func_002D00C8(obj, ownerB);
        func_002D0138(obj, ownerC, ownerD);
        func_002D0230(obj, ownerE);
    }
    if (tailPtr != 0) {
        func_002CF240(obj, tailPtr, tailLen);
    }
    return 0;
}

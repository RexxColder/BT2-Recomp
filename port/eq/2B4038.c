#include "common.h"

s32 func_002B4488(u8 *arg0);
s32 func_002B61E0(void);
void func_002B6700(s32 arg0);
s32 func_002B43E0(s32 arg0);
void func_002B4430(u8 *arg0, u8 *arg1);
s32 func_002B34D8(s32 arg0, s32 arg1);
void func_002B78F8(s32 arg0);
void func_002B3C80(void *arg0);
void func_002B2D10(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6);
void func_002B3E28(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
s32 func_002B4010(s32 arg0);
s32 func_00303D48(s32 arg0, s32 arg1);
s32 func_002D0A58(s32 arg0, s32 arg1, s32 arg2);
void func_002BD1C8(s32 arg0, s32 arg1);
void func_002BD1D8(s32 arg0, s32 arg1);
s32 func_002BD630(s32 arg0);
void func_002B7448(void *arg0);
s32 func_002FFA00(s32 arg0);
void func_002FFBC0(s32 arg0, s32 arg1);
s32 func_002B4510(u8 *arg0);
s32 func_002B93D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002B9FE8(u8 *arg0);
s32 func_002BA078(s32 arg0);
void func_002BA0D8(u8 *arg0);
void func_002B5DC8(u8 *arg0);
void func_002B5E30(s32 arg0, s32 arg1, s32 arg2);
void func_002B45D8(s32 arg0);
void EftObj_SetMtx(s32 arg0, s32 arg1);
void Rand_Range(const char *msg);

u8 *func_002B4038(u8 *cprm) {
    s32 out[6];
    s32 i;
    s32 sfd;
    s32 sj;
    u8 *table;
    u8 *h;
    const char *err;

    if (cprm == 0) {
        Rand_Range("E1122612 mwPlyCreateSofdec : cprm is NULL.");
        return 0;
    }
    if (func_002B4488(cprm) != 1) {
        return 0;
    }
    table = (u8 *)func_002B61E0();
    i = 0;
    h = table + 0x6C;
    if (*(s32 *)h == 1) {
        i = 1;
        while (i < 8) {
            h += 0x304;
            if (*(s32 *)h != 1) {
                break;
            }
            i++;
        }
    }
    if (i == 8) {
        func_002B6700(-11);
        Rand_Range("E4061801 mwPlyCreateSofdec: Number of MWPLY handles exceeds its maximum number.");
        return 0;
    }
    if (func_002B43E0((s32)cprm) == -1) {
        Rand_Range("E2053006 mwPlyCreateSofdec: Didn't set malloc/free func.");
        return 0;
    }
    __builtin_memset(h, 0, 0x304);
    func_002B4430(h, cprm);
    __builtin_memcpy(h + 8, cprm, 0x30);
    sfd = func_002B34D8((s32)h, (s32)cprm);
    *(s32 *)(h + 0x3C) = sfd;
    if (sfd == 0) {
        err = "E2012 mwPlyCreate:can't create SFD";
        goto fail_msg;
    }
    func_002B78F8((s32)h);
    func_002B3C80(h);
    func_002B2D10((s32 *)cprm, &out[0], &out[1], &out[2], &out[3], &out[4], &out[5]);
    func_002B3E28(h, cprm, *(s32 *)(table + 8), *(s32 *)(table + 0xC));
    sj = func_002B4010((s32)h);
    *(s32 *)(h + 0x1C0) = sj;
    if (sj == 0) {
        err = "E2013 mwPlyCreate:can't create SJ";
        goto fail_msg;
    }
    sj = func_00303D48(0, 0);
    *(s32 *)(h + 0x1E0) = sj;
    if (sj == 0) {
        err = "E2020 mwPlyCreate:can't create SJ";
        goto fail_msg;
    }
    *(s32 *)(h + 0x38) = 1;
    *(s32 *)(h + 0x58) = out[0];
    *(s32 *)(h + 0x68) = 0;
    *(s32 *)(h + 4) = 0;
    *(s32 *)(h + 0x4C) = *(s32 *)(cprm + 0x20);
    *(s32 *)(h + 0x50) = *(s32 *)(cprm + 0x20);
    if (func_002D0A58(sfd, 3, (s32)(h + 0x44)) != 0) {
        *(s32 *)(h + 0x44) = 0;
    }
    *(s32 *)(h + 0x6C) = 1;
    h[0x70] = 0;
    h[0x71] = 0;
    h[0x72] = 0;
    h[0x73] = 0;
    *(s32 *)(h + 0x5C) = 0;
    func_002BD1C8((s32)h, 0);
    func_002BD1D8((s32)h, 0);
    *(s32 *)(h + 0x54) = 1;
    *(s32 *)(h + 0x84) = 0;
    sj = func_002BD630(*(s32 *)(h + 0x1C0));
    *(s32 *)(h + 0x40) = sj;
    if (sj == 0) {
        goto fail;
    }
    func_002B7448(h);
    sj = func_002FFA00(*(s32 *)(h + 0x1C0));
    *(s32 *)(h + 0x74) = 0;
    *(s32 *)(h + 0x48) = sj;
    func_002FFBC0(sj, *(s32 *)(h + 0x40));
    if (func_002B4510(h) == -1) {
        goto fail;
    }
    sj = func_002B93D8(*(s32 *)(h + 0xAC), *(s32 *)(h + 0xB0), *(s32 *)(cprm + 8), *(s32 *)(cprm + 0xC));
    if (sj == 0) {
        err = "E201185: can't create SfxHn";
        goto fail_msg;
    }
    *(s32 *)(h + 0xA8) = sj;
    EftObj_SetMtx((s32)h, *(s32 *)(h + 0x28));
    sj = func_002B9FE8(h);
    *(s32 *)(h + 0x17C) = sj;
    if (func_002BA078((s32)h) != 0) {
        err = "E201212 mwPlyCreate: can't set AddInfSJ";
        goto fail_msg;
    }
    func_002BA0D8(h);
    func_002B5DC8(h);
    func_002B5E30((s32)h, 0, 0);
    *(s32 *)h = 1;
    *(s32 *)(h + 0x2FC) = -1;
    *(s32 *)(h + 0x2E8) = 0;
    *(s32 *)(h + 0x2D8) = 0;
    *(s32 *)(h + 0x2DC) = 0;
    *(s32 *)(h + 0x2E0) = 0;
    *(s32 *)(h + 0x300) = 0;
    return h;

fail_msg:
    Rand_Range(err);
fail:
    func_002B45D8((s32)h);
    return 0;
}

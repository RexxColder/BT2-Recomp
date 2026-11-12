#include "m2c_macros.h"

M2C_UNK func_0011FAC8(void *);                      /* extern */
M2C_UNK func_0011FE00(void *);                      /* extern */
void *func_00125FF0(s32);                           /* extern */
s32 func_00126040(void *);                          /* extern */
void *func_00202DC0(s32);                           /* extern */
s32 func_0023FCE8(s32, s32);                        /* extern */
s32 func_0023FD38(s32, s32);                        /* extern */
s32 func_0023FD58(s32, s32);                        /* extern */
s32 func_0023FD78(s32, s32);                        /* extern */
s32 func_0023FD98(s32, s32);                        /* extern */
extern void *D_003876A0;
extern void *D_003876FC;

void func_0011E6C0(void) {
    s32 temp_a1;
    s32 temp_v0_2;
    s32 var_s3;
    void *temp_v0;

    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        M2C_FIELD(D_003876FC, s32 *, 8) = 0;
        var_s3 = 0;
        if (M2C_FIELD(D_003876FC, s32 *, 4) > 0) {
            do {
                temp_v0 = func_00125FF0(var_s3);
                M2C_FIELD(temp_v0, s32 *, 0) = var_s3;
                M2C_FIELD(temp_v0, s32 *, 4) = var_s3;
                var_s3 += 1;
                func_0011FAC8(temp_v0);
                func_0011FE00(temp_v0);
                M2C_FIELD(temp_v0, s8 *, 0x10) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x11) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x12) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x13) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x24) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x25) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x26) = -0x80;
                M2C_FIELD(temp_v0, s8 *, 0x27) = -0x80;
                temp_v0_2 = func_00126040(temp_v0);
                M2C_FIELD(temp_v0, s32 *, 8) = (s32) M2C_FIELD(func_00202DC0(temp_v0_2), s32 *, 0x30);
                temp_a1 = M2C_FIELD(func_00202DC0(temp_v0_2), s32 *, 0x34);
                M2C_FIELD(temp_v0, s32 *, 0xC) = temp_a1;
                M2C_FIELD(temp_v0, s32 *, 0x11D8) = func_0023FCE8(temp_v0_2, temp_a1);
                M2C_FIELD(temp_v0, s32 *, 0x11DC) = func_0023FD38(temp_v0_2, M2C_FIELD(temp_v0, s32 *, 0xC));
                M2C_FIELD(temp_v0, s32 *, 0x11E0) = func_0023FD58(temp_v0_2, M2C_FIELD(temp_v0, s32 *, 0xC));
                M2C_FIELD(temp_v0, s32 *, 0x11E4) = func_0023FD78(temp_v0_2, M2C_FIELD(temp_v0, s32 *, 0xC));
                M2C_FIELD(temp_v0, s32 *, 0x11E8) = func_0023FD98(temp_v0_2, M2C_FIELD(temp_v0, s32 *, 0xC));
            } while (var_s3 < M2C_FIELD(D_003876FC, s32 *, 4));
        }
    }
}

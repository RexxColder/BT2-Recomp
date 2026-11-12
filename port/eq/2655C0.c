#include "common.h"

extern u8 *D_00387A40;

void func_00262FB8(s32 arg0, s32 arg1, s32 arg2);
void func_002644F0();
void func_002652E8(u8 *arg0, s32 arg1);
void func_002651B8(u8 *arg0, s32 arg1, s32 arg2, f32 farg0);

/* 0x002655C0: walks the entity table at D_00387A40 (base pointer at +0, count at +4,
 * 99712-byte entries). Entities with flag 0x2 at +0xAF8 get func_00262FB8 first. With
 * mode 0 the entities go through func_002651B8. Otherwise, for each k < arg1, the
 * entities get func_002652E8(ent, k) when word(+0xB00 + 64*k) has bit 0x200000 clear
 * (first pass) or set (second pass). Returns nothing useful (the asm leaves stale v0). */
void func_002655C0(u8 mode, s32 arg1)
{
    u8 *tbl;
    u8 *ent;
    s32 i;
    s32 k;

    tbl = D_00387A40;

    for (i = 0; i < *(s32 *)(tbl + 4); i++) {
        ent = *(u8 **)tbl + i * 99712;
        if ((*(u32 *)(ent + 0xAF8) & 2) != 0) {
            func_00262FB8((s32)ent, arg1, (s32)tbl);
        }
    }

    if (mode == 0) {
        for (i = 0; i < *(s32 *)(tbl + 4); i++) {
            ent = *(u8 **)tbl + i * 99712;
            if ((*(u32 *)(ent + 0xAF8) & 2) != 0) {
                func_002651B8(ent, arg1, 0, 0.0f); /* f12 not set by this asm: dead/stale slot */
            }
        }
        return;
    }

    if (arg1 <= 0) {
        return;
    }

    for (k = 0; k < arg1; k++) {
        if (arg1 >= 2) {
            func_002644F0(k, arg1, (s32)tbl);
        }

        for (i = 0; i < *(s32 *)(tbl + 4); i++) {
            ent = *(u8 **)tbl + i * 99712;
            if ((*(u32 *)(ent + 0xAF8) & 2) != 0) {
                if ((*(u32 *)(ent + 0xB00 + (k << 6)) & 0x200000) == 0) {
                    func_002652E8(ent, k);
                }
            }
        }

        for (i = 0; i < *(s32 *)(tbl + 4); i++) {
            ent = *(u8 **)tbl + i * 99712;
            if ((*(u32 *)(ent + 0xAF8) & 2) != 0) {
                if ((*(u32 *)(ent + 0xB00 + (k << 6)) & 0x200000) != 0) {
                    func_002652E8(ent, k);
                }
            }
        }
    }
}

#include "common.h"

extern f32 D_0038479C;
extern f32 D_003847A0;

s32 func_001F3758(s32 arg0);
void func_001C1258(u8 *arg0, s32 arg1);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 EftShot_GetAttrKind(s32 arg0, u64 arg1);
u8 *func_001AE300(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fa, f32 fb);
void func_001AE5E8(u8 *arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, void *arg2, s32 arg3);
void func_001AE3E8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 fa, f32 fb, f32 fc);
s32 func_001AE4D0(u8 *arg0);
void func_001C1460(u8 *arg0, s32 arg1);
s32 func_001C1210(u8 *arg0);
void func_001C1480(u8 *arg0, s32 arg1);
void func_001AE5C8(u8 *arg0);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
void func_00164130(s32 arg0, u8 *arg1, u8 *arg2);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(s32 arg0);

#define FLAGS(st) (*(u32 *)((st) + 4))
#define COUNT(st) (*(s32 *)((st) + 8))
#define PART(st, i) (*(u8 **)((st) + 0xA80 + 4 * (i)))   /* effect objects */
#define SLOT(st, i) (*(u8 **)((st) + 0xA98 + 4 * (i)))   /* paired objects */

/* Shot task update for a multi-part shot (arg0 = task; state at arg0+0x38 holds COUNT parts):
   state byte at arg0+1 runs 0..5 (spawn the first part, step through the parts as the character emits
   them, wait for all parts to finish), then updates part flags and kills / advances the task. */
void func_001644E0(u8 *arg0) {
    s32 advance = 0;
    u8 *st;
    u8 *ch;
    u8 *owner;
    u8 sp[0x10];
    s32 i;
    s32 n;
    s32 done;
    s32 kind;
    s32 idx;
    s32 busy;
    u32 flags;

    owner = (u8 *)*(s32 *)(func_001F3758((s32)arg0) + 0x38);
    st = *(u8 **)(arg0 + 0x38);
    ch = *(u8 **)(st + 0x80);
    for (i = 0; i < COUNT(st); i++) {
        func_001C1258(SLOT(st, i), 0);
    }
    if (BtlScene_IsCharStopped(*(s32 *)ch) != 0) {
        return;
    }

    if ((FLAGS(st) & 0x40) == 0) {
        if (EftShot_TestBits(*(s32 *)ch, 2) != 0) {
            arg0[1] = 0;
            FLAGS(st) |= 0x40;
        } else if (EftShot_TestBits(*(s32 *)ch, 4) != 0) {
            arg0[1] = 2;
            FLAGS(st) |= 0x40;
        }
    }

    if ((FLAGS(st) & 0x40) != 0 && arg0[1] < 6) {
        switch (arg0[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)ch, 2) != 0) {
                kind = EftShot_GetAttrKind(*(s32 *)ch, 2);
                *(u8 **)(st + 0xA80) = func_001AE300(kind, *(s32 *)ch, *(s32 *)(st + 0x10), 1,
                                                     *(f32 *)(st + 0x14), -1.0f);
                func_001C1258(SLOT(st, 0), 2);
                arg0[1] = 1;
            }
            break;
        case 1:
            *(s32 *)(st + 0xC) = 0;
            advance = 1;
            break;
        case 2:
            __builtin_memset(sp, 0, 0x10);
            if (EftShot_TestBits(*(s32 *)ch, 0x40) != 0) {
                idx = *(s32 *)(st + 0xC);
                func_001C1258(SLOT(st, idx), 0x40);
                kind = EftShot_GetAttrKind(*(s32 *)ch, 0x40);
                idx = *(s32 *)(st + 0xC);
                PART(st, idx) = func_001AE300(kind, *(s32 *)ch, *(s32 *)(st + 0x10),
                                              ((idx / 2) * 2 == idx - 1) ? st[0] : st[1],
                                              *(f32 *)(st + 0x14), D_0038479C);
                if (*(s32 *)(st + 0xC) == COUNT(st) - 1) {
                    func_001AE5E8(PART(st, *(s32 *)(st + 0xC)));
                }
            }
            if (EftShot_TestBits(*(s32 *)ch, 4) != 0) {
                kind = EftShot_GetAttrKind(*(s32 *)ch, 4);
                func_00208DE8(*(s32 *)ch, sp, kind);
                func_0012D488(ch, st + 0x20, sp, *(s32 *)ch);
                idx = *(s32 *)(st + 0xC);
                func_001AE3E8(PART(st, idx), ch, st + 0x20, 1, *(f32 *)(st + 0x18), D_003847A0,
                              (f32) * (s32 *)(*(u8 **)(ch + 0x24)) / 30.0f);
                func_001C1258(SLOT(st, *(s32 *)(st + 0xC)), 4);
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0xC) + 1;
                if (*(s32 *)(st + 0xC) == COUNT(st)) {
                    arg0[1] = 3;
                }
            }
            break;
        case 3:
        case 5:
            advance = 1;
            break;
        case 4:
            done = 0;
            n = COUNT(st);
            for (i = 0; i < COUNT(st); i++) {
                if (func_001AE4D0(PART(st, i)) == 0) {
                    done++;
                }
                n = COUNT(st);
            }
            if (done == n) {
                done = 0;
                for (i = 0; i < COUNT(st); i++) {
                    if (SLOT(st, i) != NULL) {
                        func_001C1460(SLOT(st, i), 1);
                        SLOT(st, i) = NULL;
                    }
                    if (func_001C1210(NULL) == 0) {
                        done++;
                    }
                }
                n = COUNT(st);
                if (done == n) {
                    FLAGS(st) |= 1;
                    arg0[1] = 5;
                }
            }
            break;
        }
    }

    if (EftShot_TestBits(*(s32 *)ch, 0x80) != 0) {
        FLAGS(st) |= 5;
    }
    for (i = 0; i < COUNT(st); i++) {
        func_001C1480(SLOT(st, i), FLAGS(st) & 4);
        if ((FLAGS(st) & 4) != 0) {
            func_001AE5C8(PART(st, i));
            PART(st, i) = NULL;
        }
    }
    func_00152530(ch, st + 0x830);
    func_00151FB0(st + 0x84);
    func_00164130(*(s32 *)ch, arg0, owner);
    busy = func_00152200(owner, st + 0x84) != 0;
    if (advance != 0) {
        arg0[1] = arg0[1] + 1;
    }
    flags = FLAGS(st);
    if (!busy) {
        if ((flags & 2) != 0) {
            BtlTask_SetDead((s32)arg0);
            return;
        }
    }
    if ((flags & 1) != 0) {
        FLAGS(st) = flags | 2;
    }
}

#include "common.h"
#include "battle/eft_o.h"

s32 func_001F3758(s32 arg0);
s32 func_0016B2D8(s32 arg0);
s32 func_00191728(u8 *arg0);
s32 func_001918F8(u8 *arg0, s32 arg1);
void *EftBlastObj_Create(EftBlastObjArg *arg0);
s32 EftShot_TestBits(s32 objId, s32 mask);
void EftTechEvt_RequestRestart(s32 objId);
void func_00129C28(void *arg0, void *arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);

/* 0x0016B2E8: when the unit's shot object (kind 0x15A) passes EftShot_TestBits(obj, 2): count the shot
   (+0x14), copy 0x250 bytes of unit state from +0x860 to +0xAB0, refresh two 16-byte vectors, and on the
   first pass of the slot at +0xD10 create a blast object (EftBlastObjArg built from the unit and shot).
   Returns 1 while func_00191728 on the slot object is nonzero, else clears the slot object and returns 0. */
s32 func_0016B2E8(s32 a0) {
    u8 *unit = (u8 *)a0;
    u8 *ctx = *(u8 **)(unit + 0x38);
    u8 *other = (u8 *)func_001F3758(a0);
    u8 *set = *(u8 **)(other + 0x38);
    u8 *src = *(u8 **)(ctx + 0xB0);
    s32 kind = *(s32 *)*(u8 **)(src + 0x20);
    s32 result = 0;
    s32 count;
    u8 *slot;
    u8 *created;
    u8 v23[16];
    u8 v24[16];
    EftBlastObjArg blast;

    if (kind != 0x15A) {
        return 0;
    }
    if (EftShot_TestBits(*(s32 *)src, 2)) {
        count = *(s32 *)(ctx + 0x14) + 1;
        *(s32 *)(ctx + 0x14) = count;
        if (*(s32 *)*(u8 **)(src + 0x20) == 0x15A) {
            if (count < 2) {
                return 0;
            }
        }
        __builtin_memcpy(ctx + 0xAB0, ctx + 0x860, 0x250);
        func_00129C28((void *)v23, (void *)(ctx + 0x40));
        func_00129C28((void *)v24, (void *)(ctx + 0x30));
        if (*(s32 *)*(u8 **)(src + 0x20) == 0x15A) {
            func_00208DE8(2, (s32)v23, *(s32 *)(ctx + 0x4));
            func_00129C28((void *)(ctx + 0xAD0), (void *)v23);
        }

        slot = (u8 *)func_0016B2D8((s32)ctx);
        if (slot != NULL) {
            blast.src = (EftOSrc *)src;
            blast.set = (EftOSet *)set;
            blast.nodes = (EftOEmitNodes *)(ctx + 0xAB0);
            blast.pos = (Vec4 *)v23;
            blast.dir = (Vec4 *)v24;
            blast.index = *(s32 *)(ctx + 0xD00);
            blast.count = 1;
            blast.kind = 0;
            blast.evtIdx = 0;
            blast.life = 0.0f;
            blast.scale = *(f32 *)(ctx + 0x20);
            blast.speed = *(f32 *)(ctx + 0x1C);
            blast.model = NULL;

            created = (u8 *)EftBlastObj_Create(&blast);
            *(u8 **)(slot + 0x20) = created;
            func_001918F8(created, 1);
            *(s32 *)(ctx + 0xD00) += 1;
            *(u32 *)ctx |= 0x2000;
        }
        EftTechEvt_RequestRestart(*(s32 *)src);
    }

    slot = ctx + 0xD10;
    if (func_00191728(*(u8 **)(slot + 0x20))) {
        result = 1;
    } else {
        *(u8 **)(slot + 0x20) = NULL;
    }
    return result;
}

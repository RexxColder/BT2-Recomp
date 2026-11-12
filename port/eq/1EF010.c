#include "common.h"

extern u8 *D_00387AD8;
extern u8 *gOtFirst;

/* GS packet builder: 8 register args and 5 stack args (8-byte slots at sp+0..+0x20). Appends a 0x30-byte packet
 * at D_00387AD8 and links it into the OT (when D_00387AD8 is not NULL). */
void func_001EF010(u64 a0, u64 a1, u64 a2, u64 a3, u64 t0, u64 t1, u64 t2, u64 t3,
                   u64 sp0, u64 sp8, u64 sp16, u64 sp24, u64 sp32) {
    u8 *t4;
    u64 v0;
    u64 v1;
    u64 t5;
    s64 low;

    v0 = sp32;
    low = (s8)(u8)(v0 & 0xFF);
    t5 = (u64)(low + 6);

    a1 = a1 << 14;
    a2 = a2 << 20;
    a3 = a3 << 26;
    t0 = t0 << 30;
    t1 = t1 << 34;
    t2 = t2 << 35;
    t3 = t3 << 37;
    a3 = a3 | t1;
    t4 = D_00387AD8;
    D_00387AD8 = t4 + 0x30;
    a1 = a1 | a2;
    t0 = t0 | t2;
    a0 = a0 | t3;
    a0 = a0 | a3;
    a1 = a1 | t0;
    a0 = a0 | a1;
    v0 = sp0 << 51;
    a0 = a0 | v0;
    v1 = sp8 << 55;
    a3 = a0 | v1;
    if (t4 == NULL) {
        return;
    }
    v0 = sp16 << 56;
    v1 = sp24 << 61;
    a1 = 0x1000000000008001ULL;
    v0 = a3 | v0;
    v0 = v0 | v1;
    a0 = 0xA0000002ULL;
    a2 = 0xE;
    *(u64 *)(t4 + 0x28) = t5;
    *(u64 *)(t4 + 0x00) = a0;
    *(u64 *)(t4 + 0x10) = a1;
    *(u64 *)(t4 + 0x18) = a2;
    *(u64 *)(t4 + 0x20) = v0;
    *(u8 **)(*(u8 **)(gOtFirst + 4) + 4) = t4;
    *(u8 **)(gOtFirst + 4) = t4;
}

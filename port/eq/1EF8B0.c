#include "m2c_macros.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

/* GS packet builder: takes a 0x60-byte packet from the bump pointer D_00387AD8, fills it, and links it
 * into the list head at D_00387AE4 + ((arg6 * 2 + arg14) * 8). arg8..arg14 are stack words, arg15 an s64
 * pointer, arg16 a multiplier (the stack words are 8-byte slots). */
void GsPkt_EmitQuad(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                    s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14,
                    s64 *arg15, s32 arg16) {
    u8 *pkt;
    u8 *entry;
    u8 *prev;
    s32 q3;
    s32 q0;
    s32 t5;
    s32 idx;

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x60;

    q3 = (s32)(((u32)arg7 * (u32)arg16) >> 13);
    q0 = (s32)(((u32)arg8 * (u32)arg16) >> 13);

    *(u16 *)(pkt + 0x40) = (u16)((arg4 - q3) * 16 + 0x7000);
    *(u16 *)(pkt + 0x42) = (u16)((arg5 - q0) * 16 + 0x7200);
    *(u16 *)(pkt + 0x50) = (u16)((arg4 + q3) * 16 + 0x7000);
    *(u16 *)(pkt + 0x52) = (u16)((arg5 + q0) * 16 + 0x7200);

    t5 = (s8)arg13;

    *(u64 *)(pkt + 0x40) = *(u64 *)(pkt + 0x40) | 0x00FFFFFF00000000ULL;
    *(u64 *)(pkt + 0x50) = *(u64 *)(pkt + 0x50) | 0x00FFFFFF00000000ULL;
    *(u64 *)(pkt + 0x00) = 0xA0000005ULL;
    *(u64 *)(pkt + 0x10) = 0x8400000000008001ULL;
    *(u64 *)(pkt + 0x18) = (s64)(t5 * 16) + 0xF4343160LL;
    *(u64 *)(pkt + 0x20) = (((s64)t5 << 9) | 0x156);
    *(u64 *)(pkt + 0x28) = *arg15;

    pkt[0x30] = (u8)arg0;
    pkt[0x31] = (u8)arg1;
    pkt[0x32] = (u8)arg2;
    pkt[0x33] = (u8)arg3;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(u16 *)(pkt + 0x38) = (u16)(arg9 * 16);
    *(u16 *)(pkt + 0x3A) = (u16)(arg10 * 16);
    *(u16 *)(pkt + 0x48) = (u16)((arg9 + arg11) * 16);
    *(u16 *)(pkt + 0x4A) = (u16)((arg10 + arg12) * 16);
    pkt[0x47] = 0xFF;
    pkt[0x57] = 0xFF;

    idx = ((s32)arg6 * 2 + arg14) * 8;
    entry = D_00387AE4 + idx;
    prev = *(u8 **)(entry + 4);
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(entry + 4) = pkt;
}

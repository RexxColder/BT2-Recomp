#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

u8 *func_001EF698(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s16 arg5, s32 arg6,
                  s16 arg7, s16 arg8, s16 arg9, s16 arg10, s16 arg11, s16 arg12,
                  s8 arg13, s32 arg14, s64 *arg15, s32 arg16) {
    s32 v21;
    s32 v22;
    s32 v23;
    s32 v26;
    s32 v25;
    u8 *pkt;
    u8 *link;
    u8 *ent;
    u8 *tail;

    v21 = 0;
    v22 = 0;
    v23 = 0;
    v26 = 0;
    switch (arg16) {
    case 1:
        v22 = arg5;
        v21 = arg4 + arg7;
        v26 = arg4;
        v23 = arg5 + arg8;
        break;
    case 0:
        v21 = arg4;
        v22 = arg5;
        v26 = arg4 + arg7;
        v23 = arg5 + arg8;
        break;
    case 2:
        v21 = arg4;
        v22 = arg5 + arg8;
        v26 = arg4 + arg7;
        v23 = arg5;
        break;
    case 3:
        v21 = arg4 + arg7;
        v26 = arg4;
        v22 = arg5 + arg8;
        v23 = arg5;
        break;
    default:
        break;
    }
    v25 = 16 * v26;

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x60;

    *(s16 *)(pkt + 0x42) = (s16)(16 * v22 + 0x7200);
    *(s16 *)(pkt + 0x40) = (s16)(16 * v21 + 0x7000);
    *(s16 *)(pkt + 0x50) = (s16)(v25 + 0x7000);
    *(s16 *)(pkt + 0x52) = (s16)(16 * v23 + 0x7200);
    *(s64 *)(pkt + 0x40) = *(s64 *)(pkt + 0x40) | 0x00FFFFFF00000000LL;
    *(s64 *)(pkt + 0x50) = *(s64 *)(pkt + 0x50) | 0x00FFFFFF00000000LL;
    *(s64 *)(pkt + 0x28) = *arg15;

    *(u8 *)(pkt + 0x31) = arg1;
    *(u8 *)(pkt + 0x32) = arg2;
    *(u8 *)(pkt + 0x33) = arg3;
    *(s64 *)(pkt + 0x20) = (((s64)arg13 << 9) | 0x156LL);
    *(s64 *)(pkt + 0x00) = 0xA0000005LL;
    *(s64 *)(pkt + 0x10) = (s64)0x8400000000008001ULL;
    *(s64 *)(pkt + 0x18) = (s64)0xF4343160ULL + ((s64)arg13 << 4);
    *(u8 *)(pkt + 0x30) = arg0;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(s16 *)(pkt + 0x38) = (s16)(16 * arg9);
    *(s16 *)(pkt + 0x3A) = (s16)(16 * arg10);
    *(s16 *)(pkt + 0x48) = (s16)(16 * (arg9 + arg11));
    *(s16 *)(pkt + 0x4A) = (s16)(16 * (arg10 + arg12));
    *(u8 *)(pkt + 0x57) = 0xFF;
    *(u8 *)(pkt + 0x47) = 0xFF;

    link = D_00387AE4;
    ent = link + 8 * (2 * arg6 + arg14);
    tail = *(u8 **)(ent + 4);
    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
    return link;
}

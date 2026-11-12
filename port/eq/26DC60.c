#include "common.h"

void func_0026D090(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026D250(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026D528(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026D640(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026D6A0(u8 *arg0, u8 *arg1, s32 *arg2);

void func_0026DC60(u8 *st, u8 *p) {
    s32 pos;
    u16 hdr;
    u16 code;

    pos = 0;
    hdr = 0;
    code = 0;
    if (p != NULL) {
        hdr = (u16)(p[0] | (p[1] << 8));
        pos = 2;
    }
    if (p == NULL || hdr == 0) {
        st[0x11] = (u8)(st[0x11] | 1);
        *(s32 *)(st + 0x8) = *(s32 *)(st + 0x8) - 1;
        return;
    }

    code = (u16)(p[pos] | (p[pos + 1] << 8));
    pos += 2;
    for (;;) {
        if (code == 1) {
            return;
        }
        if (code == 0) {
            st[0x11] = (u8)(st[0x11] | 1);
            return;
        }
        switch (code) {
            case 4:
                func_0026D090(st, p, &pos);
                break;
            case 5:
                func_0026D528(st, p, &pos);
                break;
            case 12:
                func_0026D6A0(st, p, &pos);
                break;
            case 26:
                func_0026D250(st, p, &pos);
                break;
            case 28:
                func_0026D640(st, p, &pos);
                break;
            default:
                break;
        }
        code = (u16)(p[pos] | (p[pos + 1] << 8));
        pos += 2;
    }
}

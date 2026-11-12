#include "common.h"

#define LE32(p) ((u32)(p)[0] | ((u32)(p)[1] << 8) | ((u32)(p)[2] << 16) | ((u32)(p)[3] << 24))

extern s32 D_0036740C;
extern u8 *D_00366ED8[];
extern s32 D_00367404;
extern u8 *D_00367408;
extern s32 D_00367410;
extern u8 *D_00348D58;
extern s32 D_00348D5C;
extern u8 D_0037BC28[];
extern u8 D_0037BC60[];
extern u8 D_0037BC68[];
extern u8 D_0037BCA0[];
extern u8 D_0037BCD8[];

void func_002EA050(void *a0);
void func_002EAEC0(void);
s32 func_002EC9C8(void *a0);
s32 func_002EC120(void *a0, s32 a1, void *a2);
s32 func_002ED0F0(u32 a0);
s32 memcmp(void *a, void *b, u32 n);

s32 func_002EB030(s32 arg0) {
    u8 *tbl = NULL;
    u8 *rec;
    u8 *fp = NULL;
    u8 *p118;
    u8 *D;
    s32 kind;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 r;
    s32 x;
    s32 y;
    s32 idx;
    s32 cnt;
    u32 w;
    u32 v;

    if (arg0 != D_0036740C) {
        func_002EA050(D_0037BC28);
        return -3;
    }

    if (D_00367408 == NULL) {
        if (arg0 != -1) {
            return D_00367410;
        }
    }
    /* L2EB0B8 */
    r = func_002EC9C8(D_00367408);
    D_00367410 = r;
    if (r != 3) {
        return r;
    }

    rec = D_00366ED8[arg0];
    kind = *(s8 *)(rec + 0xF);
    p118 = rec + 0x118;
    if (kind == 1) {
        fp = rec + 0x11C;
    } else {
        tbl = rec + 0x11A;
    }

    s1 = 1;
    if (*(u32 *)(rec + 0x8) == 0) {
        D = D_00348D58;
        if (memcmp(D, D_0037BC60, 3) != 0) {
            func_002EA050(D_0037BC68);
            D_00367410 = 4;
            func_002EAEC0();
            return D_00367410;
        }
        /* L2EB148 */
        x = (s32)LE32(D + 4);
        if (0x10000 < x) {
            func_002EA050(D_0037BCA0);
            D_00367410 = 4;
            func_002EAEC0();
            return D_00367410;
        }
        /* L2EB1A8 */
        y = (s32)(u16)(D[4] | ((u32)D[5] << 8));
        *(u16 *)(rec + 0xC) = (u16)y;
        *(s32 *)(rec + 0x8) = y;
        if (kind == 1) {
            v = ((u32)y << 2) + 0x120;
        } else {
            v = (((u32)y << 1) + 0x11C) >> 2;
            v = v << 2;
        }
        *(u32 *)(rec + 0x4) = v;
        if (kind == 1) {
            *(u32 *)p118 = LE32(D + 8);
        } else {
            x = (s32)LE32(D_00348D58 + 8);
            if (x < 0) {
                x = x + 0x7FF;
            }
            *(u16 *)p118 = (u16)(x >> 11);
        }
        s1 = 3;
    }

    /* L2EB29C */
    s4 = D_00348D5C << 9;
    s3 = (s1 < s4);
    if (s3 != 0) {
        for (;;) {
            D = D_00348D58;
            if (kind == 1) {
                idx = D_00367404;
                w = LE32(D + 4 * s1);
                *(u32 *)(fp + 4 * idx) = w;
                D_00367404 = idx + 1;
            } else {
                w = LE32(D + 4 * s1);
                r = func_002ED0F0(w);
                if ((r & (s32)0xFFFF0000) != 0) {
                    /* L2EB3E8 */
                    func_002EA050(D_0037BCD8);
                    D_00367410 = 4;
                    func_002EAEC0();
                    return D_00367410;
                }
                idx = D_00367404;
                *(u16 *)(tbl + 2 * idx) = (u16)r;
                D_00367404 = idx + 1;
            }
            /* L2EB384 */
            cnt = D_00367404;
            if (!(cnt < *(s32 *)(rec + 0x8))) {
                /* L2EB288 */
                func_002EAEC0();
                D_00367410 = 3;
                return D_00367410;
            }
            s1 = s1 + 2;
            s3 = (s1 < s4);
            if (s3 == 0) {
                break;
            }
        }
    }

    /* L2EB3B8 */
    r = func_002EC120(D_00367408, D_00348D5C, D_00348D58);
    if (r < 0) {
        D_00367410 = 4;
        func_002EAEC0();
        return D_00367410;
    }
    D_00367410 = (s32)*(s8 *)(D_00367408 + 1);
    return D_00367410;
}

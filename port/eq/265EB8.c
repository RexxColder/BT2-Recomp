#include "common.h"

extern u8 gGfx[] __attribute__((section(".data")));
extern u8 *D_003876A0;
extern u8 *D_00387A40;
extern f32 D_00386EA8, D_00386EAC;

extern s32 BtlStage_IsReady();
extern s32 Dma_AddFrame();
extern s32 Dma_AddScissor();
extern s32 Dma_AddZbuf();
extern s32 func_00271A00();
extern s32 func_00280E90();
extern s32 BtlObjDraw_SetEnv();
extern s32 TexFile_UploadOne();
extern s32 ObjGs_AddTexEnv();
extern s32 func_00265808();
extern s32 func_002655C0();
extern s32 ObjGs_AddFadeEnv();
extern s32 func_00265920();
extern s32 func_002658A8();
extern s32 func_00276D00();
extern s32 func_00276D40();
extern s32 func_00269778();
extern s32 func_002644F0();
extern s32 func_00269798();
extern s32 func_00269848();
extern s32 ObjGs_AddFlatShadowEnv();
extern u8 *func_0029E6D0();
extern void func_002628A8(u8 *arg0, u8 *arg1, s32 arg2, f32 farg0);
extern s32 Vu0Screen_StoreMtx();
extern s32 Vu0Clip_StoreMtx();
extern s32 sceVu0MulMatrix();
extern s32 func_00264540();
extern s32 func_002659B8();
extern s32 func_00269948();
extern void *memset();

static void clearScreen(void)
{
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0xFFFFFF);
    Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
    Dma_AddZbuf(0xE0, 1);
    func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
    Dma_AddZbuf(0xE0, 0);
    Dma_AddFrame((*(s32 *)(gGfx + 0x234) & 1) ? 0 : 0x70, 8, 0);
}

static void drawProj(u8 *sp, u8 *a, u8 *b, f32 fl, f32 neg)
{
    u8 *m = func_0029E6D0(0);
    __builtin_memset(sp + 0x40, 0, 0x10);
    *(f32 *)(sp + 0x44) = neg;
    func_002628A8(sp, sp + 0x40, D_00387A40 + 0x38030, fl);
    Vu0Screen_StoreMtx(m + 0xC0);
    sceVu0MulMatrix(m + 0xC0, m + 0xC0, sp);
    Vu0Clip_StoreMtx(m + 0x100);
    sceVu0MulMatrix(m + 0x100, m + 0x100, sp);
    func_00264540(a, b, 2, 0, 0, 0);
}

static void drawObjs(u8 *o, s32 n, s32 flag54)
{
    s32 i, d = 0;
    u8 *p = o + 0xB00;
    for (i = 0; i < n; i++) {
        u64 v;
        if (flag54) func_002644F0(i);
        v = *(u64 *)p;
        p += 0x40;
        if ((v & 0x12) == 0x12) {
            if (!d) {
                d = 1;
                func_00269798(o, *(s32 *)(D_00387A40 + 0x38018 + i * 4));
            }
            func_00269848(o, *(s32 *)(D_00387A40 + 0x38018 + i * 4));
        }
    }
}

s32 func_00265EB8(s32 a0)
{
    u8 sp[0x60];
    s32 n, flag54, i, j, k;
    s32 s1 = 0;
    u8 *b;

    if ((*(u64 *)(D_003876A0 + 0x4D8) & 3) == 0 || BtlStage_IsReady()) {
        n = a0 ? 2 : 1;
        flag54 = (n >= 2);
        b = D_00387A40;
        for (i = 0; i < n; i++) {
            for (j = 0; j < *(s32 *)(b + 4); j++) {
                u8 *o = *(u8 **)b + j * 0x18580;
                *(s32 *)(o + 0xAF8) |= *(s32 *)(o + 0xB00 + i * 0x40);
                b = D_00387A40;
                s1 |= *(s32 *)(o + 0xB00 + i * 0x40);
            }
            for (j = 0; j < *(s32 *)(b + 0xC); j++) {
                u8 *o = *(u8 **)(b + 8) + j * 0x1520;
                if (*(s32 *)(o + 0xC)) {
                    *(s32 *)(o + 0xAF8) |= *(s32 *)(o + 0xB00 + i * 0x40);
                    b = D_00387A40;
                    s1 |= *(s32 *)(o + 0xB00 + i * 0x40);
                }
            }
        }
        if (s1 & 2) {
            clearScreen();
            BtlObjDraw_SetEnv();
            TexFile_UploadOne(*(s32 *)(D_00387A40 + 0x38080), 0, 0x3D40, -1);
            ObjGs_AddTexEnv();
            func_00265808(n);
            func_002655C0((s1 >> 21) & 1, n);
            ObjGs_AddTexEnv();
            func_00280E90();
            if (s1 & 8) {
                ObjGs_AddFadeEnv(0xE0);
                Dma_AddZbuf(0xE0, 1);
                func_00265920(n);
                func_002658A8(n);
                Dma_AddZbuf(0xE0, 0);
            }
            if ((s1 & 0x12) != 0x12 || (*(u64 *)(D_003876A0 + 0x4D8) & 0x2000) || func_00276D00()) {
                goto done;
            }
            if (!(s1 & 0x20000000) && !func_00276D40()) {
                func_00269778();
                clearScreen();
                b = D_00387A40;
                for (i = 0; i < *(s32 *)(b + 4); i++) {
                    drawObjs(*(u8 **)b + i * 0x18580, n, flag54);
                    b = D_00387A40;
                }
                for (i = 0; i < *(s32 *)(b + 0xC); i++) {
                    u8 *o = *(u8 **)(b + 8) + i * 0x1520;
                    if (*(s32 *)(o + 0xC) && (*(s32 *)(o + 0xAF8) & 2)) {
                        drawObjs(o, n, flag54);
                        b = D_00387A40;
                    }
                }
                func_00269948();
                goto done;
            }
            BtlObjDraw_SetEnv();
            clearScreen();
            ObjGs_AddFlatShadowEnv();
            b = D_00387A40;
            for (i = 0; i < *(s32 *)(b + 4); i++) {
                u8 *o = *(u8 **)b + i * 0x18580;
                u8 *p = o + 0xB00;
                for (k = 0; k < n; k++, p += 0x40) {
                    if ((*(u64 *)p & 0x12) != 0x12) continue;
                    if (flag54) func_002644F0(k);
                    if ((*(u64 *)p & 0x12) == 0x12) {
                        drawProj(sp, o, p, D_00386EA8, -1.0f);
                    }
                }
                b = D_00387A40;
            }
            for (i = 0; i < *(s32 *)(b + 0xC); i++) {
                u8 *o = *(u8 **)(b + 8) + i * 0x1520;
                u8 *p = o + 0xB00;
                if (*(s32 *)(o + 0xC)) {
                    if ((*(u64 *)p & 0x12) == 0x12) {
                        if (flag54) func_002644F0(0);
                        b = D_00387A40;
                        if ((*(u64 *)p & 0x12) == 0x12) {
                            drawProj(sp, o, p, D_00386EAC, -1.0f);
                            b = D_00387A40;
                        }
                    }
                }
            }
done:
            BtlObjDraw_SetEnv();
            return func_002659B8();
        }
    }
    clearScreen();
    func_00280E90();
    return func_002659B8();
}

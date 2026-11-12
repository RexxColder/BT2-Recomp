#include "common.h"

/* Callees: named helpers of the battle scene and effects, and the original's func_ labels for the rest. */
extern s32 BtlStage_IsReady(void);
extern void BtlTaskList_Draw(s32 list);
extern void EftSurf_BuildPalettes(void);
extern void EftVram_Reset(void);
extern void func_00128758(void);
extern void func_00128EC0(void);
extern void func_0012B9C0(void);
extern void func_0012E900(void);
extern void func_001E4ED0(void);
extern void func_001F3D10(void);

/* Battle scene block (gBtlScene, gp-relative). */
extern void *gBtlScene;

/* One frame of the battle scene's draw: the flag at +0x20 is (mode != 1); mode != 0 also rebuilds the palettes
 * and the VRAM state (the stage part when the stage is ready); the task list at +0 is drawn last. */
void BtlScene_DrawFrame(s32 mode) {
    s32 m;

    m = mode & 0xFF;
    *(s32 *)((u8 *)gBtlScene + 0x20) = (m != 1);
    func_00128758();
    func_00128EC0();
    if (m != 0) {
        func_001E4ED0();
        EftSurf_BuildPalettes();
        if (BtlStage_IsReady() != 0) {
            func_001F3D10();
        }
        EftVram_Reset();
    }
    func_0012B9C0();
    func_0012E900();
    BtlTaskList_Draw(*(s32 *)gBtlScene);
}

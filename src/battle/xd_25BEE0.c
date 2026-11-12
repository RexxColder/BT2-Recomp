/*
 * BtlCam_Term (BT3 btl_cam.c, same code).
 */
#include "common.h"
#include "main.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "battle/btl_demo_cam.h"
#include "sys/heap.h"
#include "sys/pad.h"
#include "sys/math3d.h"

extern void func_0028BB60(void *p);
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern void func_00312680(Vec4 *dst, Vec4 *src, f32 scale);
extern BattleResult *func_0023EA20(void);

/* Frees the camera block and the demo camera. */
void BtlCam_Term(void) {
    func_0028BB60(gBtlCam);
    gBtlCam = NULL;
    DemoCam_Term();
}

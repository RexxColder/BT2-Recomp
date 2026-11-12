#include "common.h"

/*
 * EftAura_Command, 0x17D218..0x17D2D8 (BT3 src/battle/eft_n.c, same code). Own file: the switch compiles to a
 * jump table (jtbl_0036E850 in the original .rodata).
 */
#include "battle/xb_eft_n.h"

extern s32 EftAura_Request(s32 objId, s32 variant);
extern s32 EftAura_Stop(s32 objId, s32 variant);
extern s32 EftAura_StartBurst(s32 objId);
extern s32 EftAura_EndBurst(s32 objId);
extern s32 EftAura_PeakBurst(s32 objId);
extern s32 EftAura_FadeIn(s32 objId);
extern s32 EftAura_FadeOut(s32 objId);
extern s32 EftAura_Kill(s32 objId);

/* What the fighter effect layer calls: 0 start, 1 stop, 2 burst start, 3 burst end, 4 burst peak, 5 fade in,
   6 fade out, 7 kill. */
s32 EftAura_Command(s32 objId, s32 cmd) {
    if (gEftAuraPool == NULL) {
        return 0;
    }
    switch (cmd) {
    case 0:
        EftAura_Request(objId, 0);
        break;
    case 1:
        EftAura_Stop(objId, 0);
        break;
    case 2:
        EftAura_StartBurst(objId);
        break;
    case 3:
        EftAura_EndBurst(objId);
        break;
    case 4:
        EftAura_PeakBurst(objId);
        break;
    case 5:
        EftAura_FadeIn(objId);
        break;
    case 6:
        EftAura_FadeOut(objId);
        break;
    case 7:
        EftAura_Kill(objId);
        break;
    }
    return 1;
}

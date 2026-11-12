#include "common.h"

extern s32 gEftAuraPool;

void EftAura_Request(s32 arg0, s32 arg1);
void EftAura_Stop(s32 arg0, s32 arg1);
void EftAura_Kill(s32 arg0);
void EftAura_StartBurst(s32 arg0);
void EftAura_EndBurst(s32 arg0);
void EftAura_PeakBurst(s32 arg0);
void EftAura_FadeIn(s32 arg0);
void EftAura_FadeOut(s32 arg0);

s32 EftAura_Command(s32 arg0, s32 arg1) {
    s32 result;

    result = 0;
    if (gEftAuraPool != 0) {
        result = 1;
        if ((u32)arg1 < 8) {
            switch (arg1) {
                case 0:
                    EftAura_Request(arg0, 0);
                    break;
                case 1:
                    EftAura_Stop(arg0, 0);
                    break;
                case 2:
                    EftAura_StartBurst(arg0);
                    break;
                case 3:
                    EftAura_EndBurst(arg0);
                    break;
                case 4:
                    EftAura_PeakBurst(arg0);
                    break;
                case 5:
                    EftAura_FadeIn(arg0);
                    break;
                case 6:
                    EftAura_FadeOut(arg0);
                    break;
                case 7:
                    EftAura_Kill(arg0);
                    break;
            }
        }
    }
    return result;
}

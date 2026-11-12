#include "common.h"
#include "battle/btl_demo_cam.h"

/* BT3 DemoCam_EvalAnim (exact instruction match in BT3); BT2 asm at 0x0025A188. */
extern u8 *D_00387A30;
/* BT2: el bloque de camara es D_00387A30 y la animacion esta en +0x2B0 (en BT3 gDemoCam->anim, +0x2C0); asm 0x0025A188. */
void DemoCam_EvalAnim(DemoCamPose *out, f32 time) {
    DemoCamAnim *anim = *(DemoCamAnim **)(D_00387A30 + 0x2B0);
    DemoCamChannel *ch = anim->channels;
    s32 i;

    *out = *anim->defaults;
    for (i = 0; i < anim->channelCount; i++) {
        DemoCamKey *key = ch->keys;
        DemoCamKey *prev = NULL;
        DemoCamKey *next = NULL;
        s32 j;

        for (j = 0; j < ch->keyCount; j++) {
            if (key->time == time) {
                out->f.frame = (s32)key->time;
                prev = key;
                break;
            }
            if (key->time < time) {
                prev = key;
            }
            if (time < key->time) {
                next = key;
                break;
            }
            key++;
        }
        if (next != NULL && prev != NULL) {
            if (prev->flags & 0x10) {
                out->v[ch->index] = prev->value;
            } else {
                out->v[ch->index] =
                    (next->value - prev->value) * ((time - prev->time) / (next->time - prev->time)) + prev->value;
            }
        } else if (prev != NULL) {
            out->v[ch->index] = prev->value;
        } else if (next != NULL) {
            out->v[ch->index] = next->value;
        }
        ch++;
    }
}

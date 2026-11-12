#include "common.h"

/* Stops the demo camera (DemoCam_Stop, 0x25AC40). */
extern void DemoCam_Stop(void);

/* Effect camera cut block (gEftCam, gp-relative); the byte at +0xC is its running flag. */
extern u8 *gEftCam;

/* Stops the effect's camera cut when its running byte (+0xC) is set, and clears the byte. */
void EftCam_StopIfRunning(void) {
    if (gEftCam[0xC] != 0) {
        DemoCam_Stop();
        gEftCam[0xC] = 0;
    }
}

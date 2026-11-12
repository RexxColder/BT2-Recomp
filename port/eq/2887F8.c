#include "common.h"

extern s32 sceMcMkdir();
extern s32 sceMcSync();
extern s32 sceMcOpen();
extern s32 sceMcWrite();
extern s32 sceMcClose();
char *strcpy(char *dst, const char *src);
extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern u8 gMcCardPort[];
extern u8 gMcCardIconSys[];
extern u8 D_00377420[], D_00377460[], D_00377490[], D_003774C0[];
extern char D_00387D28[];

#define PORT_RET(p) (*(s32 *)((p) + 4))
#define PORT_RESULT(p) (*(s32 *)((p) + 8))
#define PORT_FD(p) (*(s32 *)((p) + 0x18))

s32 McCard_CreateSave(s32 port, u8 *file) {
    u8 *pt;
    s32 ret;

    if (gMcCardCmd != 0 && gMcCardCmd != 0xE) {
        gMcCardStep = 0;
    }
    pt = gMcCardPort + port * 36;
    switch (gMcCardStep) {
    case 0:
        PORT_RESULT(pt) = 0;
        gMcCardCmd = 0xE;
        ret = sceMcMkdir(port, 0, file + 0x18);
        PORT_RET(pt) = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, 0, &PORT_RESULT(pt)) == 0) {
            return 0;
        }
        if (PORT_RESULT(pt) < 0) {
            if (PORT_RESULT(pt) != -4) {
                return 0;
            }
            PORT_RESULT(pt) = 0;
        }
        gMcCardStep++;
        return 0;
    case 2:
        ret = sceMcOpen(port, 0, file + 0x98, 0x202);
        PORT_RET(pt) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 3:
        if (sceMcSync(1, 0, &PORT_RESULT(pt)) == 0) {
            return 0;
        }
        ret = PORT_RESULT(pt);
        if (ret < 0) {
            return 0;
        }
        PORT_FD(pt) = ret;
        gMcCardStep++;
        return 0;
    case 4:
        __builtin_memset(gMcCardIconSys, 0, 0x3C4);
        strcpy((char *)gMcCardIconSys, D_00387D28);
        strcpy((char *)(gMcCardIconSys + 0xC0), (char *)(file + 0x318));
        *(u16 *)(gMcCardIconSys + 6) = *(u16 *)(file + 0x41C);
        *(s32 *)(gMcCardIconSys + 0xC) = 0x60;
        __builtin_memcpy(gMcCardIconSys + 0x10, D_00377420, 0x40);
        __builtin_memcpy(gMcCardIconSys + 0x50, D_00377460, 0x30);
        __builtin_memcpy(gMcCardIconSys + 0x80, D_00377490, 0x30);
        __builtin_memcpy(gMcCardIconSys + 0xB0, D_003774C0, 0x10);
        strcpy((char *)(gMcCardIconSys + 0x104), (char *)(file + 0x35C));
        strcpy((char *)(gMcCardIconSys + 0x144), (char *)(file + 0x39C));
        strcpy((char *)(gMcCardIconSys + 0x184), (char *)(file + 0x3DC));
        ret = sceMcWrite(PORT_FD(pt), gMcCardIconSys, 0x3C4);
        PORT_RET(pt) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 5:
    case 7:
    case 11:
        if (sceMcSync(1, 0, &PORT_RESULT(pt)) == 0) {
            return 0;
        }
        if (PORT_RESULT(pt) < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 6:
    case 12:
        ret = sceMcClose(PORT_FD(pt));
        PORT_RET(pt) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 8:
        ret = sceMcOpen(port, 0, file + 0x118, 0x202);
        PORT_RET(pt) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 9:
        if (sceMcSync(1, 0, &PORT_RESULT(pt)) == 0) {
            return 0;
        }
        ret = PORT_RESULT(pt);
        if (ret < 0) {
            return 0;
        }
        PORT_FD(pt) = ret;
        gMcCardStep++;
        return 0;
    case 10:
        ret = sceMcWrite(PORT_FD(pt), *(s32 *)(file + 0), *(s32 *)(file + 0xC));
        PORT_RET(pt) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 13:
        if (sceMcSync(1, 0, &PORT_RESULT(pt)) == 0) {
            return 0;
        }
        if (PORT_RESULT(pt) < 0) {
            return 0;
        }
        gMcCardStep++;
        return 1;
    default:
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    }
}

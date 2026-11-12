/* F4 (saltar intro): los logos y el opening del arranque se pueden saltear sin tocar el flujo del juego.
   Mismo patron que plat_autosave.c (F3): BT2_SKIP_INTRO gana por corrida; si no, setting persistente
   "skip_intro" de bt2_settings.txt. Default: encendido (1); con BT2_SKIP_INTRO=0 o skip_intro=0 se ve
   la intro original. Las funciones de settings viven en port/full/gs/plat_settings_bt3.c y pueden no
   entrar en todos los enlaces: quedan weak. */
#include <stdlib.h>

int Port_Setting(const char *name, int def) __attribute__((weak));
void Port_SettingSave(const char *name, int value) __attribute__((weak));
void Port_SettingsWrite(void) __attribute__((weak));

static int sSkip = -1;

int Port_SkipIntro(void) {
    if (sSkip < 0) {
        const char *e = getenv("BT2_SKIP_INTRO");
        if (e != NULL) {
            sSkip = (*e != '0' && *e != 0);
        } else if (Port_Setting != NULL) {
            sSkip = Port_Setting("skip_intro", 1);   /* 0 = ver la intro siempre */
        } else {
            sSkip = 1;
        }
    }
    return sSkip;
}

void Port_SkipIntroSet(int on) {
    sSkip = on != 0;
    if (Port_SettingSave != NULL) {
        Port_SettingSave("skip_intro", sSkip);
        if (Port_SettingsWrite != NULL) {
            Port_SettingsWrite();
        }
    }
}

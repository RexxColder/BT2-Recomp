/* F3 (autoguardado): el juego pregunta si guardar/sobrescribir y el port contesta "si" por el jugador.
   Mismo patron que Tenkaichi3Decomp (port/src/plat_autosave.c): no agrega puntos de guardado ni formato.
   Las funciones de settings viven en port/full/gs/plat_settings_bt3.c, que no entra en todos los enlaces:
   quedan weak y, si no estan, el autoguardado simplemente queda encendido. */
#include <stdlib.h>

int Port_Setting(const char *name, int def) __attribute__((weak));
void Port_SettingSave(const char *name, int value) __attribute__((weak));
void Port_SettingsWrite(void) __attribute__((weak));

static int sAuto = -1;

int Port_Autosave(void) {
    if (sAuto < 0) {
        const char *e = getenv("BT2_AUTOSAVE");
        if (e != NULL) {
            sAuto = (*e != '0' && *e != 0);
        } else if (Port_Setting != NULL) {
            sAuto = Port_Setting("autosave", 1);
        } else {
            sAuto = 1;
        }
    }
    return sAuto;
}

void Port_AutosaveSet(int on) {
    sAuto = on != 0;
    if (Port_SettingSave != NULL) {
        Port_SettingSave("autosave", sAuto);
        if (Port_SettingsWrite != NULL) {
            Port_SettingsWrite();
        }
    }
}

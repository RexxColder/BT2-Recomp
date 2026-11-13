/*
 * F5: textos del dialogo de memory card.
 *
 * El juego muestra los mensajes de guardado/carga desde una tabla UTF-16LE que vive dentro del
 * recurso 0x550 de ZS2US_1.AFS, descomprimido en RAM por func_003E3D38
 * (port/eq/3E3D38.c:101). Esta capa reescribe esa copia EN RAM justo despues de cargarla: no toca
 * el AFS, el ISO ni el save, y no afecta a otras pantallas (cada pantalla que llama a 3E3D38 tiene
 * su propia copia).
 *
 * Formato de la tabla (staging/F5_textos_memorycard.md):
 *   u32 count = 49; word[1..49] = offsets (relativos a la tabla, alineados a 4) a strings UTF-16LE
 *   con BOM FF FE, '\n' = U+000A y terminador U+0000.  MSG n usa la entrada n+1.
 *   Cada string vive en un slot alineado a 0x40: no se puede escribir mas alla del siguiente offset.
 *
 * Configuracion (todo opcional):
 *   FILTRO "(PS2)": ENCENDIDO por defecto (los textos salen sin "(PS2)").
 *     - bt2_settings.txt:  texto_ps2=1   deja "(PS2)" como el juego; texto_ps2=0 (o ausente) lo saca.
 *     - entorno:           BT2_TEXTO_PS2=1  deja "(PS2)";  BT2_TEXTO_PS2=0 (o ausente) lo saca.
 *     La variable de entorno gana sobre el archivo de settings. El nombre significa "dejar el texto
 *     (PS2)": 0 = sacarlo (default), 1 = dejarlo.
 *   Textos: bt2_texto.txt en el directorio actual (o la ruta de $BT2_TEXTO), lineas "MSG=texto" con
 *     \n para el salto de linea. Sin archivo no hay overrides: queda el texto del juego (ya sin "(PS2)").
 *   Idioma del texto (F8): setting "idioma" en bt2_settings.txt o variable BT2_IDIOMA
 *     (0=EN, 1=ES, 2=FR, 3=DE, 4=IT; tambien acepta en/es/fr/de/it).
 *     0 -> bt2_texto.txt; 1..4 -> textos/bt2_texto.<lang>.txt; si no existe, fallback a bt2_texto.txt.
 *     $BT2_TEXTO gana sobre todo. Se lee una sola vez por proceso: cambiar de idioma pide reiniciar.
 *
 * Nada de esto escribe fuera de la tabla ni mas alla del slot de cada string: si un texto no entra,
 * queda el original y se avisa UNA vez por MSG en stderr.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Port_Setting(const char *name, int def) __attribute__((weak));

#define TEXTO_ENTRADAS 49
#define TEXTO_MAX      256 /* u16 por string: sobra para el slot mas grande (0x200 bytes) */
#define TEXTO_ANCHO    429 /* px: la linea mas ancha del juego mide 429 (ver el informe) */
#define TEXTO_LINEAS   5   /* port/eq/29C038.c:47-65 contempla 1..5 lineas */

typedef struct {
    int msg; /* campo +0x10C del dialogo; la tabla es word[msg+1] */
    const char *utf8;
} TextoDef;

/* Overrides de ejemplo. El MSG es el del estado de port/eq/3E51F8.c, no el indice de la tabla:
   MSG 21 = estados 18/32 ("already exists"), 24 = estado 27 ("card replaced"),
   28 = estado 16 ("save game data?"), 37 = estado 28 ("settings changed"). */
static const TextoDef kDefs[] = {
    { 21, "Save data already exists.\nOverwrite it?" },
    { 24, "The memory card has been replaced.\nOverwrite the data?" },
    { 28, "Save game data?" },
    { 37, "Settings have been changed.\nSave the changes?" },
    { 13, "Memory card is unformatted.\nFormat it?" },
    { 27, "Memory card is unformatted." },
};

/* Texto por defecto del port para un MSG (los de kDefs), o NULL. */
static const char *def_por_msg(unsigned msg) {
    unsigned i;
    for (i = 0; i < sizeof(kDefs) / sizeof(kDefs[0]); i++) {
        if ((unsigned)kDefs[i].msg == msg) {
            return kDefs[i].utf8;
        }
    }
    return NULL;
}

/* Avance (px) de los glifos 0x20..0x7E del font0 del juego (AFS 0x542, font en +0x40). */
static const unsigned char kAdv[95] = {
     9, 5, 7,13,11,19,15, 5, 7, 7, 9,13, 7, 7, 5, 9,11,11,11,
    11,13,11,11,11,11,11, 5, 7,13,13,13, 9,17,15,11,13,13,11,
    11,13,11, 9, 9,11, 9,13,11,13, 9,13,11,13,13,13,15,17,13,
    13,13, 7, 9, 7,13,13, 7,11,11,11,11,11, 9,11,11, 5, 7,11,
     5,17,11,11,11,11, 9,11, 9,11,11,15,11,11, 9,11, 5,11,13,
};

static int sInit;
static char *sOverride[TEXTO_ENTRADAS];
static unsigned sWarned;   /* bit MSG: ya se aviso que ese texto no entra (una sola vez) */

/* Idioma de texto pedido por BT2_IDIOMA: numero 0..4 o codigo en/es/fr/de/it. Otro valor -> 0 (EN). */
static int idioma_de_texto(const char *s) {
    if (s == NULL || s[0] == 0) {
        return 0;
    }
    if (s[0] >= '0' && s[0] <= '4' && s[1] == 0) {
        return s[0] - '0';
    }
    if ((s[0] == 'e' && s[1] == 'n') || (s[0] == 'E' && s[1] == 'N')) return 0;
    if ((s[0] == 'e' && s[1] == 's') || (s[0] == 'E' && s[1] == 'S')) return 1;
    if ((s[0] == 'f' && s[1] == 'r') || (s[0] == 'F' && s[1] == 'R')) return 2;
    if ((s[0] == 'd' && s[1] == 'e') || (s[0] == 'D' && s[1] == 'E')) return 3;
    if ((s[0] == 'i' && s[1] == 't') || (s[0] == 'I' && s[1] == 'T')) return 4;
    return 0;
}

/* Idioma resuelto de los datos (F8, multiidioma EU): el mismo indice que elige la ruta de textos.
   0 = EN/apagado, 1 = ES, 2 = FR, 3 = DE, 4 = IT. Lo usa plat_file.c para remapear los ids de la
   particion EU. Se resuelve una sola vez por proceso (reiniciar para cambiar de idioma). */
static int sIdioma = -1;

int Port_Idioma(void) {
    const char *texto;
    const char *env;
    int lang;

    if (sIdioma >= 0) {
        return sIdioma;
    }
    texto = getenv("BT2_TEXTO");
    if (texto != NULL && texto[0] != 0) {
        sIdioma = 0; /* texto impuesto por archivo: no hay idioma de datos */
        return sIdioma;
    }
    env = getenv("BT2_IDIOMA");
    if (env != NULL && env[0] != 0) {
        lang = idioma_de_texto(env);
    } else if (Port_Setting != NULL) {
        lang = Port_Setting("idioma", 0);
    } else {
        lang = 0;
    }
    if (lang < 0 || lang > 4) {
        lang = 0;
    }
    sIdioma = lang;
    return sIdioma;
}

static void leer_archivo(void) {
    static const char *kTextoIdioma[5] = {
        "textos/bt2_texto.txt",   /* producto: todo en textos/ (bt2_texto.txt suelto sigue valiendo, abajo) */
        "textos/bt2_texto.es.txt",
        "textos/bt2_texto.fr.txt",
        "textos/bt2_texto.de.txt",
        "textos/bt2_texto.it.txt",
    };
    const char *ruta;
    FILE *fp;
    char linea[512];
    int lang = 0;

    if (sInit != 0) {
        return;
    }
    sInit = 1;
    ruta = getenv("BT2_TEXTO");
    if (ruta == NULL || ruta[0] == 0) {
        lang = Port_Idioma();
        if (lang < 0 || lang > 4) {
            lang = 0;
        }
        ruta = kTextoIdioma[lang];
    }
    fp = fopen(ruta, "r");
    if (fp == NULL && ruta == kTextoIdioma[lang]) {
        fprintf(stderr, "F8 idioma %d: no existe '%s'; fallback a bt2_texto.txt\n", lang, ruta);
        ruta = "bt2_texto.txt";
        fp = fopen(ruta, "r");
    }
    if (fp == NULL) {
        return;
    }
    while (fgets(linea, sizeof(linea), fp) != NULL) {
        char *p = linea;
        char *q;
        int msg;
        size_t n;
        while (*p == ' ' || *p == '\t') {
            p++;
        }
        if (*p == '#' || *p == '\n' || *p == 0) {
            continue;
        }
        msg = (int)strtol(p, &q, 10);
        if (q == p || *q != '=') {
            continue;
        }
        q++;
        while (*q == ' ' || *q == '\t') {
            q++;
        }
        n = strlen(q);
        while (n > 0 && (q[n - 1] == '\n' || q[n - 1] == '\r')) {
            q[--n] = 0;
        }
        if (msg >= 0 && msg < TEXTO_ENTRADAS) {
            free(sOverride[msg]);
            sOverride[msg] = strdup(q);
        }
    }
    fclose(fp);
}

/* 1 cuando hay que sacar "(PS2)". ENCENDIDO por defecto: solo se apaga con texto_ps2=1 /
   BT2_TEXTO_PS2=1 (el entorno gana). */
static int quitar_ps2(void) {
    const char *e = getenv("BT2_TEXTO_PS2");
    if (e != NULL && e[0] != 0) {
        return *e != '1';
    }
    if (Port_Setting != NULL) {
        return Port_Setting("texto_ps2", 0) == 0;
    }
    return 1;
}

/* UTF-8 -> UTF-16LE. Acepta \\n como salto. Devuelve la cantidad de u16 (sin el NUL). */
static int utf8_a_utf16(const char *s, unsigned short *out, int cap) {
    int n = 0;
    while (*s != 0) {
        unsigned char c = (unsigned char)*s++;
        unsigned cp;
        if (c == '\\' && *s == 'n') {
            s++;
            cp = '\n';
        } else if (c < 0x80) {
            cp = c;
        } else if ((c & 0xE0) == 0xC0) {
            cp = ((unsigned)(c & 0x1F) << 6) | (unsigned)((unsigned char)*s++ & 0x3F);
        } else if ((c & 0xF0) == 0xE0) {
            cp = ((unsigned)(c & 0x0F) << 12) | ((unsigned)((unsigned char)*s++ & 0x3F) << 6);
            cp |= (unsigned)((unsigned char)*s++ & 0x3F);
        } else {
            continue; /* 4 bytes (emoji): el font del juego no los tiene */
        }
        if (n + 1 >= cap) {
            break;
        }
        out[n++] = (unsigned short)cp;
    }
    out[n] = 0;
    return n;
}

/* Saca "(PS2)" y el espacio que lo precede. */
static int filtrar_ps2(const unsigned short *in, unsigned short *out, int cap) {
    int i = 0;
    int n = 0;
    while (in[i] != 0) {
        if (in[i] == '(' && in[i + 1] == 'P' && in[i + 2] == 'S' && in[i + 3] == '2' && in[i + 4] == ')') {
            if (n > 0 && out[n - 1] == ' ') {
                n--;
            }
            i += 5;
            continue;
        }
        if (n + 1 >= cap) {
            break;
        }
        out[n++] = in[i++];
    }
    out[n] = 0;
    return n;
}

static int ancho_char(unsigned c) {
    if (c >= 0x20 && c < 0x7F) {
        return kAdv[c - 0x20];
    }
    return 11; /* Latin-1 acentuado: el font0 mide 11 para casi todos */
}

static int ancho_linea(const unsigned short *s, int n) {
    int w = 0;
    int i;
    for (i = 0; i < n; i++) {
        w += ancho_char(s[i]);
    }
    return w;
}

/* Corta las lineas que pasen de TEXTO_ANCHO px en el ultimo espacio. -1 si no entra en el buffer
   o si necesita mas de TEXTO_LINEAS lineas. */
static int envolver(const unsigned short *in, int len, unsigned short *out, int cap) {
    int i;
    int n = 0;
    int ini = 0;
    int lineas = 1;

    for (i = 0; i < len; i++) {
        unsigned c = in[i];
        if (c == '\n') {
            if (n + 1 >= cap) {
                return -1;
            }
            out[n++] = (unsigned short)c;
            ini = n;
            if (++lineas > TEXTO_LINEAS) {
                return -1;
            }
            continue;
        }
        if (n > ini && ancho_linea(out + ini, n - ini) + ancho_char(c) > TEXTO_ANCHO) {
            int j = n - 1;
            while (j > ini && out[j] != ' ') {
                j--;
            }
            if (j > ini) {
                out[j] = '\n';
                ini = j + 1;
            } else {
                if (n + 1 >= cap) {
                    return -1;
                }
                out[n++] = '\n';
                ini = n;
            }
            if (++lineas > TEXTO_LINEAS) {
                return -1;
            }
        }
        if (n + 1 >= cap) {
            return -1;
        }
        out[n++] = (unsigned short)c;
    }
    out[n] = 0;
    return n;
}

/* u16 utiles del slot de la entrada k (sin contar el NUL). */
static int slot_u16(const unsigned int *w, unsigned count, unsigned k, unsigned *off_out) {
    unsigned off = w[k] & ~3u;
    unsigned next;
    if (k < count) {
        next = w[k + 1] & ~3u;
    } else {
        next = off + 0x40; /* ultima entrada del bloque: el siguiente paso de alineacion */
    }
    *off_out = off;
    if (next <= off) {
        return -1;
    }
    return (int)((next - off) / 2) - 1;
}

static void escribir(unsigned char *base, unsigned off, const unsigned short *s, int n) {
    unsigned short *dst = (unsigned short *)(base + off);
    int i;
    for (i = 0; i <= n; i++) {
        dst[i] = s[i];
    }
}

/* Un solo aviso por MSG (el bit 31 queda libre para "no se pudo envolver"). */
static void avisar(unsigned msg, int envolver_fallo) {
    unsigned bit = msg < 32 ? 1u << msg : 1u << 31;
    static unsigned sWarnedWrap;
    unsigned *mask = envolver_fallo ? &sWarnedWrap : &sWarned;
    unsigned *other = envolver_fallo ? &sWarned : &sWarnedWrap;
    if ((*mask & bit) || (*other & bit)) {
        return;
    }
    *mask |= bit;
    if (envolver_fallo) {
        fprintf(stderr, "F5 texto: MSG %u no se pudo envolver; queda el original\n", msg);
    } else {
        fprintf(stderr, "F5 texto: MSG %u no entra en el slot; queda el original\n", msg);
    }
}

/* Se llama desde func_003E3D38 (port/eq/3E3D38.c) con la tabla ya descomprimida en RAM.
   `tabla` es una direccion de 32 bits del juego (la RAM de la PS2 esta mapeada en 0). */
void Port_TextoAplicarTabla(uint32_t tabla) {
    unsigned char *base = (unsigned char *)(uintptr_t)tabla;
    unsigned int *w;
    unsigned count;
    unsigned msg;

    if (base == NULL) {
        return;
    }
    leer_archivo();
    w = (unsigned int *)base;
    count = w[0];
    /* Solo la tabla del dialogo de memory card (0x550 sub-bloque 0): 49 entradas y el primer
       string en +0x100 ("MEMORY CARD slot 1"). Cualquier otra tabla se deja intacta. */
    if (count != TEXTO_ENTRADAS || (w[1] & ~3u) != 0x100) {
        return;
    }

    for (msg = 0; msg < TEXTO_ENTRADAS; msg++) {
        unsigned kk = msg + 1;
        unsigned off;
        int slot, n;
        const char *src = NULL;
        unsigned short tmp[TEXTO_MAX], tmp2[TEXTO_MAX];
        int cur_len;

        if (kk > count) {
            break;
        }
        slot = slot_u16(w, count, kk, &off);
        if (slot < 0) {
            continue;
        }

        if (sOverride[msg] != NULL) {
            src = sOverride[msg];            /* override del usuario */
        } else {
            src = def_por_msg(msg);          /* default del port (kDefs) o NULL */
        }

        if (src != NULL) {
            n = utf8_a_utf16(src, tmp, TEXTO_MAX);
        } else if (quitar_ps2() != 0) {
            /* sin override ni default: filtrar "(PS2)" sobre el texto actual de la tabla */
            const unsigned short *cur = (const unsigned short *)(base + off);
            cur_len = 0;
            while (cur_len < slot && cur_len < TEXTO_MAX - 1 && cur[cur_len] != 0) {
                cur_len++;
            }
            for (n = 0; n < cur_len; n++) {
                tmp[n] = cur[n];
            }
            tmp[n] = 0;
        } else {
            continue;                        /* nada que hacer */
        }

        if (quitar_ps2() != 0) {
            n = filtrar_ps2(tmp, tmp2, TEXTO_MAX);
            memcpy(tmp, tmp2, (size_t)(n + 1) * sizeof(tmp[0]));
        }
        n = envolver(tmp, n, tmp2, TEXTO_MAX);
        if (n < 0) {
            avisar(msg, 1);
            continue;
        }
        if (n > slot) {
            avisar(msg, 0);
            continue;
        }
        escribir(base, off, tmp2, n);
    }
}

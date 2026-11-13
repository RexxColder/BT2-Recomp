// bt2-setup: instalador del port de Dragon Ball Z: Budokai Tenkaichi 2.
//
//   bt2-setup                         ventana (SDL3 + ImGui)
//   bt2-setup --install <iso> ...     consola
//   bt2-setup --check [--iso <iso>]   revisa la ISO y/o la instalación
//   bt2-setup --list <iso>            lista el contenido del disco
//   bt2-setup --play [--dest <dir>]   lanza el juego
//
// Códigos de salida: 0 ok, 1 error, 3 el programa del disco no es el de la edición USA sin modificar.
#include <SDL3/SDL.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "gui.h"
#include "install.h"
#include "iso.h"
#include "launch.h"
#include "paths.h"

#define BT2_SETUP_VERSION "2.0"

namespace {

struct Options {
    std::string iso;
    std::string dest;
    std::string eu_iso;
    bool install = false;
    bool check = false;
    bool list = false;
    bool play = false;
    bool force = false;
    bool help = false;
    bool version = false;
};

void usage(FILE *out)
{
    fprintf(out,
            "bt2-setup " BT2_SETUP_VERSION " — instalador de BT2 (Budokai Tenkaichi 2, edición USA)\n"
            "\n"
            "Uso:\n"
            "  bt2-setup                          abre la ventana del setup\n"
            "  bt2-setup <iso>                    abre la ventana con la ISO ya puesta\n"
            "  bt2-setup --install <iso> [opciones]\n"
            "  bt2-setup --check [--iso <iso>] [--dest <carpeta>]\n"
            "  bt2-setup --list <iso>\n"
            "  bt2-setup --play [--dest <carpeta>]\n"
            "\n"
            "Opciones:\n"
            "  --dest <carpeta>   carpeta de datos (por defecto: gamedata/ junto al juego)\n"
            "  --eu-iso <iso>     ISO PAL opcional: copia DATA/ZS2EU_1.AFS para el multiidioma\n"
            "  --force            vuelve a copiar todo, aunque los archivos ya estén\n"
            "  --help             esta ayuda\n"
            "  --version          versión\n"
            "\n"
            "Códigos de salida: 0 ok, 1 error, 3 el programa del disco no es el de la edición USA.\n");
}

std::string with_default_dest(const std::string &dest, const std::string &root)
{
    return dest.empty() ? root + "/gamedata" : bt2_absolute(dest);
}

int parse_args(int argc, char **argv, Options *o)
{
    bool positional = false;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto value = [&](const char *what) -> std::string {
            if (i + 1 >= argc) {
                fprintf(stderr, "error: %s necesita un valor.\n", what);
                return std::string();
            }
            return std::string(argv[++i]);
        };
        if (a == "--install") {
            o->install = true;
            o->iso = value("--install");
            if (o->iso.empty()) {
                return 1;
            }
        } else if (a == "--dest") {
            o->dest = value("--dest");
            if (o->dest.empty()) {
                return 1;
            }
        } else if (a == "--eu-iso") {
            o->eu_iso = value("--eu-iso");
            if (o->eu_iso.empty()) {
                return 1;
            }
        } else if (a == "--iso") {
            o->iso = value("--iso");
            if (o->iso.empty()) {
                return 1;
            }
        } else if (a == "--check") {
            o->check = true;
        } else if (a == "--list") {
            o->list = true;
        } else if (a == "--play") {
            o->play = true;
        } else if (a == "--force") {
            o->force = true;
        } else if (a == "--help" || a == "-h") {
            o->help = true;
        } else if (a == "--version") {
            o->version = true;
        } else if (a.size() > 0 && a[0] == '-') {
            fprintf(stderr, "error: opción desconocida: %s\n", a.c_str());
            return 1;
        } else if (!positional && o->iso.empty()) {
            o->iso = a;
            positional = true;
        } else {
            fprintf(stderr, "error: argumento de más: %s\n", a.c_str());
            return 1;
        }
    }
    return 0;
}

struct CliProgress {
    int last_pct = -1;
};

volatile sig_atomic_t gSigCancel = 0;

void on_sigint(int sig)
{
    (void)sig;
    gSigCancel = 1;
}

int cli_cancel(void *user)
{
    (void)user;
    return gSigCancel != 0 ? 1 : 0;
}

void cli_event(const Bt2Event *ev, void *user)
{
    CliProgress *p = (CliProgress *)user;
    switch (ev->kind) {
    case BT2_EV_STEP:
        p->last_pct = -1;
        printf("\n== [%d/%d] %s ==\n", ev->step, ev->steps, ev->step_name);
        fflush(stdout);
        break;
    case BT2_EV_FILE: {
        char size[64];
        bt2_human_bytes(ev->file_size, size, sizeof(size));
        printf("[%2d/%2d] %-56s %10s\n", ev->index, ev->files_total, ev->path, size);
        fflush(stdout);
        break;
    }
    case BT2_EV_NOTE:
        if (ev->message != nullptr) {
            if (strcmp(ev->message, "ya estaba") == 0) {
                printf("         ya está\n");
            } else {
                printf("         %s\n", ev->message);
            }
            fflush(stdout);
        }
        break;
    case BT2_EV_PROGRESS: {
        int pct = ev->total_bytes > 0 ? (int)((double)ev->done_bytes * 100.0 / (double)ev->total_bytes) : 0;
        if (pct >= p->last_pct + 10 || pct == 100) {
            char done[64], total[64];
            bt2_human_bytes(ev->done_bytes, done, sizeof(done));
            bt2_human_bytes(ev->total_bytes, total, sizeof(total));
            printf("         %3d%%  %s / %s\n", pct, done, total);
            fflush(stdout);
            p->last_pct = pct;
        }
        break;
    }
    case BT2_EV_ERROR:
        fprintf(stderr, "\nerror: %s\n", ev->message != nullptr ? ev->message : "falló la instalación");
        fflush(stderr);
        break;
    case BT2_EV_DONE:
        printf("\n%s\n", ev->message != nullptr ? ev->message : "listo");
        fflush(stdout);
        break;
    }
}

int cmd_preflight_print(const Options &o, const std::string &dest, Bt2Preflight *pre)
{
    int rc = bt2_preflight(o.iso.c_str(), dest.c_str(), o.eu_iso.empty() ? nullptr : o.eu_iso.c_str(),
                           o.force ? 1 : 0, pre);
    printf("ISO: %s\n", o.iso.c_str());
    if (rc == 0) {
        printf("  ok: %s\n", pre->message);
    } else {
        printf("  error: %s\n", pre->error);
    }
    return rc;
}

int cmd_check(const Options &o, const std::string &root)
{
    std::string dest = with_default_dest(o.dest, root);
    int rc = 0;
    Bt2Check check;

    if (!o.iso.empty()) {
        Bt2Preflight pre;
        int prc = cmd_preflight_print(o, dest, &pre);
        if (prc == 3) {
            rc = 3;
        } else if (prc != 0) {
            rc = 1;
        }
    }
    printf("Destino: %s\n", dest.c_str());
    int crc = bt2_check_dest(dest.c_str(), 1, &check);
    if (crc == 0) {
        printf("  ok: %s\n", check.summary);
        printf("  ELF: %s\n", check.elf_hash_ok == 1 ? "SHA-1 correcto" : "no verificado");
        printf("  DBZP: %s\n", check.dbzp_hash_ok == 1 ? "SHA-1 correcto" : "no verificado");
    } else {
        printf("  error: %s\n", check.summary);
        if (check.missing[0] != '\0') {
            printf("  faltan:\n");
            const char *p = check.missing;
            while (*p != '\0') {
                const char *nl = strchr(p, '\n');
                int len = nl != nullptr ? (int)(nl - p) : (int)strlen(p);
                printf("    %.*s\n", len, p);
                p = nl != nullptr ? nl + 1 : p + strlen(p);
            }
        }
    }
    if (crc == 3) {
        rc = 3;
    } else if (crc != 0 && rc == 0) {
        rc = 1;
    }
    return rc;
}

int cmd_list(const Options &o)
{
    Iso iso;
    char err[1024];
    if (o.iso.empty()) {
        fprintf(stderr, "error: falta la ISO. Uso: bt2-setup --list <iso>\n");
        return 1;
    }
    if (iso_open(&iso, o.iso.c_str(), err, sizeof(err)) != 0) {
        fprintf(stderr, "error: %s\n", err);
        return 1;
    }
    printf("Volumen: %s\n", iso.volume_id);
    bt2_list_iso(&iso, stdout);
    iso_close(&iso);
    return 0;
}

int cmd_install(const Options &o, const std::string &root)
{
    std::string dest = with_default_dest(o.dest, root);
    Bt2Preflight pre;
    int prc = cmd_preflight_print(o, dest, &pre);
    if (prc != 0) {
        return prc == 3 ? 3 : 1;
    }
    CliProgress prog;
    signal(SIGINT, on_sigint);
    signal(SIGTERM, on_sigint);
    int rc = bt2_install(o.iso.c_str(), dest.c_str(), o.eu_iso.empty() ? nullptr : o.eu_iso.c_str(),
                         o.force ? 1 : 0, cli_cancel, nullptr, cli_event, &prog);
    if (rc == 0) {
        char game[4096];
        printf("\nDatos instalados en: %s\n", dest.c_str());
        if (bt2_find_game(root.c_str(), game, sizeof(game))) {
            printf("Para jugar: %s\n", game);
            if (dest != root + "/gamedata") {
                printf("  (con BT2_DATA=\"%s\" BT2_ELF=\"%s/SLUS_214.41\")\n", dest.c_str(), dest.c_str());
            }
        } else {
            printf("Compilá el port para obtener port/build/full/bt2full.\n");
        }
        return 0;
    }
    if (rc == 2) {
        printf("\nCancelado. Los archivos ya copiados se conservan; se puede retomar.\n");
        return 1;
    }
    return rc == 3 ? 3 : 1;
}

int cmd_play(const Options &o, const std::string &root)
{
    std::string dest = with_default_dest(o.dest, root);
    Bt2Check check;
    int crc = bt2_check_dest(dest.c_str(), 0, &check);
    if (crc != 0) {
        fprintf(stderr, "error: los datos no están completos en %s: %s\n", dest.c_str(), check.summary);
        return 1;
    }
    if (!SDL_Init(0)) {
        fprintf(stderr, "error: SDL: %s\n", SDL_GetError());
        return 1;
    }
    char err[1024], game[4096];
    if (bt2_launch_game(root.c_str(), dest.c_str(), err, sizeof(err)) != 0) {
        fprintf(stderr, "error: %s\n", err);
        SDL_Quit();
        return 1;
    }
    if (bt2_find_game(root.c_str(), game, sizeof(game))) {
        printf("Jugando: %s (datos en %s)\n", game, dest.c_str());
    }
    SDL_Quit();
    return 0;
}

} // namespace

int main(int argc, char **argv)
{
#ifdef SIGXFSZ
    /* Si el sistema operativo limita el tamaño de archivo, preferimos ver el error de escritura
     * ("¿disco lleno?") en vez de morir por SIGXFSZ. */
    signal(SIGXFSZ, SIG_IGN);
#endif
    Options o;
    if (parse_args(argc, argv, &o) != 0) {
        usage(stderr);
        return 1;
    }
    if (o.help) {
        usage(stdout);
        return 0;
    }
    if (o.version) {
        printf("bt2-setup %s\n", BT2_SETUP_VERSION);
        return 0;
    }
    std::string root = bt2_root();

    if (o.list) {
        return cmd_list(o);
    }
    if (o.check) {
        return cmd_check(o, root);
    }
    if (o.install) {
        return cmd_install(o, root);
    }
    if (o.play) {
        return cmd_play(o, root);
    }
    return bt2_gui_run(root, o.iso, o.dest);
}

#include "launch.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <SDL3/SDL.h>

static int file_ok(const char *path)
{
    struct stat st;
    return path != NULL && path[0] != '\0' && stat(path, &st) == 0 && S_ISREG(st.st_mode) && st.st_size > 0 &&
           access(path, X_OK) == 0;
}

int bt2_find_game(const char *root, char *out, size_t outsz)
{
    const char *env = getenv("BT2_GAME");
    char candidates[8][4096];
    int i, n = 0;

    if (env != NULL && env[0] != '\0') {
        snprintf(candidates[n++], 4096, "%s", env);
    }
    if (root != NULL && root[0] != '\0') {
        snprintf(candidates[n++], 4096, "%s/port/build/full/bt2full", root);
        snprintf(candidates[n++], 4096, "%s/../BT2-test/bin/bt2", root);
        snprintf(candidates[n++], 4096, "%s/BT2-test/bin/bt2", root);
        snprintf(candidates[n++], 4096, "%s/bt2full", root);
        snprintf(candidates[n++], 4096, "%s/bt2", root);
    }
    snprintf(candidates[n++], 4096, "port/build/full/bt2full");
    for (i = 0; i < n; i++) {
        if (file_ok(candidates[i])) {
            if (realpath(candidates[i], out) != NULL) {
                return 1;
            }
            snprintf(out, outsz, "%s", candidates[i]);
            return 1;
        }
    }
    return 0;
}

int bt2_launch_game(const char *root, const char *dest, char *err, size_t errsz)
{
    char game[4096];
    char data[4096];
    char elf[4096];
    char absdest[4096];
    const char *args[2];
    SDL_PropertiesID props;
    SDL_Environment *env;
    SDL_Process *proc;

    if (!bt2_find_game(root, game, sizeof(game))) {
        snprintf(err, errsz,
                 "No encontré el binario del juego. Compilá el port (port/build/full/bt2full) o definí BT2_GAME.");
        return -1;
    }
    if (dest == NULL || dest[0] == '\0') {
        snprintf(err, errsz, "No hay carpeta de datos para el juego.");
        return -1;
    }
    if (realpath(dest, absdest) == NULL) {
        snprintf(err, errsz, "La carpeta de datos no existe: %s", dest);
        return -1;
    }
    snprintf(data, sizeof(data), "%s", absdest);
    if (snprintf(elf, sizeof(elf), "%s/SLUS_214.41", absdest) >= (int)sizeof(elf)) {
        snprintf(err, errsz, "La ruta de los datos es demasiado larga.");
        return -1;
    }
    {
        struct stat st;
        if (stat(elf, &st) != 0 || !S_ISREG(st.st_mode)) {
            snprintf(err, errsz, "Faltan los datos del juego en %s (no está SLUS_214.41).", absdest);
            return -1;
        }
    }
    args[0] = game;
    args[1] = NULL;
    props = SDL_CreateProperties();
    if (props == 0) {
        snprintf(err, errsz, "SDL: %s", SDL_GetError());
        return -1;
    }
    env = SDL_CreateEnvironment(true);
    if (env == NULL) {
        SDL_DestroyProperties(props);
        snprintf(err, errsz, "SDL: %s", SDL_GetError());
        return -1;
    }
    SDL_SetEnvironmentVariable(env, "BT2_DATA", data, true);
    SDL_SetEnvironmentVariable(env, "BT2_ELF", elf, true);
    SDL_UnsetEnvironmentVariable(env, "BT2_DEMO");
    SDL_UnsetEnvironmentVariable(env, "BT2_REPLAY");
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)args);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ENVIRONMENT_POINTER, env);
    SDL_SetStringProperty(props, SDL_PROP_PROCESS_CREATE_WORKING_DIRECTORY_STRING, root != NULL ? root : ".");
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_NULL);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_INHERITED);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_NUMBER, SDL_PROCESS_STDIO_INHERITED);
    SDL_SetBooleanProperty(props, SDL_PROP_PROCESS_CREATE_BACKGROUND_BOOLEAN, true);
    proc = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDL_DestroyEnvironment(env);
    if (proc == NULL) {
        snprintf(err, errsz, "No se pudo lanzar el juego: %s", SDL_GetError());
        return -1;
    }
    SDL_DestroyProcess(proc); /* en segundo plano: sigue solo aunque se cierre el setup */
    return 0;
}

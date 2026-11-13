#include "paths.h"

#include <SDL3/SDL.h>

#include <climits>
#include <cstdlib>
#include <limits.h>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

static bool is_dir(const std::string &p)
{
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

static bool is_file(const std::string &p)
{
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

std::string bt2_exe_dir()
{
    const char *base = SDL_GetBasePath();
    if (base != nullptr && base[0] != '\0') {
        std::string s(base);
        if (!s.empty() && s.back() != '/') {
            s += '/';
        }
        return s;
    }
    return "./";
}

std::string bt2_absolute(const std::string &path)
{
    if (path.empty()) {
        return path;
    }
    if (path[0] == '/') {
        return path;
    }
    const char *cwd = SDL_GetCurrentDirectory();
    std::string base = cwd != nullptr ? std::string(cwd) + "/" : std::string("./");
    SDL_free((void *)cwd);
    return base + path;
}

std::string bt2_root()
{
    const char *env = getenv("BT2_SETUP_ROOT");
    std::vector<std::string> candidates;

    if (env != nullptr && env[0] != '\0') {
        candidates.push_back(bt2_absolute(env));
    }
    std::string exe = bt2_exe_dir();
    /* Producto: BT2-setup al lado del juego (BT2/BT2, BT2/BT2-setup, BT2/gamedata). Esa carpeta es la raíz. */
    {
        char resolved[PATH_MAX];
        if (realpath(exe.c_str(), resolved) != nullptr && is_file(std::string(resolved) + "/BT2")) {
            return std::string(resolved);
        }
    }
    candidates.push_back(exe);
    candidates.push_back(exe + "..");
    candidates.push_back(exe + "../..");
    candidates.push_back(exe + "../../..");
    if (const char *cwd = SDL_GetCurrentDirectory()) {
        candidates.push_back(cwd);
        candidates.push_back(std::string(cwd) + "/..");
        SDL_free((void *)cwd);
    }
    for (const std::string &c : candidates) {
        char resolved[PATH_MAX];
        if (realpath(c.c_str(), resolved) == nullptr) {
            continue;
        }
        std::string r(resolved);
        if (is_file(r + "/setup/install.py") || (is_dir(r + "/port/full") && is_file(r + "/README.md"))) {
            return r;
        }
    }
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return std::string(cwd);
    }
    return ".";
}

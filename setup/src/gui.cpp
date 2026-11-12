// Ventana del setup de BT2: elegir la ISO, ver el progreso y jugar. SDL3 + Dear ImGui (OpenGL 3).
//
// El trabajo lo hace install.c en un hilo aparte; acá sólo se muestran los eventos que manda. La ventana
// no bloquea: el botón Play lanza el juego en segundo plano y el setup se puede cerrar.
#include "gui.h"

#include <SDL3/SDL.h>

#include <atomic>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "imgui_impl_sdl3.h"

#include "install.h"
#include "launch.h"
#include "paths.h"

namespace {

enum Page { PAGE_PICK, PAGE_RUN, PAGE_DONE, PAGE_FAILED };
enum RowState { ROW_PENDING, ROW_RUNNING, ROW_OK, ROW_SKIPPED, ROW_FAILED };
enum DialogTarget { DLG_NONE, DLG_ISO, DLG_EU, DLG_DEST };

struct StepRow {
    std::string title;
    std::string detail;
    RowState state = ROW_PENDING;
    Uint64 start = 0;
    Uint64 end = 0;
};

struct Msg {
    int kind = 0; // Bt2EventKind o MSG_RESULT
    int step = 0, steps = 0;
    std::string step_name, path, message;
    uint64_t file_size = 0, file_done = 0, done_bytes = 0, total_bytes = 0;
    int index = 0, files_done = 0, files_total = 0, code = 0;
};

const int MSG_RESULT = 1000;

const ImVec4 kAccent(0.96f, 0.55f, 0.13f, 1.0f);
const ImVec4 kGreen(0.36f, 0.80f, 0.45f, 1.0f);
const ImVec4 kRed(0.93f, 0.36f, 0.33f, 1.0f);
const ImVec4 kDim(0.60f, 0.63f, 0.70f, 1.0f);

SDL_Window *gWindow = nullptr;
SDL_GLContext gGl = nullptr;
ImFont *gFont = nullptr;
ImFont *gFontBig = nullptr;

Page gPage = PAGE_PICK;
std::string gRoot;
char gIso[4096] = "";
char gEuIso[4096] = "";
char gDest[4096] = "";
bool gEuEnabled = false;
bool gForce = false;

Bt2Preflight gPre;
int gPreCode = 0;
bool gPreReady = false;
std::string gPreKey;
Uint64 gPreDue = 0;

Bt2Check gInstalled;
bool gAlreadyInstalled = false;
std::string gNotice;
std::string gError;
std::string gSummary;
std::string gPlayError;
int gErrorCode = 0;

std::vector<StepRow> gRows;
std::vector<std::string> gNotes;
uint64_t gDoneBytes = 0, gTotalBytes = 0, gFileDone = 0, gFileSize = 0;
int gFilesDone = 0, gFilesTotal = 0;
std::string gCurrentPath;
Uint64 gRunStart = 0, gRunEnd = 0;
double gSpeed = 0.0;
Uint64 gSpeedTicks = 0;
uint64_t gSpeedBytes = 0;

std::atomic<int> gCancel{0};
bool gCancelling = false;
std::thread gWorker;
bool gWorkerDone = false;

std::mutex gMsgLock;
std::vector<Msg> gMsgs;

struct DialogState {
    std::mutex lock;
    std::string path;
    int target = DLG_NONE;
    bool ready = false;
};
DialogState gDialog;

bool gQuit = false;
Uint64 gStartTicks = 0;
int gFrameNo = 0;
Page gShotPage = (Page)-1;
int gShotNo = 0;

bool file_exists(const std::string &p)
{
    SDL_PathInfo info;
    return !p.empty() && SDL_GetPathInfo(p.c_str(), &info) && info.type == SDL_PATHTYPE_FILE;
}

std::string human(uint64_t n)
{
    char buf[64];
    bt2_human_bytes(n, buf, sizeof(buf));
    return std::string(buf);
}

void style()
{
    ImGuiStyle &st = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    st.WindowRounding = 0.0f;
    st.FrameRounding = 6.0f;
    st.GrabRounding = 6.0f;
    st.WindowPadding = ImVec2(30.0f, 24.0f);
    st.FramePadding = ImVec2(12.0f, 8.0f);
    st.ItemSpacing = ImVec2(10.0f, 10.0f);
    st.WindowBorderSize = 0.0f;
    ImVec4 *c = st.Colors;
    c[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.11f, 1.0f);
    c[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.17f, 0.23f, 1.0f);
    c[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.24f, 0.32f, 1.0f);
    c[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.29f, 0.38f, 1.0f);
    c[ImGuiCol_Button] = ImVec4(0.17f, 0.20f, 0.27f, 1.0f);
    c[ImGuiCol_ButtonHovered] = ImVec4(0.96f, 0.55f, 0.13f, 0.55f);
    c[ImGuiCol_ButtonActive] = kAccent;
    c[ImGuiCol_PlotHistogram] = kAccent;
    c[ImGuiCol_TextSelectedBg] = ImVec4(0.96f, 0.55f, 0.13f, 0.35f);
    c[ImGuiCol_CheckMark] = kAccent;
}

void heading(const char *title, const char *sub)
{
    if (gFontBig != nullptr) {
        ImGui::PushFont(gFontBig);
    }
    ImGui::TextColored(kAccent, "%s", title);
    if (gFontBig != nullptr) {
        ImGui::PopFont();
    }
    ImGui::TextColored(kDim, "%s", sub);
    ImGui::Dummy(ImVec2(0.0f, 8.0f));
}

bool big_button(const char *label, bool primary, bool enabled = true, float width = 160.0f)
{
    bool clicked = false;
    if (!enabled) {
        ImGui::BeginDisabled();
    }
    if (primary) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.96f, 0.55f, 0.13f, 0.85f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kAccent);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.85f, 0.44f, 0.08f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.05f, 0.05f, 0.07f, 1.0f));
    }
    clicked = ImGui::Button(label, ImVec2(width, 42.0f));
    if (primary) {
        ImGui::PopStyleColor(4);
    }
    if (!enabled) {
        ImGui::EndDisabled();
    }
    return clicked;
}

void bottom_buttons_start(int count)
{
    float width = count * 160.0f + (count - 1) * ImGui::GetStyle().ItemSpacing.x;
    float x = ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x - width;
    float y = ImGui::GetWindowHeight() - ImGui::GetStyle().WindowPadding.y - 42.0f;
    ImGui::SetCursorPos(ImVec2(x, y));
}

/* ------------------------------------------------------------------------------------------ eventos del motor */

void event_cb(const Bt2Event *ev, void *user)
{
    (void)user;
    Msg m;
    m.kind = (int)ev->kind;
    m.step = ev->step;
    m.steps = ev->steps;
    m.step_name = ev->step_name != nullptr ? ev->step_name : "";
    m.path = ev->path != nullptr ? ev->path : "";
    m.message = ev->message != nullptr ? ev->message : "";
    m.file_size = ev->file_size;
    m.file_done = ev->file_done;
    m.done_bytes = ev->done_bytes;
    m.total_bytes = ev->total_bytes;
    m.index = ev->index;
    m.files_done = ev->files_done;
    m.files_total = ev->files_total;
    m.code = ev->code;
    std::lock_guard<std::mutex> lock(gMsgLock);
    gMsgs.push_back(std::move(m));
}

static int cancel_cb(void *user)
{
    return ((std::atomic<int> *)user)->load() != 0 ? 1 : 0;
}

void reset_run_state()
{
    gRows.clear();
    gNotes.clear();
    gDoneBytes = gTotalBytes = gFileDone = gFileSize = 0;
    gFilesDone = gFilesTotal = 0;
    gCurrentPath.clear();
    gSpeed = 0.0;
    gSpeedTicks = SDL_GetTicks();
    gSpeedBytes = 0;
    gCancel.store(0);
    gCancelling = false;
    gError.clear();
    gErrorCode = 0;
    gPlayError.clear();
    gSummary.clear();
    gWorkerDone = false;
    std::lock_guard<std::mutex> lock(gMsgLock);
    gMsgs.clear();
}

void start_install()
{
    if (gIso[0] == '\0' || gDest[0] == '\0') {
        return;
    }
    if (gWorker.joinable()) {
        gWorker.join();
    }
    reset_run_state();
    gPage = PAGE_RUN;
    gRunStart = SDL_GetTicks();
    gRunEnd = 0;
    std::string iso(gIso);
    std::string dest(gDest);
    std::string eu = (gEuEnabled && gEuIso[0] != '\0') ? std::string(gEuIso) : std::string();
    bool force = gForce;
    gWorker = std::thread([iso, dest, eu, force]() {
        int rc = bt2_install(iso.c_str(), dest.c_str(), eu.empty() ? nullptr : eu.c_str(), force, cancel_cb, &gCancel,
                             event_cb, nullptr);
        Msg m;
        m.kind = MSG_RESULT;
        m.code = rc;
        std::lock_guard<std::mutex> lock(gMsgLock);
        gMsgs.push_back(std::move(m));
    });
}

void mark_running_ok()
{
    for (auto &r : gRows) {
        if (r.state == ROW_RUNNING) {
            r.state = ROW_OK;
            r.end = SDL_GetTicks();
        }
    }
}

StepRow *current_row()
{
    for (auto &r : gRows) {
        if (r.state == ROW_RUNNING) {
            return &r;
        }
    }
    return nullptr;
}

void pump_events()
{
    std::vector<Msg> msgs;
    {
        std::lock_guard<std::mutex> lock(gMsgLock);
        msgs.swap(gMsgs);
    }
    for (const Msg &m : msgs) {
        if (m.kind == MSG_RESULT) {
            gWorkerDone = true;
            if (m.code == 2) {
                gPage = PAGE_PICK;
                gNotice = "Instalación cancelada. Los archivos ya copiados se conservan y se pueden retomar.";
            } else if (m.code == 0) {
                if (gPage != PAGE_DONE) {
                    gPage = PAGE_DONE;
                }
            } else if (gPage != PAGE_FAILED) {
                gPage = PAGE_FAILED;
                if (gError.empty()) {
                    gError = "La instalación terminó con un error.";
                }
            }
            continue;
        }
        switch ((Bt2EventKind)m.kind) {
        case BT2_EV_STEP:
            if (gRows.size() != (size_t)m.steps) {
                gRows.assign((size_t)m.steps, StepRow());
            }
            mark_running_ok();
            if (m.step >= 1 && m.step <= (int)gRows.size()) {
                StepRow &r = gRows[(size_t)m.step - 1];
                r.title = m.step_name;
                r.state = ROW_RUNNING;
                r.start = SDL_GetTicks();
                r.detail = "";
            }
            break;
        case BT2_EV_FILE:
            gFilesDone = m.files_done;
            gFilesTotal = m.files_total;
            gCurrentPath = m.path;
            gFileSize = m.file_size;
            gFileDone = 0;
            if (StepRow *r = current_row()) {
                r->detail = m.path;
            }
            break;
        case BT2_EV_PROGRESS:
            gDoneBytes = m.done_bytes;
            gTotalBytes = m.total_bytes;
            gFilesDone = m.files_done;
            gFilesTotal = m.files_total;
            gFileDone = m.file_done;
            gFileSize = m.file_size;
            break;
        case BT2_EV_NOTE:
            if (!m.message.empty() && m.message != "ya estaba") {
                gNotes.push_back(m.message);
                if (gNotes.size() > 8) {
                    gNotes.erase(gNotes.begin());
                }
            }
            if (StepRow *r = current_row()) {
                if (m.message == "ya estaba") {
                    r->detail = m.path + " — ya estaba";
                } else {
                    r->detail = m.message;
                }
            }
            break;
        case BT2_EV_ERROR: {
            bool marked = false;
            for (auto &r : gRows) {
                if (r.state == ROW_RUNNING) {
                    r.state = ROW_FAILED;
                    r.end = SDL_GetTicks();
                    marked = true;
                }
            }
            if (!marked && !gRows.empty()) {
                gRows.back().state = ROW_FAILED;
            }
            for (auto &r : gRows) {
                if (r.state == ROW_PENDING && r.title.empty()) {
                    r.title = "No se ejecutó";
                }
            }
            gError = m.message;
            gErrorCode = m.code;
            gPage = PAGE_FAILED;
            break;
        }
        case BT2_EV_DONE:
            mark_running_ok();
            for (auto &r : gRows) {
                if (r.state == ROW_PENDING) {
                    r.state = ROW_SKIPPED;
                }
            }
            gSummary = m.message;
            gDoneBytes = m.done_bytes;
            gTotalBytes = m.total_bytes;
            gRunEnd = SDL_GetTicks();
            gPage = PAGE_DONE;
            break;
        }
    }
    if (gWorkerDone && gWorker.joinable()) {
        gWorker.join();
    }
}

/* ------------------------------------------------------------------------------------------------ preflight */

void pump_preflight()
{
    if (gPage != PAGE_PICK) {
        return;
    }
    std::string eu = (gEuEnabled && gEuIso[0] != '\0') ? std::string(gEuIso) : std::string();
    std::string key = std::string(gIso) + "|" + std::string(gDest) + "|" + eu + "|" + (gForce ? "1" : "0");
    if (key != gPreKey) {
        bool first = gPreKey.empty();
        gPreKey = key;
        gPreReady = false;
        gPreDue = SDL_GetTicks() + 350;
        if (!first) {
            gNotice.clear();
        }
        return;
    }
    if (gPreReady || SDL_GetTicks() < gPreDue) {
        return;
    }
    gPreReady = true;
    if (gIso[0] == '\0' || gDest[0] == '\0') {
        gPreCode = 0;
        return;
    }
    if (!file_exists(gIso)) {
        memset(&gPre, 0, sizeof(gPre));
        snprintf(gPre.error, sizeof(gPre.error), "Ese archivo no existe: %s", gIso);
        gPreCode = 1;
        return;
    }
    gPreCode = bt2_preflight(gIso, gDest, eu.empty() ? nullptr : eu.c_str(), gForce ? 1 : 0, &gPre);
}

/* ------------------------------------------------------------------------------------------------- diálogos */

void SDLCALL dialog_cb(void *userdata, const char *const *filelist, int filter)
{
    (void)filter;
    std::lock_guard<std::mutex> lock(gDialog.lock);
    gDialog.target = (int)(intptr_t)userdata;
    gDialog.path = (filelist != nullptr && filelist[0] != nullptr) ? filelist[0] : "";
    gDialog.ready = true;
}

void pump_dialog()
{
    std::string path;
    int target = DLG_NONE;
    {
        std::lock_guard<std::mutex> lock(gDialog.lock);
        if (!gDialog.ready) {
            return;
        }
        path = gDialog.path;
        target = gDialog.target;
        gDialog.ready = false;
    }
    if (path.empty()) {
        return;
    }
    if (target == DLG_ISO) {
        snprintf(gIso, sizeof(gIso), "%s", path.c_str());
    } else if (target == DLG_EU) {
        snprintf(gEuIso, sizeof(gEuIso), "%s", path.c_str());
        gEuEnabled = true;
    } else if (target == DLG_DEST) {
        snprintf(gDest, sizeof(gDest), "%s", path.c_str());
    }
}

/* --------------------------------------------------------------------------------------------------- páginas */

void step_list()
{
    float t = (float)SDL_GetTicks() / 1000.0f;
    for (size_t i = 0; i < gRows.size(); i++) {
        StepRow &r = gRows[i];
        ImDrawList *dl = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImVec2 c(p.x + 11.0f, p.y + 11.0f);
        bool done = r.state == ROW_OK || r.state == ROW_SKIPPED;
        if (done) {
            ImU32 col = ImGui::GetColorU32(kGreen);
            dl->AddCircle(c, 10.0f, col, 32, 1.6f);
            dl->AddLine(ImVec2(c.x - 5.0f, c.y), ImVec2(c.x - 1.5f, c.y + 4.0f), col, 2.0f);
            dl->AddLine(ImVec2(c.x - 1.5f, c.y + 4.0f), ImVec2(c.x + 5.5f, c.y - 4.0f), col, 2.0f);
        } else if (r.state == ROW_FAILED) {
            ImU32 col = ImGui::GetColorU32(kRed);
            dl->AddCircle(c, 10.0f, col, 32, 1.6f);
            dl->AddLine(ImVec2(c.x - 4.0f, c.y - 4.0f), ImVec2(c.x + 4.0f, c.y + 4.0f), col, 2.0f);
            dl->AddLine(ImVec2(c.x - 4.0f, c.y + 4.0f), ImVec2(c.x + 4.0f, c.y - 4.0f), col, 2.0f);
        } else if (r.state == ROW_RUNNING) {
            float a = t * 5.0f;
            dl->AddCircle(c, 10.0f, ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.12f)), 32, 2.0f);
            dl->PathArcTo(c, 10.0f, a, a + 1.9f, 24);
            dl->PathStroke(ImGui::GetColorU32(kAccent), 0, 2.4f);
        } else {
            dl->AddCircle(c, 10.0f, ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.18f)), 32, 1.4f);
        }
        ImGui::Dummy(ImVec2(22.0f, 22.0f));
        ImGui::SameLine(0.0f, 14.0f);
        ImGui::BeginGroup();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 1.0f));
        ImGui::TextColored(r.state == ROW_PENDING ? kDim : ImGui::GetStyleColorVec4(ImGuiCol_Text), "%s",
                           r.title.empty() ? "Preparando..." : r.title.c_str());
        ImGui::TextColored(kDim, "%s", r.detail.c_str());
        ImGui::PopStyleVar();
        ImGui::EndGroup();
        char clock[32] = "";
        if (r.state == ROW_RUNNING) {
            snprintf(clock, sizeof(clock), "%d s", (int)((SDL_GetTicks() - r.start) / 1000));
        } else if ((r.state == ROW_OK || r.state == ROW_FAILED) && r.end >= r.start && r.end - r.start >= 2000) {
            snprintf(clock, sizeof(clock), "%d s", (int)((r.end - r.start) / 1000));
        }
        if (clock[0] != '\0') {
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x - ImGui::CalcTextSize(clock).x);
            ImGui::TextColored(kDim, "%s", clock);
        }
    }
}

void row_input(const char *label, const char *hint, char *buf, size_t bufsz, DialogTarget target, bool folder)
{
    static const SDL_DialogFileFilter filters[] = {{"Imagen de disco PS2", "iso;bin;img"}, {"Todos los archivos", "*"}};
    ImGui::TextUnformatted(label);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 150.0f);
    ImGui::InputTextWithHint("##input", hint, buf, bufsz);
    ImGui::SameLine();
    if (ImGui::Button(folder ? "Elegir carpeta..." : "Examinar...", ImVec2(140.0f, 0.0f))) {
        {
            std::lock_guard<std::mutex> lock(gDialog.lock);
            gDialog.target = target;
            gDialog.path.clear();
            gDialog.ready = false;
        }
        if (folder) {
            SDL_ShowOpenFolderDialog(dialog_cb, (void *)(intptr_t)target, gWindow, nullptr, false);
        } else {
            SDL_ShowOpenFileDialog(dialog_cb, (void *)(intptr_t)target, gWindow, filters, 2, nullptr, false);
        }
    }
}

void page_pick()
{
    heading("BT2 Setup", "Instalá los datos de tu propio disco de PlayStation 2 y jugá. No se descarga nada.");

    ImGui::TextWrapped("Elegí la imagen .iso de la edición USA de Dragon Ball Z: Budokai Tenkaichi 2 "
                       "(SLUS-21441). Los archivos se copian a la carpeta que elijas; la ISO no se modifica.");
    ImGui::Dummy(ImVec2(0.0f, 6.0f));

    row_input("Imagen de disco (ISO)", "arrastrá el archivo a esta ventana, o usá Examinar...", gIso, sizeof(gIso),
              DLG_ISO, false);

    if (file_exists(gIso)) {
        if (!gPreReady) {
            ImGui::TextColored(kDim, "Revisando la imagen...");
        } else if (gPreCode == 0) {
            ImGui::TextColored(kGreen, "✓ %s", gPre.message);
            if (gPre.already_files > 0) {
                char line[256];
                snprintf(line, sizeof(line), "Ya hay %d archivos instalados (%s); se saltean.", gPre.already_files,
                         human(gPre.already_bytes).c_str());
                ImGui::TextColored(kDim, "%s", line);
            }
            if (gPre.eu_requested && gPre.eu_present) {
                ImGui::TextColored(kDim, "Multiidioma: se agrega %s (%s).", BT2_EU_AFS, human(gPre.eu_bytes).c_str());
            }
        } else if (gPreCode == 3) {
            ImGui::TextColored(kRed, "La imagen no es la edición USA sin modificar.");
            ImGui::TextWrapped("%s", gPre.error);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Text, kRed);
            ImGui::TextWrapped("%s", gPre.error);
            ImGui::PopStyleColor();
        }
    } else if (gIso[0] != '\0' && !file_exists(gIso)) {
        ImGui::TextColored(kRed, "Ese archivo no existe.");
    } else if (gIso[0] == '\0') {
        ImGui::TextColored(kDim, "Necesita unos 4 GB libres y tarda un minuto o dos.");
    }

    ImGui::Dummy(ImVec2(0.0f, 6.0f));
    ImGui::Checkbox("Agregar los datos multiidioma de una ISO PAL (opcional)", &gEuEnabled);
    if (gEuEnabled) {
        row_input("ISO PAL (para textos y menús en español, francés, alemán o italiano)", "ISO de la edición europea",
                  gEuIso, sizeof(gEuIso), DLG_EU, false);
    }

    row_input("Carpeta de destino", "por defecto gamedata/ al lado del port", gDest, sizeof(gDest), DLG_DEST, true);
    ImGui::Checkbox("Volver a copiar todo (ignorar archivos ya presentes)", &gForce);

    if (gIso[0] == '\0') {
        ImGui::TextColored(kDim, "El puerto lee la carpeta de datos; podés moverla y apuntar BT2_DATA a ella.");
    }
    ImGui::Dummy(ImVec2(0.0f, 4.0f));
    if (!gNotice.empty()) {
        ImGui::TextWrapped("%s", gNotice.c_str());
    }

    bool can = gPreReady && gPreCode == 0 && gIso[0] != '\0' && gDest[0] != '\0';
    bottom_buttons_start(2);
    if (big_button("Salir", false)) {
        gQuit = true;
    }
    ImGui::SameLine();
    if (big_button("Instalar", true, can)) {
        gNotice.clear();
        start_install();
    }
}

void page_run()
{
    heading("Instalando", "Podés cancelar cuando quieras: los archivos ya copiados se conservan y se retoma.");
    step_list();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    float frac = gTotalBytes > 0 ? (float)((double)gDoneBytes / (double)gTotalBytes) : 0.0f;
    char overlay[128];
    snprintf(overlay, sizeof(overlay), "%d%%   %s / %s", (int)(frac * 100.0f), human(gDoneBytes).c_str(),
             human(gTotalBytes).c_str());
    ImGui::ProgressBar(frac, ImVec2(-FLT_MIN, 12.0f), overlay);
    if (!gCurrentPath.empty()) {
        ImGui::TextWrapped("%s", gCurrentPath.c_str());
        if (gFileSize > 0) {
            char line[256];
            snprintf(line, sizeof(line), "%s / %s", human(gFileDone).c_str(), human(gFileSize).c_str());
            ImGui::TextColored(kDim, "%s", line);
        }
    }
    if (gFilesTotal > 0) {
        ImGui::TextColored(kDim, "Archivo %d de %d", gFilesDone, gFilesTotal);
    }
    if (gSpeed > 0.01) {
        double left = (double)gTotalBytes - (double)gDoneBytes;
        int eta = left > 0 && gSpeed > 0 ? (int)(left / gSpeed) : 0;
        char line[128];
        snprintf(line, sizeof(line), "%.1f MB/s · faltan %d min %d s", gSpeed, eta / 60, eta % 60);
        ImGui::TextColored(kDim, "%s", line);
    }
    if (gCancelling) {
        ImGui::TextColored(kAccent, "Cancelando...");
    }
    bottom_buttons_start(1);
    if (big_button("Cancelar", false, !gCancelling)) {
        gCancel.store(1);
        gCancelling = true;
    }
}

void page_done()
{
    heading("Listo para jugar", "Los datos del juego quedaron instalados. Podés jugar ahora.");
    if (gAlreadyInstalled) {
        ImGui::TextWrapped("Los datos ya estaban instalados: %s.", gInstalled.summary);
        if (gInstalled.elf_hash_ok == 1) {
            ImGui::TextColored(kDim, "El programa del juego coincide con la edición USA (SHA-1 verificado).");
        }
    } else {
        ImGui::TextWrapped("%s", gSummary.c_str());
    }
    step_list();
    ImGui::Dummy(ImVec2(0.0f, 4.0f));
    ImGui::TextColored(kDim, "En el juego, F1 abre la configuración: resolución, widescreen, controles y sonido.");
    char game[4096];
    bool have_game = bt2_find_game(gRoot.c_str(), game, sizeof(game)) != 0;
    if (have_game) {
        ImGui::TextColored(kDim, "Juego: %s", game);
    } else {
        ImGui::TextColored(kRed, "No encontré el binario del juego (port/build/full/bt2full). Compilá el port o definí BT2_GAME.");
    }
    if (!gPlayError.empty()) {
        ImGui::TextColored(kRed, "%s", gPlayError.c_str());
    }
    ImGui::TextColored(kDim, "Podés cerrar esta ventana y ejecutar el juego desde una terminal.");
    bottom_buttons_start(4);
    if (big_button("Salir", false, true, 130.0f)) {
        gQuit = true;
    }
    ImGui::SameLine();
    if (big_button("Reinstalar", false, true, 130.0f)) {
        gAlreadyInstalled = false;
        gForce = true;
        gPage = PAGE_PICK;
    }
    ImGui::SameLine();
    if (big_button("Abrir carpeta", false, true, 150.0f)) {
        std::string url = "file://" + bt2_absolute(gDest);
        SDL_OpenURL(url.c_str());
    }
    ImGui::SameLine();
    if (big_button("Jugar", true, have_game, 140.0f)) {
        char err[1024];
        if (bt2_launch_game(gRoot.c_str(), gDest, err, sizeof(err)) == 0) {
            gQuit = true;
        } else {
            gPlayError = err;
        }
    }
}

void page_failed()
{
    heading("No se pudo instalar", "La instalación no terminó; podés reintentar o elegir otra imagen.");
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.93f, 0.36f, 0.33f, 0.10f));
    ImGui::BeginChild("why", ImVec2(0.0f, 150.0f), ImGuiChildFlags_AlwaysUseWindowPadding);
    ImGui::TextWrapped("%s", gError.c_str());
    ImGui::EndChild();
    ImGui::PopStyleColor();
    if (gErrorCode == 3) {
        ImGui::TextColored(kDim, "El instalador sólo acepta la edición USA original (SLUS-21441); no modifica la imagen.");
    }
    ImGui::Dummy(ImVec2(0.0f, 4.0f));
    step_list();
    bottom_buttons_start(3);
    if (big_button("Salir", false)) {
        gQuit = true;
    }
    ImGui::SameLine();
    if (big_button("Volver", false)) {
        gPage = PAGE_PICK;
    }
    ImGui::SameLine();
    if (big_button("Reintentar", true, gIso[0] != '\0' && gDest[0] != '\0')) {
        start_install();
    }
}

void build_ui()
{
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("setup", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);
    switch (gPage) {
    case PAGE_PICK: page_pick(); break;
    case PAGE_RUN: page_run(); break;
    case PAGE_DONE: page_done(); break;
    case PAGE_FAILED: page_failed(); break;
    }
    ImGui::End();
}

/* ---------------------------------------------------------------------------------------------------- ventana */

void save_shot(const char *prefix, int number)
{
    int w = 0, h = 0;
    SDL_GetWindowSizeInPixels(gWindow, &w, &h);
    if (w <= 0 || h <= 0) {
        return;
    }
    std::vector<unsigned char> px((size_t)w * (size_t)h * 4);
    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px.data());
    char name[1024];
    snprintf(name, sizeof(name), "%s_%d.ppm", prefix, number);
    FILE *fp = fopen(name, "wb");
    if (fp == nullptr) {
        return;
    }
    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    for (int y = h - 1; y >= 0; y--) {
        for (int x = 0; x < w; x++) {
            const unsigned char *p = &px[((size_t)y * (size_t)w + (size_t)x) * 4];
            unsigned char rgb[3] = {p[0], p[1], p[2]};
            fwrite(rgb, 1, 3, fp);
        }
    }
    fclose(fp);
}

bool setup_window()
{
    const char *glsl = "#version 330";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    gWindow = SDL_CreateWindow("BT2 Setup — Budokai Tenkaichi 2", 880, 700,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (gWindow != nullptr) {
        gGl = SDL_GL_CreateContext(gWindow);
    }
    if (gGl == nullptr) {
        if (gWindow != nullptr) {
            SDL_DestroyWindow(gWindow);
            gWindow = nullptr;
        }
        SDL_GL_ResetAttributes();
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        glsl = "#version 130";
        gWindow = SDL_CreateWindow("BT2 Setup — Budokai Tenkaichi 2", 880, 700,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
        if (gWindow != nullptr) {
            gGl = SDL_GL_CreateContext(gWindow);
        }
    }
    if (gWindow == nullptr || gGl == nullptr) {
        fprintf(stderr, "bt2-setup: no se pudo abrir la ventana: %s\n"
                        "El modo consola equivalente es: bt2-setup --install <iso> [--dest carpeta]\n",
                SDL_GetError());
        return false;
    }
    SDL_GL_MakeCurrent(gWindow, gGl);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = nullptr;
    style();
    static const char *fonts[] = {
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/noto/NotoSans-Regular.ttf",
        "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
        "/usr/share/fonts/liberation/LiberationSans-Regular.ttf",
    };
    for (const char *path : fonts) {
        if (file_exists(path)) {
            gFont = io.Fonts->AddFontFromFileTTF(path, 18.0f);
            gFontBig = io.Fonts->AddFontFromFileTTF(path, 30.0f);
            if (gFont != nullptr) {
                io.FontDefault = gFont;
            }
            break;
        }
    }
    ImGui_ImplSDL3_InitForOpenGL(gWindow, gGl);
    ImGui_ImplOpenGL3_Init(glsl);
    return true;
}

} // namespace

int bt2_gui_run(const std::string &root, const std::string &initial_iso, const std::string &initial_dest)
{
    gRoot = root;
    std::string dest_default = root + "/gamedata";
    snprintf(gDest, sizeof(gDest), "%s", initial_dest.empty() ? dest_default.c_str() : initial_dest.c_str());
    if (const char *env = getenv("BT2_SETUP_DEST")) {
        snprintf(gDest, sizeof(gDest), "%s", env);
    }
    if (!initial_iso.empty()) {
        snprintf(gIso, sizeof(gIso), "%s", initial_iso.c_str());
    }
    if (const char *env = getenv("BT2_SETUP_ISO")) {
        snprintf(gIso, sizeof(gIso), "%s", env);
    }
    if (const char *env = getenv("BT2_SETUP_EU_ISO")) {
        snprintf(gEuIso, sizeof(gEuIso), "%s", env);
        gEuEnabled = true;
    }
    bool autostart = false;
    if (const char *env = getenv("BT2_SETUP_AUTOSTART")) {
        autostart = env[0] == '1' || env[0] == 'y' || env[0] == 'Y';
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "bt2-setup: %s\nEl modo consola equivalente es: bt2-setup --install <iso> [--dest carpeta]\n",
                SDL_GetError());
        return 1;
    }
    if (!setup_window()) {
        SDL_Quit();
        return 1;
    }
    gStartTicks = SDL_GetTicks();

    std::string check_dest(gDest);
    int check_rc = bt2_check_dest(check_dest.c_str(), 1, &gInstalled);
    if (check_rc == 0 && gIso[0] == '\0') {
        gAlreadyInstalled = true;
        gPage = PAGE_DONE;
        gSummary = gInstalled.summary;
    } else if (gInstalled.marker || gInstalled.files > 0) {
        if (check_rc != 0) {
            gNotice = "Hay datos incompletos o distintos en " + check_dest + ": " + gInstalled.summary + ".";
        }
    }

    if (autostart && gIso[0] != '\0') {
        start_install();
    }

    const char *shot = getenv("BT2_SETUP_SHOT");
    const char *autoclose = getenv("BT2_SETUP_AUTOCLOSE_MS");
    const char *autocancel = getenv("BT2_SETUP_AUTOCANCEL_MS");
    const char *autoplay = getenv("BT2_SETUP_AUTOPLAY");
    bool autoplay_done = false;

    while (!gQuit) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            ImGui_ImplSDL3_ProcessEvent(&ev);
            if (ev.type == SDL_EVENT_QUIT || ev.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                if (gWorker.joinable()) {
                    gCancel.store(1);
                }
                gQuit = true;
            } else if (ev.type == SDL_EVENT_DROP_FILE && ev.drop.data != nullptr && gPage == PAGE_PICK) {
                std::string dropped(ev.drop.data);
                std::string lower = dropped;
                for (char &ch : lower) {
                    ch = (char)tolower((unsigned char)ch);
                }
                bool euish = lower.find("europe") != std::string::npos || lower.find("pal") != std::string::npos;
                if (gEuEnabled && gIso[0] != '\0' && euish) {
                    snprintf(gEuIso, sizeof(gEuIso), "%s", dropped.c_str());
                } else {
                    snprintf(gIso, sizeof(gIso), "%s", dropped.c_str());
                }
            }
        }
        pump_dialog();
        pump_preflight();
        pump_events();

        if (gPage == PAGE_RUN) {
            Uint64 now = SDL_GetTicks();
            if (now - gSpeedTicks >= 500) {
                double dt = (double)(now - gSpeedTicks) / 1000.0;
                gSpeed = dt > 0 ? (double)(gDoneBytes - gSpeedBytes) / dt / (1024.0 * 1024.0) : 0.0;
                gSpeedTicks = now;
                gSpeedBytes = gDoneBytes;
            }
        }
        if (autoplay != nullptr && autoplay[0] == '1' && gPage == PAGE_DONE && !autoplay_done) {
            autoplay_done = true;
            char err[1024];
            if (bt2_launch_game(gRoot.c_str(), gDest, err, sizeof(err)) == 0) {
                gQuit = true;
            } else {
                gPlayError = err;
            }
        }
        if (autocancel != nullptr && atoi(autocancel) > 0 && gPage == PAGE_RUN && !gCancelling &&
            SDL_GetTicks() - gStartTicks >= (Uint64)atoi(autocancel)) {
            gCancel.store(1);
            gCancelling = true;
        }
        if (autoclose != nullptr && atoi(autoclose) > 0 && SDL_GetTicks() - gStartTicks >= (Uint64)atoi(autoclose)) {
            if (gWorker.joinable()) {
                gCancel.store(1);
            }
            gQuit = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        build_ui();
        ImGui::Render();
        ImDrawData *dd = ImGui::GetDrawData();
        int pw = 0, ph = 0;
        SDL_GetWindowSizeInPixels(gWindow, &pw, &ph);
        glViewport(0, 0, pw, ph);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(dd);
        if (shot != nullptr && pw > 0 && ph > 0 && (gFrameNo == 30 || gPage != gShotPage)) {
            save_shot(shot, gShotNo++);
            gShotPage = gPage;
        }
        SDL_GL_SwapWindow(gWindow);
        gFrameNo++;
    }

    if (gWorker.joinable()) {
        gCancel.store(1);
        gWorker.join();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(gGl);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}

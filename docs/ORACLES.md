# Oráculos: PCSX2 instrumentado y Ghidra (MCP)

Estado tras ponerlos en marcha (2026-10-09). Los dos corren **fuera del árbol del proyecto** (binarios en
`~/pcsx2-src` y `/mnt/datos/Herramientas`), y cada uno con su propio directorio de datos en `/tmp/opencode`,
así que no tocan `~/.config/PCSX2` ni el proyecto original.

## 1. PCSX2 — dos canales en el mismo proceso

Binario: `~/pcsx2-src/build/bin/pcsx2-qt` (fuente en `~/pcsx2-src`, con los ficheros sin commitear
`pcsx2/DebugTools/DebugServer.{h,cpp}` + `pcsx2/VMManager.cpp`). Es el mismo emulador que el port imita.

| Canal | Dónde | Para qué |
|---|---|---|
| **DebugServer** | TCP `127.0.0.1:21512`, JSON por líneas | todo: registros de 128 bits, desensamblado nativo, expresiones, breakpoints condicionales, watchpoints, step/step_over, hilos, módulos, **cobertura de código EE** |
| **Pine IPC** | socket Unix `$XDG_RUNTIME_DIR/pcsx2.sock` | memoria rápida, título/ID/UUID/versión del juego, save states |

Arranque usado (aislado, sin tocar la config del usuario):

```sh
# 1) datapath propio: <datapath>/PCSX2/inis/PCSX2.ini (copia de la del usuario, con Bios absoluto) + bios/
mkdir -p /tmp/opencode/pcsx2-bt2/PCSX2/{inis,bios}
cp ~/.config/PCSX2/inis/PCSX2.ini /tmp/opencode/pcsx2-bt2/PCSX2/inis/
sed -i 's|^Bios = .*|Bios = /mnt/datos/Rexx/Descargas/Roms/PS2/ps2_bios|; s|^Renderer = .*|Renderer = 6|' \
       /tmp/opencode/pcsx2-bt2/PCSX2/inis/PCSX2.ini   # Renderer 6 = Software
ln -sf .../ps2_bios/scph39001.bin /tmp/opencode/pcsx2-bt2/PCSX2/bios/
# 2) arrancar: PCSX2_EE_COVERAGE=1 activa el mapa de cobertura (0x100000-0x2000000, bloques de 4 bytes)
PCSX2_EE_COVERAGE=1 xvfb-run -a -s "-screen 0 640x480x24" \
  ~/pcsx2-src/build/bin/pcsx2-qt -datapath /tmp/opencode/pcsx2-bt2 -nogui \
  -logfile /tmp/opencode/pcsx2-bt2/console.log "<iso de BT2>"
```

Opciones útiles de la CLI (de `pcsx2-qt --help`): `-datapath`, `-nogui` (implica batch), `-turbo`, `-fullscreen`,
`-elf <file>`, `-logfile`, `-bios` (arranca el menú del BIOS). El DebugServer se levanta **siempre** que la
máquina virtual arranca (`VMManager::Initialize` → `DebugServer::Start(21512)`), y escribe
`[DebugServer] Listening on 127.0.0.1:21512` por stderr.

### El MCP (`~/PCSX2-MCP/pcsx2-mcp-server`, `pcsx2` en opencode)

32 herramientas, en 3 niveles: 1) DebugServer (todo), 2) Pine (memoria + game info), 3) herramientas propias
del proyecto PS2Recomp (`ps2recomp_lookup_function`, `ps2recomp_list_overrides`; leen `PS2RECOMP_ROOT`, que
apunta al proyecto de RE Outbreak, no a este → poco útiles aquí).

- La conexión **no es automática**: hay que llamar a `pcsx2_connect` (modo `auto`, `debug` o `pine`) la primera
  vez; `pcsx2_status` sólo informa.
- De lo más útil para el port: `pcsx2_pause` (devuelve el PC), `pcsx2_get_backtrace` (pila de llamadas con entradas
  de función — p. ej. `main` 0x100388 → bucle 0x100680 → overlay `func_0x003b7fa8`), `pcsx2_disassemble`
  (desensamblado nativo de PCSX2), `pcsx2_read_memory`, `pcsx2_find_pattern`, `pcsx2_memory_diff`,
  `pcsx2_set_watchpoint` (con condición), `pcsx2_step_over`.
- **Lo que el MCP no expone y el servidor sí tiene**: `coverage_stats`, `clear_coverage`, `get_coverage`
  (devuelve los rangos direcciones EE ejecutadas). Se usan por TCP directo; ver `tools/pcsx2_diff/dbg.py`.

## 2. Ghidra headless con el MCP

- Ghidra 12.1.2 en `/mnt/datos/Herramientas/Ghidra` (plugin EmotionEngine ya instalado en `Extensions/Ghidra/`).
- `ghidra-mcp` 7.0.0 en `/mnt/datos/Herramientas/ghidra-mcp`: el plugin `target/GhidraMCP-7.0.0.jar` contiene
  `com.xebyte.headless.GhidraMCPHeadlessServer`, que sirve el mismo protocolo que el plugin de GUI
  (226 endpoints) **sin necesidad de interfaz**.

```sh
G=/mnt/datos/Herramientas/Ghidra
CP="$(find $G/Ghidra -name '*.jar' | tr '\n' ':')/mnt/datos/Herramientas/ghidra-mcp/target/GhidraMCP-7.0.0.jar"
GHIDRA_INSTALL_DIR=$G java -Xmx6g -Djava.awt.headless=true -cp "$CP" \
  com.xebyte.headless.GhidraMCPHeadlessServer --port 8089 --bind 127.0.0.1 \
  --file disc/SLUS_214.41 --project /tmp/opencode/ghidra/b2/bt2 --program SLUS_214.41
# el análisis de funciones no arranca solo: hay que llamar a la herramienta MCP `reanalyze`
# (la llamada puede expirar en el cliente; Ghidra sigue y termina: 9.541 funciones)
```

- El bridge (`uv run bridge-mcp-ghidra`, configurado en `opencode.json` con `GHIDRA_MCP_URL=...:8089` y
  `GHIDRA_MCP_ALLOW_SCRIPTS=1`) carga por defecto sólo los grupos `listing,function,program`
  (83 de 226 herramientas). Para xrefs hay que cargar el grupo `xref` (`load_tool_group("xref")`);
  hay 15 grupos más (datatype, analysis, comment, documentation, symbol, headless…).
- Comprobado: `get_metadata` (MIPS-R5900, 41 bloques), `reanalyze` → 9.541 funciones,
  `decompile_function` (el `main` en 0x100388 sale limpio y con los nombres del SDK: `sceSifInitRpc`,
  `sceCdInit`, `ChangeThreadPriority`, `GetThreadId`, la llamada al overlay `func_0x003b7fa8`…),
  `get_xrefs_to` y `get_function_callers`.

## 3. Cliente directo del DebugServer

`tools/pcsx2_diff/dbg.py` (copia del patrón del kit `DownhillJam/tools/pcsx2_diff/dbg.py`) habla el protocolo
JSON/TCP sin depender del MCP: cómodo para guiones y para los comandos de cobertura.

```sh
python3 tools/pcsx2_diff/dbg.py status            # pc, ciclos
python3 tools/pcsx2_diff/dbg.py coverage_stats    # bloques EE ejecutados
python3 tools/pcsx2_diff/dbg.py get_coverage > cov.json
python3 tools/pcsx2_diff/dbg.py read_memory --address 0x100000 --length 32 --raw
```

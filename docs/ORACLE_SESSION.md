# Sesión del oráculo — Dragon Adventure hasta combate (2026-10-09)

- PCSX2 (build propio, datapath aislado `/tmp/opencode/pcsx2-bt2`) lanzado en el escritorio del usuario
  (Wayland, GPU real, renderer automático) con `PCSX2_EE_COVERAGE=1`: jugado por el usuario desde el
  arranque hasta el primer combate.
- Monitor (`tools/pcsx2_diff/monitor.py`, cada 2 s): ciclos, bloques cubiertos, PC/estado de cada hilo +
  histograma del PC del hilo principal. Registro: `/tmp/opencode/pcsx2-bt2/monitor.log`.
- Cobertura completa del recorrido: **45.000+ bloques** de código EE ejecutados
  (`/tmp/opencode/pcsx2-bt2/coverage-fight.json`, rangos base 0x100000).
- Estado al llegar al combate: 8 hilos EE; hilo 1 en `0x32EC88` (idle/bucle de espera, alias `0x28C798`
  visto en el backtrace), hilo 4 en `0x2EDE80` (batalla, entrada `0x2EDF48`);
  backtrace de la pausa: `main` 0x100388 → 0x103000 → 0x102E80 → 0x2711E8 (sceGsSyncV 0x3104B0).

## Qué compara esto con el port

- `coverage-fight.json` da el conjunto de direcciones que la consola ejecuta. El mismo mapa se puede
  sacar del port con la traza de funciones (`PS_LOG_ENTRY`, `PS2_FUNCTION_LOG_TRACKER`), que el CMake
  del port fuerza apagada; para activarla sin tocar el proyecto:
  `cmake -S port -B port/build/trace -DCMAKE_CXX_FLAGS="-DAGRESSIVE_LOGS=1 -DPS2_FUNCTION_LOG_TRACKER=1"`
  y cruzar después los nombres de función contra `port/funcmap.csv`.
- El histograma de PCs del hilo principal sirve para ver en qué se gasta el tiempo la consola
  (batalla = `0x2EDE80..`), que es la referencia de rendimiento del port.

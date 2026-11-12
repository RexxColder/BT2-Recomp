# Plan de audio de BT2 (musica, efectos, voces)

Estado 2026-10-21: suena la musica ADX del titulo/menus, las voces ADX y los efectos (SE) del SPU2. Pendiente: audio de las peliculas
(gancho `Movie_AudioPacket` del agente de video), afinar volumen de los SE, verificacion con oidos.

## Como suena BT2: dos caminos, ambos en el lado EE

El juego **no** habla con el IOP por un unico canal. Hay dos mecanismos independientes (IRX en `gamedata/IOPModules`):

1. **Musica, voces y SE "largos": CRI ADX (ADXT).** El juego (`Adx_*`, `Bgm_*`, `Voice_*`, `StreamSe_*`, codigo propio en el rango
   0x101xxx y los `File_*` de `src/sys/file_2EE8B8.c`) tiene 6 reproductores ADXT (`gAdxPlayerTbl`: BGM, MAP, SE0, SE1, VIC0, VIC1) y
   arranca archivos del AFS con `ADXT_StartAfs(adxt, particion, indice)`. La libreria CRI de abajo (adxt/adxrna/adxstm/SJ + RPC
   al modulo `CRI_ADXI.IRX`) **no** se ejecuta: se sustituye la API publica ADXT_* (mismo criterio que `plat_file.c` con ADXF_*).
2. **Efectos de sonido (SE) cortos: driver propio `SOUNDS.IRX`** (RPC servidor `0x02000004`). El EE (`src/sys/snd_298170.c`, y los
   `port/eq/2974xx..2980xx`) sube los bancos al SPU2 (`sceSdRemote 0x80D0`, EE -> `sceSifSetDma` -> memoria del IOP -> SPU2) y manda
   comandos con `sceSifCallRpc`. El IOP los pasa a `modhsyn/modsesq`. Se sustituye todo el IOP/SPU2 por un sampler en el host.

Punto de HLE elegido: **funciones de alto nivel de CRI (ADXT_*) y la frontera RPC/DMA/sdRemote hacia el IOP**. No se emula MIPS del IOP.

## Direcciones de BT2 (mapeadas por delta con BT3: `config/xmatch_bt3.csv`)
| Funcion | BT2 | Fichero |
|---|---|---|
| ADXT_Create / SetReloadSct / SetSvrFreq | 0x2F39D8 / 0x2F5858 / 0x2F5620 | plat_snd_adx.c |
| ADXT_StartAfs / StartFname | 0x2F7040 / 0x2F72A0 | idem |
| ADXT_Stop / GetStat / Pause | 0x2F44A0 / 0x2F4590 / 0x2F6230 | idem |
| ADXT_SetOutVol / GetOutVol / SetOutPan / SetOutputMono | 0x2F52A8 / 0x2F5358 / 0x2F4F88 / 0x2F6D90 | idem |
| Snd_RpcCall tipos: `func_002974F8` (fno, buf), `func_00297420`, `func_00297490` | 0x2974F8.. | `sceSifCallRpc` en plat_sys.c |
| Subida de banco al SPU: `func_00297A78` (apila) / `func_00297D78` (ranura) | | `sceSifSetDma` + `sceSdRemote` |
| Reserva en el SPU2: `func_0028BC68` (arreglado: devolvia void) | 0x28BC68 | port/eq |

El manejador ADXT que ve el juego es un entero chico (0x300 + indice), no un puntero del host (el juego pasa valores por mascaras de
direccion del PS2).

## Formatos
- **ADX** (musica y voces): tipo 3, ADPCM de 4 bits en tramas de 18 bytes, version 4, mono o estereo 16/24/48 kHz, bucle en cabecera
  (0x24 flag, 0x28 inicio, 0x30 fin). Estan crudos dentro de `DATA/ZS2US_1.AFS` / `ZS2US_2.AFS` (indice del AFS = el que pasa
  `ADXT_StartAfs`; el juego traduce id global -> (particion, indice) en `func_00101438` y similares: `id < 0x33B2` -> particion 0).
- **Bancos SE**: archivo `{u32, bodyOfs, hdOfs, seqOfs, endOfs}` + tres secciones. Cuerpo = ADPCM del SPU2 (bloques de 16 bytes),
  `hd` = cabecera Sony HD (Vagi/Setb: offset, tasa, bucle de cada muestra), `seq` = Sesq. Un SE es "tocar la nota de la secuencia N":
  secuencia -> timbre -> muestra (la logica de `lookup()` de plat_snd_se.c; heredada de snd_se.c de BT3, funciona con los datos de BT2).

## Protocolo RPC de SOUNDS.IRX en BT2 (distinto del de BT3)
Servidor 0x02000004. Cada llamada: `sceSifCallRpc(client, fno, mode, buf(0x100), ...)`; respuesta de 0x40 bytes (primera palabra = resultado).
Derivado de los `eq` y confirmado desanmblando el despacho de `SOUNDS.IRX` (`.text` 0x0..0x260, tabla de `fno`):

| fno | funcion | payload |
|---|---|---|
| 0x10 | INIT | {stereo, tam} |
| 0x20 | apilar banco | {spuAddr, hdIop, seqIop}; la ranura es el orden de llegada |
| 0x30 | desapilar el ultimo banco | - |
| 0x80 | banco en ranura | {spuAddr, hdIop, seqIop, ranura} (subida diferida) |
| 0x40 | COLA por cuadro | `u8 n; u8 banco[32]; u8 id[32]; u8 vol[32]; u8 pan[32]; pad; s16 pitch[32]`; bits del byte de banco: 0x1F ranura, 0x80 recordar voz, 0x40 parar (banco,id) |
| 0x50 | fundido de volumen por mascara | {-, -, -, mascara} (solo al arrancar) |
| 0x60 | estereo/mono | {1 = estereo} |
| 0x70 | volumen global | {0..127} |
| 0x100 | RESET | - |
| 0x200 | parar bancos | {-, -, -, mascara} |
Escritura de cola en el EE: `func_002976A0` (anade), `func_00297720` (envia 0xC2 bytes y limpia); `func_00297FE0(banco, id, vol, pan, pitch)` es el
`Snd_PlaySeEx` de BT2 (vol 0..127 escalado por la opcion; pan 0x40 = centro; pitch en cents).

La "memoria del IOP" es un buffer del host de 16 MB (`sIop` en plat_snd_se.c) con reparto de bloques; las direcciones del IOP son
desplazamientos en el. La RAM del SPU2 (2 MB) es `sSpu`.

## Implementacion
- `port/full/plat_snd_adx.c`: ADXT_* sustituidas (ver tabla), decodificador ADX, un `SDL_AudioStream` por reproductor, dispositivo
  SDL y volcado WAV.
- `port/full/plat_snd_se.c`: IOP/SPU2 simulados + sampler de SE (48 voces, ADPCM del SPU2, tono por cents, pan, bucles).
- Ediciones minimas: `plat_sys.c` (sceSifCallRpc -> `Port_SndRpc`, sceSifSetDma -> `Port_SifSetDma`, sceSifAllocIopHeap ->
  `Port_IopAlloc`), `plat_gs.c` (sceSdRemote -> `Port_SdRemote`, fuera los huecos de audio), `plat_file.c` (`Port_ReadAudioFile`),
  `port/eq/28BC68.c` (devuelve la direccion del SPU2), `src/auto/m2c_2979F0.c` (argumento de mono).
- `port/tools/link_full.py` no necesita cambios: enlaza todo `port/full/*.c`; `gs/snd_adx.c`/`snd_se.c` (BT3) siguen excluidos.

## Variables de entorno
`BT2_NOSOUND=1` sin audio; `BT2_SOUND=1` fuerza audio sin ventana; `BT2_AUDIO_DUMP=<f.wav>` escribe tambien la mezcla final (post-mezcla de
SDL, 16 bit, tasa/canales del dispositivo); `BT2_SND_VERBOSE=1` traza de reproductores y PLAY; `BT2_SND_RPCLOG=1` cada RPC y subida al SPU.
Sin dispositivo de audio (o sin ventana) todo queda en modo silencioso sin caerse.

## Verificacion sin oidos
Xvfb :92, `SDL_AUDIODRIVER=dummy` (el dummy consume en tiempo real, asi que el WAV dura lo que tarda la corrida), `BT2_AUDIO_DUMP`.
Analisis con `ffmpeg -af volumedetect/silencedetect/astats`. Ver `docs/agents/b12/audio.txt` para los resultados.

## Pendiente
- Audio de peliculas (SFD): cuando el agente de video exponga `Movie_AudioPacket`, alimentar un stream propio (ADX o PCM del SFD).
- Pausa de SE en combate (no hay orden de pausa en el IOP de BT2; el juego la hace parando bancos), reverb del SPU2, release de envolvente.
- Volumen relativo SE/musica por oido (`BT2_SE_GAIN=<porcentaje>`; por defecto 25 % como en BT3).
- Revisar `ADXT_IsIbufSafety`/`func_002F8B70` si alguna ruta del juego los espera para sincronizar.

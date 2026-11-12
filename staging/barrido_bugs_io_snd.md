# Barrido: bugs de rango en buffers del IOP/SPU y afines (BT2-Port)

Fecha: 2026-11-07. Trabajo de **solo lectura**: no se modificó ni compiló nada. Este archivo es el único que escribí.
Alcance pedido: `port/full/*.c` y `port/eq/*.c` (más los archivos de `src/` que el enlace compila y que son el
productor de los datos que consumen esos buffers, porque sin ellos no se puede juzgar el rango).

Contexto: se acaba de arreglar el crash de `plat_snd_se.c::chunk()/lookup()` que leía fuera del bloque del IOP con topes
fijos `0x4000/0x8000`. Este barrido busca **más casos de la misma forma** (tope fijo o tamaño que viene de la RAM/del
archivo, sin comparar contra el tamaño real del bloque ni contra el destino) y separa lo que **se dispara hoy** de lo
que es **latente** (no se dispara con los datos del juego, pero el chequeo no existe).

## Resumen priorizado

| # | Archivo:línea | Qué | Gravedad | ¿Se dispara hoy? |
|---|---|---|---|---|
| H1 | `port/full/plat_snd_se.c:136-142` | `so + 0x14` da la vuelta: el tope se saltea y `sesq + so` sale del bloque | **crash** (misma clase que el bug recién arreglado) | No con los 290 bancos del disco; sí con un banco tocado (36 entradas `0xFFFFFFFF` reales prueban que el campo no es de confianza) |
| H2 | `port/full/plat_snd_se.c:86-101` (y `73-85`) | `Port_IopAlloc` acepta tamaños enormes por wrap (`size+63`, `cand+size`); queda un bloque de tamaño basura e `iop_remain` devuelve un resto sin tope | **crash/corrupción** | No (los tamaños que manda el juego son chicos), pero se dispara con una cabecera de banco corrupta |
| H3 | `port/full/plat_snd_se.c:347-357` | `Port_SifSetDma`: copia desde un puntero EE (`data`) y hacia un offset del IOP **sin validar ni el origen ni el bloque destino** (solo la arena de 16 MB) | **crash / corrupción silenciosa del IOP** | No con los datos reales (máx. body 0x81240 vs bloque 0x81800), pero es el mismo agujero que el fix anterior dejó abierto |
| H4 | `port/full/plat_gs.c:39-51` | `sceGsExecLoadImage` lee `w*h*bits/8` bytes de `src` (32 bits) sin ningún tope: `w,h` de 12 bits permiten ~67 MB | **crash** | No con texturas normales; latente. **No propongo clamp ciego** (ver por qué en H4) |
| H5 | `port/eq/2981B8.c:12-28` + `port/eq/298240.c:7,13-24` | `maxNumber` del banco se usa como tope de dos escrituras sin rango: `arg1[0..count]` y `count` bits; destinos de 8 y 128 bytes | corrupción silenciosa / pisa la pila del host | No con los datos: 290 bancos, máx. 84 (y ese va al buffer de 128 bits). Roto con `maxNumber ≥ 64` (bitmaps de 8 B) o `≥ 128` (pila) |
| H6 | `port/eq/28BC68.c:8-16` | El heap del SPU (`func_0028BC68`) no chequea el espacio libre: `*(p+4) -= t` puede quedar negativo y devolver direcciones ≥ 2 MB | queda "sin audio", no crash (lo frena `Port_SdRemote`) | Sí puede pasar (bancos grandes), pero es cosmético |
| H7 | `port/full/plat_file.c:105,208-212`; `:69-70` | `ADXF_ReadNw`/`sceRead` con `size`/`nsct` negativos: `(size_t)` negativo → `fread/memset` gigantes. `malloc(count*8)` del AFS sin chequear NULL | crash (defensivo: ningún llamador actual pasa negativo) | No |
| H8 | `port/full/gs/snd_se.c:101-131` | Es la copia **vieja y sin arreglar** de `plat_snd_se.c` (mismo `lookup` sin `iop_remain`) | no aplica | No se compila (`port/tools/link_full.py:187-188`); no reactivarla tal cual |

---

## H1. `lookup()`: el tope del offset de secuencia se saltea por wrap (crash, misma clase)

**Archivo:línea**: `BT2-Recomp/port/full/plat_snd_se.c:135-144`

```
132:    const uint8_t *sesq = chunk(b->sq, "Sesq", 0x4000), ...;
135:    if (sesq != NULL) {
136:        uint32_t off = 0x34 + 4u * (uint32_t)id;
137:        if (iop_remain(sesq) >= off + 4) {
138:            uint32_t so = le32(sesq + off);
139:            if (iop_remain(sesq) >= so + 0x14) {
140:                const uint8_t *seq = sesq + so;
141:                if (seq[0x11] == 0x90) timbre = seq[0x13];
```

**Qué se va del rango y con qué dato**: `so` es un `u32` leído de la tabla de offsets del chunk `Sesq` (dato del
archivo de banco, copiado al bloque del IOP). La comparación `iop_remain(sesq) >= so + 0x14` se hace **sumando en
32 bits**: si `so ≥ 0xFFFFEC`, `so + 0x14` da la vuelta a un valor chico, el chequeo pasa y `seq = sesq + so` cae hasta
~4 GB antes del bloque; `seq[0x11]` es la lectura que revienta. Si `so` fuese 0, el chequeo funcionaría bien.

**Evidencia de que el campo no es de confianza** (barrido de los 2 AFS con el formato real de banco
`{magic, bodyOfs, hdOfs, seqOfs, endOfs}` y los chunks `IECSsreV/IECSdaeH/IECSuqeS/IECSqseS/IECSigaV/IECSbteS`):
- 290 bancos reales; **36 entradas con `so = 0xFFFFFFFF`** repartidas en **23 archivos de `ZS2US_2.AFS`**
  (idx 26, 27, 30, 34-49, 51-54).
- El juego carga en `D_003876A0+0xC` (`port/eq/103CB0.c:70`: `func_00100ED0(D_003876A0[0xD4] + 0x33D4, ...)`) la
  familia de bancos idx 34..54 de `ZS2US_2.AFS`; **todos salvo el 50** tienen entradas `0xFFFFFFFF` (por ejemplo el 34
  en los ids 77 y 78, con `VagiMax` 7). O sea: el centinela aparece justo en los bancos de personaje que se cargan en
  pelea, no es un caso teórico.
- Hoy `0xFFFFFFFF + 0x14 = 0x13` pasa el chequeo, pero `sesq - 1` cae **dentro** del bloque (el chunk `Sesq` está en
  `seqBlock + 0x30`), lee `sesq[0x10]` (= `0x10`, no `0x90`), deja `timbre = id = 77`, y después lo rechaza
  `vag > le32(vagi+0x0C)` (77 > 7). O sea: **hoy no crashea, pero el chequeo está roto**; cualquier valor distinto de
  `-1` en ese rango (banco modificado, AFS tocado, o un id que lea la cola de la tabla) lee fuera del bloque.
- Los ids 0..84 (`VagiMax` = 84) tienen offset y nota-on válidos; del 85 en adelante el chunk `Sesq` contiene otras
  estructuras y se leen como `so` valores como `0x3E84064`, `0xFF0064`, `0x9000`… (o sea: un id fuera de rango produce
  un `so` arbitrario, que es justo la entrada del chequeo roto).

**Gravedad**: crash (lectura fuera del `calloc` de `sIop`, o dentro de otro bloque: audio equivocado).

**Arreglo propuesto** (comparar restando, y descartar el centinela):

```c
    if (sesq != NULL) {
        uint32_t off  = 0x34 + 4u * (uint32_t)id;
        uint32_t srem = iop_remain(sesq);
        if (off + 4 <= srem) {
            uint32_t so = le32(sesq + off);
            /* 0xFFFFFFFF = "sin efecto"; el tope se compara restando porque so + 0x14 puede envolver */
            if (srem >= 0x14 && so != 0xFFFFFFFFu && so <= srem - 0x14) {
                const uint8_t *seq = sesq + so;
                if (seq[0x11] == 0x90) timbre = seq[0x13];
            }
        }
    }
```

(Nota: `off + 4` no puede envolver porque `off ≤ 0x34 + 4*255 = 0x430`. `srem >= 0x14` está garantizado por
`off + 4 <= srem` con `off ≥ 0x34`, pero lo dejo explícito para que la resta no dependa de eso.)

---

## H2. `Port_IopAlloc` / `iop_remain`: el tamaño del bloque puede dar la vuelta

**Archivo:línea**: `BT2-Recomp/port/full/plat_snd_se.c:73-101`

```
 89:    size = (size + 63u) & ~63u;
 ...
 93:            if (sIopBlk[i].size && cand < sIopBlk[i].addr + sIopBlk[i].size && sIopBlk[i].addr < cand + size) ...
 97:    if (cand + size > IOP_SIZE) { ...; return 0; }
100:    sIopBlk[j].addr = cand; sIopBlk[j].size = size;
```

**Qué se va del rango y con qué dato**: `size` viene de `sceSifAllocIopHeap(a0v)` (`port/full/plat_sys.c:78`) y `a0v`
es una **resta de dos offsets de la cabecera del banco**, calculada en `s32`:
`port/eq/297A78.c:85` (`a0v = v1 - *(s32 *)(s1 + 8)`), `:112`, y `:52` (`s2 = v1 - *(s1 + 4)`). Si la cabecera es
inconsistente (`hdOfs < bodyOfs`, `seqOfs < hdOfs`, etc.), `a0v` queda negativo → al pasarlo a `u32` es ~4 GB:
- `size + 63` no cambia el orden de magnitud y `& ~63` lo deja ~`0xFFFFFF00`;
- el test de solape `sIopBlk[i].addr < cand + size` **envuelve** y da falso → no detecta solape;
- `cand + size > IOP_SIZE` **envuelve** y da falso → lo acepta;
- `sIopBlk[j].size = 0xFFFFFF00` e `iop_remain()` devuelve `addr + 0xFFFFFF00 - a`, un resto enorme.

Con ese "bloque" de tamaño enorme, `chunk(p, name, 0x4000)` recibe `limit = 0x4000` y escanea 16 KB desde `p` **sin
saber que el bloque no existe**, y `lookup()` lee secuencias dentro de esos 16 KB. Si `cand` quedó cerca del final de
los 16 MB, la lectura se va del `calloc` de `sIop`. Además, el resto de las reservas posteriores ven un solape falso y
el allocator termina en "memoria del IOP agotada" (se queda sin sonido).

**Gravedad**: corrupción de la tabla de bloques + lectura fuera de `sIop` (crash) con cabecera corrupta; con datos
sanos no se dispara (el body más grande mide 0x81240, ver H3).

**Arreglo propuesto**:

```c
uint32_t Port_IopAlloc(uint32_t size) {
    uint32_t cand = IOP_BASE, i, j;
    if (sIop == NULL) { sIop = calloc(1, IOP_SIZE); if (sIop == NULL) { return 0; } }
    if (size == 0 || size > IOP_SIZE - IOP_BASE) {
        fprintf(stderr, "bt2: pedido de IOP invalido 0x%X\n", size);
        return 0;
    }
    size = (size + 63u) & ~63u;
```

y en `iop_remain()`, acotar el resto a lo que queda de la arena (por si la tabla ya está corrupta):

```c
        if (sIopBlk[i].size && a >= sIopBlk[i].addr && a < sIopBlk[i].addr + sIopBlk[i].size) {
            uint32_t end = sIopBlk[i].addr + sIopBlk[i].size;        /* puede envolver si size es basura */
            uint32_t rem = end > (uint32_t)a ? end - (uint32_t)a : 0;
            uint32_t lim = IOP_SIZE - (uint32_t)a;
            return rem < lim ? rem : lim;
        }
```

---

## H3. `Port_SifSetDma`: el origen EE y el bloque destino no se validan

**Archivo:línea**: `BT2-Recomp/port/full/plat_snd_se.c:346-357`

```
347: void Port_SifSetDma(uint32_t dp, int count) {
351:     for (i = 0; sIop != NULL && d != NULL && i < count; i++) {
352:         uint32_t data = d[i * 4], addr = d[i * 4 + 1], size = d[i * 4 + 2];
353:         if (addr != 0 && data != 0 && (int32_t)size > 0 && addr < IOP_SIZE && size <= IOP_SIZE - addr) {
354:             memcpy(sIop + addr, (void *)(uintptr_t)data, size);
```

**Qué se va del rango y con qué dato**: `data`/`size` salen de `SifDmaData` que arma el juego con offsets del archivo
de banco: `port/eq/297A78.c:57-58`, `89-90`, `116-117` (`s1 + bodyOfs`, `hdOfs-bodyOfs`, etc.) y `port/eq/297D78.c:29-36`.
`s1` es el buffer del archivo en la RAM del juego (tamaño = sectores*2048) y esas palabras de la cabecera **no se
validan en ningún lado**: el que la carga (`port/eq/100ED0.c:14-44`, `func_00100ED0`) solo abre el archivo, cuenta
sectores, reserva `sectores << 11` y lo cierra; nadie compara `bodyOfs/hdOfs/seqOfs/endOfs` contra ese tamaño.
- **Origen**: `data` es un puntero de 32 bits de la PS2 sin traducir ni comparar con `RAM_SIZE`; si `hdOfs` es mayor que
  el tamaño del archivo, `memcpy` lee fuera del buffer (y si se pasa de 0x02000000, SIGSEGV en el host; en la PS2 solo
  leería basura del bus).
- **Destino**: el chequeo es contra **la arena de 16 MB**, no contra el bloque asignado. El buffer de staging es de
  `0x81800` (`port/eq/297908.c:18`: `sceSifAllocIopHeap(0x81800)`) y las copias van ahí (297A78:57, 297D78:29). Si el
  body superara 0x81800, se escribiría encima de los bloques `hd/seq` que el allocator puso a continuación →
  corrupción silenciosa de los encabezados de otros bancos.

**Verificación con datos** (para no vender un bug que no existe): escaneé los 290 bancos reales; el body más grande es
el del banco común (`ZS2US_2.AFS`, índice 33): `body = 0x81240` contra un staging de `0x81800` → **entra, con 0x5C0
de margen**. Ningún body real supera el staging. Por eso: **no es un crash actual**, es el chequeo que falta.

**Gravedad**: crash (origen fuera de la RAM) / corrupción silenciosa del IOP (tamaño mayor que el bloque).

**Arreglo propuesto**:

```c
/* Un puntero del EE es válido si cae en la RAM del PS2 o en un espejo uncached/UCAB. */
static int ee_ok(uint32_t a, uint32_t n) {
    uint64_t e = (uint64_t)a + (uint64_t)n;
    return (a >= 0x10000u && e <= 0x02000000ull) ||
           (a >= 0x20000000u && e <= 0x22000000ull) ||
           (a >= 0x30000000u && e <= 0x32000000ull);
}
/* Resto del bloque del IOP que contiene el offset `a` (0 si no está en ninguno). */
static uint32_t iop_block_remain(uint32_t a) {
    uint32_t i;
    for (i = 0; i < IOP_BLOCKS; i++)
        if (sIopBlk[i].size && a >= sIopBlk[i].addr && a < sIopBlk[i].addr + sIopBlk[i].size)
            return sIopBlk[i].addr + sIopBlk[i].size - a;
    return 0;
}
...
        if (addr != 0 && data != 0 && (int32_t)size > 0 && addr < IOP_SIZE && size <= IOP_SIZE - addr) {
            uint32_t blk = iop_block_remain(addr);
            if (!ee_ok(data, size)) {
                static int w1; if (!w1) { w1 = 1; fprintf(stderr, "bt2: SifDma con origen invalido 0x%X+0x%X\n", data, size); }
            } else if (blk == 0 || size > blk) {
                static int w2; if (!w2) { w2 = 1; fprintf(stderr, "bt2: SifDma 0x%X+0x%X fuera del bloque del IOP (resto 0x%X)\n", addr, size, blk); }
            } else {
                memcpy(sIop + addr, (void *)(uintptr_t)data, size);
            }
        }
```

(`ee_ok` acepta los espejos porque `full_dma_addr()` ya trata con direcciones físicas en otros caminos; los llamadores
de hoy pasan direcciones cacheadas de la RAM.)

---

## H4. `sceGsExecLoadImage`: `TRXREG` manda el tamaño, el puntero de 32 bits no se valida

**Archivo:línea**: `BT2-Recomp/port/full/plat_gs.c:39-51`

```
41:    uint32_t w = (uint32_t)(l->trxreg & 0xFFF), h = (uint32_t)((l->trxreg >> 32) & 0xFFF), psm = ...;
42:    uint32_t qw = (uint32_t)(((uint64_t)w * h * (uint32_t)Gs_PsmBits(psm) + 127) / 128);
...
49:        Port_GsGifChannel(src, n, 0);
50:        src += n * 16; qw -= n;
```

**Qué se va del rango y con qué dato**: `w`/`h` son campos de 12 bits de `TRXREG` (los escribe
`sceGsSetDefLoadImage` con lo que le pasa el juego, línea 35). Con `w = h = 0xFFF` y `psm` de 32 bits, `qw ≈ 4.19 M`
quadwords → **67 MB** leídos desde `src` (un `u32` de la PS2 usado como dirección del host, en
`port/full/gs/gs_core.c:1399` `Gs_Gif((const uint8_t *)(uintptr_t)addr, qwc)`). Una textura/descriptor raro lee fuera
de la RAM de 32 MB y revienta.

**Por qué NO propongo el clamp obvio**: el puerto le pasa a esta misma API **punteros del host**, no de la PS2:
`port/full/plat_movie.c:83` mapea `M.strips` con `MAP_32BIT` y lo entrega al juego (`out[0] = (u32)(uintptr_t)M.strips`,
línea 161); el juego lo pasa por `func_0024B980` y llega a `sceGsExecLoadImage` (`port/eq/24B980.c:28`). Un chequeo
`src < 0x02000000` **rompería las películas**. El arreglo real es registrar los buffers que el puerto entrega al juego
(o que la capa GS lea con una tabla de regiones válidas); mientras tanto queda como **riesgo conocido, sin parche**.

**Gravedad**: crash, latente (los descriptores reales son chicos). Lo único que se puede agregar sin riesgo es
rechazar `src < 0x10000` (página cero); el tamaño sigue sin tope.

---

## H5. `func_002981B8` / `func_00298240`: `maxNumber` sin rango contra destinos fijos

**Archivo:línea**: `BT2-Recomp/port/eq/2981B8.c:12-28` y `port/eq/298240.c:7,13-24`

```
2981B8.c
12:    vag = SndHd_GetVagInfo(arg0 + (*(u32 *)(arg0 + 8) & ~3));
13:    count = *(s32 *)(vag + 0xC);
14:    p = vag + 0x14 + count * 4;
15:    if (count >= 0) {
17:        for (i = count + 1; i != 0; i--) {
20:                if (p[0] & 1) { arg1[k] = 1; } else { arg1[k] = 0; }
27:            k++;

298240.c
 7:    u8 sp[0x80];
13:    temp_s1 = SndHd_GetVagMax(arg0);
14:    func_002981B8(arg0, sp);
...
20:                temp_v0_2 = arg1 + temp_v0;
21:                *temp_v0_2 |= 1 << (var_a1 - (temp_v0 * 8));
24:        } while (var_a1 < temp_s1);
```

**Qué se va del rango y con qué dato**: `count = *(u32*)(vag + 0xC)` es el `maxNumber` del chunk `SCEIVagi` del banco
(dato del archivo; `SndHd_GetVagInfo` lo ubica con `head[0xC]`, ver `port/build/full/bt2full` → `SndHd_GetVagInfo`:
`eax = [rdi+0x30] & ~3; rax += rdi`, o sea `vagi = head + hd[0xC]`).
- `func_002981B8` escribe `arg1[0..count]` en **`sp[0x80]`** (`298240.c:7`) → overflow de la pila del host si
  `count ≥ 128`, con el valor de retorno guardado ahí.
- `func_00298240` prende `count` bits en `arg1`: los llamadores le pasan **8 bytes** (`*(u64*)(st+0xA0) = 0`,
  `*(u64*)(st+0xA8) = 0` en `port/eq/104990.c:42-43`; ídem `103650.c:90-94` y `1031E0.c:81-85`) o **16 bytes**
  (`memset(st+0x90, 0, 16)`, `104990.c:41`) → pisa `st+0xA8`/`st+0xB0`… (estado del sonido de la pelea) si
  `maxNumber ≥ 64` (bitmaps de 8 B) o `≥ 128` (el de 16 B y la pila).

**Verificación con datos** (290 bancos): `maxNumber` máximo = 84 y es el del **banco común**, que va al buffer de 16 B;
todos los bancos de personaje ≤ 56 (entran en 8 B). **Hoy no se dispara**, pero el código no tiene tope: un banco
modificado o una ruta que mande un banco grande al buffer de 8 B pisa memoria del juego (y si el `count` es basura,
la pila del host).

**Gravedad**: corrupción silenciosa (globals del juego) / pila pisada (crash).

**Arreglo propuesto** (contención; con los datos actuales no cambia nada, porque todo entra):

```c
/* 2981B8.c, después de leer count */
13:    count = *(s32 *)(vag + 0xC);
+     if (count < 0) return;
+     if (count > 0x7F) count = 0x7F;      /* escribe count+1 bytes en sp[0x80] (298240.c:7): 128 es el máximo seguro */
```
y en `298240.c`, antes del `do/while`:
```c
+     if (temp_s1 < 0) temp_s1 = 0;
+     if (temp_s1 > 0x7F) temp_s1 = 0x7F;  /* con los bancos de personaje reales (≤56) no recorta nada */
```

**Límite de este arreglo**: el clamp a 0x7F protege la **pila** (`sp[0x80]`) y el bitmap de 16 B; los dos bitmaps de
**8 B** (`st+0xA0`/`st+0xA8`) seguirían pisándose con un banco de 64..127 muestras. Cerrarlo del todo requiere pasar el
tamaño del destino como argumento a `func_00298240`, y **eso no lo propongo ahora**: la función está expuesta en la
tabla de direcciones (`0x298240`) y puede llamarse desde el relleno MIPS recompilado con la ABI de dos argumentos, que
leería basura como tercer parámetro. Alternativa sin cambiar la firma: que los llamadores usen un destino de 16 B (el
mismo que ya usa el banco común) en `104990.c:46,49`, `103650.c:90-94` y `1031E0.c:81-85`.

---

## H6. Heap del SPU sin chequeo de espacio (`func_0028BC68`)

**Archivo:línea**: `BT2-Recomp/port/eq/28BC68.c:8-16`

```
 9:    s32 t = (arg0 + 0xF) & ~0xF;
10:    u8 *p = D_0038A638 + D_00387EB4 * 8;
11:    s32 start = *(s32 *)p;
13:    *(s32 *)p += t;
14:    *(s32 *)(p + 4) -= t;
15:    return start;
```

No compara `t` con el libre (`p+4`): si no entra, el libre queda negativo, `start` crece más allá de los 2 MB del
SPU2 y el bloque se marca como usado igual. Lo consume `port/eq/297A78.c:55` (`s3 = func_0028BC68(s2)`) y ese valor
viaja a `sceSdRemote(..., spuAddr = s3, size = s2)`; **hoy lo frena `Port_SdRemote`** (`plat_snd_se.c:367`:
`spuAddr < SPU_SIZE && size <= SPU_SIZE - spuAddr`), así que no hay escritura fuera de `sSpu`, pero el banco queda
mudo (o con muestras viejas) sin aviso. El tope de 2 MB lo pone el puerto, no el juego: **no sacar ese chequeo**.

**Gravedad**: solo cosmético (audio faltante). **Arreglo propuesto** (en el juego, opcional; `port/eq/*.c`
no incluye `stdio.h`, haría falta agregarlo):
```c
+    if (*(s32 *)(p + 4) < t) { static int w; if (!w) { w = 1; fprintf(stderr, "bt2: SPU sin espacio (piden 0x%X, quedan 0x%X)\n", t, *(s32 *)(p + 4)); } return -1; }  /* -1: Port_SdRemote lo rechaza (spuAddr >= SPU_SIZE) */
```

---

## H7. Tamaños negativos y `malloc` sin chequear en la capa de archivos (defensivo)

**`port/full/plat_file.c:100-117`** (`func_002EC0C8`, `ADXF_ReadNw`):
```
105:    if (nsct > (s32)(total - f->posSct)) nsct = (s32)(total - f->posSct);
106:    want = (size_t)nsct * SECTOR;
...
111:        got = fread((void *)(uintptr_t)buf, 1, n, f->part->fp);
112:        memset((uint8_t *)(uintptr_t)buf + got, 0, want - got);
```
Si `nsct < 0` (el clamp de la línea 105 solo recorta cuando `nsct` es **mayor**), `want = (size_t)(-1) * 2048` ≈ 2^64 (envuelve) →
`memset` gigante sobre `buf` (una dirección de 32 bits del juego) → crash. Ningún llamador actual pasa negativo
(`100CB8.c:30`, `100FC8.c:90` usan el conteo de sectores del archivo), así que es defensivo. Arreglo:
```c
+    if (nsct <= 0) { f->stat = STAT_READEND; return 0; }
     want = (size_t)nsct * SECTOR;
```
**`plat_file.c:208-212`** (`sceRead`): `size` es `s32` y se pasa como `(size_t)size` sin chequear; negativo → `fread`
gigante sobre `buf`. El llamador real (`src/main_1002D8.c:74`) pasa el tamaño del archivo. Arreglo: `if (size <= 0) return 0;`.

**`plat_file.c:69-70`** (`func_002EA588`): `p->count` sale de la cabecera del AFS y hace
`malloc(count*8)` **sin chequear NULL** y después `fread(p->tab, 8, p->count, ...)`: un AFS corrupto con `count`
enorme → `fread(NULL, …)` (segfault) en vez del `exit(2)` que la línea 70 pretende dar. Arreglo:
```c
     p->tab = malloc((size_t)p->count * 8);
+    if (p->tab == NULL) { fprintf(stderr, "bt2full: tabla AFS imposible (%u archivos): %s\n", p->count, path); fclose(p->fp); p->fp = NULL; return 0; }
```

---

## H8. Copias muertas que NO hay que reactivar

- `port/full/gs/snd_se.c` es la versión **anterior** de `plat_snd_se.c`: `lookup()` sin `iop_remain`
  (`gs/snd_se.c:103-126`: `sesq + le32(...)` directo, `le32(vagi + 0x10 + 4*vag)` sin tope) y `sceSdRemote` sin rango
  (`gs/snd_se.c:332-334`). `port/tools/link_full.py:187-188` la excluye a propósito (igual que `gs/snd_adx.c`).
- `port/full/temp_stubs.c:14-21` (`func_0028AFA0`) no chequea el NULL de `func_0028BAA8` antes de guardar los
  punteros; los usa el juego como buffer de DMA. Con 31 MB de heap no falla, pero si se agrega C que consuma más
  memoria, primero se rompe acá.

---

## Qué descarté y por qué (para no repetir el análisis)

1. **Tags de chunk equivocados (`Sesq`/`Setb`/`Vagi`)**: los verifiqué contra el archivo real. `lookup` busca
   `IECS`+nombre invertido; en el banco común (ZS2US_2 idx 33) están `IECSqseS` en `seq+0x30`, `IECSbteS` y `IECSigaV`
   en el bloque `hd`. **Coinciden**; no hay bug de nombres (lo sospeché por la diferencia con BT3 y lo descarté con
   el hexdump).
2. **"El body de slots 3/4/5 (0x8F000) desborda el staging de 0x81800"**: falso con los datos. Escaneé los 290 bancos
   (cabecera `{magic, bodyOfs, hdOfs, seqOfs, endOfs}` + `SCEIVers/SCEIHead/SCEISequ` + `Vagi`): el body máximo es
   0x81240 (banco común) y **ninguno** supera 0x81800. Queda como H3 (falta el chequeo, no el desborde).
3. **`maxNumber` pisando los bitmaps de 8 B hoy**: falso con los datos (máx. 84, y ese va al buffer de 16 B; los bancos
   de personaje ≤ 56). Queda como H5 latente.
4. **Tabla `D_00387F80` (`func_00100ED0`/`100FC8`, índice `D_00387698` que crece +3)**: el bss arranca en 0x387F80 y el
   heap del juego en 0x430590 → ~690 KB de tabla (172k entradas); no hay overflow realista.
5. **Contador de ranura de banco `*(D_00387ED0+0x60)` (`297A78.c:64,91,118`)**: es el único escritor y solo se
   incrementa en la carga *inicial* de un banco (las recargas van por `297D78`); el juego carga 4 slots fijos. No se
   dispara. (Si algún día se cargan >8 bancos sin recargar, escribiría sobre `g+0x60..` y el staging en `g+0x6C`; el
   chequeo `slot < 8` de `plat_snd_se` no cubre esto porque es del lado del juego.)
6. **`spu_ptr`**: no existe en el árbol. El único acceso al SPU es `sSpu[]` con topes en `decode_block`
   (`plat_snd_se.c:167`) y `Port_SdRemote` (`:367`); `decode_block` además acota contra `SPU_SIZE`, no contra el bloque
   del banco (una muestra puede leer la RAM del SPU de otro banco: audio basura, no crash).
7. **`gs/snd_adx.c`**: ídem H8 (no compilada).
8. **`plat_fightlog.c` / `plat_trace.c` / `plat_mc.c` / `plat_movie.c`**: tienen sus propios chequeos (`ok()`,
   `ncarry < 64`, `unit ≥ 18`, `fd` en rango) y no encontré lecturas con tamaño de la RAM sin límite.

## Cómo verifiqué

- `grep -rn "Port_IopAlloc|Port_IopFree|sIop|sSpu|IOP_SIZE|SPU_SIZE|iop_ptr|iop_remain" port/` y
  `grep -rn "memcpy|memset|memmove" port/full/*.c`.
- Lectura completa de `plat_snd_se.c`, `plat_snd_adx.c`, `plat_file.c`, `plat_sdk.c`, `plat_movie.c`, `plat_mc.c`,
  `plat_gs.c`, `plat_sys.c`, `plat_mem.c`, `mem.c`, `plat_demo.c`, `plat_trace.c`, `temp_stubs.c`, `compat.c` y de
  todos los `port/eq/29*.c` + `28B*.c` que tocan IOP/SPU, más los productores en `src/` (`sys/dma_28B290.c`,
  `sys/snd_298170.c`, `auto/m2c_298438.c`, `auto/perm_298460.c`, `auto/m2c_297640.c`).
- Para los tamaños reales: script Python de solo lectura sobre `BT2-test/gamedata/DATA/ZS2US_{1,2}.AFS` (tabla AFS +
  cabecera de cada archivo + chunks), sin escribir nada. Números citados arriba (290 bancos, máx. body 0x81240, máx.
  `maxNumber` 84, 36 entradas `so = 0xFFFFFFFF`).
- Confirmé que `port/full/gs/snd_se.c` y `gs/snd_adx.c` **no** se compilan (`port/tools/link_full.py:187-188`).
- No compilé ni ejecuté el juego; **nada de esto está verificado en ejecución**. Las verificaciones son de código y de
  datos del disco.

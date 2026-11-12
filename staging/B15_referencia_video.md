# B15 — Referencia de video del usuario (selección de escenario) + comparación con el port

Analista: subagente visor (solo lectura). Fecha: 2026-11-11.
Material:
- Referencia (original): `/home/rexx/Vídeos/Videocapturas de pantalla/Videocaptura de pantalla_20261111_121232.webm`
  (1058x695, 106.2 s). Hojas de contacto 1 cuadro/s en `/tmp/opencode/refsel/sheets/sheet_01..07.png`,
  cuadros completos en `/tmp/opencode/refsel/all/f_001..f_106.png` y extracciones propias en `/tmp/opencode/refsel/extra/`.
- Port: `/tmp/opencode/portsel/p_001..p_360.png` (12 s a ~30 fps, 1024x896 = 512x448 x2), hoja en
  `/tmp/opencode/port_sheet_05s.png` (ojo: esa hoja quedó mal armada, los cuadros se ven cortados y repetidos;
  **usé los 360 PNG sueltos, no la hoja**).

---

## 0. Datos técnicos de la referencia (importante para medir ritmos)

| Dato | Valor medido |
|---|---|
| Ventana / grabación | 1058x695, incluye barra de menú (~0..46) y barra de estado (~666..695) de **PCSX2** |
| Área del juego en el video | aprox. **x 116..940, y 48..666** (824x618 ≈ 4:3) |
| Resolución interna | la barra de estado dice **512x448 (×1)**, backend **Vulkan**, "Automático" |
| Cuadros por segundo | **NO son 60 constantes**: medí 119 cuadros en 3.0 s ⇒ **≈40 fps promedio, VFR**
| Factor de escala video→píxel de juego | x: ×0.6214, y: ×0.7249 (la imagen sale estirada a 4:3, no cuadrada) |

Esto es clave: **no se pueden contar cuadros "de 60 fps"**. Todo lo de abajo está en segundos.

---

## 1. Recorrido segundo a segundo (tramos)

| Seg. inicio–fin | Pantalla | Observaciones |
|---|---|---|
| 0.0–1.0 | Negro → logo **Atari** | fundido de entrada |
| 1–3 | Atari (rojo sobre beige) → negro | |
| 3–4 | Pantalla gris/clara | fundido |
| 4–5 | Logo **Spike** (fondo blanco) | |
| 5–7 | **Sofdec + ADX** (fondo blanco, se va apagando) | |
| 7–10 | Negro | carga |
| 10–13 | **Texto de copyright** (dos bloques, Atari / BIRD STUDIO…) | |
| 14–16 | **Pantalla de título** (carátula BT2) + botón "New Game" | |
| 16–19 | **Diálogos de memory card**: "Do you wish to create a save file…", "Checking memory card (PS2)…", "Start a new game without saving?" | |
| 20 | Título otra vez | |
| 21–24 | **Main Menu** (Shenron de fondo; texto de ayuda abajo) | a los 22 resaltado *Dueling*, a los 23 *Ultimate Training* |
| 24–27 | Negro | carga del submenú |
| 27–28 | Submenú **Ultimate Training** (Training / Practice) + diálogo de personajes | |
| 29–34 | **Selección de personaje** (Goku ® vs Kid Gohan; tira de iconos arriba y abajo; "Select Color" a los 33–34) | el layout coincide con `BT2-test/capturas/.../07_charselect.png` del port |
| 35.0–35.4 | Transición: cielo con texto en japonés | pantalla de carga, PCSX2 en "Sin imagen"/bajón de fps |
| **35.4–35.9** | **Entrada a Map Select** | barrido circular girando; a los 36.0 el cuadro ya está completo |
| **36–69.5** | **MAP SELECT (mapa + música) — la pantalla de B15** | detalle en §3 y tabla de §3.1 |
| 69.5–69.9 | Fundido a negro | al apretar Decide |
| 70–79 | **"NOW LOADING"** (Goku cargando energía, destellos, cajas rojas) | |
| 80 | Pelea cargando: escena oscura con HUD, PCSX2 dice "Sin imagen", Velocidad 59 % | bajón real de PCSX2 |
| 81 | **"READY?"** con HUD de pelea | |
| 82–85 | Arranca la pelea; a los 83–85 aparece/sale el menú **"1P PAUSE"** | el "FIGHT!" se ve como banner translúcido detrás del menú |
| 86–95 | Pelea libre (vuelo sobre el agua, isla, HUD, radar) | |
| 96–105 | **Dos Kamehameha** (ver §5) | fin del video a los 106 s |

---

## 2. ¿Original, port o mezcla?

**Es el original corriendo en PCSX2, de punta a punta. No hay un solo cuadro del port.**

Evidencia:
- Barra de título: "Dragon Ball Z - Budokai Tenkaichi 2" (título autodetectado del disco por PCSX2).
- Menú en español de PCSX2: **Sistema / Ajustes / Vista / Herramientas / Ayuda**.
- Barra de estado de PCSX2: `Automático (Vulkan)  512×448 (×1)  GPU: x %  FPS: nn  VPS: 60  Velocidad: 100 %  Volumen: 100 %`.
- Hay indicadores que el port no tiene: "**Sin imagen**" y "Velocidad: 59 %" durante las cargas (80 s), y caídas
  de FPS puntuales (17–30) — es el comportamiento de PCSX2, no de un build nativo.
- Resolución interna 512x448 con estirado 4:3: el port saca 512x448 con píxeles cuadrados (los PNG del port
  son 512x448 ×2, sin estirar).

---

## 3. La pantalla de selección de escenario (+ música) en la referencia

**Rango: 35.4 s a 69.5 s** (entrada con barrido circular a los 35.4–35.9; fundido a negro 69.5–69.9).

### 3.1 Escenarios por los que va pasando el usuario

| Seg. | Nombre en pantalla | Música (línea "…") | Notas |
|---|---|---|---|
| 36–41 | **Wasteland** | `…Random…` | estado inicial; mismo estado que capturaron los cuadros del port |
| 42–48 | **Dying Namek** | `…Random…` | |
| 49–52 | **Namek** | `…Random…` | |
| 53–56 | **Planet** | `Dark Half` a los 53–55, `Escape to freedom` a los 56 | |
| 57–58 | **Supreme Kai's World** | `Escape to freedom` | |
| 59–61 | **Hyperbolic Time Chamber** | `Escape to freedom` | |
| 62–63 | **Kami's Lookout** | `Escape to freedom` | |
| 64 | **Ruined Earth** | `Escape to freedom` | |
| 65 | **World Tournament Stage** | `Escape to freedom` | |
| 66 | **Glacier** | `Escape to freedom` | |
| 67 | **Kame House** | `Escape to freedom` | |
| 68 | **Islands** | `Escape to freedom` | |
| 69 | **Kame House** | `Escape to freedom` | vuelve atrás y decide |

La música cambia sola con el mapa (cada mapa trae su BGM por defecto: `…Random…` = sin asignar): el nombre
aparece en la línea debajo de "Map Effect", junto a "L1 R1 Change Music". No vi en el video que se use L1/R1.

### 3.2 Layout exacto (en píxeles de juego, 512x448)

| Elemento | Posición (px de juego) | Descripción |
|---|---|---|
| Logo "Map Select" | x 37..223, y 22..61 | texto azul/blanco con contorno, arriba a la izquierda |
| **Fondo grande** | cubre toda la pantalla (x 0..512, y 0..448) | **la imagen del escenario seleccionado, desenfocada y velada (azulada)**, detrás de TODO (también detrás del logo y del panel inferior). Se ve claramente a los 1:06 (World Tournament): arriba del cuadro nítido hay una versión borrosa del mismo pueblo de piedra |
| **Cuadro nítido del escenario** | x ≈0..325, y ≈63..273 | segunda copia **nítida** de la imagen del escenario, con **esquinas redondeadas**; es el "preview" grande de B15. **Está en movimiento continuo y lento** (encuadre distinto cada segundo) |
| Aro/círculo del HUD | x ≈300..512, y ≈0..448 | círculo enorme translúcido con rayado diagonal fino y tinte azul; tapa parcialmente la imagen grande |
| Carrusel de miniaturas | x 360..462 | **columna vertical sobre el aro**, 5 ranuras visibles (3 completas + 2 cortadas arriba y abajo), cada una ~102x85, con marco gris |
| Ranura seleccionada | x 333..462, y 165..280 (~129x115) | más grande, **marco amarillo**, dos **triángulos naranjas** (uno arriba, uno abajo). Adentro hay **otra vista, más cercana, del mismo escenario** (también animada) |
| Rótulo amarillo dentro de la ranura | x ≈340..400, y ≈175..190 | texto **ilegible a esta resolución, y dibujado en espejo** (se lee invertido). Aparece solo en algunos escenarios/estados y desaparece. En Wasteland (36–37) se ve; en Wasteland tardío ya no. Candidato a "1 vs CPU", pero **no lo pude leer**: no lo afirmo |
| Banda del nombre | x 0..~430, y 277..313 | banda morada con el nombre del escenario en blanco con contorno azul (ej. "Wasteland") |
| Panel inferior | y 313..448 | banda celeste con: `⊡ Random` `✕ Decide`, `Map Effect  ON`, la línea de música (`…Random…` / `Escape to freedom`), `[L1][R1] Change Music` y el icono redondo de ○ abajo a la izquierda |
| Objeto blanco con cuadradito rojo | x ≈450..512, y ≈130..295 | pieza blanca (¿decoración del aro?) pegada al borde derecho, con un rectángulo rojo; presente en todos los cuadros |

### 3.3 Comportamiento del preview (lo que hay que reproducir)

- **Movimiento continuo**: el encuadre cambia todo el tiempo. Medí entre los segundos 37 y 38 un corrimiento
  aparente de ~6 px del video (≈3.6 px de juego) hacia un lado, pero **con paralaje** (el cielo y el suelo no se
  mueven igual), así que no es una traslación pura: parece una **cámara 3D** o un paneo con efecto.
  Con la resolución del video no puedo distinguir "cámara 3D" de "paneo sobre una imagen panorámica".
- **Al cambiar de escenario hay un corte duro, de 1 cuadro** (medido: de 41.733 s a 41.750 s, el fondo cambia de
  golpe; diff medio 72 y después 0.0 en los cuadros siguientes). **No hay cross-fade visible**, aunque el header
  del decomp (`bgAlpha[2]`) hable de cross-fade: con este video no se ve ninguno.
- **Destello en la ranura seleccionada**: al entrar/cambiar, dentro del cuadro amarillo aparece un **aro
  amarillo-verdoso** que crece y se apaga (pico a los 36.2–36.3 s, ya no está a los 36.6; ~0.4 s). Se repite en
  cada cambio de mapa (42.2, 49, 53, 59, 66, 69…).
- Las miniaturas del carrusel son **imágenes fijas** (no se mueven entre sí); el carrusel se desplaza al cambiar
  de ranura.

---

## 4. Comparación con lo que dibuja el port hoy

Base documental: `staging/B15_investigacion_stage_select.md` (síntoma "sale la columna de miniaturas pero no la
vista previa grande") + capturas `BT2-test/capturas/20261106_fontheight/0*.png` + **cuadros nuevos del port**
(`/tmp/opencode/portsel/p_*.png`, ver §7).

Elemento por elemento:

| Elemento de la referencia | ¿Está en el port? |
|---|---|
| Logo "Map Select" | **Sí** (mismo lugar; la fuente se ve distinta — más "ocre/dorada" — pero es un tema conocido del port) |
| Carrusel de miniaturas + ranura amarilla + flechas naranjas | **Sí** (mismas posiciones, mismas miniaturas: Dying Namek arriba, desierto abajo) |
| Imagen pequeña dentro de la ranura seleccionada | **Sí** (se ve la vista del escenario, misma forma con esquina recortada) |
| Banda morada con el nombre ("Wasteland") | **Sí** (misma posición) |
| Panel inferior (Random/Decide/Map Effect/ON/música/Change Music) | **Sí** (idéntico) |
| Icono ○ abajo a la izquierda | **Sí** |
| Objeto blanco con cuadradito rojo a la derecha | **Sí** |
| **Fondo grande desenfocado del escenario** | **NO** — en el port toda esa zona es **cielo azul con nubes** |
| **Cuadro nítido del escenario (el preview grande)** | **NO** — no aparece en ningún cuadro de los 12 s |
| Rótulo amarillo espejado dentro de la ranura | No lo vi en el port (puede ser que en la referencia sea un texto de modo) |

**Posiciones medidas (para comparar 1:1):** el layout del port **coincide con el original dentro de ±5 px de
juego** en logo, carrusel, ranura seleccionada, banda de nombre (y≈277..313 en ambos) y panel inferior
(y≈313..448 en ambos). O sea: **no es un problema de layout; lo único que falta es la imagen del escenario.**

Lo que falta, en coordenadas de juego: el fondo a pantalla completa (ambas capas: desenfocada + nítida
x 0..325, y 63..273 con esquinas redondeadas). En el port queda el cielo con nubes (que en la referencia está
**tapado** por esas capas).

---

## 5. Ultimate / proyectil en el video

Sí: hay **dos Kamehameha** en la pelea (mapa Kame House de noche / atardecer):

| Seg. | Qué se ve |
|---|---|
| 96 (1:36) | Rótulo azul "**Kamehameha**" arriba a la izquierda + orbe blanco cargándose en las manos |
| 97 (1:37) | Orbe blanco grande con rayos radiales |
| 98 (1:38) | Goku envuelto en resplandor blanco/naranja, rayos, icono amarillo de skill abajo a la izquierda |
| 99 (1:39) | **El rayo dispara**: cono de energía blanco/azulado con núcleo brillante que avanza a la derecha, chispas radiales, y aparece "**First Attack!**" + contador "5 HITS! 9120" |
| 100–101 | Contador "6 HITS! 9120", el rayo ya se apagó, Goku posando |
| 102 (1:42) | Segundo Kamehameha: vuelve a aparecer el rótulo y el orbe cargándose |
| 103 (1:43) | Segundo rayo disparando |
| 104 (1:44) | "4 HITS! 3320" |
| 105 (1:45) | "6 HITS! 9870" (fin del video) |

Es un **rayo/beam**, no una bola que viaja y explota: se enciende en las manos del personaje y se extiende de
golpe hacia la derecha, con núcleo blanco y "spikes". **El rival no se ve en el cuadro** (está fuera de cámara):
solo aparecen los contadores de golpes y daño. El rótulo del nombre del ataque aparece al **inicio** de la
animación y se va.

---

## 6. Otras cosas raras o de interés

- **Caídas de PCSX2** en las transiciones: a los 35 y 80 la barra de estado dice "Sin imagen" con 59 % de
  velocidad y 17–30 FPS. Es la máquina, no un glitch del juego.
- **Pantallas negras de carga**: 7–10, 24–27 y el fundido 69.5–69.9.
- **Menú de pausa** (83–85): los ítems del "1P PAUSE" se ven **semitransparentes** y el "FIGHT!" se lee a través;
  parece el *fade-in* de los textos del menú, no un glitch.
- El retrato del jugador 2 en el HUD de pelea se ve **oscuro/silueteado** en varios cuadros (80–101). No pude
  determinar en este video si es el personaje (Kid Gohan con ropa oscura) o un retrato que no cargó.
- **El video es VFR (~40 fps promedio)**: para medir ritmos hay que usar segundos, no cuadros.
- El barrido de entrada a Map Select (35.4–35.9, ~0.5 s) es un **giro circular** con el motivo del aro; no es un
  fundido.

---

## 7. Port vs referencia (corregido)

Los cuadros del port (`/tmp/opencode/portsel/p_001..p_360.png`, 12 s a ~30 fps) **NO son la selección de
personajes**: muestran **la misma pantalla de selección de mapa+música** de la referencia
(logo "Map Select", carrusel, **"Wasteland"**, `…Random…`, Map Effect ON, Change Music). Y están en el **mismo
estado exacto** que la referencia a los **36–41 s**: Wasteland seleccionado, Dying Namek en la ranura de arriba y
el desierto en la de abajo. O sea: se puede comparar A/B ese estado.

### 7.1 Ritmo de animación: lo que se puede y lo que no

**Medición hecha sobre los 360 cuadros del port:** la pantalla está **prácticamente congelada**.
- Diferencia media entre cuadros consecutivos: **0.27** (escala 0–255). El máximo en 12 s es **0.44**.
- Entre el cuadro 1 y el 360 (12 s) cambian **4.234 píxeles de 917.504 (>20 de diferencia): el 0,5 %**, y están
  todos localizados en: (a) la franja de los **dos triángulos naranjas** (~1.300 px arriba y ~1.400 px abajo),
  (b) una **ilustración del ángulo inferior izquierdo** (~7.400 px) que se desliza.
- El **preview** (zona x 327..457, y 170..267) cambia **2 píxeles** en 12 s ⇒ **está quieto**.
- No hay barrido de carrusel, ni paneo, ni corte, ni destello en esos 12 s.

**Conclusión honesta: con estos 12 s NO se puede medir un ratio de ritmo.** No hay ninguna animación de la
referencia que esté presente en el port para comparar (la imagen del escenario no existe, y el carrusel no se
movió). Tampoco se ve "acelerado" en estos cuadros: se ve **quieto**.

**Lo que la referencia sí permite cronometrar** (para comparar cuando haya cuadros del port):

| Animación de la referencia | Duración |
|---|---|
| Entrada a Map Select (barrido circular, de negro a cuadro completo) | **≈0.5–0.7 s** (36 cuadros del burst a ~40 fps: negro hasta el cuadro 5, se estabiliza en el 33) |
| Fundido de salida al apretar Decide | **≈0.4 s** (69.5 → 69.9) |
| Destello del aro en la ranura (crece y se apaga) | **≈0.4–0.5 s** |
| Corte del preview al cambiar de escenario | **1 cuadro** |
| Paneo lento del preview | ~3.6 px de juego/s (medido 37→38 s, con paralaje) |

**Para medir el ratio (lo que necesito del port):** cuadros densos (a 30 o 60 por segundo) del port en:
1. la **entrada** a la pantalla de mapa+música (desde el fundido hasta el cuadro completo),
2. el momento de **apretar arriba/abajo para cambiar de mapa** (carrusel + cambio del preview),
3. el momento de **apretar Decide** (transición a "NOW LOADING"),
4. si se puede, un cuadro fijo durante 5–10 s con el mapa elegido, para ver si el preview del port se mueve.
Con eso se cuenta en segundos y se saca el ratio exacto (p. ej. "la entrada dura 0.6 s en la referencia y 0.3 s
en el port").

### 7.1 bis. Un único dato medido de ritmo: el bucle decorativo del ángulo inferior izquierdo

Es el **único elemento animado comparable** entre los dos materiales.

- **Port**: el dibujo del ángulo inferior izquierdo es **periódico exacto cada 120 cuadros** de la captura.
  Comparé `p_001` contra los 360: los más parecidos son `p_121` (diff 1.3), `p_241` (1.4) y `p_360` (3.0),
  mientras los vecinos dan 10–20. **Período = 120 cuadros = 4.0 s** si la captura es realmente a 30 fps
  (1 cuadro = 1/30 s), como se indicó.
- **Referencia**: comparé la franja visible de esa esquina (video x 116..138, y 596..666) contra `t=43.0 s`:
  el diff crece hasta ~38 a los 3.4 s y **vuelve a un mínimo a los 4.0 s (6.04)** y sube otra vez después.
  **Período ≈ 4.0 s.**

**Lectura**: ese adorno **no va acelerado** (ratio ≈ 1.0). Es una medición **débil** (en la referencia la esquina
está casi tapada por el panel y el mínimo no llega a 0), así que **no alcanza para decir que la pantalla entera
va a ritmo normal** — de hecho el usuario la ve acelerada. Lo dejo como el único punto de anclaje medido hasta
ahora; el ratio real hay que sacarlo de las transiciones (§7.1).

### 7.2 Diferencia del preview (punto 4 del pedido)

En la referencia, en ese mismo estado (Wasteland):

- **Imagen grande del escenario** ocupando casi toda la pantalla (fondo desenfocado + cuadro nítido
  x 0..325, y 63..273, esquinas redondeadas), **en movimiento continuo**.
- En el port, esa misma zona es **cielo azul con nubes**: no hay ni el fondo desenfocado ni el cuadro nítido.
- **Marco**: en la referencia el cuadro nítido tiene esquinas redondeadas y un borde tenue; en el port no hay
  marco porque no hay cuadro.
- **Nombre del escenario**: **está en los dos** (banda morada "Wasteland", misma posición).
- **Miniaturas**: **están en los dos** (mismo carrusel, mismas imágenes, mismas flechas).
- **Música**: **está en los dos** (`…Random…` en ese estado).

O sea: de la pantalla de mapa+música, en el port **falta exactamente una cosa: la imagen del escenario (las dos
capas)**. Todo el resto del HUD está y en su lugar.

---

## 8. Qué NO pude determinar (no inventar)

- El texto amarillo espejado dentro de la ranura seleccionada: **ilegible**.
- Si el preview grande es un render 3D o un paneo sobre una imagen: **no se puede distinguir** con este video
  (el decomp dice que `bg[]` es una imagen `MTexRes`, lo cual favorece "imagen con paneo", pero no lo afirmo).
- Si hay cross-fade al cambiar de escenario: **no se vio** (corte de 1 cuadro). El `bgAlpha[2]` del header puede
  estar usándose para algo que no es visible a esta resolución.
- El ritmo del port en esta pantalla: **no medible** con los cuadros que hay (ver §7.1).
- Ritmo de la pelea (también reportada como acelerada): **no la medí** porque no hay cuadros del port de la
  pelea. La referencia tiene pelea de **80.5 a 105 s** (con "READY?" a los 81 y el menú de pausa a los 83–85),
  lo cual sirve para cronometrar cuando haya material del port.

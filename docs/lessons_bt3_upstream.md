# Lecciones de BT3-Decompiled (upstream) para las funciones difíciles

Resumen de lo que el proyecto original (`~/Escritorio/BT3-Decompiled-up`, clon de
<https://github.com/z3xox/BT3-Decompiled>) aprendió cerrando su último 24 %: de 75,6 % a **99,92 %**
del programa principal y 99,97 % del menú, con **0 INCLUDE_ASM**. FC: 330 commits, 257 ficheros C,
216.487 líneas, ~60 agentes en 8 tandas.

Lo de abajo está sacado de su `docs/decomp_guide.md` (§"Lessons from the night of 2026-10-08") y de
`docs/status.md`. Léelo cuando una función se resista: casi siempre es una de estas formas.

## Formas de fuente que hacen casar (cada una con el ejemplo suyo)

- **El contador propio de cada bucle.** Un contador reutilizado por un bucle posterior arrastra las
  preferencias de registro de ese bucle al anterior. Si el original tiene los punteros del bucle
  interno en registores `t` donde el tuyo usa `v1`/`a0`: dale a cada bucle su propio contador.
  (*ObjShadow_BuildPacket, ChrGrid_Build*)
- **La sentencia compartida, escrita en todos los brazos.** Bloques idénticos mantenidos separados
  aunque salten al mismo sitio: la sentencia detrás del `if`/`else` o del `switch` (un `(*count)++`,
  una cola común) estaba escrita **en cada brazo**. El compilador solo fusiona colas iguales después
  de asignar registros, así que `if (k == 2) {A} else if (k == 6) {A}` NO es `if (k == 2 || k == 6) {A}`.
  Y dos `case` comparten cola solo si acaban igual: escribe la cola entera en cada caso y **quita
  `default: return`**. (*ChrGrid_Build, EftEmit_Spawn, EftEmit_SpawnType0*)
- **El clamp como macro sobre la expresión entera** (`((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))`
  o `MAX(0, MIN(x, 255))`) da `move`, donde una ayudante `u8` en línea da `andi`. (*TextBox_DrawClip*)
- **Una ayudante de envoltura que recibe el `count`**, con `count - 1` escrito en cada uso, no un
  límite `hi` pasado como parámetro. Sonda: si `-fno-sched-spec` reproduce el original, busca esto.
  (*DcPass_WrapPos*)
- **`if`/`else` que asigna en los dos brazos** (`if (c) x = a; else x = b;`) NO es
  `x = b; if (c) x = a;`: el valor muere en la copia y es una cantidad local más.
  (*HudPrompt_UpdateCue*)
- **El caso barato como su brazo propio**: `if (paused) n = i; else { bucle }`, no
  `n = i; if (!paused) { bucle }`. (*HudGauge_UpdateAura*)
- **`for (;;) { ...; if (a || b || c || d) break; }`** no está rotado; un do-while con una cadena `&&`
  sí se rota por el medio. (*HudGauge_UpdateAura*)
- **Una local a nivel de función para una dirección** usada en algunas llamadas y la expresión
  escrita en las demás: un prólogo que salva un `sN` fuera de orden significa que ese registro se
  fija en el bloque de entrada. (*DcPass_DrawStatus*)
- **Una constante a través de una variable local al bloque** (`{ s32 w = 0x80; f(.., w, ..); }`)
  impide que la segunda pasada de CSE la comparta con la misma constante tras un bucle que siempre
  ejecuta una vez. (*DcPass_DrawStatus*)
- **Una comparación de flotantes muerta** (`if (a < K1 && f() > K2) { }`) conserva la llamada, no emite
  comparación y cuenta como instrucción para la asignación: mira la función hermana para ver la
  condición completa. (*EftRibbon_DrawKind1*)
- **El orden de declaración es el orden de los spill-slot**; los flotantes declarados delante de un
  vector, un parámetro no usado conservado. (*EftRibbon_DrawStrip, EftEmit_SpawnType0*)
- **Prototipos entre ficheros**: un `extern` local del llamante con punteros antes que flotantes
  cambia la preparación de argumentos de las demás llamadas del mismo `switch`. (*EftEmit_Spawn*)
- **Una vista alineada a 4 de una tabla** (`f32 color[3][4]`) para `y, z, w` mientras `x` comparte
  una dirección calculada para una llamada. (*EftRibbon_UpdateKeys*)
- **Inicializador de struct local**: miembros planos, un array y un struct que contiene un array dan
  tres calendarios distintos de las stores tras el `memset` inicial. (*EftEmit_SpawnType0*)
- **Copia el gemelo que ya casó**: las formas de sentencia y el orden de declaración de una función
  hermana que ya funciona. Es el atajo más barato y el que más usaron. (*EftZap_DrawQuad de
  EftLink_DrawQuad; DrawKind1 de DrawKind2*)

## Sondas del compilador (de sus volcados, inferidas)

- El pase de bucles eleva una constante mientras `threshold >= nº de instrucciones del bucle`; el
  umbral ronda **126-128** sin llamada y baja 3 por constante movida. Los `__asm__("")` vacíos son una
  sonda precisa de cuántas instrucciones le faltan a un bucle. Un contador muerto se elimina antes
  del pase y no explica un bucle más largo.
- Prioridad de asignación local: `floor_log2(refs) * refs / (muerte - nacimiento)` en posiciones de
  instrucción dentro del bloque. Los registros ligados por una forma de operación son una sola
  cantidad y sus referencias se suman.
- `p->f = p->f;` es una store que vive hasta la recarga y **no emite nada**: sirve para probar "una
  instrucción más al principio del bloque" (la primera pasada de planificación emite dos por ciclo).
- `la rD,sym+K(rS)` ensambla a `lui / addiu / addu` cuando `rD != rS`: no es prueba de una constante
  de dirección aparte.
- Sonda de empate de flotantes: `__asm__("" : "=f"(v) : "0"(v));` (`"=r"` fuerza `mfc1`/`mtc1`).

## El "FAKE MATCH" (su salida honesta para el residuo)

Byte-idéntico pero con una sentencia que no emite nada en el sitio donde no se conoce la forma real
del fuente. Va **marcada en el fuente** con `FAKE MATCH` y listada en `docs/status.md`:

- `ObjShadow_BuildPacket` (diez sentencias `__asm__("")` vacías)
- `DemoCam_Update` (`gDemoCam->fixed = gDemoCam->fixed;`)
- la variable de anchura de `DcPass_DrawStatus`
- `EftStreak_Draw` (usa `register ... __asm__("$0")`: solo el compilador PS2)
- `ObjShadow_BuildPacket`, `EftStreak_DrawScreen`, `EftStreak_Draw`, `EftBlade_AddPoint`,
  `Shen_DrawList`, `StgDepthTint_Draw`, `EftWater_DrawClippedFan` (8 en total)
- candidatos a stand-in: la variable de anchura de `DcPass_DrawStatus`, `base = &p0;` en
  `EftBolt_Shape`

**Regla suya, que copiamos**: un fake match se usa cuando todo lo demás falló, se marca en el fuente
con un comentario que dice qué se desconoce, y se apunta en `docs/status.md`. Nunca se presenta como
descompilación real.

## Lo que quedó en asm a propósito

Las cuatro rutinas que los autores del juego escribieron a mano en VU0 (`ObjSeam_TransformVtx`,
`StgVu_RotateZ/X/Y`) y las librerías (Sony, CRI, libc) por encima de 0x273CF0. Los 9 microprogramas
VU1 quedaron como **listados anotados** que ensamblan a los bytes originales.

## Para nosotros

- Nuestra copia local de BT3 (`~/Proyectos/BT3-Decompiled`) tiene el mismo volumen de código pero va
  107 commits por detrás: le faltan esas 45 funciones y toda esta documentación.
- El clon del upstream está en `~/Escritorio/BT3-Decompiled-up` (solo lectura). Sus documentos
  completos: `docs/systems/` (18 sistemas + los programas VU1), `docs/names/fields/*.tsv` (nombres de
  campo por struct), `docs/briefs_*.md` (los briefs por área) y `docs/decomp_guide.md` completo.

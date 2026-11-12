# B14 — Special Beam Cannon: PORT vs ORIGINAL (PCSX2)

Comparación visual cuadro a cuadro. **Sólo descripción de lo que se ve**; no se editó código.

## Material y método

| | PORT | ORIGINAL |
|---|---|---|
| Video | 1360x728, 60 fps, 6.85 s | 1360x728, 60 fps, 9.57 s |
| Cuadros extraídos | `p_001.png` … `p_103.png` (15 fps, 1 cuadro = 66.7 ms) | `o_001.png` … `o_143.png` (15 fps, idem) |
| Ventana | sólo título; **área de juego x 210→1148, y 35→728** | menú PCSX2 + barra de estado; **área de juego x 240→1130, y 62→728** |
| Personaje | Piccolo (verde/púrpura), de espaldas | Piccolo, de espaldas |

> Las dos ventanas están desplazadas ~30 px entre sí (x e y). Todas las coordenadas de abajo son
> **píxeles del cuadro de 1360x728**, sin descontar ese offset: para comparar posición conviene usar al
> personaje como referencia, no el borde de la ventana.
> Los 15 fps implican ±1 cuadro (±66 ms) en cada transición. Donde hace falta precisión pedí cuadros a 60 fps
> (ver el final).

## 1. Rango de timestamps de cada fase

### PORT (0.00 → 6.80 s)
| Fase | Desde | Hasta | Notas |
|---|---|---|---|
| Quieto / guardia | 0.00 | 0.40 | escenario de día |
| Aura de carga (chispas blancas/verdes) | 0.40 | 0.93 | personaje flexionando |
| Rótulo azul “Special Beam Cannon” | **0.93** | 3.73 | aparece arriba-izq. (≈ x 295, y 160) |
| Se forma la bola en las manos | 1.07 | 1.20 | |
| Aparecen los anillos dorados | 1.20 | 1.33 | |
| **“Hold” de carga** (bola + anillos + cables) | 1.33 | **2.47** | **1.14 s** |
| Flash blanco de disparo | **2.53** | 2.67 | 0.13 s, whiteout total |
| Pose de disparo **sin rayo** (bola + anillos + hélice suelta) | **2.67** | **3.67** | 1.00 s |
| Contador de daño “7000” | 3.47 | — | |
| Fin del efecto / restos flotando | 3.73 | 4.13 | hélice y arcos sueltos derivando |
| Escenario pasa a pleno día | **3.80** | — | |
| Quieto | 4.20 | 6.80 | |

### ORIGINAL (0.00 → 9.47 s)
| Fase | Desde | Hasta | Notas |
|---|---|---|---|
| Aura de carga | 0.00 | 0.87 | |
| Rótulo azul “Special Beam Cannon” | **0.87** | 3.73 | (≈ x 295, y 203) |
| Bola + primer anillo | 1.27 | 1.33 | |
| **“Hold” de carga** | 1.33 | **1.80** | **0.47 s** |
| Flash de disparo (bola gigante + cuña horizontal) | **1.87** | 2.07 | 0.27 s |
| **CUERPO DEL RAYO** | **2.13** | **3.53** | **1.40 s** |
| Rayo se retrae, queda un blob chico en la punta | 3.60 | 3.73 | |
| Contador de daño “5120” | 3.33 | — | |
| Pose de descarga | 3.73 | 3.87 | |
| Escenario pasa a pleno día | **3.87** | — | |
| Quieto | 4.00 | 9.47 | |

**Diferencia de ritmo global:** el ataque arranca en el mismo momento en los dos (rótulo 0.87 vs 0.93 s) y
termina en el mismo momento (efecto termina 3.67 vs 3.73 s), pero **el port estira la fase de carga 0.65 s
de más** (flash en 2.53 en vez de 1.87) y por eso su fase de “disparo” dura la mitad.

## 2. Tabla por elemento

| Elemento | ORIGINAL (PCSX2) | PORT | Veredicto |
|---|---|---|---|
| **Aura de carga** | halo verde/blanco pegado al cuerpo, chispas cortas | igual idea, pero **más chispas, más largas y más brillantes**; algunas cruzan el cuerpo | coincide con exceso |
| **Rótulo “Special Beam Cannon”** | azul, arriba-izq. (x≈295, y≈203) | idéntico, mismo lugar relativo (x≈295, y≈160) | coincide |
| **Bola / núcleo** | centro ≈ **(775, 372)**; núcleo blanco ~35 px de radio, halo amarillo | centro ≈ **(795, 375)**; núcleo blanco ~35-40 px, halo algo más grande y más “bloom” | coincide (port un poco más brillante) |
| **Anillo dorado alrededor de la bola** | anillo amarillo fino, r ≈ 130-135, semitransparente, con caída suave | anillo amarillo **más grueso y más marcado**, r ≈ 150, más opaco; se le suma un segundo anillo interior r ≈ 70 | difiere (más grueso/grande) |
| **Chispas radiales (spikes) desde la bola** | presentes, cortas, ~1-3 px de ancho, no llegan lejos | presentes pero **más largas, más cantidad y atraviesan al personaje** y el escenario | difiere |
| **Cables/relámpagos que salen de las manos** | 1-2 filamentos con quiebres, se van al borde izq. | los mismos filamentos, pero **más y mucho más largos** (cruzan toda la pantalla y forman una X) | difiere en cantidad/largo |
| **Flash de disparo** | bola blanca gigante + **cuña horizontal blanca** que sale de las manos y llega al borde izquierdo del cuadro (y 340-420) | bola blanca gigante + whiteout amarillo de pantalla completa; en el cuadro 2.533 hay **una banda horizontal brillante** de un solo cuadro, después desaparece | falta la cuña sostenida (el port no la mantiene más de 1 cuadro) |
| **CUERPO DEL RAYO** | **SÍ.** Cono/aguja amarilla con núcleo blanco, desde las manos (≈760, 372) hacia la izquierda y apenas hacia arriba, hasta la punta (x≈450 en 2.13 → x≈430 en 3.07). Largo ≈ 320-340 px. **Se afina con el tiempo**: 26 px de alto en x=600 (2.07) → 15 px (2.60) → 7-8 px (3.07) → 1-3 px (3.53) | **NO EXISTE en ningún cuadro.** Entre la bola (x≈795) y x≈650 no hay nada por encima de la luminancia de fondo: medido con umbral 170, las columnas x=650/700 dan *sin píxeles* o 1-5 px sueltos de chispa. Lo único que se ve a la izquierda de la bola es la hélice suelta y los cables | **FALTA** |
| **Hélice / resorte** (el “layer adicional”) | **sí, y siempre pegada a la punta del rayo**: 3-4 vueltas de ~25 px de diámetro, ocupa (435-540, 335-395) en 2.13; se achica hasta un blob de ~30 px en 3.60, cuando muere con el rayo | **sí se dibuja**, pero **desconectada**: flota a ~330 px a la izquierda de la bola. 2.67: enorme y abierta (≈200x180 px, dos vueltas grandes); 2.87-3.20: se achica y se corre a la izquierda; 3.27-3.67: estable en (430-540, 380-415), tamaño similar al del original, con un “tallo” curvo colgando | **está, pero suelta** (posición ≈ correcta, sin rayo que la una) |
| **Arcos / medialunas sueltas** | no existen | **sí**: medialunas abiertas de ~80-110 px, a la derecha de la hélice y girando (3.27: 540-620, 375-445; 3.73: 680-745, 375-430) | sobra |
| **Restos después del ataque** | el efecto muere completo en 3.73; no queda nada flotando | 3.73 → 4.13: la hélice y las medialunas **siguen dibujándose y se desplazan hacia la derecha** (x≈540 → 735 → 1225) con el personaje ya en pose de guardia | sobra |
| **Iluminación del escenario** | oscurece durante el ataque, vuelve a día en 3.87 | igual, vuelve a día en 3.80 | coincide |
| **HUD / daño** | contador **5120**, en (≈355, 288) | contador **7000**, en (≈360, 270) | no comparable (dificultad/variante distinta) |
| **Ícono inferior izquierdo (sol + glifo)** | alterna dos glifos (uno blanco tipo “vela” y uno con marca) | alterna los mismos dos glifos | coincide |

## 3. El “layer adicional”, en detalle (punto 4 del pedido)

El elemento que en el port **sí** se dibuja es la **hélice/resorte** (cuerpo de alambre enrollado, amarillo
intenso, con núcleo más claro): la misma forma que en el original envuelve la **punta** del rayo.

- En el original **nunca aparece sola**: siempre hay un rayo fino que la atraviesa y la conecta con las manos.
- En el port aparece sola y **en la posición correcta de la punta** (≈330 px a la izquierda de la bola,
  a la altura de las manos), lo que confirma que el punto de anclaje/largo del rayo se calcula bien.
- Evolución en el port: chica junto a la bola durante la carga (1.33-2.47) → **enorme y abierta** en 2.67 →
  se achica y deriva a la izquierda (2.87-3.20) → **quieta y desconectada** (3.27-3.67) → queda flotando y
  se va hacia la derecha (3.73-4.13).
- En el original: chica y pegada a la punta desde 2.13 hasta 3.53, y muere junto con el rayo en 3.60-3.73.

## 4. Diferencias concretas (qué dibuja el port que el original no, qué falta, en qué cuadros)

1. **Falta el cuerpo del rayo en TODO el ataque** (port 2.67 → 3.67, 1.00 s). El original lo tiene
   2.13 → 3.53 (1.40 s). Es la diferencia principal.
2. **Falta la cuña blanca del disparo**: original 1.87-2.07 (3 cuadros sostenidos, llega al borde izq.);
   el port sólo tiene una banda horizontal en **1 cuadro (2.533)** y después nada.
3. **Sobra el estado “bola flotando” durante 1.00 s** (port 2.67-3.67): después del flash el efecto vuelve
   a verse como en la carga (bola + anillos) mientras el personaje ya está en pose de disparo (comparar
   `port/p_056.png` 3.67 s con `orig/o_054.png` 3.53 s: misma cámara y misma pose, y al original le sale el rayo).
4. **La hélice queda desacoplada del origen**: port 2.87-3.67. En el original va siempre unida al rayo.
5. **Sobran medialunas/arcos sueltos** (port 3.27-4.13) que no existen en el original.
6. **Sobran restos que sobreviven al ataque** (port 3.73-4.13) cruzando la pantalla; en el original el efecto
   se apaga limpio en 3.73.
7. **Anillo dorado y chispas radiales más grandes/marcados** en el port (anillo r 150 vs 130-135; spikes que
   atraviesan al personaje).
8. **Timing**: la carga dura 0.65 s más en el port (flash 2.53 vs 1.87), aunque el ataque empieza y termina
   en el mismo instante.

## 5. Otras cosas raras (punto 6)

- **Cámara**: sin saltos ni glitches en ninguno de los dos. El original hace un barrido más amplio mientras
  dispara (el personaje queda a la derecha y se ve de perfil); el port hace un plano parecido pero el
  personaje está ~30-40 px más a la derecha y el encuadre se queda más cerrado durante el “hold”.
- **Transparencia/orden de capas**: en el port el anillo dorado y las medialunas se dibujan **por encima** del
  brazo y del torso del personaje (se ve el anillo pasar sobre el hombro y el brazo en `p_045`, `p_056`); en
  el original el anillo y el rayo quedan por detrás/del borde del brazo, sin atravesarlo de forma tan visible.
- **Bloom/exposición**: el port satura más (el whiteout de 2.53-2.67 lava toda la pantalla, incluido el HUD
  del suelo; en el original el HUD queda legible).
- **Daño distinto** (7000 vs 5120): no lo cuento como bug, pero conviene saber que los dos videos **no son de
  la misma situación exacta** (barras de vida y números distintos), así que no sirven para comparar daño.
- En el port, ya sin efecto (4.0-4.2), quedan dos pixelitos amarillos sueltos en el pasto (x≈600, y≈480 y
  x≈760, y≈425) que se van; en el original no queda nada.
- La luz del escenario, el polvo levantado y el resto de partículas coinciden razonablemente.

## 6. Lo que NO está verificado

- No miré los 103/143 cuadros uno por uno: usé las 9 hojas de contacto completas + ~20 cuadros a resolución
  total + un barrido numérico de luminancia (columnas x=470-740, filas 250-520) sobre port 2.00-4.60 s y
  orig 1.53-4.00 s.
- Con 15 fps no puedo decir en qué cuadro exacto (de 60) nace/muere el rayo ni si el port tiene 1, 2 o 3
  cuadros de cuña blanca. **Si hace falta, pedime:**
  - PORT `t = 2.500 → 2.750` a 60 fps (¿existe la cuña blanca? ¿hay algún cuadro con el cono?).
  - ORIG `t = 1.800 → 2.150` a 60 fps (transición flash → cono, para comparar forma exacta).
  - PORT `t = 3.600 → 3.800` a 60 fps (si la hélice existe como objeto independiente o es la punta del rayo).
- No comparé contra la variante Kamehameha en video: este informe es sólo Special Beam Cannon.
- Coincide con lo ya anotado en `constructo_rayo.md` (el cuerpo del rayo no se dibuja en el port y el sistema
  de slots sí crea la tarea); **este informe no aporta ni descarta causas**, sólo la evidencia visual.

# scripts/dev: herramientas de prueba (copiadas de /tmp el 2026-10-23, /tmp es volatil)
- start.sh / start_trace.sh: arrancan el juego bajo Xvfb :87 (binario en /tmp/bt2full_test, copiarlo antes desde
  port/build/full[_trace]/bt2full). Pad por archivo: BT3_PADFILE=/tmp/pad.txt.
- btn.sh <boton|none> <seg>: escribe el boton en /tmp/pad.txt. Build normal: 0.08 s = un paso. Build de trazas
  (~9 fps): usar 0.12 s o la pulsacion se pierde.
- look.sh: captura a /tmp/look.png.
- emp.py: reenvio automatico de arg0 (ver docs/audit y BT2-backups/m2c_pre_emp).
Trazas grabadas: BT2-backups/traces/menu1.bin (primer menu) y t.txt.bin (pelea + menu); el exe que las grabo es
BT2-backups/traces/bt2full_trace_build (trace_sym.py lo necesita para resolver nombres).

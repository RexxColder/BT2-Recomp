#!/usr/bin/env python3
"""xkey.py [-d :87] tecla[:segundos] ...  -> pulsa teclas con XTEST (para PCSX2 en Xvfb)."""
import sys, time
from Xlib import X, display, XK
from Xlib.ext import xtest
args = sys.argv[1:]; disp = ":87"
if args and args[0] == "-d": disp = args[1]; args = args[2:]
d = display.Display(disp)
root = d.screen().root
root.warp_pointer(100, 100)
for c in root.query_tree().children:   # sin WM: foco explicito a la ventana del juego
    try:
        if c.get_wm_name() and c.get_attributes().map_state == 2 and c.get_geometry().width > 100:
            c.set_input_focus(X.RevertToParent, X.CurrentTime); break
    except Exception: pass
d.sync()
for a in args:
    k, _, t = a.partition(":")
    if k == "wait": time.sleep(float(t or 1)); continue
    kc = d.keysym_to_keycode(XK.string_to_keysym(k))
    xtest.fake_input(d, X.KeyPress, kc); d.sync()
    time.sleep(float(t or 0.15))
    xtest.fake_input(d, X.KeyRelease, kc); d.sync()
    time.sleep(0.25)

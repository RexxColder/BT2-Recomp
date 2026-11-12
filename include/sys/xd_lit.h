#ifndef SYS_XD_LIT_H
#define SYS_XD_LIT_H

/* Agent D: read a .lit4 constant that stays in the assembly data (BT2 batch 1 keeps all data in asm).
   `extern const f32 D_x;` gives the same lwc1 %gp_rel load, but the compiler may then move that single
   instruction into a delay slot, which it never does with the li.s the original compiler wrote for a literal;
   this form is opaque to the delay-slot filler. */
#ifdef __mips__
#define LIT4(sym) ({ f32 _lit4; __asm__("lwc1 %0,%%gp_rel(" #sym ")($28)" : "=f"(_lit4)); _lit4; })
#else
#define LIT4(sym) (sym) /* PC: just the constant (the asm only keeps the PS2 build matching) */
#endif

#endif

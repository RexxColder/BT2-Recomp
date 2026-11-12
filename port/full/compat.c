/* Ayudantes de 64 bits / coma flotante del libgcc de la PS2 que clang x86-64 no trae. */
#include <stdint.h>
long long __divdi3(long long a, long long b) { return b ? a / b : 0; }
long long __muldi3(long long a, long long b) { return a * b; }
float __floatdisf(long long a) { return (float)a; }

/* Estado del VU0 en modo macro para el C del juego (include/vu0_state.h). vf0 es siempre (0,0,0,1). */
typedef struct { float vf[32][4]; float acc[4]; int32_t vi[16]; float q, i; uint32_t r; uint8_t mem[0x1000]; } Vu0StateHost;
Vu0StateHost gVu0 = { .vf = { [0] = { 0, 0, 0, 1 } } };


asm(".include \"labels.inc\"\n");;
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
extern M2C_UNK D_00366ED8 __attribute__((section(".data")));
s32 func_002EB490(s32 arg0)
{
  return *((s32 *) (((u8 *) (*((&D_00366ED8) + arg0))) + 4));
  arg0 = arg0 * 4;
}

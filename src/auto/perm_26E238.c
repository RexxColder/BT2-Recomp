
asm(".include \"labels.inc\"\n");;
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
s32 func_0026CD98(u8 *, u8 *);
void func_0026E238(void *arg0, u8 *arg1) /* asm 0x26E238 passes a1 (the label) through */
{
  s32 temp_v0;
  s32 temp_v1;
  temp_v0 = func_0026CD98((u8 *) (unsigned long) (*((u32 *) (((u8 *) arg0) + 4))), arg1);
  if (temp_v0 >= 0)
  {
    *((s32 *) (((u8 *) arg0) + 0xC)) = (temp_v1 = *((s32 *) (((u8 *) arg0) + 8)));
    *((s32 *) (((u8 *) arg0) + 8)) = temp_v0;
    *((u8 *) (((u8 *) arg0) + 0x11)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0x11))) | 0x50);
  }
}

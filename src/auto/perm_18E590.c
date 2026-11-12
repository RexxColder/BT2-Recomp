
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
extern s32 D_003877B8;
void func_0018E590(void *arg0, s32 arg1)
{
  void *temp_a0;
  u16 temp_v1;
  int new_var;
  new_var = arg1 & 0xFF;
  if ((((D_003877B8 != 0) && (arg0 != 0)) && ((temp_a0 = *((void **) (((u8 *) arg0) + 0x38)), 0 != temp_a0))) && ((temp_v1 = (unsigned long) (*((u16 *) (((u8 *) temp_a0) + 0x56))), (temp_v1 & 2) != 0)))
  {
    if (new_var)
    {
      *((u16 *) (((u8 *) temp_a0) + 0x56)) = (u16) (temp_v1 | 0x800);
      return;
    }
    *((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 0x38)))) + 0x56)) = (u16) (temp_v1 & 0xF7FF);
  }
}

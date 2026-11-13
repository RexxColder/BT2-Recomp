
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
extern M2C_UNK D_003B0F44 __attribute__((section(".data")));
void *func_002A3C08(s32 arg0)
{
  void *temp_v1;
  s32 new_var;
  M2C_UNK *new_var2;
  new_var = arg0;
  temp_v1 = &D_003B0F44;
  new_var2 = temp_v1 + (new_var * 4);
  temp_v1 = *new_var2;
  return temp_v1 + ((((u32) (*((u32 *) (((u8 *) temp_v1) + 4)))) >> 2) * 4);
}

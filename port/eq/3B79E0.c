
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
void func_003B79E0(s32 *arg0, s32 arg1)
{
  void *temp_a2;
  u16 *new_var;
  temp_a2 = (*arg0) + (arg1 * 0xBC);
  new_var = &(*((u16 *) (((u8 *) temp_a2) + 0x64)));
  if ((!((*(*((s32 **) (((u8 *) temp_a2) + 4)))) & 2)) && ((*((u16 *) (((u8 *) temp_a2) + 0))) & 4))
  {
    *((u16 *) (((u8 *) temp_a2) + 0x64)) = (u16) ((*new_var) | 4);
  }
}

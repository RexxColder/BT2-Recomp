
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
M2C_UNK func_101438(s32);
extern void *D_0042BB80 __attribute__((section(".data")));
void func_004190C0(void)
{
  s32 *new_var;
  s32 temp_v1;
  temp_v1 = *((s32 *) (((u8 *) D_0042BB80) + 0xD8));
  if (temp_v1 == 0)
  {
    func_101438(0x3E29);
    return;
  }
  func_101438((*(new_var = (s32 *) (((u8 *) ((*((s32 *) (((u8 *) D_0042BB80) + 0x140))) + (temp_v1 * 8))) + (-8)))) + 0x3E1E);
}


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
M2C_UNK func_2B8328(s32);
extern s32 D_00421384 __attribute__((section(".data")));
void *func_003B4B58(void)
{
  u8 *new_var;
  void *temp_s0;
  temp_s0 = D_00421384 + 0x20;
  new_var = (u8 *) temp_s0;
 do { func_2B8328(*((s32 *) (new_var + 0xC0))); } while (0);
  return temp_s0;
}

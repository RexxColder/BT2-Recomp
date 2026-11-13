
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
M2C_UNK func_26E9E8(void *);
extern void *D_00421C94 __attribute__((section(".data")));
void func_003BEC90(void)
{
  s32 temp_v0;
  s32 var_s0;
  s32 var_s1;
  void *temp_a0;
 do { temp_v0 = *((s32 *) (((u8 *) D_00421C94) + 0x54C)); } while (0);
  var_s1 = 0;
  if (temp_v0 > 0)
  {
    *((s32 *) (((u8 *) D_00421C94) + 0x54C)) = (s32) (temp_v0 - 1);
  }
  var_s0 = 1;
  do
  {
    var_s0 -= 1;
    temp_a0 = D_00421C94 + var_s1;
    var_s1 += 0x28;
    func_26E9E8(temp_a0 + 0x448);
  }
  while (var_s0 >= 0);
}

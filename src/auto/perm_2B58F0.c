
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
M2C_UNK Rand_Range(M2C_UNK *, M2C_UNK);
M2C_UNK func_002B5138(void *, M2C_UNK);
s32 func_002B7CB8(void *);
s32 func_002B8280();
M2C_UNK func_002CF0C8(s32, s32);
extern M2C_UNK D_00378558 __attribute__((section(".data")));
void func_002B58F0(void *arg0)
{
  s32 temp_a0;
  s32 temp_s0;
  s32 temp_s1;
  s32 temp_s2;
  s32 temp_v1;
  if (func_002B8280(arg0) != 1)
  {
    Rand_Range(&D_00378558, 1);
    return;
  }
  temp_s1 = *((s32 *) (((u8 *) arg0) + 0x7C));
  temp_s0 = *((s32 *) (((u8 *) arg0) + 0x80));
  temp_s2 = *((s32 *) (((u8 *) arg0) + 0x78));
  func_002B5138(arg0, 1);
  temp_a0 = func_002B7CB8(arg0);
  if (temp_s0 < temp_s1)
  {
    func_002CF0C8(temp_a0, temp_s2);
    temp_v1 = (*((s32 *) (((u8 *) arg0) + 0x80)) = (*((s32 *) (((u8 *) arg0) + 0x80))) + 1);
    *((s32 *) (((u8 *) arg0) + 0x7C)) = temp_v1;
  }
}

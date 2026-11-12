
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
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
void func_00124098(void *arg0)
{
  s32 temp_a0;
  void *var_s0;
  void *var_s1;
  var_s0 = arg0;
  var_s1 = var_s0 + 0x160;
  temp_a0 = var_s0 + 0xA9C;
  *((s32 *) (((u8 *) var_s1) + 0x28)) = 0;
  *((s32 *) (((u8 *) var_s1) + 0x2C)) = 0;
  var_s0 += 0xBE0;
  memset(temp_a0, 0, 0x100);
  *((s32 *) (((u8 *) var_s0) + 4)) = 0;
  *((s32 *) (((u8 *) var_s1) + 0x30)) = 0;
  *((s32 *) (((u8 *) var_s1) + 0x34)) = 0;
}

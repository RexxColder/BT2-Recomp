
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
s32 func_002C2FF0(M2C_UNK, M2C_UNK);
s32 func_002C3210();
M2C_UNK func_002D05E8(s32, M2C_UNK, M2C_UNK);
s32 func_002D19A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  void *temp_s0;
  if (func_002C3210(arg0) != 0)
  {
    return func_002C2FF0(0, 0xFF000129);
  }
  temp_s0 = arg0 + 0xD30;
  if (arg1 != 0)
  {
    *((s32 *) (((u8 *) temp_s0) + 0x2D4)) = arg1;
    *((s32 *) (((u8 *) temp_s0) + 0x2E4)) = arg2;
    *((s32 *) (((u8 *) temp_s0) + 0x2E8)) = arg3;
    func_002D05E8(arg0, 0xF, 5);
    func_002D05E8(arg0, 0x47, 0);
  }
  else
  {
    func_002D05E8(arg0, 0x47, 1);
    func_002D05E8(arg0, 0xF, 1);
    *((s32 *) (((u8 *) temp_s0) + 0x2E8)) = arg3;
    *((s32 *) (((u8 *) temp_s0) + 0x2E4)) = arg2;
    *((s32 *) (((u8 *) temp_s0) + 0x2D4)) = 0;
  }
  return 0;
}

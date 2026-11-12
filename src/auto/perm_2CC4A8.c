
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
M2C_UNK func_002CBDB8(s32);
void func_002CC4A8(void *arg0, s32 arg1)
{
  s32 temp_a0;
  void *temp_s0;
  temp_a0 = *((s32 *) (((u8 *) arg0) + 0x1FC0));
  temp_s0 = temp_a0 + 0x1128;
  if ((*((s32 *) (((u8 *) temp_s0) + 0x1C))) != 1)
  {
    func_002CBDB8(temp_a0 + 0x1198);
    *((s32 *) (((u8 *) temp_s0) + 0x1C)) = 1;
    *((s32 *) (((u8 *) temp_s0) + 0x20)) = arg1;
  }
}

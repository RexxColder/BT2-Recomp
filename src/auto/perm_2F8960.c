
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
s32 func_002F1ED0(s32);
s32 func_00300150(s32);
void func_002F8960(void *arg0)
{
  s32 temp_a0;
  s32 temp_v0;
  temp_v0 = *((s32 *) (((u8 *) arg0) + 8));
  if ((temp_v0 != 0) && (func_002F1ED0(temp_v0) == 4))
  {
    *((s16 *) (((u8 *) arg0) + 0x60)) = -1;
    *((s8 *) (((u8 *) arg0) + 1)) = 6;
  }
  temp_a0 = *((s32 *) (((u8 *) arg0) + 0x94));
  if ((temp_a0 != 0) && (func_00300150(temp_a0) == 3))
  {
    *((s16 *) (((u8 *) arg0) + 0x60)) = -1;
    *((s8 *) (((u8 *) arg0) + 1)) = 6;
  }
}

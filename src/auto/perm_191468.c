
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
s32 BtlScene_IsCharStopped(s32);
M2C_UNK func_00129C38(void *, void *);
M2C_UNK func_00190CA8(s32, void *, s32, M2C_UNK);
void func_00191468(void *arg0)
{
  s32 *temp_s2;
  s32 temp_v0;
  void *temp_s0;
  temp_s0 = *((void **) (((u8 *) arg0) + 0x38));
  temp_s2 = *((s32 **) (((u8 *) temp_s0) + 0));
  if (BtlScene_IsCharStopped(*temp_s2) == 0)
  {
    if (((*((u16 *) (((u8 *) arg0) + 8))) & 1) & 0xFFFF)
    {
      func_00129C38(temp_s0 + 0x820, arg0 + 0x10);
      func_00190CA8(*temp_s2, arg0, *((s32 *) (((u8 *) temp_s0) + 4)), 1);
      temp_v0 = *((s32 *) (((u8 *) temp_s0) + 0x30));
      if (!(temp_v0 & 0x20))
      {
        *((s32 *) (((u8 *) temp_s0) + 0x30)) = (s32) (temp_v0 | 0x20);
      }
    }
    if ((*((u16 *) (((u8 *) arg0) + 8))) & 4)
    {
      temp_v0 = *((s32 *) (((u8 *) temp_s0) + 0x30));
      *((s32 *) (((u8 *) temp_s0) + 0x30)) = (s32) (temp_v0 | 2);
    }
  }
}


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
void *func_00203CC0(M2C_UNK);
s32 func_0020C730(M2C_UNK);
s32 func_0020C780(M2C_UNK);
s32 func_0020C7D0(M2C_UNK);
s32 func_0020C820(M2C_UNK);
void func_0010F2A8(void *arg0, M2C_UNK arg1)
{
  s32 temp_v0_2;
  s32 temp_v0_3;
  s32 temp_v0_4;
  s32 new_var2;
  u8 *new_var;
  s32 temp_v0_5;
  void *temp_v0;
  temp_v0 = func_00203CC0(arg1);
  *((s32 *) (((u8 *) arg0) + 0x690)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x694)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x698)) = 0;
  if ((*((s32 *) (((u8 *) temp_v0) + 0x14))) != (*((s32 *) (((u8 *) temp_v0) + 0x18))))
  {
    *((s32 *) (((u8 *) arg0) + 0x694)) = (*((s32 *) (((u8 *) arg0) + 0x690)) = 1);
  }
  new_var = (u8 *) arg0;
  temp_v0_2 = func_0020C730(arg1);
  if (temp_v0_2 != 0)
  {
    *((s32 *) (new_var + 0x690)) = (s32) ((*((s32 *) (new_var + 0x690))) + 1);
    *((s32 *) (new_var + 0x694)) = (s32) ((*((s32 *) (new_var + 0x694))) | 2);
    if (temp_v0_2 < 0)
    {
      *((s32 *) (((u8 *) arg0) + 0x698)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x698))) | 2);
    }
  }
  temp_v0_3 = func_0020C820(arg1);
  if (temp_v0_3 != 0)
  {
    *((s32 *) (((u8 *) arg0) + 0x690)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x690))) + 1);
    *((s32 *) (new_var + 0x694)) = (s32) ((*((s32 *) (new_var + 0x694))) | 4);
    if (temp_v0_3 < 0)
    {
      *((s32 *) (new_var + 0x698)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x698))) | 4);
    }
  }
  temp_v0_4 = func_0020C780(arg1);
  new_var2 = temp_v0_4;
  if (new_var2 != 0)
  {
    *((s32 *) (new_var + 0x690)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x690))) + 1);
    *((s32 *) (((u8 *) arg0) + 0x694)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x694))) | 8);
    if (new_var2 < 0)
    {
      *((s32 *) (new_var + 0x698)) = (s32) ((*((s32 *) (new_var + 0x698))) | 8);
    }
  }
  temp_v0_5 = func_0020C7D0(arg1);
  if (temp_v0_5 != 0)
  {
    *((s32 *) (((u8 *) arg0) + 0x690)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x690))) + 1);
    *((s32 *) (new_var + 0x694)) = (s32) ((*((s32 *) (new_var + 0x694))) | 0x10);
    if (temp_v0_5 < 0)
    {
      *((s32 *) (((u8 *) arg0) + 0x698)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x698))) | 0x10);
    }
  }
}

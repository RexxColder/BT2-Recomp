
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
M2C_UNK func_00270A10(s32, s32 *, M2C_UNK, M2C_UNK);
M2C_UNK func_00270B40(s32, s32 *, M2C_UNK);
M2C_UNK func_00270C18(s32, M2C_UNK);
M2C_UNK func_00270D00(s32, s32 *);
void func_0026EFC8(void *arg0, s32 *arg1, s32 arg2)
{
  s32 *new_var2;
  void *new_var;
  new_var = arg0;
  if ((*arg1) >= 0)
  {
    new_var2 = &arg2;
    if ((*new_var2) & 1)
    {
      func_00270C18(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1);
    }
    if (arg2 & 2)
    {
      func_00270D00(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1);
    }
    if (arg2 & 4)
    {
      func_00270A10(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1, 2, 1);
    }
    if (arg2 & 8)
    {
      func_00270A10(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1, 2, 0);
    }
    if ((*new_var2) & 0x10)
    {
      func_00270B40(*((s32 *) (((u8 *) arg0) + 0x1C)), arg1, 0x40);
    }
    if ((*new_var2) & 0x20)
    {
      func_00270B40(*((s32 *) (((u8 *) arg0) + 0x1C)), arg1, 0x80);
    }
    if ((*new_var2) & 0x40)
    {
      func_00270B40(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1, 0x200);
    }
    if ((*new_var2) & 0x80)
    {
      func_00270B40(*((s32 *) (((u8 *) new_var) + 0x1C)), arg1, 0x400);
    }
    if ((*new_var2) & 0x100)
    {
      func_00270B40(*((s32 *) (((u8 *) arg0) + 0x1C)), arg1, 0x800);
    }
  }
}


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
M2C_UNK func_002F2108();
M2C_UNK func_0030A5F0();
void func_002F21D0(void *arg0)
{
  s32 new_var;
  func_002F2108(arg0);
  do
  {
    loop_1:
    func_0030A5F0();

    new_var = *((s8 *) (((u8 *) arg0) + 1));
    if (new_var != 1)
    {
      goto loop_1;
    }
  }
  while ((new_var = *((s32 *) (((u8 *) arg0) + 0x24))) != 0);
}

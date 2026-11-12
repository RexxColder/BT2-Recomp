
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
M2C_UNK func_002EA050(M2C_UNK *);
M2C_UNK func_0030C678(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0037EF78 __attribute__((section(".data")));
extern M2C_UNK D_0037EFA0 __attribute__((section(".data")));
void func_00301840(void *arg0, s32 arg1, s32 arg2)
{
  s32 temp_a0;
  void *temp_s0;
  if (arg0 == 0)
  {
    func_002EA050(&D_0037EF78);
    return;
  }
  temp_s0 = *((void **) (((u8 *) (*((void **) (((u8 *) arg0) + 4)))) + 4));
  temp_a0 = *((s32 *) (((u8 *) temp_s0) + 0xE8));
  if (((*((s8 *) (((u8 *) arg0) + 3))) < 2) || (temp_a0 == 0))
  {
    func_002EA050(&D_0037EFA0);
    return;
  }
  func_0030C678(temp_a0, arg1, arg2);
  *((s32 *) (((u8 *) temp_s0) + 0xEC)) = arg1;
  *((s32 *) (((u8 *) temp_s0) + 0xF0)) = arg2;
}

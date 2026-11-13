
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
M2C_UNK Rand_Range(M2C_UNK *);
M2C_UNK func_002B6700(M2C_UNK);
M2C_UNK func_002BBC08(void *);
M2C_UNK func_002BD2E0();
M2C_UNK func_002BD748(s32);
s32 func_002CE680(s32);
M2C_UNK func_002FFF90(s32);
extern M2C_UNK D_00378C78 __attribute__((section(".data")));
void func_002B7138(void *arg0)
{
  s32 temp_a0;
  s32 temp_a0_2;
  s32 temp_s1;
  temp_s1 = *((s32 *) (((u8 *) arg0) + 0x3C));
  if (temp_s1 != 0)
  {
    func_002BD2E0(arg0);
    *((s32 *) (((u8 *) arg0) + 4)) = 0;
    *((s32 *) (((u8 *) arg0) + 0x3C)) = 0;
    if (func_002CE680(temp_s1) != 0)
    {
      func_002B6700(-0x134);
      Rand_Range(&D_00378C78);
    }
    *((s32 *) (((u8 *) arg0) + 0x3C)) = temp_s1;
    func_002BBC08(arg0 + 0x284);
    func_002BBC08(arg0 + 0x2A4);
    *((s32 *) (((u8 *) arg0) + 0x2CC)) = 0;
    temp_a0 = *((s32 *) (((u8 *) arg0) + 0x40));
    if (temp_a0 != 0)
    {
      func_002BD748(temp_a0);
    }
    temp_a0_2 = *((s32 *) (((u8 *) arg0) + 0x48));
    if (temp_a0_2 != 0)
    {
      func_002FFF90(temp_a0_2);
    }
    if ((*((s32 *) (((u8 *) arg0) + 0x2E0))) == 0)
    {
      *((s32 *) (((u8 *) arg0) + 0x2E8)) = 0;
      *((s32 *) (((u8 *) arg0) + 0x2FC)) = -1;
      *((s32 *) (((u8 *) arg0) + 0x2E4)) = 0;
 do { } while (0);
      *((s32 *) (((u8 *) arg0) + 0x2DC)) = 0;
      *((s32 *) (((u8 *) arg0) + 0x300)) = 0;
      return;
    }
    *((s32 *) (((u8 *) arg0) + 0x2E8)) = 2;
  }
}

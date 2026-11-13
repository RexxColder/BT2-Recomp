
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
M2C_UNK Dma_AddZbuf(M2C_UNK, M2C_UNK);
M2C_UNK StgTint_CalcColor(void *);
M2C_UNK func_00281CF8(M2C_UNK, void *);
extern f32 D_003870C4;
extern s32 D_00387B00;
void func_00282268(void)
{
  void *temp_s0;
  f32 new_var;
  Dma_AddZbuf(0xE0, 1);
  temp_s0 = D_00387B00 + 0x120;
  StgTint_CalcColor(temp_s0);
  new_var = *((f32 *) (((u8 *) temp_s0) + 0xC));
  if (D_003870C4 < new_var)
  {
    func_00281CF8(0x44, temp_s0);
  }
  Dma_AddZbuf(0xE0, 0);
}

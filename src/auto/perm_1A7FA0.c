
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
s32 func_00126560();
M2C_UNK func_001A8060(s32);
M2C_UNK func_001A8220(s32);
extern void *D_003876A0;
void EftStruggle_Update(s32 arg0)
{
  if (!((*((s64 *) (((u8 *) D_003876A0) + 0x4D8))) & 0x100))
  {
    if (func_00126560() != 0)
    {
 do { func_001A8220(arg0); return; } while (0);
    }
    func_001A8060(arg0);
  }
}

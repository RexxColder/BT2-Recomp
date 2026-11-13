
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
s32 EftStage_IsDrawOn();
s32 func_00126588();
M2C_UNK func_00145DF0(s32, void *, s32);
M2C_UNK func_00146770(s32, s32);
extern void *D_003876A0;
extern void *gBtlStage;
extern void *gEftWeather;
void func_00146AA0(void *arg0)
{
  s32 temp_a0;
  s32 var_s1;
  s64 temp_v0;
  u32 var_s0;
  temp_a0 = func_00126588();
  var_s1 = *((s32 *) (((u8 *) arg0) + 0x38));
  var_s0 = *((u32 *) (((u8 *) gEftWeather) + 0x2A4));
  if ((*((u8 *) (((u8 *) gEftWeather) + 0x2B0))) != 0)
  {
    temp_v0 = *((s64 *) (((u8 *) D_003876A0) + 0x4D8));
    if (!(temp_v0 & 0x100))
    {
      if (temp_v0 & 2)
      {
        var_s0 = (u32) (((s32) (var_s0 + (var_s0 >> 0x1F))) >> 1);
        if (temp_a0 != 0)
        {
          if (var_s0 || gEftWeather)
          {
            var_s1 += 0x2D0;
          }
          else
          {
            var_s1 += 0x2D0;
          }
        }
        func_00145DF0(var_s1, gEftWeather + 0x240, (s32) var_s0);
      }
      else
      {
        func_00145DF0(var_s1, gEftWeather + 0x240, (s32) var_s0);
      }
    }
    if ((!((*((s32 *) (((u8 *) gBtlStage) + 8))) & 1)) && (EftStage_IsDrawOn() != 0))
    {
      func_00146770(var_s1, (s32) var_s0);
    }
  }
}

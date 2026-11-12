#include "common.h"

s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0018DE48(u8 *arg0, f32 fa, f32 fb);

void func_0018DE48(u8 *arg0, f32 fa, f32 fb) {
    f32 *s;
    f32 mn0;
    f32 mn1;
    f32 mn2;
    f32 mn3;
    f32 mx0;
    f32 mx1;
    f32 mx2;
    f32 mx3;

    s = (f32 *)arg0;
    mn0 = (fb < s[0]) ? fb : s[0];
    mn1 = (fb < s[1]) ? fb : s[1];
    mn2 = (fb < s[2]) ? fb : s[2];
    mn3 = (fb < s[3]) ? fb : s[3];
    Vec4_Set((s32)arg0, mn0, mn1, mn2, mn3);
    mx0 = (s[0] < fa) ? fa : s[0];
    mx1 = (s[1] < fa) ? fa : s[1];
    mx2 = (s[2] < fa) ? fa : s[2];
    mx3 = (s[3] < fa) ? fa : s[3];
    Vec4_Set((s32)arg0, mx0, mx1, mx2, mx3);
}

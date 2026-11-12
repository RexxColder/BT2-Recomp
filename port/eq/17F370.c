#include "common.h"

extern s32 rand();
s32 EftAura_IsVisible(s32 objId);
s32 EftAura_IsBurstRising(s32 objId);
s32 EftGlow_IsActive(s32 objId);
f32 Mathf_Asin(f32 x);
f32 atan2f(f32 y, f32 x);
void sceVu0Normalize(f32 *out, f32 *in);
void sceVu0UnitMatrix(f32 *m);
void sceVu0RotMatrixZ(f32 *out, f32 *in, f32 ang);
void sceVu0RotMatrixX(f32 *out, f32 *in, f32 ang);
void sceVu0RotMatrixY(f32 *out, f32 *in, f32 ang);
void sceVu0ApplyMatrix(f32 *out, f32 *m, f32 *v);
s32 func_00208DE8(s32 objId, f32 *out, s32 node);
void func_00312650(f32 *out, f32 *a, f32 *b);
void func_00312680(f32 *out, f32 *in, f32 scale);
s32 func_0017E8A0(u8 *work, u8 *bolt, s32 objId, s32 kind, s32 nodeA, s32 nodeB, f32 *dirA, f32 *dirB, f32 length, f32 follow);
void func_0017EE40(u8 *work, s32 a1, s32 nodeA, s32 nodeB, f32 *vel, f32 size, f32 follow);
extern u8 *gEftBoltPool;
extern f32 D_00384AEC, D_00384AF0, D_00384AF4, D_00384AF8, D_00384AFC, D_00384B00, D_00384B04;
extern f32 D_00384B08, D_00384B0C, D_00384B10, D_00384B14, D_00384B18, D_00384B1C, D_00384B20;
extern f32 D_00384B24, D_00384B28, D_00384B2C, D_00384B30, D_00384B34, D_00384B38, D_00384B3C;
extern f32 D_00384B40, D_00384B44, D_00384B48, D_00384B4C, D_00384B50;

void EftBolt_Spawn(u8 *work, s32 objId) {
    s32 kinds[3];
    s32 pick[4];
    f32 m[16];
    f32 a[4];
    f32 b[4];
    f32 dirA[4];
    f32 dirB[4];
    f32 posA[4];
    f32 posB[4];
    f32 d[4];
    f32 rot[4];
    f32 vel[4];
    s32 n = 0;
    s32 count = 0;
    s32 side = 0;
    s32 spawned = 0;
    u8 *bolt;
    u8 *rec;
    s32 kind, nodeA, nodeB, i, left;
    s32 *out;
    f32 ang, dAng, turn, follow, length, size;
    s32 lt4;

    if (EftAura_IsVisible(objId)) {
        if (EftAura_IsBurstRising(objId) || *(s32 *)(work + 0xE78) <= 0 || rand() % 12 == 0) {
            count = 3;
        }
    } else if (EftGlow_IsActive(objId)) {
        if (*(s32 *)(work + 0xE78) <= 0 || rand() % 6 == 0) {
            count = 3;
        }
    } else {
        if (*(s32 *)(work + 0xE78) <= 0 || rand() % 18 == 0) {
            count = 3;
        }
    }
    if (*(s32 *)(work + 0xE70) & 8) {
        if (rand() % 20 == 0) {
            count = 3;
        }
    }
    if (count > 0) {
        spawned = 1;
        side = *(s32 *)(work + 0xE74);
        *(s32 *)(work + 0xE74) = side ^ 1;
        if (*(s32 *)(work + 0xE7C) == 0) {
            for (i = 0; i < 4; i++) {
                pick[i] = i;
            }
            left = 4;
            out = (s32 *)(work + 0xE80);
            do {
                n = rand() % left;
                *out = pick[n];
                for (i = n; i < left - 1; i++) {
                    pick[i] = pick[i + 1];
                }
                left = left - 1;
                out++;
            } while (left != 0);
        }
        kinds[0] = *(s32 *)(work + 0xE80 + *(s32 *)(work + 0xE7C) * 4);
        if (side != 0) {
            kinds[1] = 5;
            kinds[2] = 6;
        } else {
            kinds[1] = 4;
            kinds[2] = 7;
        }
        n = 0;
    }
    while (count != 0) {
        bolt = 0;
        for (i = 0; i < 10; i++) {
            if (*(s32 *)(work + i * 0x90 + 0x1C) == 0) {
                bolt = work + i * 0x90 + 0x10;
                break;
            }
        }
        if (bolt == 0) {
            break;
        }
        kind = kinds[n % 3];
        n++;
        if (side == 0) {
            ang = *(f32 *)(work + 0xE90);
            dAng = -(((f32)rand() / D_00384AEC) * D_00384AF8 + D_00384AFC) * D_00384AF0;
            turn = -(((f32)rand() / D_00384AEC) * D_00384B00 + D_00384B04);
        } else {
            ang = *(f32 *)(work + 0xE94);
            dAng = (((f32)rand() / D_00384AEC) * D_00384B08 + D_00384B0C) * D_00384AF0;
            turn = ((f32)rand() / D_00384AEC) * D_00384B10 + D_00384B14;
        }
        rec = *(u8 **)(gEftBoltPool + 0x474) + kind * 20;
        nodeB = *(s32 *)(rec + 4);
        nodeA = *(s32 *)(rec + 0);
        follow = *(f32 *)(rec + 0xC) + *(f32 *)(rec + 0x10) * ((f32)rand() / D_00384AEC);
        if (EftGlow_IsActive(objId)) {
            length = *(f32 *)(rec + 8) * D_00384B18 * *(f32 *)(work + 0xEA0);
        } else {
            length = *(f32 *)(rec + 8) * *(f32 *)(work + 0xEA0);
        }
        lt4 = kind < 4;
        a[0] = 0.0f;
        a[1] = 1.0f;
        if (lt4) {
            a[2] = ((f32)rand() / D_00384AEC) * D_00384B1C + D_00384B20;
        } else {
            a[2] = ((f32)rand() / D_00384AEC) * D_00384B24 + D_00384B28;
        }
        ang = ang + dAng;
        a[3] = 1.0f;
        sceVu0Normalize(a, a);
        sceVu0UnitMatrix(m);
        if (D_00384AF0 <= ang) {
            ang = ang - D_00384AF4;
        } else if (ang <= D_00384B2C) {
            ang = ang + D_00384AF4;
        }
        sceVu0RotMatrixZ(m, m, ang);
        sceVu0ApplyMatrix(dirA, m, a);
        b[0] = 0.0f;
        b[1] = 1.0f;
        if (lt4) {
            b[2] = D_00384B30 - ((f32)rand() / D_00384AEC) * 0.25f;
        } else {
            b[2] = 0.5f - ((f32)rand() / D_00384AEC) * D_00384B34;
        }
        ang = ang + turn;
        b[3] = 1.0f;
        sceVu0Normalize(b, b);
        sceVu0UnitMatrix(m);
        if (D_00384AF0 <= ang) {
            ang = ang - D_00384AF4;
        } else if (ang <= D_00384B38) {
            ang = ang + D_00384AF4;
        }
        sceVu0RotMatrixZ(m, m, ang);
        sceVu0ApplyMatrix(dirB, m, b);
        func_00208DE8(objId, posA, nodeA);
        func_00208DE8(objId, posB, nodeB);
        func_00312650(d, posA, posB);
        sceVu0Normalize(d, d);
        sceVu0UnitMatrix(m);
        rot[0] = Mathf_Asin(d[1]);
        sceVu0RotMatrixX(m, m, rot[0]);
        rot[1] = atan2f(d[0], d[2]) + D_00384AF0;
        if (D_00384AF0 <= rot[1]) {
            rot[1] = rot[1] - D_00384AF4;
        }
        sceVu0RotMatrixY(m, m, rot[1]);
        sceVu0ApplyMatrix(dirA, m, dirA);
        sceVu0Normalize(dirA, dirA);
        sceVu0ApplyMatrix(dirB, m, dirB);
        sceVu0Normalize(dirB, dirB);
        if (!func_0017E8A0(work, bolt, objId, kind, nodeA, nodeB, dirA, dirB, length, follow)) {
            break;
        }
        func_00312680(vel, dirA, length * D_00384B3C);
        if (EftGlow_IsActive(objId)) {
            size = ((((f32)rand() / D_00384AEC) * 0.25f + D_00384B40) * D_00384B44) * *(f32 *)(work + 0xEA0) * D_00384B48;
        } else {
            size = ((((f32)rand() / D_00384AEC) * 0.25f + D_00384B4C) * D_00384B50) * *(f32 *)(work + 0xEA0);
        }
        func_0017EE40(work, 0, nodeA, nodeB, vel, size, follow);
        if (side != 0) {
            *(f32 *)(work + 0xE94) = ang;
        } else {
            *(f32 *)(work + 0xE90) = ang;
        }
        count = count - 1;
        side = side ^ 1;
    }
    if (spawned) {
        *(s32 *)(work + 0xE7C) = *(s32 *)(work + 0xE7C) + 1;
        if (*(s32 *)(work + 0xE7C) >= 4) {
            *(s32 *)(work + 0xE7C) = 0;
        }
    }
}

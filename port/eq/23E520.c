#include "common.h"

#define PF32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PS32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern f32 D_00386C80;
extern f32 D_00386C84;

s32 func_00217488(void *arg0);
s32 BtlObjXf_Update(void *arg0);
f32 func_001FA308(void *arg0);
s32 BtlObjAnim_QueryEvent(void *arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x0023E520: maps the state code from func_00217488 (self+0x9A0 flag, self+0x9B0 value vs two
   constants) to an output code v in -1..0x69. Codes 0x2D..0x6F index a 89-entry table; out of range goes
   through BtlObjXf_Update and a 204-entry table. Generated from jtbl_00371980/AF0/B10/B50 and the label blocks. */
s32 func_0023E520(u8 *self) {
    s32 v = -1;
    s32 c;
    s32 r;
    s32 idx2;
    s32 q;
    s32 s1;
    f32 f20;
    f32 f21;
    f32 f22;

    f20 = PF32(self, 0x9B0);
    s1 = PS32(self, 0x9A0);
    f21 = D_00386C80;
    c = func_00217488(self);
    f22 = D_00386C84;
    if ((u32)(c - 0x2D) < 0x59) {
        switch (c - 0x2D) {
            case 0:
            v = 0x61;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 41:
            case 42:
            case 43:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 68:
            case 69:
            case 70:
            case 83:
            case 84:
            case 87:
                r = BtlObjXf_Update(self);
                idx2 = r - 0x43;
                if ((u32)idx2 < 0xCC) {
                    switch (idx2) {
                        case 0:
                            v = 0x0;
                            break;
                        case 1:
                            v = 0x1;
                            break;
                        case 2:
                            v = 0x2;
                            break;
                        case 3:
                            v = 0x3;
                            break;
                        case 4:
                            v = 0x4;
                            break;
                        case 5:
                            v = 0x5;
                            break;
                        case 6:
                            v = 0x6;
                            break;
                        case 7:
                            v = 0x7;
                            break;
                        case 8:
                            v = 0x8;
                            break;
                        case 9:
                            v = 0x9;
                            break;
                        case 10:
                        case 11:
                        case 13:
                        case 14:
                        case 16:
                        case 17:
                        case 18:
                        case 19:
                        case 20:
                        case 22:
                        case 23:
                        case 25:
                        case 26:
                        case 28:
                        case 29:
                        case 31:
                        case 32:
                        case 34:
                        case 35:
                        case 37:
                        case 38:
                        case 40:
                        case 41:
                        case 43:
                        case 44:
                        case 46:
                        case 47:
                        case 49:
                        case 50:
                        case 52:
                        case 53:
                        case 55:
                        case 56:
                        case 58:
                        case 59:
                        case 60:
                        case 61:
                        case 62:
                        case 63:
                        case 64:
                        case 65:
                        case 66:
                        case 67:
                        case 68:
                        case 69:
                        case 70:
                        case 71:
                        case 72:
                        case 73:
                        case 74:
                        case 75:
                        case 76:
                        case 77:
                        case 78:
                        case 79:
                        case 80:
                        case 81:
                        case 82:
                        case 83:
                        case 84:
                        case 85:
                        case 86:
                        case 87:
                        case 88:
                        case 89:
                        case 90:
                        case 93:
                        case 94:
                        case 95:
                        case 96:
                        case 97:
                        case 98:
                        case 99:
                        case 100:
                        case 101:
                        case 102:
                        case 103:
                        case 104:
                        case 105:
                        case 106:
                        case 107:
                        case 108:
                        case 109:
                        case 110:
                        case 111:
                        case 112:
                        case 113:
                        case 114:
                        case 115:
                        case 116:
                        case 117:
                        case 118:
                        case 119:
                        case 120:
                        case 121:
                        case 122:
                        case 123:
                        case 124:
                        case 125:
                        case 126:
                        case 127:
                        case 128:
                        case 129:
                        case 130:
                        case 131:
                        case 132:
                        case 133:
                        case 134:
                        case 135:
                        case 136:
                        case 137:
                        case 138:
                        case 139:
                        case 140:
                        case 141:
                        case 142:
                        case 143:
                        case 144:
                        case 145:
                        case 146:
                        case 147:
                        case 148:
                        case 149:
                        case 150:
                        case 151:
                        case 152:
                        case 153:
                        case 154:
                        case 155:
                        case 156:
                        case 157:
                        case 158:
                        case 159:
                        case 160:
                        case 161:
                        case 162:
                        case 163:
                        case 164:
                        case 165:
                        case 166:
                        case 167:
                        case 168:
                        case 169:
                        case 170:
                        case 171:
                        case 172:
                        case 173:
                        case 174:
                        case 175:
                        case 176:
                        case 177:
                        case 178:
                        case 179:
                        case 180:
                        case 181:
                        case 182:
                        case 183:
                        case 184:
                        case 185:
                        case 186:
                        case 187:
                        case 188:
                        case 189:
                        case 190:
                        case 191:
                        case 192:
                        case 193:
                        case 194:
                        case 195:
                        case 196:
                        case 197:
                        case 198:
                        case 199:
                        case 200:
                        case 201:
                        case 202:
                            v = -1;
                            break;
                        case 12:
                            if (f20 < f21) v = 0x3D;
                            else if (f20 < f22) v = 0x3E;
                            else v = 0x3F;
                            break;
                        case 15:
                            if (f20 < f21) v = 0x40;
                            else if (f20 < f22) v = 0x41;
                            else v = 0x42;
                            break;
                        case 21:
                        case 24:
                            if (f20 < f21) v = 0x15;
                            else if (f20 < f22) v = 0x1A;
                            else v = 0x1F;
                            break;
                        case 27:
                            if (f20 < f21) v = 0x13;
                            else if (f20 < f22) v = 0x18;
                            else v = 0x1D;
                            break;
                        case 30:
                            if (f20 < f21) v = 0x14;
                            else if (f20 < f22) v = 0x19;
                            else v = 0x1E;
                            break;
                        case 33:
                            if (f20 < f21) v = 0x11;
                            else if (f20 < f22) v = 0x16;
                            else v = 0x1B;
                            break;
                        case 36:
                            if (f20 < f21) v = 0x12;
                            else if (f20 < f22) v = 0x17;
                            else v = 0x1C;
                            break;
                        case 39:
                            if (s1 != 0) v = 0x37;
                            else if (f20 < f22) v = 0x2D;
                            else v = 0x32;
                            break;
                        case 42:
                            if (s1 != 0) v = 0x35;
                            else if (f20 < f22) v = 0x2B;
                            else v = 0x30;
                            break;
                        case 45:
                            if (s1 != 0) v = 0x36;
                            else if (f20 < f22) v = 0x2C;
                            else v = 0x31;
                            break;
                        case 48:
                            if (s1 != 0) v = 0x33;
                            else if (f20 < f22) v = 0x29;
                            else v = 0x2E;
                            break;
                        case 51:
                            if (s1 != 0) v = 0x34;
                            else if (f20 < f22) v = 0x2A;
                            else v = 0x2F;
                            break;
                        case 54:
                            if (f20 < f21) v = 0x20;
                            else if (f20 < f22) v = 0x21;
                            else v = 0x22;
                            break;
                        case 57:
                            if (f20 < f21) v = 0x23;
                            else if (f20 < f22) v = 0x24;
                            else v = 0x25;
                            break;
                        case 91:
                            if (f20 < f21) v = 0x26;
                            else if (f20 < f22) v = 0x27;
                            else v = 0x28;
                            break;
                        case 92:
                            f20 = func_001FA308(self);
                            q = BtlObjAnim_QueryEvent(*(u8 **)(self + 0x1530), 1, 0, 1);
                            if (f20 < (f32)q) v = 0x10;
                            else v = 0x69;
                            break;
                        case 203:
                            v = 0x4D;
                            break;
                    }
                } else {
                    v = -1;
                }
                break;
            case 35:
            v = 0x62;
                break;
            case 36:
            v = 0x63;
                break;
            case 37:
            v = 0x64;
                break;
            case 38:
            v = 0x65;
                break;
            case 39:
            case 40:
            v = 0x66;
                break;
            case 44:
                r = BtlObjXf_Update(self);
                idx2 = r - 0x48;
                if ((u32)idx2 < 5) {
                    switch (idx2) {
                        case 0:
                            v = 0x43;
                            break;
                        case 1:
                            v = 0x44;
                            break;
                        case 2:
                            v = 0x45;
                            break;
                        case 3:
                            v = 0x46;
                            break;
                        case 4:
                            v = 0x47;
                            break;
                    }
                } else {
                    v = -1;
                }
                break;
            case 45:
            v = 0x48;
                break;
            case 46:
            v = 0x5D;
                break;
            case 47:
            v = 0x4F;
                break;
            case 48:
            v = 0x1F;
                break;
            case 55:
            v = 0x22;
                break;
            case 62:
            v = 0x4E;
                break;
            case 63:
            if (f20 < f21) v = 0xA;
            else if (f20 < f22) v = 0xB;
            else v = 0xC;
                break;
            case 64:
            v = 0x49;
                break;
            case 65:
            v = 0x67;
                break;
            case 66:
            v = 0x68;
                break;
            case 67:
                r = BtlObjXf_Update(self);
                idx2 = r - 0x6A;
                if ((u32)idx2 < 0xD) {
                    switch (idx2) {
                        case 0:
                            v = 0x3C;
                            break;
                        case 1:
                        case 2:
                        case 4:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 11:
                            v = -1;
                            break;
                        case 3:
                            v = 0x3A;
                            break;
                        case 6:
                            v = 0x3B;
                            break;
                        case 9:
                            v = 0x38;
                            break;
                        case 12:
                            v = 0x39;
                            break;
                    }
                } else {
                    v = -1;
                }
                break;
            case 71:
            if (f20 < f21) v = 0x50;
            else if (f20 < f22) v = 0x52;
            else v = 0x54;
                break;
            case 72:
            if (f20 < f21) v = 0x51;
            else if (f20 < f22) v = 0x53;
            else v = 0x55;
                break;
            case 73:
            v = 0x5B;
                break;
            case 74:
            v = 0x5C;
                break;
            case 75:
            v = 0x5E;
                break;
            case 76:
            v = 0x5F;
                break;
            case 77:
            v = 0x60;
                break;
            case 78:
            v = 0xD;
                break;
            case 79:
            v = 0xE;
                break;
            case 80:
            v = 0xF;
                break;
            case 81:
            case 82:
            case 88:
            v = 0x4A;
                break;
            case 85:
            case 86:
            v = 0x4C;
                break;
        }
    } else {
        r = BtlObjXf_Update(self);
        idx2 = r - 0x43;
        if ((u32)idx2 < 0xCC) {
            switch (idx2) {
                case 0:
                    v = 0x0;
                    break;
                case 1:
                    v = 0x1;
                    break;
                case 2:
                    v = 0x2;
                    break;
                case 3:
                    v = 0x3;
                    break;
                case 4:
                    v = 0x4;
                    break;
                case 5:
                    v = 0x5;
                    break;
                case 6:
                    v = 0x6;
                    break;
                case 7:
                    v = 0x7;
                    break;
                case 8:
                    v = 0x8;
                    break;
                case 9:
                    v = 0x9;
                    break;
                case 10:
                case 11:
                case 13:
                case 14:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 22:
                case 23:
                case 25:
                case 26:
                case 28:
                case 29:
                case 31:
                case 32:
                case 34:
                case 35:
                case 37:
                case 38:
                case 40:
                case 41:
                case 43:
                case 44:
                case 46:
                case 47:
                case 49:
                case 50:
                case 52:
                case 53:
                case 55:
                case 56:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                case 64:
                case 65:
                case 66:
                case 67:
                case 68:
                case 69:
                case 70:
                case 71:
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 93:
                case 94:
                case 95:
                case 96:
                case 97:
                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                case 112:
                case 113:
                case 114:
                case 115:
                case 116:
                case 117:
                case 118:
                case 119:
                case 120:
                case 121:
                case 122:
                case 123:
                case 124:
                case 125:
                case 126:
                case 127:
                case 128:
                case 129:
                case 130:
                case 131:
                case 132:
                case 133:
                case 134:
                case 135:
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                case 141:
                case 142:
                case 143:
                case 144:
                case 145:
                case 146:
                case 147:
                case 148:
                case 149:
                case 150:
                case 151:
                case 152:
                case 153:
                case 154:
                case 155:
                case 156:
                case 157:
                case 158:
                case 159:
                case 160:
                case 161:
                case 162:
                case 163:
                case 164:
                case 165:
                case 166:
                case 167:
                case 168:
                case 169:
                case 170:
                case 171:
                case 172:
                case 173:
                case 174:
                case 175:
                case 176:
                case 177:
                case 178:
                case 179:
                case 180:
                case 181:
                case 182:
                case 183:
                case 184:
                case 185:
                case 186:
                case 187:
                case 188:
                case 189:
                case 190:
                case 191:
                case 192:
                case 193:
                case 194:
                case 195:
                case 196:
                case 197:
                case 198:
                case 199:
                case 200:
                case 201:
                case 202:
                    v = -1;
                    break;
                case 12:
                    if (f20 < f21) v = 0x3D;
                    else if (f20 < f22) v = 0x3E;
                    else v = 0x3F;
                    break;
                case 15:
                    if (f20 < f21) v = 0x40;
                    else if (f20 < f22) v = 0x41;
                    else v = 0x42;
                    break;
                case 21:
                case 24:
                    if (f20 < f21) v = 0x15;
                    else if (f20 < f22) v = 0x1A;
                    else v = 0x1F;
                    break;
                case 27:
                    if (f20 < f21) v = 0x13;
                    else if (f20 < f22) v = 0x18;
                    else v = 0x1D;
                    break;
                case 30:
                    if (f20 < f21) v = 0x14;
                    else if (f20 < f22) v = 0x19;
                    else v = 0x1E;
                    break;
                case 33:
                    if (f20 < f21) v = 0x11;
                    else if (f20 < f22) v = 0x16;
                    else v = 0x1B;
                    break;
                case 36:
                    if (f20 < f21) v = 0x12;
                    else if (f20 < f22) v = 0x17;
                    else v = 0x1C;
                    break;
                case 39:
                    if (s1 != 0) v = 0x37;
                    else if (f20 < f22) v = 0x2D;
                    else v = 0x32;
                    break;
                case 42:
                    if (s1 != 0) v = 0x35;
                    else if (f20 < f22) v = 0x2B;
                    else v = 0x30;
                    break;
                case 45:
                    if (s1 != 0) v = 0x36;
                    else if (f20 < f22) v = 0x2C;
                    else v = 0x31;
                    break;
                case 48:
                    if (s1 != 0) v = 0x33;
                    else if (f20 < f22) v = 0x29;
                    else v = 0x2E;
                    break;
                case 51:
                    if (s1 != 0) v = 0x34;
                    else if (f20 < f22) v = 0x2A;
                    else v = 0x2F;
                    break;
                case 54:
                    if (f20 < f21) v = 0x20;
                    else if (f20 < f22) v = 0x21;
                    else v = 0x22;
                    break;
                case 57:
                    if (f20 < f21) v = 0x23;
                    else if (f20 < f22) v = 0x24;
                    else v = 0x25;
                    break;
                case 91:
                    if (f20 < f21) v = 0x26;
                    else if (f20 < f22) v = 0x27;
                    else v = 0x28;
                    break;
                case 92:
                    f20 = func_001FA308(self);
                    q = BtlObjAnim_QueryEvent(*(u8 **)(self + 0x1530), 1, 0, 1);
                    if (f20 < (f32)q) v = 0x10;
                    else v = 0x69;
                    break;
                case 203:
                    v = 0x4D;
                    break;
            }
        } else {
            v = -1;
        }
    }
    return v;
}

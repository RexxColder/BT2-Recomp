#include "common.h"
extern s32 func_00217488();
extern s32 BtlObjXf_Update();
extern s32 func_00240FA0();

s32 func_00125B98(u8 *a0) {
    s32 v;
    switch (func_00217488(a0)) {
    case 6: case 217: return 1;
    case 7: case 8: return 2;
    case 9: case 10: return 5;
    case 11: return 54;
    case 12: case 17: return 6;
    case 13: return 3;
    case 14: return 4;
    case 15: return 8;
    case 16: return 9;
    case 18: return 7;
    case 19: return 10;
    case 20: return 11;
    case 21: case 22: case 24: case 25: case 26: return 12;
    case 23: return 13;
    case 27: return 15;
    case 28: case 29: case 30: case 31: return 14;
    case 32: return 82;
    case 33: return 83;
    case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43: case 44: return 85;
    case 45: return 16;
    case 46: case 47: case 48: case 49: return 21;
    case 50: case 51: return 23;
    case 52: case 53: case 54: case 55: case 56: case 57: return 22;
    case 58: case 59: case 60: case 61: case 62: case 63: case 64: case 129: return 24;
    case 65: return 25;
    case 66: return 17;
    case 67: case 68: case 69: case 70: return 19;
    case 71: return 20;
    case 72: return 18;
    case 73: return 26;
    case 74: case 75: case 76: case 77: case 78: case 79: return 27;
    case 80: case 81: case 82: case 83: case 84: case 85: return 28;
    case 86: return 29;
    case 87: case 88: return 30;
    case 89: return 55;
    case 90: return 56;
    case 91: case 92: case 114: case 115: return 44;
    case 93: case 94: case 95: case 96: case 97: case 98: return 40;
    case 99: case 100: return 31;
    case 101: return 32;
    case 102: case 103: case 104: case 105: return 39;
    case 106: return 34;
    case 107: return 45;
    case 108: return 33;
    case 109: return 57;
    case 110: return 42;
    case 111: return 43;
    case 112: return 41;
    case 113: return 35;
    case 116: case 117: return 36;
    case 118: return 46;
    case 119: return 47;
    case 120: return 51;
    case 121: return 52;
    case 122: return 53;
    case 123: return 48;
    case 124: return 49;
    case 125: return 50;
    case 126: case 127: case 133: return 37;
    case 128: case 132: case 134: return 89;
    case 130: case 131: return 38;
    case 135: case 141: return 58;
    case 136: return 59;
    case 137: return 62;
    case 138: return 63;
    case 139: return 60;
    case 140: return 61;
    case 142: return 73;
    case 143: return 74;
    case 144: case 145: case 146: case 147: return 75;
    case 148: return 77;
    case 149: return 79;
    case 150: return 80;
    case 151: case 152: case 160: case 164: return 86;
    case 154: return 88;
    case 155: case 169: return 76;
    case 156: return 78;
    case 157: return 90;
    case 158: return 91;
    case 159: return 92;
    case 161: return 93;
    case 162: case 163: return 81;
    case 165: case 166: case 167: case 168: case 170: case 171: return 84;
    case 184: case 185: case 186: case 187: case 188: case 189: case 190: case 191: case 192: case 193: case 194: case 195: case 202: case 203: case 204: case 205: case 206: case 207: return 65;
    case 196: case 197: case 198: case 199: case 200: case 201: case 208: case 209: case 210: case 211: case 212: case 213: case 214: case 215: case 216: return 67;
    case 220: case 221: return 70;
    case 222: case 223: return 68;
    case 224: case 225: case 226: case 227: return 71;
    case 228: return 72;
    case 153:
        v = BtlObjXf_Update(a0);
        if (v < 210) return 85;
        if (v < 212) return 87;
        if (v >= 251) return 85;
        if (v >= 249) return 87;
        return 85;
    case 172: case 175: case 178: case 181:
        if (func_00240FA0(a0, 2) == 7) return 66;
        v = BtlObjXf_Update(a0);
        if (v == 284 || v == 290) return 1;
        return 64;
    case 173: case 176: case 179: case 182:
        if (func_00240FA0(a0, 3) == 7) return 66;
        v = BtlObjXf_Update(a0);
        if (v == 318 || v == 324) return 1;
        return 64;
    case 174: case 177: case 180: case 183:
        if (func_00240FA0(a0, 4) == 7) return 66;
        v = BtlObjXf_Update(a0);
        if (v == 352 || v == 358) return 1;
        return 64;
    case 218:
        v = func_00240FA0(a0, 0);
        goto tail;
    case 219:
        v = func_00240FA0(a0, 1);
    tail:
        if (v <= 0) return 68;
        if (v < 3) return 69;
        return (v == 4) ? 69 : 68;
    default: return 0;
    }
}
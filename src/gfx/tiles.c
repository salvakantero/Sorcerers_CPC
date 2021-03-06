#include "tiles.h"
// Data created with Img2CPC - (c) Retroworks - 2007-2017
// Palette uses hardware values.
const u8 g_palette[16] = { 0x4d, 0x54, 0x40, 0x4b, 0x44, 0x55, 0x57, 0x53, 0x5c, 0x4c, 0x4e, 0x47, 0x56, 0x52, 0x5e, 0x4a };

u8* const g_tileset[120] = { 
	g_tiles_000, g_tiles_001, g_tiles_002, g_tiles_003, g_tiles_004, g_tiles_005, g_tiles_006, g_tiles_007, g_tiles_008, g_tiles_009, g_tiles_010, g_tiles_011, g_tiles_012, g_tiles_013, g_tiles_014, g_tiles_015, g_tiles_016, g_tiles_017, g_tiles_018, g_tiles_019, g_tiles_020, g_tiles_021, g_tiles_022, g_tiles_023, g_tiles_024, g_tiles_025, g_tiles_026, g_tiles_027, g_tiles_028, g_tiles_029, g_tiles_030, g_tiles_031, g_tiles_032, g_tiles_033, g_tiles_034, g_tiles_035, g_tiles_036, g_tiles_037, g_tiles_038, g_tiles_039, g_tiles_040, g_tiles_041, g_tiles_042, g_tiles_043, g_tiles_044, g_tiles_045, g_tiles_046, g_tiles_047, g_tiles_048, g_tiles_049, g_tiles_050, g_tiles_051, g_tiles_052, g_tiles_053, g_tiles_054, g_tiles_055, g_tiles_056, g_tiles_057, g_tiles_058, g_tiles_059, g_tiles_060, g_tiles_061, g_tiles_062, g_tiles_063, g_tiles_064, g_tiles_065, g_tiles_066, g_tiles_067, g_tiles_068, g_tiles_069, g_tiles_070, g_tiles_071, g_tiles_072, g_tiles_073, g_tiles_074, g_tiles_075, g_tiles_076, g_tiles_077, g_tiles_078, g_tiles_079, g_tiles_080, g_tiles_081, g_tiles_082, g_tiles_083, g_tiles_084, g_tiles_085, g_tiles_086, g_tiles_087, g_tiles_088, g_tiles_089, g_tiles_090, g_tiles_091, g_tiles_092, g_tiles_093, g_tiles_094, g_tiles_095, g_tiles_096, g_tiles_097, g_tiles_098, g_tiles_099, g_tiles_100, g_tiles_101, g_tiles_102, g_tiles_103, g_tiles_104, g_tiles_105, g_tiles_106, g_tiles_107, g_tiles_108, g_tiles_109, g_tiles_110, g_tiles_111, g_tiles_112, g_tiles_113, g_tiles_114, g_tiles_115, g_tiles_116, g_tiles_117, g_tiles_118, g_tiles_119
};
// Tile g_tiles_000: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_000[2 * 4] = {
	0x33, 0x33,
	0x33, 0x62,
	0x33, 0x33,
	0x62, 0x33
};

// Tile g_tiles_001: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_001[2 * 4] = {
	0x33, 0x33,
	0x33, 0x73,
	0x33, 0x33,
	0x73, 0x33
};

// Tile g_tiles_002: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_002[2 * 4] = {
	0x33, 0x33,
	0x33, 0x73,
	0x66, 0x99,
	0x26, 0x91
};

// Tile g_tiles_003: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_003[2 * 4] = {
	0x33, 0xc1,
	0x33, 0xc1,
	0x33, 0x81,
	0x62, 0x83
};

// Tile g_tiles_004: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_004[2 * 4] = {
	0x42, 0x33,
	0x42, 0x33,
	0x42, 0x33,
	0x83, 0x91
};

// Tile g_tiles_005: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_005[2 * 4] = {
	0x33, 0x33,
	0x33, 0x77,
	0x33, 0x33,
	0x77, 0x33
};

// Tile g_tiles_006: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_006[2 * 4] = {
	0x33, 0x33,
	0x33, 0x66,
	0xc4, 0x66,
	0xdd, 0xdd
};

// Tile g_tiles_007: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_007[2 * 4] = {
	0x3c, 0x3c,
	0x3c, 0x38,
	0x3c, 0x3c,
	0x38, 0x3c
};

// Tile g_tiles_008: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_008[2 * 4] = {
	0x3c, 0x3c,
	0x3c, 0x79,
	0x3c, 0x3c,
	0x79, 0x3c
};

// Tile g_tiles_009: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_009[2 * 4] = {
	0x3c, 0x3c,
	0x3c, 0x6c,
	0x3c, 0x3c,
	0x6c, 0x3c
};

// Tile g_tiles_010: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_010[2 * 4] = {
	0x38, 0x3c,
	0x60, 0x94,
	0x38, 0x3c,
	0x60, 0xc0
};

// Tile g_tiles_011: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_011[2 * 4] = {
	0x3c, 0x90,
	0x3c, 0xd0,
	0x3c, 0xd0,
	0x68, 0xb4
};

// Tile g_tiles_012: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_012[2 * 4] = {
	0x94, 0x3c,
	0x94, 0x3c,
	0x94, 0x3c,
	0x60, 0x3c
};

// Tile g_tiles_013: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_013[2 * 4] = {
	0x3c, 0x3c,
	0x3c, 0x79,
	0x6c, 0x9c,
	0x2c, 0x94
};

// Tile g_tiles_014: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_014[2 * 4] = {
	0x03, 0x03,
	0x81, 0x81,
	0x43, 0x43,
	0x43, 0x43
};

// Tile g_tiles_015: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_015[2 * 4] = {
	0x3c, 0x38,
	0x3c, 0x64,
	0x38, 0xc8,
	0x38, 0xcc
};

// Tile g_tiles_016: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_016[2 * 4] = {
	0x30, 0x3c,
	0xcc, 0x94,
	0xc4, 0xea,
	0xc8, 0xea
};

// Tile g_tiles_017: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_017[2 * 4] = {
	0x07, 0xc3,
	0x85, 0x03,
	0x48, 0xc3,
	0x81, 0xc0
};

// Tile g_tiles_018: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_018[2 * 4] = {
	0x03, 0xc2,
	0x03, 0xc2,
	0xc3, 0xc0,
	0xc0, 0x42
};

// Tile g_tiles_019: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_019[2 * 4] = {
	0x0f, 0x0f,
	0x0f, 0x5f,
	0x0f, 0x0f,
	0x5f, 0x0f
};

// Tile g_tiles_020: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_020[2 * 4] = {
	0x0f, 0x0f,
	0xff, 0xaf,
	0xc0, 0xc0,
	0x03, 0x03
};

// Tile g_tiles_021: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_021[2 * 4] = {
	0xcc, 0xff,
	0xdd, 0x7f,
	0xbf, 0x7f,
	0x5f, 0xea
};

// Tile g_tiles_022: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_022[2 * 4] = {
	0xcc, 0xf3,
	0xd9, 0x73,
	0xb3, 0x73,
	0x5b, 0xe2
};

// Tile g_tiles_023: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_023[2 * 4] = {
	0xcc, 0xfc,
	0xdc, 0x7c,
	0xbc, 0xf4,
	0x5e, 0xe8
};

// Tile g_tiles_024: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_024[2 * 4] = {
	0x0f, 0x0f,
	0x0f, 0x0b,
	0x0f, 0x0f,
	0x0b, 0x0f
};

// Tile g_tiles_025: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_025[2 * 4] = {
	0x0f, 0x0f,
	0x0f, 0x4e,
	0x0f, 0x0f,
	0x4e, 0x0f
};

// Tile g_tiles_026: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_026[2 * 4] = {
	0x4c, 0xdd,
	0x4c, 0xdd,
	0x4c, 0xdd,
	0x4c, 0xdd
};

// Tile g_tiles_027: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_027[2 * 4] = {
	0xcc, 0x8c,
	0xee, 0x8c,
	0xcc, 0x8c,
	0xee, 0x8c
};

// Tile g_tiles_028: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_028[2 * 4] = {
	0x3c, 0x3c,
	0x60, 0x90,
	0x68, 0x3c,
	0x60, 0xc0
};

// Tile g_tiles_029: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_029[2 * 4] = {
	0x3c, 0x3c,
	0x6c, 0x94,
	0xc8, 0xc8,
	0xd5, 0xd5
};

// Tile g_tiles_030: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_030[2 * 4] = {
	0x03, 0x03,
	0x81, 0x81,
	0x57, 0x4b,
	0x43, 0x43
};

// Tile g_tiles_031: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_031[2 * 4] = {
	0x03, 0x03,
	0xc0, 0xc1,
	0x0f, 0xc1,
	0x4a, 0x83
};

// Tile g_tiles_032: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_032[2 * 4] = {
	0x0f, 0x1a,
	0x0f, 0x64,
	0x1a, 0xc8,
	0x1a, 0xcc
};

// Tile g_tiles_033: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_033[2 * 4] = {
	0x30, 0x0f,
	0xcc, 0x85,
	0xc4, 0xea,
	0xc8, 0xea
};

// Tile g_tiles_034: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_034[2 * 4] = {
	0x0f, 0x0f,
	0x0f, 0x60,
	0x1a, 0xc8,
	0xd5, 0xd5
};

// Tile g_tiles_035: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_035[2 * 4] = {
	0x48, 0xc0,
	0xc0, 0x81,
	0xc0, 0xc0,
	0x85, 0xee
};

// Tile g_tiles_036: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_036[2 * 4] = {
	0xc0, 0x84,
	0x03, 0xc0,
	0xc0, 0xc0,
	0x07, 0xc2
};

// Tile g_tiles_037: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_037[2 * 4] = {
	0x81, 0x03,
	0x85, 0x46,
	0x81, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_038: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_038[2 * 4] = {
	0x03, 0x42,
	0xaf, 0xc2,
	0x03, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_039: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_039[2 * 4] = {
	0x81, 0xc0,
	0x81, 0x42,
	0x81, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_040: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_040[2 * 4] = {
	0xc8, 0xca,
	0xcf, 0xcf,
	0xc5, 0xc7,
	0xc0, 0xc0
};

// Tile g_tiles_041: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_041[2 * 4] = {
	0xc8, 0x4a,
	0xca, 0x4a,
	0xc0, 0x4a,
	0xc0, 0xc0
};

// Tile g_tiles_042: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_042[2 * 4] = {
	0xc5, 0xcf,
	0xc0, 0xc0,
	0xc5, 0xcb,
	0xc0, 0xc0
};

// Tile g_tiles_043: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_043[2 * 4] = {
	0xc3, 0xc3,
	0xc0, 0xc0,
	0xc3, 0x83,
	0xc0, 0xc0
};

// Tile g_tiles_044: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_044[2 * 4] = {
	0x03, 0x42,
	0xc0, 0xc0,
	0x03, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_045: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_045[2 * 4] = {
	0x33, 0xc0,
	0x62, 0xd9,
	0xc4, 0xf3,
	0xd1, 0xf3
};

// Tile g_tiles_046: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_046[2 * 4] = {
	0x91, 0xc0,
	0xe2, 0xf3,
	0xb3, 0xb3,
	0xf3, 0xf3
};

// Tile g_tiles_047: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_047[2 * 4] = {
	0xc0, 0x33,
	0x33, 0x91,
	0xb3, 0x62,
	0x73, 0x62
};

// Tile g_tiles_048: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_048[2 * 4] = {
	0xc4, 0xb3,
	0xd1, 0xf3,
	0x62, 0xb3,
	0x33, 0xc0
};

// Tile g_tiles_049: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_049[2 * 4] = {
	0xf3, 0xf3,
	0xf3, 0x73,
	0xf3, 0x91,
	0xc0, 0x62
};

// Tile g_tiles_050: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_050[2 * 4] = {
	0xb3, 0x62,
	0x73, 0x62,
	0xb3, 0x91,
	0xc0, 0x33
};

// Tile g_tiles_051: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_051[2 * 4] = {
	0xc4, 0xf3,
	0x62, 0xb3,
	0xc4, 0xf3,
	0xc4, 0xf3
};

// Tile g_tiles_052: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_052[2 * 4] = {
	0xf3, 0xf3,
	0xf3, 0x73,
	0xf3, 0xf3,
	0xb3, 0xf3
};

// Tile g_tiles_053: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_053[2 * 4] = {
	0x73, 0x62,
	0xb3, 0x91,
	0x73, 0x62,
	0xb3, 0x62
};

// Tile g_tiles_054: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_054[2 * 4] = {
	0xf3, 0xb3,
	0xe3, 0xf3,
	0xd7, 0xd3,
	0xe3, 0x73
};

// Tile g_tiles_055: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_055[2 * 4] = {
	0xd5, 0xd5,
	0xd5, 0x95,
	0x95, 0x95,
	0xea, 0xea
};

// Tile g_tiles_056: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_056[2 * 4] = {
	0x30, 0x30,
	0xb0, 0x78,
	0x30, 0x30,
	0x78, 0xb0
};

// Tile g_tiles_057: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_057[2 * 4] = {
	0x30, 0x30,
	0x34, 0xb0,
	0x70, 0x30,
	0x30, 0x30
};

// Tile g_tiles_058: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_058[2 * 4] = {
	0x94, 0x78,
	0x94, 0xf0,
	0x68, 0xb0,
	0x3c, 0xc0
};

// Tile g_tiles_059: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_059[2 * 4] = {
	0xf0, 0x60,
	0xb0, 0x60,
	0xb0, 0x94,
	0xc0, 0x3c
};

// Tile g_tiles_060: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_060[2 * 4] = {
	0x68, 0x78,
	0x94, 0xf0,
	0x94, 0x78,
	0x94, 0xf0
};

// Tile g_tiles_061: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_061[2 * 4] = {
	0xb0, 0x94,
	0xf0, 0x60,
	0xb0, 0x60,
	0xf0, 0x60
};

// Tile g_tiles_062: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_062[2 * 4] = {
	0x3c, 0x68,
	0x3c, 0x94,
	0x3c, 0xd0,
	0x68, 0x78
};

// Tile g_tiles_063: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_063[2 * 4] = {
	0x94, 0x3c,
	0xe0, 0x3c,
	0xe0, 0x3c,
	0xb0, 0x94
};

// Tile g_tiles_064: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_064[2 * 4] = {
	0x68, 0x68,
	0x60, 0x60,
	0x68, 0x68,
	0x60, 0x60
};

// Tile g_tiles_065: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_065[2 * 4] = {
	0x3c, 0xc0,
	0x68, 0xcc,
	0x68, 0x8c,
	0x68, 0xcc
};

// Tile g_tiles_066: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_066[2 * 4] = {
	0xc0, 0x94,
	0xcc, 0x48,
	0x84, 0x48,
	0x8c, 0xc0
};

// Tile g_tiles_067: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_067[2 * 4] = {
	0x3c, 0x68,
	0x3c, 0xc4,
	0x68, 0xcc,
	0x68, 0xc8
};

// Tile g_tiles_068: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_068[2 * 4] = {
	0xc0, 0x3c,
	0x8c, 0x94,
	0x84, 0x48,
	0xc0, 0x48
};

// Tile g_tiles_069: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_069[2 * 4] = {
	0x68, 0x8c,
	0x68, 0xcc,
	0x68, 0x8c,
	0x68, 0x84
};

// Tile g_tiles_070: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_070[2 * 4] = {
	0x84, 0x48,
	0x0c, 0xc0,
	0x48, 0x48,
	0x84, 0xc0
};

// Tile g_tiles_071: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_071[2 * 4] = {
	0x68, 0xcc,
	0x68, 0xcc,
	0x68, 0x8c,
	0x68, 0x84
};

// Tile g_tiles_072: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_072[2 * 4] = {
	0x84, 0x48,
	0x84, 0xc0,
	0x48, 0x48,
	0x84, 0xc0
};

// Tile g_tiles_073: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_073[2 * 4] = {
	0x3c, 0x3c,
	0x3c, 0x60,
	0x38, 0xc8,
	0xd5, 0xd5
};

// Tile g_tiles_074: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_074[2 * 4] = {
	0x64, 0xc8,
	0xc0, 0xcc,
	0xc8, 0xd5,
	0xd5, 0xc0
};

// Tile g_tiles_075: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_075[2 * 4] = {
	0xc8, 0xea,
	0xff, 0xc0,
	0xc0, 0xc0,
	0xd5, 0xd5
};

// Tile g_tiles_076: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_076[2 * 4] = {
	0xdc, 0xfc,
	0x9c, 0x3c,
	0xbc, 0x78,
	0x38, 0x30
};

// Tile g_tiles_077: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_077[2 * 4] = {
	0xfc, 0x3c,
	0x3c, 0xb0,
	0xf0, 0x30,
	0x30, 0x60
};

// Tile g_tiles_078: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_078[2 * 4] = {
	0xdc, 0xbc,
	0xbc, 0x78,
	0xbc, 0x38,
	0xbc, 0xb0
};

// Tile g_tiles_079: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_079[2 * 4] = {
	0xbc, 0xb0,
	0xbc, 0xb0,
	0xf8, 0xb0,
	0x78, 0x60
};

// Tile g_tiles_080: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_080[2 * 4] = {
	0x09, 0x03,
	0x03, 0x0f,
	0x07, 0x4b,
	0x07, 0xc3
};

// Tile g_tiles_081: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_081[2 * 4] = {
	0x03, 0x84,
	0x0f, 0xc0,
	0xc3, 0x4a,
	0x83, 0xc2
};

// Tile g_tiles_082: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_082[2 * 4] = {
	0xc0, 0xc0,
	0x42, 0x83,
	0xc0, 0xc0,
	0x4b, 0x42
};

// Tile g_tiles_083: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_083[2 * 4] = {
	0xc0, 0xc0,
	0x85, 0xc2,
	0xc1, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_084: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_084[2 * 4] = {
	0x42, 0xc0,
	0xd5, 0x0f,
	0x85, 0xc3,
	0xc0, 0xc0
};

// Tile g_tiles_085: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_085[2 * 4] = {
	0xc0, 0xc0,
	0xc3, 0xc2,
	0x83, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_086: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_086[2 * 4] = {
	0x42, 0xc0,
	0xd5, 0x4a,
	0x85, 0xc2,
	0x85, 0xc2
};

// Tile g_tiles_087: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_087[2 * 4] = {
	0xc1, 0xc2,
	0xc1, 0x42,
	0xc1, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_088: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_088[2 * 4] = {
	0x03, 0x03,
	0x42, 0xc3,
	0x56, 0x0f,
	0x56, 0xc3
};

// Tile g_tiles_089: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_089[2 * 4] = {
	0x03, 0x03,
	0xc5, 0x81,
	0xc4, 0x81,
	0xc5, 0x29
};

// Tile g_tiles_090: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_090[2 * 4] = {
	0x56, 0xc3,
	0x56, 0xc3,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_091: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_091[2 * 4] = {
	0xc5, 0x29,
	0xc5, 0x29,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_092: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_092[2 * 4] = {
	0x03, 0x03,
	0x42, 0xc0,
	0x07, 0x4a,
	0x43, 0xc6
};

// Tile g_tiles_093: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_093[2 * 4] = {
	0x03, 0x03,
	0xc0, 0x81,
	0x94, 0x29,
	0xda, 0xa1
};

// Tile g_tiles_094: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_094[2 * 4] = {
	0x07, 0x4e,
	0x07, 0x4e,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_095: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_095[2 * 4] = {
	0x9e, 0x29,
	0x9e, 0x29,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_096: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_096[2 * 4] = {
	0x03, 0x03,
	0x53, 0xc0,
	0x46, 0x3c,
	0x53, 0xcc
};

// Tile g_tiles_097: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_097[2 * 4] = {
	0x03, 0x03,
	0xc0, 0x81,
	0x85, 0x0b,
	0xd7, 0xab
};

// Tile g_tiles_098: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_098[2 * 4] = {
	0x53, 0x3c,
	0x53, 0x3c,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_099: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_099[2 * 4] = {
	0x87, 0x0b,
	0x87, 0x0b,
	0x03, 0x03,
	0xc0, 0xc0
};

// Tile g_tiles_100: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_100[2 * 4] = {
	0x03, 0x03,
	0x46, 0x63,
	0x46, 0x63,
	0xc0, 0xc0
};

// Tile g_tiles_101: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_101[2 * 4] = {
	0x03, 0x03,
	0x7d, 0x0b,
	0x7d, 0x0b,
	0xc0, 0xc0
};

// Tile g_tiles_102: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_102[2 * 4] = {
	0x03, 0x03,
	0x47, 0x2d,
	0x47, 0x2d,
	0xc0, 0xc0
};

// Tile g_tiles_103: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_103[2 * 4] = {
	0x03, 0x03,
	0x8c, 0x89,
	0x8c, 0xab,
	0xc0, 0xc0
};

// Tile g_tiles_104: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_104[2 * 4] = {
	0x4a, 0x4a,
	0xc0, 0xc0,
	0x4a, 0x4a,
	0xc0, 0xc0
};

// Tile g_tiles_105: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_105[2 * 4] = {
	0x85, 0xc2,
	0x85, 0xc2,
	0x85, 0xc2,
	0x85, 0xc2
};

// Tile g_tiles_106: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_106[2 * 4] = {
	0x03, 0x03,
	0x42, 0xc0,
	0x42, 0x0f,
	0x83, 0x85
};

// Tile g_tiles_107: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_107[2 * 4] = {
	0x8d, 0x0f,
	0x0f, 0x83,
	0x4b, 0x83,
	0x83, 0x03
};

// Tile g_tiles_108: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_108[2 * 4] = {
	0x48, 0xc0,
	0xc0, 0x07,
	0x85, 0x43,
	0xc1, 0x43
};

// Tile g_tiles_109: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_109[2 * 4] = {
	0xc0, 0xc0,
	0x07, 0x07,
	0x43, 0x43,
	0x43, 0x43
};

// Tile g_tiles_110: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_110[2 * 4] = {
	0xc0, 0x84,
	0x07, 0xc0,
	0x43, 0x42,
	0x43, 0x42
};

// Tile g_tiles_111: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_111[2 * 4] = {
	0xc0, 0xc0,
	0xc5, 0xce,
	0xc5, 0xc6,
	0xc1, 0xc6
};

// Tile g_tiles_112: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_112[2 * 4] = {
	0xc0, 0xc0,
	0xcd, 0xc6,
	0xc9, 0xc6,
	0xc9, 0xc6
};

// Tile g_tiles_113: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_113[2 * 4] = {
	0xc0, 0xc0,
	0xc9, 0x42,
	0xc9, 0x42,
	0xc9, 0x42
};

// Tile g_tiles_114: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_114[2 * 4] = {
	0xc1, 0xc6,
	0xc1, 0xc6,
	0xc1, 0xc2,
	0xc0, 0x81
};

// Tile g_tiles_115: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_115[2 * 4] = {
	0xc9, 0xc6,
	0xc9, 0xc6,
	0xc1, 0xc2,
	0xc0, 0xd5
};

// Tile g_tiles_116: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_116[2 * 4] = {
	0xc9, 0x42,
	0xc9, 0x42,
	0x81, 0x42,
	0xc0, 0xc0
};

// Tile g_tiles_117: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_117[2 * 4] = {
	0x81, 0x42,
	0x81, 0xc4,
	0x81, 0xc4,
	0xc0, 0xdd
};

// Tile g_tiles_118: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_118[2 * 4] = {
	0xdd, 0xaf,
	0xaf, 0x4a,
	0xea, 0xc5,
	0xc0, 0xca
};

// Tile g_tiles_119: 4x4 pixels, 2x4 bytes.
const u8 g_tiles_119[2 * 4] = {
	0x4a, 0x42,
	0x4a, 0x42,
	0x85, 0xc0,
	0xc8, 0x4a
};


// Hiding code in deterministically built binaries - Proof-of-Concept - Linux/x86
// Copyright (C) 2015 Christopher Jämthagen, Lund University
//
//   christopher.jamthagen@eit.lth.se
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>

#define FLAG0           (1 << 0)
#define FLAG1           (1 << 1)
#define FLAG2           (1 << 2)
#define FLAG3           (1 << 3)
#define FLAG4           (1 << 4)
#define FLAG5           (1 << 5)
#define FLAG6           (1 << 6)
#define FLAG7           (1 << 7)
#define FLAG8           (1 << 8)
#define FLAG9           (1 << 9)
#define FLAG10          (1 << 10)
#define FLAG11          (1 << 11)
#define FLAG12          (1 << 12)
#define FLAG13          (1 << 13)
#define FLAG14          (1 << 14)
#define FLAG15          (1 << 15)
#define FLAG16          (1 << 16)
#define FLAG17          (1 << 17)
#define FLAG18          (1 << 18)
#define FLAG19          (1 << 19)
#define FLAG20          (1 << 20)
#define FLAG21          (1 << 21)
#define FLAG22          (1 << 22)
#define FLAG23          (1 << 23)
#define FLAG24          (1 << 24)
#define FLAG25          (1 << 25)
#define FLAG26          (1 << 26)
#define FLAG27          (1 << 27)
#define FLAG28          (1 << 28)
#define FLAG29          (1 << 29)
#define FLAG30          (1 << 30)
#define FLAG31          (1 << 31)

#define FILLER1     asm("nop");
#define FILLER2     asm(".byte 0x66");asm("nop");
#define FILLER3     asm(".word 0x1F0F");asm(".byte 0x00");
#define FILLER4     asm(".word 0x1F0F");asm(".word 0x0040");
#define FILLER5     asm(".word 0x1F0F");asm(".word 0x0044");asm(".byte 0x00");
#define FILLER6     asm(".byte 0x66");asm(".word 0x1F0F");asm(".word 0x0044");asm(".byte 0x00");
#define FILLER7     asm(".word 0x1F0F");asm(".word 0x0080");asm(".word 0x0000");asm(".byte 0x00");
#define FILLER8     asm(".word 0x1F0F");asm(".word 0x0084");asm(".word 0x0000");asm(".word 0x0000");
#define FILLER16    FILLER8 FILLER8 
#define FILLER25    FILLER16 FILLER8 FILLER1
#define FILLER32    FILLER16 FILLER16
#define FILLER38    FILLER32 FILLER6
#define FILLER53    FILLER32 FILLER16 FILLER5
#define FILLER57    FILLER32 FILLER25
#define FILLER58    FILLER32 FILLER16 FILLER8 FILLER2
#define FILLER64    FILLER32 FILLER32
#define FILLER82    FILLER64 FILLER16 FILLER2
#define FILLER84    FILLER64 FILLER16 FILLER4
#define FILLER86    FILLER64 FILLER16 FILLER6
#define FILLER87    FILLER64 FILLER16 FILLER7
#define FILLER90    FILLER64 FILLER16 FILLER8 FILLER2
#define FILLER91    FILLER64 FILLER16 FILLER8 FILLER3
#define FILLER92    FILLER64 FILLER16 FILLER8 FILLER4


#define ADD_RM8_R8                  0x00
#define ADD_RM32_R32                0x01
#define ADD_R8_RM8                  0x02
#define ADD_R32_RM32                0x03
#define ADD_AL_IMM8                 0x04
#define ADD_EAX_IMM32               0x05
#define PUSH_ES                     0x06
#define POP_ES                      0x07
#define OR_RM8_R8                   0x08
#define OR_RM32_R32                 0x09
#define OR_R8_RM8                   0x0a
#define OR_R32_RM32                 0x0b
#define OR_AL_IMM8                  0x0c
#define OR_EAX_IMM32                0x0d
#define PUSH_CS                     0x0e
#define TWO_BYTE_OPCODE             0x0f
#define ADC_RM8_R8                  0x10
#define ADC_RM32_R32                0x11
#define ADC_R8_RM8                  0x12
#define ADC_R32_RM32                0x13
#define ADC_AL_IMM8                 0x14
#define ADC_EAX_IMM32               0x15
#define PUSH_SS                     0x16
#define POP_SS                      0x17
#define SBB_RM8_R8                  0x18
#define SBB_RM32_R32                0x19
#define SBB_R8_RM8                  0x1a
#define SBB_R32_RM32                0x1b
#define SBB_AL_IMM8                 0x1c
#define SBB_EAX_IMM32               0x1d
#define PUSH_DS                     0x1e
#define POP_DS                      0x1f
#define AND_RM8_R8                  0x20
#define AND_RM32_R32                0x21
#define AND_R8_RM8                  0x22
#define AND_R32_RM32                0x23
#define AND_AL_IMM8                 0x24
#define AND_EAX_IMM32               0x25
#define PREFIX_ES_OVERRIDE          0x26
#define DAA_AL                      0x27
#define SUB_RM8_R8                  0x28
#define SUB_RM32_R32                0x29
#define SUB_R8_RM8                  0x2a
#define SUB_R32_RM32                0x2b
#define SUB_AL_IMM8                 0x2c
#define SUB_EAX_IMM32               0x2d
#define PREFIX_CS_OVERRIDE          0x2e
#define DAS_AL                      0x2f
#define XOR_RM8_R8                  0x30
#define XOR_RM32_R32                0x31
#define XOR_R8_RM8                  0x32
#define XOR_R32_RM32                0x33
#define XOR_AL_IMM8                 0x34
#define XOR_EAX_IMM32               0x35
#define PREFIX_SS_OVERRIDE          0x36
#define AAA_AL                      0x37
#define CMP_RM8_R8                  0x38
#define CMP_RM32_R32                0x39
#define CMP_R8_RM8                  0x3a
#define CMP_R32_RM32                0x3b
#define CMP_AL_IMM8                 0x3c
#define CMP_EAX_IMM32               0x3d
#define PREFIX_DS_OVERRIDE          0x3e
#define AAS_AL                      0x3f
#define INC_EAX                     0x40
#define INC_ECX                     0x41
#define INC_EDX                     0x42
#define INC_EBX                     0x43
#define INC_EBP                     0x44
#define INC_ESP                     0x45
#define INC_ESI                     0x46
#define INC_EDI                     0x47
#define DEC_EAX                     0x48
#define DEC_ECX                     0x49
#define DEC_EDX                     0x4a
#define DEC_EBX                     0x4b
#define DEC_ESP                     0x4c
#define DEC_EBP                     0x4d
#define DEC_ESI                     0x4e
#define DEC_EDI                     0x4f
#define PUSH_EAX                    0x50
#define PUSH_ECX                    0x51
#define PUSH_EDX                    0x52
#define PUSH_EBX                    0x53
#define PUSH_ESP                    0x54
#define PUSH_EBP                    0x55
#define PUSH_ESI                    0x56
#define PUSH_EDI                    0x57
#define POP_EAX                     0x58
#define POP_ECX                     0x59
#define POP_EDX                     0x5a
#define POP_EBX                     0x5b
#define POP_EBP                     0x5c
#define POP_ESP                     0x5d
#define POP_ESI                     0x5e
#define POP_EDI                     0x5f
#define PUSHA                       0x60
#define POPA                        0x61
#define BOUND                       0x62
#define ARPL                        0x63
#define PREFIX_FS_OVERRIDE          0x64
#define PREFIX_GS_OVERRIDE          0x65
#define PREFIX_OPSIZE_OVERRIDE      0x66
#define PREFIX_ADDRSIZE_OVERRIDE    0x67
#define PUSH_IMM32                  0x68
#define IMUL_R32_RM32_IMM32         0x69
#define PUSH_IMM8                   0x6a
#define IMUL_R32_RM32_IMM8          0x6b
#define INS_M8                      0x6c
#define INS_M32                     0x6d
#define OUTS_M8                     0x6e
#define OUTS_M32                    0x6f
#define JO_REL8                     0x70
#define JNO_REL8                    0x71
#define JB_REL8                     0x72
#define JNB_REL8                    0x73
#define JZ_REL8                     0x74
#define JNZ_REL8                    0x75
#define JNA_REL8                    0x76
#define JA_REL8                     0x77
#define JS_REL8                     0x78
#define JNS_REL8                    0x79
#define JP_REL8                     0x7a
#define JNP_REL8                    0x7b
#define JL_REL8                     0x7c
#define JNL_REL8                    0x7d
#define JNG_REL8                    0x7e
#define JG_REL8                     0x7f
#define ARITHMETIC_RM8_IMM8         0x80
#define ARITHMETIC_RM32_IMM32       0x81
#define OPCODE_82                   0x82
#define OPCODE_83                   0x83
#define TEST_RM8_R8                 0x84
#define TEST_RM32_R32               0x85
#define XCHG_R8_RM8                 0x86 
#define XCHG_R32_RM32               0x87 
#define MOV_RM8_R8                  0x88
#define MOV_RM32_R32                0x89 
#define MOV_R8_RM8                  0x8a
#define MOV_R32_RM32                0x8b
#define MOV_RM16_SREG               0x8c 
#define LEA_R32_M                   0x8d
#define MOV_SREG_RM16               0x8e 
#define POP_RM32                    0x8f
#define NOP                         0x90
#define XCHG_ECX_EAX                0x91
#define XCHG_EDX_EAX                0x92
#define XCHG_EBX_EAX                0x93
#define XCHG_EBP_EAX                0x94
#define XCHG_ESP_EAX                0x95
#define XCHG_ESI_EAX                0x96
#define XCHG_EDI_EAX                0x97
#define CWDE                        0x98
#define CDQ                         0x99
#define CALLF                       0x9a
#define FWAIT                       0x9b
#define PUSHF                       0x9c
#define POPF                        0x9d
#define SAHF                        0x9e
#define LAHF                        0x9f
#define MOV_AL_MOFFS8               0xa0
#define MOV_EAX_MOFFS32             0xa1
#define MOV_MOFFS8_AL               0xa2
#define MOV_MOFFS32_EAX             0xa3
#define MOVSB                       0xa4
#define MOVSD                       0xa5
#define CMPSB                       0xa6
#define CMPSD                       0xa7
#define TEST_AL_IMM8                0xa8
#define TEST_EAX_IMM32              0xa9
#define STOSB                       0xaa
#define STOSD                       0xab
#define LODSB                       0xac
#define LODSD                       0xad
#define SCASB                       0xae
#define SCASD                       0xaf
#define MOV_AL_IMM8                 0xb0
#define MOV_CL_IMM8                 0xb1
#define MOV_DL_IMM8                 0xb2
#define MOV_BL_IMM8                 0xb3
#define MOV_AH_IMM8                 0xb4
#define MOV_CH_IMM8                 0xb5
#define MOV_DH_IMM8                 0xb6
#define MOV_BH_IMM8                 0xb7
#define MOV_EAX_IMM32               0xb8
#define MOV_ECX_IMM32               0xb9
#define MOV_EDX_IMM32               0xba
#define MOV_EBX_IMM32               0xbb
#define MOV_EBP_IMM32               0xbc
#define MOV_ESP_IMM32               0xbd
#define MOV_ESI_IMM32               0xbe
#define MOV_EDI_IMM32               0xbf
#define ROTATE_SHIFT_RM8_IMM8       0xc0
#define ROTATE_SHIFT_RM32_IMM32     0xc1
#define RETN_IMM16                  0xc2
#define RETN                        0xc3
#define LES                         0xc4
#define LDS                         0xc5
#define MOV_RM8_IMM8                0xc6
#define MOV_RM32_IMM32              0xc7
#define ENTER                       0xc8
#define LEAVE                       0xc9
#define RETF_IMM16                  0xca
#define RETF                        0xcb
#define INT_CC                      0xcc
#define INT_IMM8                    0xcd
#define INTO                        0xce
#define IRET                        0xcf
#define ROTATE_SHIFT_RM8_1          0xd0
#define ROTATE_SHIFT_RM32_1         0xd1
#define ROTATE_SHIFT_RM8_CL         0xd2
#define ROTATE_SHIFT_RM32_CL        0xd3
#define AAM                         0xd4
#define AAD                         0xd5
#define SALC                        0xd6
#define XLAT                        0xd7
#define FP1                         0xd8
#define FP2                         0xd9
#define FP3                         0xda
#define FP4                         0xdb
#define FP5                         0xdc
#define FP6                         0xdd
#define FP7                         0xde
#define FP8                         0xdf
#define LOOPNZ                      0xe0
#define LOOPZ                       0xe1
#define LOOP                        0xe2
#define JECXZ                       0xe3
#define IN_AL_IMM8                  0xe4
#define IN_EAX_IMM32                0xe5
#define OUT_AL_IMM8                 0xe6
#define OUT_EAX_IMM32               0xe7
#define CALL_REL32                  0xe8
#define JMP_REL32                   0xe9
#define JMPF                        0xea
#define JMP_REL8                    0xeb
#define IN_AL_DX                    0xec
#define IN_EAX_DX                   0xed
#define OUT_DX_AL                   0xee
#define OUT_DX_EAX                  0xef
#define PREFIX_LOCK                 0xf0
#define UNDEFINED2                  0xf1
#define PREFIX_REPNZ                0xf2
#define PREFIX_REPZ                 0xf3
#define HLT                         0xf4 
#define CMC                         0xf5
#define OPCODE_F6                   0xf6 
#define OPCODE_F7                   0xf7
#define CLC                         0xf8
#define STC                         0xf9
#define CLI                         0xfa
#define STI                         0xfb
#define CLD                         0xfc
#define STD                         0xfd
#define INC_DEC_RM8                 0xfe
#define OPCODE_FF                   0xff

typedef struct imm8_t imm8_t;
struct imm8_t {
    char a[256][256][256];
};

typedef struct imm32_t imm32_t;
struct imm32_t {
        int a[256][256][64];
};

typedef struct byte3_jmprel8_t byte3_jmprel8_t;
struct byte3_jmprel8_t {
    char arr1[JMP_REL8][256][256];
    char arr2[PUSH_IMM8];
    char pushimm8_0x00;
    char arr3[256-1];
    char pushimm8_0x01;
    char arr4[256-1];
    char pushimm8_0x02;
    char arr5[256*2-1];
    char pushimm8_0x04;
    char arr6[256-1];
    char pushimm8_0x05;
    char arr7[256-1];
    char arr8[256][0xb-0x5-1];
    char pushimm8_0x0b;
    char arr9[256-1];
    char arr10[256][(0xe)-(0xb)-1];
    char pushimm8_0x0e;
    char arr11[256*2-1];
    char pushimm8_0x10;
    char arr12[256-1];
    char arr13[256][(0x3f)-(0x10)-1];
    char pushimm8_0x3f;
    char arr14[0x100-PUSH_IMM8+PUSH_EDX-2];
    char arr15[256][PUSH_ECX-0x3f];
    char pushecx_pushedx;
    char arr16[256];
    char arr17[256][PUSH_ESP-PUSH_EDX-1];
    char pushedx_pushesp;
    char arr18[POP_EDI-PUSH_EDX-1];
    char arr19[256][POP_ECX-PUSH_ESP];
    char popedi_popecx;
    char arr20[256-1];
    char arr21[256][POP_EBX-POP_ECX-1];
    char popedi_popebx;
    char arr22[PUSH_IMM8-POP_EDI-1];
    char arr23[256][0x66-POP_EBX];
    char pushimm8_0x66;
    char arr24[INT_IMM8-PUSH_IMM8-1];
    char arr25[256][0x80-0x66];
    char intimm8_0x80;
    char arr26[0x100+MOV_RM32_R32-INT_IMM8-1];
    char arr27[256][0xc2-0x80-1];
    char movrm32r32_0xc2;
    char arr28[0x100+XOR_RM32_R32-MOV_RM32_R32-1];
    char arr29[256][0xd2-0xc2-1];
    char xorrm32r32_0xd2;
    char arr30[MOV_RM32_R32-XOR_RM32_R32-1];
    char arr31[256][0xe0-0xd2];
    char movrm32r32_0xe0;
    char arr32[256-1];
    char movrm32r32_0xe1;
    char arr33[256*2-1];
    char movrm32r32_0xe3;
    char temp;
};

typedef struct jmprel8_0x20_t jmprel8_0x20_t;
struct jmprel8_0x20_t {
    char arr1[0x20][256][256];
    char arr2[JMP_REL8][256];
    char arr3[PUSH_EDX];
    char pushedx;
    char pushebx;
    char pushesp;
    char arr4[XCHG_ECX_EAX - PUSH_ESP-1];
    char xchgecxeax;
    char temp1;
    char xchgebxeax;     
};

typedef struct movrm8imm8_t movrm8imm8_t;
struct movrm8imm8_t {
    char arr1[MOV_RM8_IMM8][256][256];
    char arr2[256][DEC_EAX];
    char arr3[DEC_EAX];
    int deceax_deceax;
};

typedef struct pushimm8_deceax_deceax_t pushimm8_deceax_deceax_t;
struct pushimm8_deceax_deceax_t {
    char arr1[PUSH_IMM8][256][256];
    char arr2[256][DEC_EAX];
    char arr3[DEC_EAX];
    char pushimm8_deceax_deceax;
};

typedef struct retn_pushedi_popeax_t retn_pushedi_popeax_t;
struct retn_pushedi_popeax_t {
    char arr1[RETN][256][256];
    char arr2[PUSH_EDI][256];
    char arr3[POP_EAX];
    int popeax_pushedi_retn;
};

typedef struct callrel32_t callrel32_t;
struct callrel32_t {
    char arr1[CALL_REL32];
    char arr2[256][0x010f];
    int call_010f;

    char arr3[256-4];
    char arr4[256][0x05c6-0x010f-1];
    int call_05c6;

    char arr5[256-4];
    char arr6[256][0x0746-0x05c6-1];
    int call_0746;

    char arr7[256-4];
    char arr8[256][0x0757-0x0746-1];
    int call_0757;

    char arr9[256-4];
    char arr10[256][0x08d7-0x0757-1];
    int call_08d7;

    char arr11[256-4];
    char arr12[256][0x08e8-0x08d7-1];
    int call_08e8;

    char arr13[256-4];
    char arr14[256][0x0a68-0x08e8-1];
    int call_0a68;

    char arr15[256-4];
    char arr16[256][0x0a79-0x0a68-1];
    int call_0a79;

    char arr17[256-4];
    char arr18[256][0x0c67-0x0a79-1];
    int call_0c67;

    char arr19[256-4];
    char arr20[256][0x0d58-0x0c67-1];
    int call_0d58;

    char arr21[256-4];
    char arr22[256][0x0f25-0x0d58-1];
    int call_0f25;

    char arr23[256-4];
    char arr24[256][0x0fa6-0x0f25-1];
    int call_0fa6;

    char arr25[256-4];
    char arr26[256][0x1173-0x0fa6-1];
    int call_1173;

    char arr27[256-4];
    char arr28[256][0x14a9-0x1173-1];
    int call_14a9;

    char arr29[256-4];
    char arr30[256][0x1676-0x14a9-1];
    int call_1676;

    char arr31[256-4];
    char arr32[256][0x17fa-0x1676-1];
    int call_17fa;

    char arr33[256-4];
    char arr34[256][0x1a35-0x17fa-1];
    int call_1a35;

    char arr35[256-4];
    char arr36[256][0x1b49-0x1a35-1];
    int call_1b49;
};

#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>
#include <emulator.h>

#define INSTRUCTION_COUNT 0xC

typedef enum{
    MEM = 1 << 0,
    REG_MEM = 1 << 1,
    REG_REG = 1 << 2,
    MEM_REG = 1 << 3,
    MEM_IMMEDIATE = 1 << 4,
    REG_IMMEDIATE = 1 << 5,
    REG = 1 << 6,
    NOTHING = 1 << 7
} emu_addr_modes_e;

typedef enum{
    NULL_INSTRUCTION = 0x0,
    STORE = 0x1,
    ADD = 0x2,
    SUB = 0x3,
    JMPEQ = 0x4,
    JMPMR = 0x5,
    CMP = 0x6,
    NOT = 0x7,
    AND = 0x8,
    OR = 0x9,
    SHL = 0xA,
    SHR = 0xB
} emu_opcodes_e;

typedef struct{
    emu_opcodes_e opcode;
    uint8_t addr_modes;
    bool (*execute_instruction)(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
} emu_instruction_t;

emu_instruction_t instruction_set[INSTRUCTION_COUNT];

emu_instruction_t emu_get_instruction(emu_opcodes_e opcode);

void emu_register_instruction(emu_opcodes_e opcode, uint8_t addr_modes);
void emu_register_instructions();

#endif
#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>
#include <emulator.h>
#include <arch/arch.h>

emu_instruction_t instruction_set[INSTRUCTION_COUNT];

emu_instruction_t emu_get_instruction(emu_opcodes_e opcode);

void emu_register_instruction(emu_opcodes_e opcode, uint8_t addr_modes);
void emu_register_instructions();

#endif
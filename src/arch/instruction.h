#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>

#define INSTRUCTION_COUNT

typedef struct{
    uint8_t opcode;
    uint8_t addr_modes;
    bool (*execute_instruction)(uint16_t operand1, uint16_t operand2);
} instruction_t;

void register_instruction(uint8_t opcode, uint8_t addr_modes, bool (*execute_instruction)(uint16_t operand1, uint16_t operand2));

#endif
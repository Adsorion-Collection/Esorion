#include <arch/instruction.h>

extern bool execute_NULL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_STORE_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_ADD_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_SUB_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_JMPEQ_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_JMPMR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_CMP_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_NOT_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_AND_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_OR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_SHL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
extern bool execute_SHR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);

bool (*execute_instruction_pointers[INSTRUCTION_COUNT])(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode) = {
    execute_NULL_instruction, 
    execute_STORE_instruction, 
    execute_ADD_instruction, 
    execute_SUB_instruction,
    execute_JMPEQ_instruction,
    execute_JMPMR_instruction,
    execute_CMP_instruction,
    execute_NOT_instruction,
    execute_AND_instruction,
    execute_OR_instruction,
    execute_SHL_instruction,
    execute_SHR_instruction
};

emu_instruction_t emu_get_instruction(emu_opcodes_e opcode){
    for(uint32_t i = 0; i < INSTRUCTION_COUNT; i++){
        if(opcode == instruction_set[i].opcode){
            return instruction_set[i];
        }
    }

    return instruction_set[0];
}

void emu_register_instruction(emu_opcodes_e opcode, uint8_t addr_modes){
    emu_instruction_t instruction = {.opcode = opcode, .addr_modes = addr_modes, .execute_instruction = execute_instruction_pointers[opcode]};

    instruction_set[opcode] = instruction;
}

void emu_register_instructions(){
    emu_register_instruction(NULL_INSTRUCTION, NOTHING);
    emu_register_instruction(STORE, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(ADD, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(SUB, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(JMPEQ, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(JMPMR, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(CMP, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(NOT, (MEM | REG));
    emu_register_instruction(AND, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(OR, (MEM_REG | REG_MEM | REG_REG | REG_IMMEDIATE | MEM_IMMEDIATE));
    emu_register_instruction(SHL, (REG_MEM | REG_REG | REG_IMMEDIATE));
    emu_register_instruction(SHR, (REG_MEM | REG_REG | REG_IMMEDIATE));
}
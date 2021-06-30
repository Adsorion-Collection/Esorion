#include <stdint.h>
#include <arch/instruction.h>
#include <emulator.h>
#include <stdio.h>

__attribute__((unused))bool execute_NULL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){
    return true;
}

__attribute__((unused))bool execute_STORE_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){
    return true;
}

__attribute__((unused))bool execute_ADD_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_SUB_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_JMPEQ_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_JMPMR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_CMP_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_NOT_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_AND_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_OR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, addr_modes_e addr_mode){return true;}
#include <stdint.h>
#include <arch/instruction.h>
#include <emulator.h>
#include <stdio.h>
#include <arch/bus.h>

__attribute__((unused))bool execute_NULL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    return true;
}

__attribute__((unused))bool execute_STORE_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            task->info.registers[operand1] = task->info.registers[operand2];
            return true;
        }case REG_MEM:{
            task->info.registers[operand1] = read_from_bus(task, operand2);
            return true;
        }case MEM_REG:{
            write_to_bus(task, operand1, task->info.registers[operand2]);
            return true;
        }case REG_IMMEDIATE:{
            task->info.registers[operand1] = operand2;
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, operand2);
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_ADD_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            task->info.registers[operand1] += task->info.registers[operand2];
            return true;
        }case REG_MEM:{
            task->info.registers[operand1] += read_from_bus(task, operand2);
            return true;
        }case MEM_REG:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) + task->info.registers[operand2]);
            return true;
        }case REG_IMMEDIATE:{
            task->info.registers[operand1] += operand2;
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) + operand2);
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_SUB_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            task->info.registers[operand1] -= task->info.registers[operand2];
            return true;
        }case REG_MEM:{
            task->info.registers[operand1] -= read_from_bus(task, operand2);
            return true;
        }case MEM_REG:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) - task->info.registers[operand2]);
            return true;
        }case REG_IMMEDIATE:{
            task->info.registers[operand1] -= operand2;
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) - operand2);
            return true;
        }default: break;
    }
    return false;
}
__attribute__((unused))bool execute_JMPEQ_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_JMPMR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_CMP_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_NOT_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_AND_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_OR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_SHL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}

__attribute__((unused))bool execute_SHR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){return true;}
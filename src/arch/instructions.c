#include <stdint.h>
#include <arch/instruction.h>
#include <emulator.h>
#include <stdio.h>
#include <arch/bus.h>
#include <arch/arch.h>
#include <stdbool.h>

static bool is_register_8bit(uint16_t operand){
    if((operand & (1 << 15)) || (operand & (1 << 14))){
        return true;
    }
    return false;
}

static uint8_t read_from_corresponding_8bit_register(task_t* task, uint16_t operand){
    if(operand & (1 << 15)){
        return (uint8_t)(task->info.registers[operand & 0b1111]);
    }else if(operand & (1 << 14)){
        return task->info.registers[operand & 0b1111] >> 8;
    }
    return 0;
}

static bool is_register_high_8bit(uint16_t operand){
    if(operand & (1 << 15)){
        return false;
    }
    return true;
}

static void write_to_corresponding_8bit_register(task_t* task, uint16_t register_operand, uint8_t value){
    if(is_register_high_8bit(register_operand)){
        task->info.registers[register_operand & 0b1111] = value << 8;
    }else{
        task->info.registers[register_operand & 0b1111] &= ~0xFF;
        task->info.registers[register_operand & 0b1111] = value;
    }
}

static void write_to_correct_register(task_t* task, uint16_t register_operand, uint16_t value){
    if((register_operand & 0b1111) > 0x5){
        return;
    }
    if(is_register_8bit(register_operand)){
        write_to_corresponding_8bit_register(task, register_operand, (uint8_t)value);
        return;
    }
    task->info.registers[register_operand] = value;
}

static uint16_t read_from_correct_register(task_t* task, uint16_t register_operand){
    if((register_operand & 0b1111) > 0x5){
        return 0;
    }
    if(is_register_8bit(register_operand)){
        return read_from_corresponding_8bit_register(task, register_operand);
    }
    return task->info.registers[register_operand];
}

__attribute__((unused))bool execute_NULL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    return true;
}

__attribute__((unused))bool execute_STORE_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2));
            }else{
                write_to_bus(task, operand1, (uint8_t)(read_from_correct_register(task, operand2) >> 8));
                write_to_bus(task, operand1 + 1, read_from_correct_register(task, operand2));
            }
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
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) + read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) + operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) + read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) + read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value + read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
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
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) - read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) - operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) - read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) - read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value - read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) - operand2);
            return true;
        }default: break;
    }
    return false;
}
__attribute__((unused))bool execute_JMPEQ_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG:{
            if(task->info.flags & EQUAL){
                task->info.instruction_pointer = read_from_correct_register(task, operand1);
            }
            return true;
        }case MEM:{
            if(task->info.flags & EQUAL){
                task->info.instruction_pointer = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
            }
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_JMPMR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG:{
            if(task->info.flags & MORE){
                task->info.instruction_pointer = read_from_correct_register(task, operand1);
            }
            return true;
        }case MEM:{
            if(task->info.flags & MORE){
                task->info.instruction_pointer = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
            }
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_CMP_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            if(read_from_correct_register(task, operand1) == read_from_correct_register(task, operand2)){
                task->info.flags |= EQUAL;
            }else{
                task->info.flags &= ~EQUAL;
            }

            if(read_from_correct_register(task, operand1) > read_from_correct_register(task, operand2)){
                task->info.flags |= MORE;
            }else{
                task->info.flags &= ~MORE;
            }
            return true;
        }case REG_IMMEDIATE:{
            if(read_from_correct_register(task, operand1) == operand2){
                task->info.flags |= EQUAL;
            }else{
                task->info.flags &= ~EQUAL;
            }

            if(read_from_correct_register(task, operand1) > operand2){
                task->info.flags |= MORE;
            }else{
                task->info.flags &= ~MORE;
            }
            return true;
        }default: break;
    }

    return false;
}

__attribute__((unused))bool execute_NOT_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG:{
            write_to_correct_register(task, operand1, ~read_from_correct_register(task, operand1));
            return true;
        }case MEM:{
            write_to_bus(task, operand1, ~(read_from_bus(task, operand1) << 8));
            return true;
        }default: break;
    }
    
    return false;
}

__attribute__((unused))bool execute_AND_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) & read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) & operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) & read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) & read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value + read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) & operand2);
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_OR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) | read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) | operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) | read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) | read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value | read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) | operand2);
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_SHL_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) << read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) << operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) << read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) << read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value << read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) << operand2);
            return true;
        }default: break;
    }
    return false;
}

__attribute__((unused))bool execute_SHR_instruction(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode){
    switch(addr_mode){
        case REG_REG:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) >> read_from_correct_register(task, operand2));
            return true;
        }case REG_IMMEDIATE:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) >> operand2);
            return true;
        }case REG_MEM:{
            write_to_correct_register(task, operand1, read_from_correct_register(task, operand1) >> read_from_bus(task, operand2));
            return true;
        }case MEM_REG:{
            if(is_register_8bit(operand2)){
                write_to_bus(task, operand1, read_from_correct_register(task, operand2) >> read_from_bus(task, operand1));
            }else{
                uint16_t mem_value = (read_from_bus(task, operand1) << 8) | read_from_bus(task, operand1 + 1);
                uint16_t result = mem_value << read_from_correct_register(task, operand2);
                write_to_bus(task, operand1, result >> 8);
                write_to_bus(task, operand1 + 1, (uint8_t)result);
            }
            return true;
        }case MEM_IMMEDIATE:{
            write_to_bus(task, operand1, read_from_bus(task, operand1) >> operand2);
            return true;
        }default: break;
    }
    return false;
}
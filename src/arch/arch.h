#ifndef __ARCH_H
#define __ARCH_H

#include <stdint.h>
#include <stdbool.h>

#define INSTRUCTION_COUNT 0xC

typedef enum{
    EQUAL = (1 << 0),
    MORE = (1 << 1)
} emu_flags_e;

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
    uint16_t registers[6];
    uint16_t flags;
    uint32_t instruction_pointer;
} task_info_t;

typedef struct{
    uint16_t start;
    uint16_t end;
    uint8_t* address_space;
    bool trigger_access_notifs;
    void(*on_device_read)(void* task, uint16_t address);
    void(*on_device_write)(void* task, uint16_t address, uint8_t value);
} bus_device_t;

typedef struct{
    task_info_t info;
    uint8_t id;
    uint16_t* bytecode_buffer;
    uint32_t bytecode_buffer_length;
    bus_device_t bus_devices[8];
    uint8_t free_device_slots;
    uint8_t bus_device_count; 
    void* next;
} task_t;

typedef struct{
    emu_opcodes_e opcode;
    uint8_t addr_modes;
    bool (*execute_instruction)(task_t* task, uint16_t operand1, uint16_t operand2, emu_addr_modes_e addr_mode);
} emu_instruction_t;


#endif
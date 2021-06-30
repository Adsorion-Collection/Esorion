#ifndef __EMULATOR_H
#define __EMULATOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct{
    uint16_t start;
    uint16_t end;
    uint8_t* address_space;
    bool trigger_access_notifs;
    void(*on_device_read)();
    void(*on_device_write)(uint16_t address);
} bus_device_t;

typedef struct{
    uint16_t registers[6];
    uint16_t flags;
    uint32_t instruction_pointer;
} task_info_t;

typedef struct{
    task_info_t info;
    uint16_t* bytecode_buffer;
    uint32_t bytecode_buffer_length;
    bus_device_t bus_devices[8];
    uint8_t free_device_slots;
    uint8_t bus_device_count; 
    void* next;
} task_t;

extern task_t* task_array;

void add_task(uint16_t* bytecode_buffer, uint32_t bytecode_buffer_length);
void execute_task_iteration(task_t* task);

#endif
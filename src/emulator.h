#ifndef __EMULATOR_H
#define __EMULATOR_H

#include <stdint.h>
#include <stdbool.h>
#include <arch/arch.h>

extern task_t* task_array;

void add_task(uint16_t* bytecode_buffer, uint32_t bytecode_buffer_length);
void execute_task_iteration(task_t* task);

#endif
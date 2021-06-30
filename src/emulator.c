#include <emulator.h>
#include <stdio.h>
#include <stdlib.h>
#include <arch/instruction.h>
#include <arch/bus.h>

task_t* task_array = NULL;

void add_task(uint16_t* bytecode_buffer, uint32_t bytecode_buffer_length){
    task_t* task = (task_t*)calloc(1, sizeof(task_t));
    task->bytecode_buffer = bytecode_buffer;
    task->bytecode_buffer_length = bytecode_buffer_length;
    task->next = NULL;
    add_device_to_bus(task, 0, UINT16_MAX, false, NULL, NULL);
    if(task_array == NULL){
        task_array = task;
        return;
    }else{
        for(task_t* t = task_array; t->next; t = t->next){
            t->next = task;
        }
    }
}

void execute_task_iteration(task_t* task){
    instruction_t instruction;
    
    if(task->info.instruction_pointer < task->bytecode_buffer_length) instruction = get_instruction(task->bytecode_buffer[task->info.instruction_pointer]);
    else {
        task->info.instruction_pointer = 0;
        execute_task_iteration(task);
    }

    instruction.execute_instruction(task, task->bytecode_buffer[task->info.instruction_pointer + 1], task->bytecode_buffer[task->info.instruction_pointer + 2], (uint8_t)task->bytecode_buffer[task->info.instruction_pointer]);
}
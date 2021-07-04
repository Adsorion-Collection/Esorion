#include <emulator.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arch/instruction.h>
#include <arch/bus.h>

task_t* task_array = NULL;
uint64_t task_count = 0;

void schedule_tasks(){
    while(1){
        if(task_array != NULL){
            system("clear");
            for(task_t* t = task_array; t; t = t->next){
                execute_task_iteration(t);
                printf("REG0: %d\nREG1: %d\nREG2: %d\nREG3: %d\nREG4: %d\nREG5: %d\n", t->info.registers[0], t->info.registers[1], t->info.registers[2], t->info.registers[3], t->info.registers[4], t->info.registers[5]);
                printf("%d:%d\n", t->info.instruction_pointer, t->bytecode_buffer_length);
            }
            sleep(1);
        }
    }
}

void add_task(uint16_t* bytecode_buffer, uint32_t bytecode_buffer_length){
    task_t* task = (task_t*)calloc(1, sizeof(task_t));
    task->bytecode_buffer = bytecode_buffer;
    task->bytecode_buffer_length = bytecode_buffer_length;
    task->next = NULL;
    task->id = task_count;
    add_device_to_bus(task, 0, UINT16_MAX, false, NULL, NULL);
    if(task_array == NULL){
        task_array = task;
        return;
    }else{
        task_t* t = task_array;
        for(; t->next; t = t->next){
        }
        t->next = task;
    }
    task_count++;
}

void execute_task_iteration(task_t* task){
    emu_instruction_t instruction;

    if(task->info.instruction_pointer < task->bytecode_buffer_length) instruction = emu_get_instruction(task->bytecode_buffer[task->info.instruction_pointer / sizeof(uint16_t)] >> 8);
    else{
        task->info.instruction_pointer = 0;
        instruction = emu_get_instruction(task->bytecode_buffer[0] >> 8);
        task->info.instruction_pointer += 6;
        instruction.execute_instruction(task, task->bytecode_buffer[1], task->bytecode_buffer[2], (uint8_t)task->bytecode_buffer[0]);
        return;
    }

    uint16_t old_instruction_pointer = task->info.instruction_pointer;
    task->info.instruction_pointer += 6;
    instruction.execute_instruction(task, task->bytecode_buffer[old_instruction_pointer / sizeof(uint16_t) + 1], task->bytecode_buffer[old_instruction_pointer / sizeof(uint16_t) + 2], (uint8_t)task->bytecode_buffer[old_instruction_pointer / sizeof(uint16_t)]);
}
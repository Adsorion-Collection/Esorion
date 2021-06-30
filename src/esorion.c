#include <stdio.h>
#include <stdlib.h>
#include <arch/instruction.h>
#include <emulator.h>

int main(void){
    register_instructions();

    add_task((uint16_t*)calloc(1, UINT16_MAX), UINT16_MAX);
    execute_task_iteration(task_array);
}
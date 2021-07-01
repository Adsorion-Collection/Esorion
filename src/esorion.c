#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arch/instruction.h>
#include <emulator.h>
#include <arch/bus.h>

void on_read(uint16_t address){
    printf("O2\n");
}
void on_write(uint16_t address, uint8_t value){
    printf("YO\n");
}
int main(void){
    emu_register_instructions();

    uint16_t* bytecode_buffer = (uint16_t*)calloc(1, 0x100);
    bytecode_buffer[0] = REG_IMMEDIATE | (ADD << 8);
    bytecode_buffer[1] = 0x1;
    bytecode_buffer[2] = 0x1;
    add_task(bytecode_buffer, 6);
    while(1){
        system("clear");
        printf("REG0: %d\nREG1: %d\nREG2: %d\nREG3: %d\nREG4: %d\nREG5: %d\n", task_array->info.registers[0], task_array->info.registers[1], task_array->info.registers[2], task_array->info.registers[3], task_array->info.registers[4], task_array->info.registers[5]);
        printf("%d:%d\n", task_array->info.instruction_pointer, task_array->bytecode_buffer_length);
        sleep(1);
        execute_task_iteration(task_array);
    }
}
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
    bytecode_buffer[1] = 0x2;
    bytecode_buffer[2] = 0x1;
    bytecode_buffer[3] = REG_IMMEDIATE | (CMP << 8);
    bytecode_buffer[4] = 0x1;
    bytecode_buffer[5] = 0x0;
    add_task(bytecode_buffer, 24);
    add_task(bytecode_buffer, 24);
    write_to_bus(task_array, 0, 0x10);
    printf("%x\n", read_from_bus(task_array, 0));
    //schedule_tasks();
}
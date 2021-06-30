#include <arch/bus.h>
#include <stdlib.h>
#include <stddef.h>

void add_device_to_bus(task_t* task, uint16_t start, uint16_t end, bool trigger_access_notifs, void(*on_device_read)(), void(*on_device_write)(uint16_t address)){
    bus_device_t device = {};
    device.address_space = (uint8_t*)calloc(1, end - start);
    device.end = end;
    device.start = start;
    device.on_device_read = on_device_read;
    device.on_device_write = on_device_write;
    device.trigger_access_notifs = trigger_access_notifs;
    
    for(uint8_t i = 0; i < 8; i++){
        if(task->free_device_slots >> i){
            continue;
        }
        task->bus_devices[i] = device;
    }
}

void write_to_bus(task_t* task, uint16_t address, uint8_t value){
    for(uint8_t i = 0; i < 8; i++){
        if(address >= task->bus_devices[i].start && address < task->bus_devices[i].end){
            task->bus_devices[i].address_space[address - task->bus_devices[i].start] = value;
            return;
        }
    }
}

uint8_t read_from_bus(task_t* task, uint16_t address){
    for(uint8_t i = 0; i < 8; i++){
        if(address >= task->bus_devices[i].start && address < task->bus_devices[i].end){
            return task->bus_devices[i].address_space[address - task->bus_devices[i].start];
        }
    }

    return 0;
}
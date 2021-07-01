#ifndef __BUS_H
#define __BUS_H

#include <stdint.h>
#include <emulator.h>
#include <stdbool.h>

void add_device_to_bus(task_t* task, uint16_t start, uint16_t end, bool trigger_access_notifs, void(*on_device_read)(uint16_t address), void(*on_device_write)(uint16_t address, uint8_t value));
void write_to_bus(task_t* task, uint16_t address, uint8_t value);
uint8_t read_from_bus(task_t* task, uint16_t address);

#endif
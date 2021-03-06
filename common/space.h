#pragma once

#include <stdio.h>

// implement these

#ifdef STM32F1
#define START_ADDRESS 0x08030000
#define page_size 2048
#define buffer_size 4096
#endif

#ifdef STM32F4
#define START_ADDRESS 0x080C0000
#define page_size 0x20000
#define buffer_size 0x40000
#endif

#ifdef WIN32
#define page_size 1024
#define buffer_size 4096
#endif

int space_raw_write(int address, const void *data, int size);
int space_raw_read(int address, void *data, int size);
int space_raw_erase(int address);
int space_raw_init();

// use these
int space_init(bool erase = false);
int space_read(const void *key, int keysize, void *data, int num_to_read, int *num_read);
int space_write(const void *key, int keysize, const void *data, int num_to_write, int *num_written);
int space_delete(const void *key, int keysize);
int space_resort();
int space_available();

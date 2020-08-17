#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory_system.h"
#include "memory_chip.h"
#include "decoder.h"

void memory_store(int address, unsigned char value) {
	int lowerhalf = address & 0x1F;
	int upperhalf = (address >> 5) & 0x1F;
	mem_put(decoder(lowerhalf), decoder(upperhalf), value);
	return;
}

void memory_fill(int start_address, unsigned char value, int num_bytes) {
	int i;
	for(i = 0; i < start_address + num_bytes; i++) {
		memory_store(start_address + i, value);
	}
	return;
}

unsigned char memory_fetch(int address) {
	int lowerhalf = address & 0x1F;
	int upperhalf = (address >> 5) & 0x1F;
	return mem_get(decoder(lowerhalf), decoder(upperhalf));
}

unsigned int memory_fetch_word(int address) {
	unsigned int x;
	unsigned char a = memory_fetch(address);
	unsigned char b = memory_fetch(address + 1);
	unsigned char c = memory_fetch(address + 2);
	unsigned char d = memory_fetch(address + 3);
	x = a | (b << 8) | (c << 16) | (d << 24);
	return x;
}

void memory_dump(int start_address, int num_bytes) {
	int i;
	for(i = 0; i < num_bytes; i++) {
		unsigned char a = memory_fetch(start_address + i);
		printf("%x \n", a);
	}
	return;
}

void memory_store_word(int address, unsigned int value) {
	unsigned char a = value & 0xff;
	unsigned char b = (value >> 8) & 0xff;
	unsigned char c = (value >> 16) & 0xff;
	unsigned char d = (value >> 24) & 0xff;
	memory_store(address, a);
	memory_store(address + 1, b);
	memory_store(address + 2, c);
	memory_store(address + 3, d);
	return;
}
void load_memory(char *filename) {
	FILE *fp = fopen(filename, "r");
	unsigned int start_address;
	unsigned int x;
	fscanf(fp, "%d", &start_address);
	int count = 0;
	while(1) {
		if(fscanf(fp, "%x", &x) == EOF) {
			break;
		} else {
			memory_store_word(start_address, x);
			start_address = start_address + 4;
			printf("loading... %x\n", x);
			count = count + 1;
		}
	}
	fclose(fp);
	return;
}

#include "cpu.h"
#include "memory_system.h"
#include <stdlib.h>
#include <stdio.h>

int registers[16];

int cpsr = 0;

void set_reg(int reg, int value) {
	registers[reg] = value;
	return;
}

int get_reg(int reg) {
	return registers[reg];
}

int get_cpsr() {
	return cpsr;
}

void set_cpsr(int value) {
	cpsr = value;
	return;
}

void show_regs() {
	int i;
	for(i = 0; i < 16; i++) {
		printf("%d\n", registers[i]);
	}
	return;
}
void step() {
	unsigned int inst = memory_fetch_word(registers[PC]);
	int opcode = inst >> 24;
	int reg = 0;
	int reg1 = 0;
	int reg2 = 0;
	int address = 0;
	int bitZ = 0;
	int bitLT = 0;
	int bitGT = 0;
	switch(opcode) {
		case LDR:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			registers[reg] = memory_fetch_word(address);
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case STR:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			memory_store_word(address, registers[reg]);
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case ADD:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			reg1 = (inst >> 8) & 0xff;
			reg2 = inst & 0xff;
			registers[reg] = registers[reg1] + registers[reg2];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case SUB:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			reg1 = (inst >> 8) & 0xff;
			reg2 = inst & 0xff;
			registers[reg] = registers[reg2] - registers[reg1];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case MUL:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			reg1 = (inst >> 8) & 0xff;
			reg2 = inst & 0xff;
			registers[reg] = registers[reg1] * registers[reg2];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case DIV:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			reg1 = (inst >> 8) & 0xff;
			reg2 = inst & 0xff;
			registers[reg] = registers[reg1] / registers[reg2];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case CMP:
			reg = (inst >> 16) & 0xff;
			address = inst & 0xffff;
			if (address > 1023 || reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			reg1 = (inst >> 8) & 0xff;
			reg2 = inst & 0xff;
			if(reg1 == reg2) {
				set_cpsr(Z);
				bitZ = 1;
				bitLT = 0;
				bitGT = 0;
			} else if (reg1 < reg2) {
				set_cpsr(LT);
				bitZ = 0;
				bitLT = 1;
				bitGT = 0;
			} else if (reg1 > reg2) {
				set_cpsr(GT);
				bitZ = 0;
				bitLT = 0;
				bitGT = 1;
			}
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case B:
			reg = (inst >> 16) & 0xff;
			if (reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			registers[PC] = registers[reg];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case BEQ:
			reg = (inst >> 16) & 0xff;
			if (reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			if (bitZ == 1) {
				registers[PC] = registers[reg];
			}
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case BNE:
			reg = (inst >> 16) & 0xff;
			if (reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			if(bitZ == 0) {
				registers[PC] = registers[reg];
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case BLT:
			reg = (inst >> 16) & 0xff;
			if (reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			if(bitLT == 1) {
				registers[PC] = registers[reg];
			}
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case BGT:
			reg = (inst >> 16) & 0xff;
			if (reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1); 
			}
			if(bitGT == 1) {
				registers[PC] = registers[reg];
			}
			printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
			registers[PC] = registers[PC] + 4;
			break;
		case MOV:
			reg = (inst >> 16) & 0xff;
			if(reg > 15) {
				printf("Address/Register out of bounds.\n");
				exit(1);
			}
			reg1 = (inst >> 8) & 0xff;
			registers[reg] = registers[reg1];
			registers[PC] = registers[PC] + 4;
			break;
		case BL:
			address = inst & 0xffff;
			registers[LR] = registers[PC] + 4;
			registers[PC] = address;
			break;
	}
	return;
} }

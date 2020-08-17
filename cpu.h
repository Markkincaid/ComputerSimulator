#define LDR 1
#define STR 2
#define ADD 3
#define SUB 4
#define MUL 5
#define DIV 6
#define CMP 7
#define B   8
#define BEQ 9
#define BNE 10
#define BLT 11
#define BGT 12
#define MOV 13
#define BL 14
#define Z 1
#define LT 2
#define GT 3
#define SR 13
#define LR 14
#define PC 15
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
void set_reg(int reg, int value);
int get_reg(int reg);
int get_cpsr();
void set_cpsr(int value);
void step();
void show_regs();

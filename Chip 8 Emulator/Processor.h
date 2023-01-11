#pragma once
#include <vector>
#include <stack>
#include <SFML/Audio.hpp>
#include "RAM.h"
#include "ScreenHelper.h"
#include "GraphicsHelper.h"
#include "InputHelper.h"

class Processor {
	private:
		//16 bit program counter
		unsigned int PC = 0x200;
		//8 bit stack pointer
		unsigned char SP = 0;

		//16 bit index register
		unsigned int I = 0;

		//8 bit delay timer
		unsigned char delayTimer = 0;
		//8 bit sound timer
		unsigned char soundTimer = 0;

		//Frequency to decrement delay and sound timers
		const int timerFrequency = 60;

		sf::SoundBuffer soundBuffer;
		sf::Sound sound;

		//Stack of 16 16 bit values
		std::stack<unsigned int> stack;

		//8 bit registers V0 - VF
		std::vector<unsigned char> registers = std::vector<unsigned char>(16, 0);

		//Processor frequency in Hertz
		int processorFrequency = 600;

		//Memory
		RAM memory = RAM();

		//Graphics driver
		GraphicsHelper graphics = GraphicsHelper();

		//Input
		InputHelper keyboard = InputHelper();

		//Draw flag
		bool drawFlag = true;

		//Opcode methods:

		//Instruction 00E0 - CLS
		void op_cls();
		//Instruction 00EE - RET
		void op_ret();
		//Instruction 1NNN - JMP
		void op_jmp_immed(unsigned int nnn);
		//Instruction 2NNN - CALL
		void op_call(unsigned int nnn);
		//Instruction 3XNN - SE VX, NN
		void op_se_immed(unsigned char vx, unsigned char nn);
		//Instruction 4XNN - SNE VX, NN
		void op_sne_immed(unsigned char vx, unsigned char nn);
		//Instruction 5XY0 - SE VX, VY
		void op_se_reg(unsigned char vx, unsigned char vy);
		//Instruction 6XNN - LD VX, NN
		void op_ld_reg_immed(unsigned char vx, unsigned char nn);
		//Instruction 7XNN - ADD VX, NN
		void op_add_immed(unsigned char vx, unsigned char nn);
		//Instruction 8XY0 - LD VX, VY
		void op_ld_reg(unsigned char vx, unsigned char vy);
		//Instruction 8XY1 - OR VX, VY
		void op_or(unsigned char vx, unsigned char vy);
		//Instruction 8XY2 - AND VX, VY
		void op_and(unsigned char vx, unsigned char vy);
		//Instruction 8XY3 - XOR VX, VY
		void op_xor(unsigned char vx, unsigned char vy);
		//Instruction 8XY4 - ADD VX, VY
		void op_add_reg(unsigned char vx, unsigned char vy);
		//Instruction 8XY5 - SUB VX, VY
		void op_sub_reg(unsigned char vx, unsigned char vy);
		//Instruction 8XY6 - SHR VX {, VY}
		void op_shr(unsigned char vx, unsigned char vy);
		//Instruction 8XY7 - SUBN VX, VY
		void op_subn(unsigned char vx, unsigned char vy);
		//Instruction 8XYE - SHL VX {, VY}
		void op_shl(unsigned char vx, unsigned char vy);
		//Instruction 9XY0 - SNE VX, VY
		void op_sne_reg(unsigned char vx, unsigned char vy);
		//Instruction ANNN - LD I, NNN
		void op_ld_immed(unsigned int nnn);
		//Instruction BNNN - JMP V0, NNN
		void op_jmp_reg(unsigned int nnn);
		//Instruction CXNN - RND VX, NN
		void op_rnd(unsigned char vx, unsigned char nn);
		//Instruction DXYN - DRW VX, VY, N
		void op_drw(unsigned char vx, unsigned char vy, unsigned char n);
		//Instruction EX9E - SKP VX
		void op_skp(unsigned char vx);
		//Instruction EXA1 - SKNP VX
		void op_sknp(unsigned char vx);
		//Instruction FX07 - LD VX, DT
		void op_ld_to_delay(unsigned char vx);
		//Instruction FX0A - LD VX, K
		void op_ld_key(unsigned char vx);
		//Instruction FX15 - LD DT, VX
		void op_delay_to_ld(unsigned char vx);
		//Instruction FX18 - LD ST, VX
		void op_ld_sound(unsigned char vx);
		//Instruction FX1E - ADD I, VX
		void op_add_i(unsigned char vx);
		//Instruction FX29 - LD F, VX
		void op_ld_sprite(unsigned char vx);
		//Instruction FX33 - LD B, VX
		void op_ld_sprite_dec(unsigned char vx);
		//Instruction FX55 - LD [I], VX
		void op_ld_reg_to_mem(unsigned char vx);
		//Instruction FX65 - LD VX, [I]
		void op_ld_mem_to_reg(unsigned char vx);

		void executeNextInstruction();
		void tick();

	public:
		void init(std::string romPath);
		void loop();

};
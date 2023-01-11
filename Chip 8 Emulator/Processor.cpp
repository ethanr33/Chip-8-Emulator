#include <iostream>
#include <chrono>
#include <cstdlib>
#include "Processor.h"

short SineWave(double time, double freq, double amp) {
	short result;
	double tpc = 44100 / freq; // ticks per cycle
	double cycles = time / tpc;
	double rad = 2 * 3.1415926535 * cycles;
	short amplitude = 32767 * amp;
	result = amplitude * sin(rad);
	return result;
}

void Processor::init(std::string romPath) {
	//Load ROM

	this->memory.loadRomIntoRAM(romPath);

	//Init sound

	std::vector<sf::Int16> samples;

	for (int i = 0; i < 187425; i++) {
		samples.push_back(SineWave(i, 440, 0.9));
	}

	this->soundBuffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
	this->sound.setBuffer(this->soundBuffer);
}

void Processor::tick() {
	this->executeNextInstruction();

	if (drawFlag) {
		this->graphics.draw();
		drawFlag = false;
	}
}

void Processor::loop() {
	using namespace std::chrono;

	high_resolution_clock::time_point last = high_resolution_clock::now();
	high_resolution_clock::time_point timer = high_resolution_clock::now();

	bool soundFlag = true;

	while (this->graphics.isWindowOpen()) {
		high_resolution_clock::time_point cur = high_resolution_clock::now();

		int tickElapsed = duration_cast<std::chrono::microseconds>(cur - last).count();
		int timerElapsed = duration_cast<std::chrono::microseconds>(cur - timer).count();

		if (tickElapsed > (1000000 / this->processorFrequency)) {
			this->graphics.pollEvent();
			this->tick();

			last = high_resolution_clock::now();
		}

		if (timerElapsed > (1000000 / this->timerFrequency)) {
			
			if (this->delayTimer > 0) {
				delayTimer--;
			}

			if (this->soundTimer > 0 && soundFlag) {
				soundFlag = false;
				this->soundTimer--;
				this->sound.play();
			} else if (this->soundTimer > 0) {
				this->soundTimer--;
			} else {
				this->sound.stop();
				soundFlag = true;
			}

			timer = high_resolution_clock::now();
		}

	}
}

void Processor::executeNextInstruction() {
	//Execute next instruction

	unsigned int nextInstruction = this->memory.getInstructionAt(this->PC);

	//std::cout << std::hex << "PC: " << this->PC << " " << this->memory.getInstructionAt(this->PC) << std::endl;

	int firstNibble = (nextInstruction & 0xF000) >> 12;
	int nnn = nextInstruction & 0x0FFF;
	int nn = nextInstruction & 0x00FF;
	int x = (nextInstruction & 0x0F00) >> 8;
	int y = (nextInstruction & 0x00F0) >> 4;
	int n = nextInstruction & 0x000F;

	switch (firstNibble) {
		case 0x0:
			switch (n) {
				case 0x0:
					this->op_cls();
					break;
				case 0xE:
					this->op_ret();
					break;
			}
			break;
		case 0x1:
			this->op_jmp_immed(nnn);
			break;
		case 0x2:
			this->op_call(nnn);
			break;
		case 0x3:
			this->op_se_immed(x, nn);
			break;
		case 0x4:
			this->op_sne_immed(x, nn);
			break;
		case 0x5:
			this->op_se_reg(x, y);
			break;
		case 0x6:
			this->op_ld_reg_immed(x, nn);
			break;
		case 0x7:
			this->op_add_immed(x, nn);
			break;
		case 0x8:
			switch (n) {
				case 0x0:
					this->op_ld_reg(x, y);
					break;
				case 0x1:
					this->op_or(x, y);
					break;
				case 0x2:
					this->op_and(x, y);
					break;
				case 0x3:
					this->op_xor(x, y);
					break;
				case 0x4:
					this->op_add_reg(x, y);
					break;
				case 0x5:
					this->op_sub_reg(x, y);
					break;
				case 0x6:
					this->op_shr(x, y);
					break;
				case 0x7:
					this->op_subn(x, y);
					break;
				case 0xE:
					this->op_shl(x, y);
					break;
			}
			break;
		case 0x9:
			this->op_sne_reg(x, y);
			break;
		case 0xA:
			this->op_ld_immed(nnn);
			break;
		case 0xB:
			this->op_jmp_reg(nnn);
			break;
		case 0xC:
			this->op_rnd(x, nn);
			break;
		case 0xD:
			this->op_drw(x, y, n);
			break;
		case 0xE:
			switch (nn) {
				case 0x9E:
					this->op_skp(x);
					break;
				case 0xA1:
					this->op_sknp(x);
					break;
			}
			break;
		case 0xF:
			switch (nn) {
				case 0x07:
					this->op_ld_to_delay(x);
					break;
				case 0x0A:
					this->op_ld_key(x);
					break;
				case 0x15:
					this->op_delay_to_ld(x);
					break;
				case 0x18:
					this->op_ld_sound(x);
					break;
				case 0x1E:
					this->op_add_i(x);
					break;
				case 0x29:
					this->op_ld_sprite(x);
					break;
				case 0x33:
					this->op_ld_sprite_dec(x);
					break;
				case 0x55:
					this->op_ld_reg_to_mem(x);
					break;
				case 0x65:
					this->op_ld_mem_to_reg(x);
					break;
			}
			break;
		default:
			std::cout << "Unrecognized opcode " << nextInstruction << std::endl;
	}
}

//00E0
void Processor::op_cls() {
	this->graphics.getScreen()->resetPixels();
	this->drawFlag = true;
	this->PC += 2;
}

//00EE
void Processor::op_ret() {
	this->PC = this->stack.top();
	this->stack.pop();
	this->PC += 2;
}

//1NNN
void Processor::op_jmp_immed(unsigned int nnn) {
	this->PC = nnn;
}

//2NNN
void Processor::op_call(unsigned int nnn) {
	this->stack.push(this->PC);
	this->PC = nnn;
}

//3XNN
void Processor::op_se_immed(unsigned char vx, unsigned char nn) {
	if (this->registers.at(vx) == nn) {
		this->PC += 2;
	}

	this->PC += 2;
}

//4XNN
void Processor::op_sne_immed(unsigned char vx, unsigned char nn) {
	if (this->registers.at(vx) != nn) {
		this->PC += 2;
	}

	this->PC += 2;
}

//5XY0
void Processor::op_se_reg(unsigned char vx, unsigned char vy) {
	if (this->registers.at(vx) == this->registers.at(vy)) {
		this->PC += 2;
	}

	this->PC += 2;
}

//6XNN
void Processor::op_ld_reg_immed(unsigned char vx, unsigned char nn) {
	this->registers.at(vx) = nn;
	this->PC += 2;
}

//7XNN
void Processor::op_add_immed(unsigned char vx, unsigned char nn) {
	this->registers.at(vx) += nn;
	this->PC += 2;
}

//Instruction 8XY0 - LD VX, VY
void Processor::op_ld_reg(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vy);
	this->PC += 2;
}

//Instruction 8XY1 - OR VX, VY
void Processor::op_or(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vx) | this->registers.at(vy);
	this->registers.at(15) = 0;
	this->PC += 2;
}

//Instruction 8XY2 - AND VX, VY
void Processor::op_and(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vx) & this->registers.at(vy);
	this->registers.at(15) = 0;
	this->PC += 2;
}

//Instruction 8XY3 - XOR VX, VY
void Processor::op_xor(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vx) ^ this->registers.at(vy);
	this->registers.at(15) = 0;
	this->PC += 2;
}

//Instruction 8XY4 - ADD VX, VY
void Processor::op_add_reg(unsigned char vx, unsigned char vy) {
	int sum = this->registers.at(vx) + this->registers.at(vy);

	if (sum > 255) {
		this->registers.at(15) = 1;
	} else {
		this->registers.at(15) = 0;
	}

	sum = sum & 0xFF;

	this->registers.at(vx) = sum;
	this->PC += 2;
}

//Instruction 8XY5 - SUB VX, VY
void Processor::op_sub_reg(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = (this->registers.at(vx) - this->registers.at(vy)) & 0xFF;

	if (this->registers.at(vx) > this->registers.at(vy)) {
		this->registers.at(15) = 1;
	}
	else {
		this->registers.at(15) = 0;
	}

	this->PC += 2;
}

//Instruction 8XY6 - SHR VX {, VY}
void Processor::op_shr(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vy);
	int carryBit = this->registers.at(vx) % 2;
	this->registers.at(vx) = this->registers.at(vx) / 2;
	this->registers.at(15) = carryBit;
	this->PC += 2;
}

//Instruction 8XYE - SHL VX {, VY}
void Processor::op_shl(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = this->registers.at(vy);
	int carryBit = (this->registers.at(vx) & 0x80) >> 7;
	this->registers.at(vx) *= 2;
	this->registers.at(15) = carryBit;
	this->PC += 2;
}

//Instruction 8XY7 - SUBN VX, VY
void Processor::op_subn(unsigned char vx, unsigned char vy) {
	this->registers.at(vx) = (this->registers.at(vy) -  this->registers.at(vx)) & 0xFF;

	if (this->registers.at(vx) < this->registers.at(vy)) {
		this->registers.at(15) = 1;
	}
	else {
		this->registers.at(15) = 0;
	}

	this->PC += 2;
}

//9XY0
void Processor::op_sne_reg(unsigned char vx, unsigned char vy) {
	if (this->registers.at(vx) != this->registers.at(vy)) {
		this->PC += 2;
	}

	this->PC += 2;
}

//ANNN
void Processor::op_ld_immed(unsigned int nnn) {
	this->I = nnn;
	this->PC += 2;
}

//BNNN
void Processor::op_jmp_reg(unsigned int nnn) {
	this->PC = nnn + this->registers.at(0);
}

//Instruction CXNN - RND VX, NN
void Processor::op_rnd(unsigned char vx, unsigned char nn) {
	this->registers.at(vx) = (rand() % 256) & nn;
	this->PC += 2;
}

//DXYN
void Processor::op_drw(unsigned char x, unsigned char y, unsigned char n) {
	this->registers.at(15) = 0;

	int xStart = this->registers.at(x);
	int yStart = this->registers.at(y);

	bool isOverridden = false;

	for (int i = 0; i < n; i++) {
		int curIndex = this->I + i;
		unsigned int curByte = this->memory.getDataAt(curIndex);

		for (int j = 0; j < 8; j++) {
			int row = (yStart + i);
			int col = (xStart + j);

			if ((xStart % 64 >= 56 && col % 64 < 7) || (yStart % 32 >= 24 && row % 32 < 7)) {
				continue;
			} else {
				row = row % 32;
				col = col % 64;
			}

			int curBit = ((1 << (7 - j)) & curByte) >> (7 - j);

			int curPixelValue = this->graphics.getScreen()->getPixelValue(row, col);
			int newPixelValue = curPixelValue ^ curBit;

			if (curPixelValue == 1 && newPixelValue == 0) {
				isOverridden = true;
			}
			
			this->graphics.getScreen()->setPixelValue(row, col, newPixelValue);
		}
	}

	if (isOverridden) {
		this->registers.at(15) = 1;
	} else {
		this->registers.at(15) = 0;
	}

	this->drawFlag = true;
	this->PC += 2;
}

//Instruction EX9E - SKP VX
void Processor::op_skp(unsigned char vx) {
	if (this->keyboard.isKeyPressed(this->registers.at(vx))) {
		this->PC += 2;
	}

	this->PC += 2;
}


//Instruction EXA1 - SKNP VX
void  Processor::op_sknp(unsigned char vx) {
	if (!this->keyboard.isKeyPressed(this->registers.at(vx))) {
		this->PC += 2;
	}

	this->PC += 2;
}


//Instruction FX07 - LD VX, DT
void Processor::op_ld_to_delay(unsigned char vx) {
	this->registers.at(vx) = this->delayTimer;
	this->PC += 2;
}

//Instruction FX0A - LD VX, K
void Processor::op_ld_key(unsigned char vx) {
	bool pressingKey = false;
	for (int i = 0; i < 16; i++) {
		pressingKey = keyboard.isKeyPressed(i);

		if (pressingKey) {
			this->registers.at(vx) = pressingKey;
			this->PC += 2;
			break;
		}
	}
}

//Instruction FX15 - LD DT, VX
void Processor::op_delay_to_ld(unsigned char vx) {
	this->delayTimer = this->registers.at(vx);
	this->PC += 2;
}

//Instruction FX18 - LD ST, VX
void Processor::op_ld_sound(unsigned char vx) {
	this->soundTimer = this->registers.at(vx);
	this->PC += 2;
}

//Instruction FX1E - ADD I, VX
void Processor::op_add_i(unsigned char vx) {
	this->I += this->registers.at(vx);
	this->registers.at(15) = (this->I >= 0x1000);
	this->PC += 2;
}

//FX29
void Processor::op_ld_sprite(unsigned char vx) {
	this->I = this->memory.getSpriteDigitIndex() + 5 * this->registers.at(vx);
	this->PC += 2;
}

//Instruction FX33 - LD B, VX
void Processor::op_ld_sprite_dec(unsigned char vx) {
	int num = this->registers.at(vx);
	this->memory.setDataAt(this->I, num / 100);
	this->memory.setDataAt(this->I + 1, (num / 10) % 10);
	this->memory.setDataAt(this->I + 2, num % 10);
	this->PC += 2;
}

//Instruction FX55 - LD [I], VX
void Processor::op_ld_reg_to_mem(unsigned char vx) {
	for (int i = 0; i <= vx; i++) {
		this->memory.setDataAt(this->I + i, this->registers.at(i));
	}

	this->I++;

	this->PC += 2;
}

//Instruction FX65 - LD VX, [I]
void Processor::op_ld_mem_to_reg(unsigned char vx) {
	for (int i = 0; i <= vx; i++) {
		this->registers.at(i) = this->memory.getDataAt(this->I + i);
	}

	this->I++;

	this->PC += 2;
}
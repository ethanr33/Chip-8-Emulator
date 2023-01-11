#include <iostream>
#include "RAM.h"
#include "FileReader.h"

RAM::RAM() {
	//Load digit sprites into memory
	for (int i = 0; i < this->DIGIT_SPRITES.size(); i++) {
		this->memory.at(this->DIGIT_SPRITES_INDEX + i) = this->DIGIT_SPRITES.at(i);
	}
}

void RAM::loadRomIntoRAM(std::string romPath) {
	FileReader fr = FileReader(romPath);

	std::vector<unsigned char> fileData = fr.getFileData();

	//Copy data from file into RAM
	for (int i = 0; i < fileData.size(); i++) {
		this->memory.at(this->ROM_START_INDEX + i) = fileData.at(i);
	}

}

unsigned char RAM::getDataAt(unsigned int index) {
	return this->memory.at(index);
}

unsigned int RAM::getInstructionAt(unsigned int index) {
	unsigned int instruction = this->memory.at(index) << 8;
	instruction = instruction | this->memory.at(index + 1);
	return instruction;
}

unsigned int RAM::getSpriteDigitIndex() {
	return DIGIT_SPRITES_INDEX;
}

void RAM::setDataAt(unsigned int index, unsigned char data) {
	this->memory.at(index) = data;
}

#include "FileReader.h"

FileReader::FileReader(std::string filePath) {
	this->filePath = filePath;
}

void FileReader::setFilePath(std::string newFilePath) {
	this->filePath = newFilePath;
}

std::string FileReader::getFilePath() {
	return this->filePath;
}

std::vector<unsigned char> FileReader::getFileData() {
	std::vector<unsigned char> fileData;

	this->in.open(this->filePath, std::ios::binary);

	this->in.seekg(0, this->in.end);
	int length = this->in.tellg();
	this->in.seekg(0, this->in.beg);

	unsigned char* buffer = new unsigned char[length];

	this->in.read((char*) &buffer[0], length);

	this->in.close();

	for (int i = 0; i < length; i++) {
		fileData.push_back(buffer[i]);
	}

	delete[] buffer;

	return fileData;
}
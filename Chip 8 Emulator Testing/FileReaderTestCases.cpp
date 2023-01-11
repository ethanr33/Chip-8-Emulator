#include "pch.h"
#include <iostream>
#include "../Chip 8 Emulator/FileReader.cpp"

TEST(FileReader_Constructor, TestFilePath) {
	std::string path = "this/is/a/path.txt";
	FileReader f = FileReader(path);

	ASSERT_EQ(path, f.getFilePath());

	path = "newfilepath.something";

	FileReader f2 = FileReader(path);

	ASSERT_EQ(f2.getFilePath(), path);
}

TEST(FileReader_GetFileData, TestSmallerFile) {
	FileReader f = FileReader("roms/test1");
	std::vector<unsigned char> data = f.getFileData();

	bool dataMatches = true;

	for (int i = 0; i < 16; i++) {
		EXPECT_EQ(i, data.at(i));
	}
}

TEST(FileReader_GetFileData, TestLargerFile) {
	FileReader f2 = FileReader("roms/test_opcode");
	std::vector<unsigned char> data = f2.getFileData();

	bool dataMatches = true;
	std::vector<unsigned char> expected = { 0x12, 0x4e, 0xea, 0xac, 0xaa, 0xea, 0xce, 0xaa, 0xaa, 0xae, 0xe0, 0xa0, 0xa0, 0xe0, 0xc0, 0x40 };

	for (int i = 0; i < expected.size(); i++) {
		EXPECT_EQ(data.at(i), expected.at(i));
	}


	EXPECT_EQ(0x20, data.at(0x13));
	EXPECT_EQ(0xdc, data.at(data.size() - 1));
}

TEST(FileReader_GetFileData, TestFileSizes) {
	FileReader f1 = FileReader("roms/test1");
	FileReader f2 = FileReader("roms/test_opcode");

	std::vector<unsigned char> data1 = f1.getFileData();
	std::vector<unsigned char> data2 = f2.getFileData();

	EXPECT_EQ(data1.size(), 16);
	EXPECT_EQ(data2.size(), 478);
}
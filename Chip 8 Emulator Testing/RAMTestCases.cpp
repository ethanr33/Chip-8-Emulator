#include "pch.h"
#include "../Chip 8 Emulator/RAM.cpp"

TEST(RAM_TESTS, LoadRomIntoRam_TestSampleRom) {
	RAM r = RAM();

	r.loadRomIntoRAM("roms/test1");

	for (int i = 0; i < 16; i++) {
		ASSERT_EQ(r.getDataAt(0x200 + i), i);
	}
}

TEST(RAM_TESTS, LoadRomIntoRam_LoadNewRom) {

	RAM r = RAM();

	r.loadRomIntoRAM("roms/ibm_logo");
	r.loadRomIntoRAM("roms/test1");

	for (int i = 0; i < 16; i++) {
		EXPECT_EQ(r.getDataAt(0x200 + i), i);
	}

	r.loadRomIntoRAM("roms/ibm_logo");

	EXPECT_EQ(r.getInstructionAt(0x200), 0x00E0);
	EXPECT_EQ(r.getInstructionAt(0x202), 0xA22A);
	EXPECT_EQ(r.getInstructionAt(0x204), 0x600C);
	EXPECT_EQ(r.getInstructionAt(0x206), 0x6108);
	EXPECT_EQ(r.getInstructionAt(0x208), 0xD01F);
	EXPECT_EQ(r.getInstructionAt(0x27E), 0x0080);
	EXPECT_EQ(r.getInstructionAt(0x280), 0x00E0);
	EXPECT_EQ(r.getInstructionAt(0x282), 0x00E0);

}

TEST(RAM_TESTS, GetInstructionAt_TestNormalCase) {
	RAM r = RAM();

	r.loadRomIntoRAM("roms/test1");

	EXPECT_EQ(r.getInstructionAt(0x200), 0x0001);
	EXPECT_EQ(r.getInstructionAt(0x202), 0x0203);
	EXPECT_EQ(r.getInstructionAt(0x204), 0x0405);
	EXPECT_EQ(r.getInstructionAt(0x206), 0x0607);
	EXPECT_EQ(r.getInstructionAt(0x208), 0x0809);
	EXPECT_EQ(r.getInstructionAt(0x20A), 0x0A0B);
	EXPECT_EQ(r.getInstructionAt(0x20C), 0x0C0D);
	EXPECT_EQ(r.getInstructionAt(0x20E), 0x0E0F);

	RAM r2 = RAM();

	r2.loadRomIntoRAM("roms/ibm_logo");

	EXPECT_EQ(r2.getInstructionAt(0x200), 0x00E0);
	EXPECT_EQ(r2.getInstructionAt(0x202), 0xA22A);
	EXPECT_EQ(r2.getInstructionAt(0x204), 0x600C);
	EXPECT_EQ(r2.getInstructionAt(0x206), 0x6108);
	EXPECT_EQ(r2.getInstructionAt(0x208), 0xD01F);
	EXPECT_EQ(r2.getInstructionAt(0x27E), 0x0080);
	EXPECT_EQ(r2.getInstructionAt(0x280), 0x00E0);
	EXPECT_EQ(r2.getInstructionAt(0x282), 0x00E0);
}
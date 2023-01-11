
#include "pch.h"
#include "../Chip 8 Emulator/ScreenHelper.cpp"

//Test getPixelValue
TEST(GetPixelValue, HandlesNormalCases) {
	ScreenHelper s = ScreenHelper();

	ASSERT_EQ(s.getPixelValue(10, 1), 0);
	ASSERT_EQ(s.getPixelValue(23, 23), 0);
	ASSERT_EQ(s.getPixelValue(13, 6), 0);

	s.setPixelValue(10, 1, 1);
	s.setPixelValue(23, 23, 1);
	s.setPixelValue(13, 6, 1);

	ASSERT_EQ(s.getPixelValue(10, 1), 1);
	ASSERT_EQ(s.getPixelValue(23, 23), 1);
	ASSERT_EQ(s.getPixelValue(13, 6), 1);
}

TEST(GetPixelValue, HandlesEdgeCases) {
	ScreenHelper s = ScreenHelper();
	const int maxCol = s.getScreenWidthPixels() - 1;
	const int maxRow = s.getScreenHeightPixels() - 1;

	ASSERT_EQ(s.getPixelValue(0, 0), 0);
	ASSERT_EQ(s.getPixelValue(maxRow, 0), 0);
	ASSERT_EQ(s.getPixelValue(0, maxCol), 0);
	ASSERT_EQ(s.getPixelValue(maxRow, maxCol), 0);

	s.setPixelValue(0, 0, 1);
	s.setPixelValue(maxRow, 0, 1);
	s.setPixelValue(0, maxCol, 1);
	s.setPixelValue(maxRow, maxCol, 1);

	ASSERT_EQ(s.getPixelValue(0, 0), 1);
	ASSERT_EQ(s.getPixelValue(maxRow, 0), 1);
	ASSERT_EQ(s.getPixelValue(0, maxCol), 1);
	ASSERT_EQ(s.getPixelValue(maxRow, maxCol), 1);
}

TEST(ResetPixels, HandlesNormalCases) {
	ScreenHelper s = ScreenHelper();
	const int maxCol = s.getScreenWidthPixels() - 1;
	const int maxRow = s.getScreenHeightPixels() - 1;

	for (int i = 0; i < maxRow; i++) {
		for (int j = 0; j < maxCol; j++) {
			s.setPixelValue(i, j, 1);
		}
	}

	s.resetPixels();

	for (int i = 0; i < maxRow; i++) {
		for (int j = 0; j < maxCol; j++) {
			EXPECT_EQ(s.getPixelValue(i, j), 0);
		}
	}
}
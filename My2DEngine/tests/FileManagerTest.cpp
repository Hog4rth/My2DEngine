#include <cstdio>

#include <fstream>

#include <gtest/gtest.h>

#include "../FileManager.h"

namespace Engine::Tests {

class FileManagerTest : public ::testing::Test {
protected:
	void SetUp() override {
		std::ofstream out("test_config.ini");
		out << "ValidInt = 42 \n";
		out << "\tValidFloat= 3.14\r\n";
		out << "ValidString = Hello World\n";
		out << "InvalidInt = abc\n";
		out << "TrailingInt = 42abc\n";
		out << "NoEqualSignLine\n";
		out.close();
	}

	void TearDown() override { std::remove("test_config.ini"); }
};

TEST_F(FileManagerTest, FallbackOnMissingFile) {
	FileManager fm{"non_existent_file.ini"};
	fm.LoadFile();
	EXPECT_EQ(fm.Load<int>("AnyKey", 100), 100);
}

TEST_F(FileManagerTest, LoadValidValues) {
	FileManager fm{"test_config.ini"};
	fm.LoadFile();

	EXPECT_EQ(fm.Load<int>("ValidInt", 0), 42);
	EXPECT_FLOAT_EQ(fm.Load<float>("ValidFloat", 0.0f), 3.14f);
	EXPECT_EQ(fm.Load<std::string>("ValidString", ""), "Hello World");
}

TEST_F(FileManagerTest, FallbackOnMissingKey) {
	FileManager fm("test_config.ini");
	fm.LoadFile();
	EXPECT_EQ(fm.Load<int>("MissingKey", 99), 99);
}

TEST_F(FileManagerTest, FallbackOnConversionFailure) {
	FileManager fm("test_config.ini");
	fm.LoadFile();
	EXPECT_EQ(fm.Load<int>("InvalidInt", 77), 77);
}

TEST_F(FileManagerTest, FallbackOnTrailingCharacters) {
	FileManager fm("test_config.ini");
	fm.LoadFile();
	EXPECT_EQ(fm.Load<int>("TrailingInt", 88), 88);
}
}  // namespace Engine::Tests

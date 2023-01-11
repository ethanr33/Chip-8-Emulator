#pragma once

#include <string>
#include <fstream>
#include <vector>


class FileReader {
	private:
		std::string filePath;
		std::ifstream in;
	public:
		/*
			string filePath: path of file to read in
		*/
		FileReader(std::string filePath);
		/*
			Returns raw data of file specified as a vector<int>
			return vector<unsigned char>: Raw data of file
		*/
		std::vector<unsigned char> getFileData();
		/*
			Returns current file path
			return string: current file path
		*/
		std::string getFilePath();
		/*
			Sets current file path
			@param newFilePath: new file path to set
		*/
		void setFilePath(std::string newFilePath);
};
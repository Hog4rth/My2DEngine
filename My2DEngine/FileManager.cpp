#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "FileManager.h"

void FileManager::LoadDefaultSettings() {

	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;

		auto trim = [](std::string& str) {
			str.erase(0, str.find_first_not_of(" \t\r\n"));
			str.erase(str.find_last_not_of(" \t\r\n") + 1);
		};

		while (std::getline(file, line)) {
			size_t equalPosition = line.find('=');

			if (equalPosition != std::string::npos) {
				std::string key = line.substr(0, equalPosition);
				std::string value = line.substr(++equalPosition);

				trim(key);
				trim(value);

				defaultSettings[key] = value;
			}
		}
		file.close();
	}
	else {
		std::cerr << "Warning: Config file not found! Using default settings.\n";
	}
}

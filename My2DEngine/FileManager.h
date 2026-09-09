#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

class FileManager {
public:
	explicit FileManager(std::string_view path) : filePath(path) {}

	void LoadFile();

	template <typename T>
	T Load(std::string_view key, const T defaultValue) {
		auto it = dataMap.find(key);
		if (it == dataMap.end()) {
			return defaultValue;
			std::cerr << "Warning: Key '" << key << "' not found. Using default value.\n";
		}

		const std::string keyFound = it->second;

		if constexpr (std::is_same_v<T, std::string>) {
			return keyFound;
		} else {
			T valueFound;
			std::stringstream Convert(keyFound);
			Convert >> valueFound;

			if (Convert.fail() || !Convert.eof()) {
				std::cerr << "Warning: Failed to convert value for key '" << key << "'. Using default value.\n";
				return defaultValue;
			}

			return valueFound;
		}
	}

private:
	std::map<std::string, std::string, std::less<>> dataMap;
	std::string filePath;
};

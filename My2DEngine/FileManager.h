#pragma once
#include <map>
#include <sstream>

class FileManager {
private:
	std::map<std::string, std::string, std::less<>> defaultSettings;
	const std::string filePath = "Settings.ini";

public:
	void LoadDefaultSettings();

	template <typename T>
	T Load(std::string_view key, const T defaultValue) {

		auto it = defaultSettings.find(key);
		if (it == defaultSettings.end()) {
			return defaultValue;
		}

		const std::string keyFound = it->second;

		if constexpr (std::is_same_v<T, std::string>) {
			return keyFound;
		}
		else {
			T valueFound;
			std::stringstream Convert(keyFound);
			Convert >> valueFound;

			if (Convert.fail()) {
				std::cerr << "Warning: Failed to convert value for key '" << key << "'. Using default value.\n";
				return defaultValue;
			}

			return valueFound;
		}
	}
};

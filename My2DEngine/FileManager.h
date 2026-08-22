#pragma once
#include <map>
#include <sstream>

class FileManager {
private:
	std::map<std::string, std::string> defaultSettings;
	const std::string filePath = "Settings.ini";

public:
    //void Save(); 
	void LoadDefaultSettings();

	template <typename T>
	T Load(const std::string& key, T defaultValue) {

		if (defaultSettings.find(key) != defaultSettings.end()) {

			std::string keyFound = defaultSettings[key];

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
		return defaultValue;
	}
};

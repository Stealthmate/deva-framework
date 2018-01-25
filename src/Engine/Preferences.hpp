#ifndef DEVA_ENGINE_PREFERENCES_HPP
#define DEVA_ENGINE_PREFERENCES_HPP

#include "Config.hpp"
#include <any>

namespace DevaEngine {

	class Preferences {

	public:

		DEVA_ENGINE_API std::any getPreference(const std::string &key) const {
			auto i = prefs.find(key);
			if (i == prefs.end()) return std::any();
			return i->second;
		}

	private:
		std::unordered_map<std::string, std::any> prefs;
	};

}

#endif //DEVA_ENGINE_PREFERENCES_HPP
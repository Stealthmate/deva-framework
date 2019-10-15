#ifndef DEVA_FRAMEWORK_CORE_CONFIG_HPP
#define DEVA_FRAMEWORK_CORE_CONFIG_HPP

#include "../Config.hpp"

namespace DevaFramework {

	template<typename T>
	std::enable_if_t<std::disjunction_v<std::is_fundamental<T>, std::is_enum<T>>, std::string> strf(const T& v) {
		std::ostringstream stm;
		stm << v;
		return stm.str();
	}

	template<typename T>
	std::enable_if_t<std::is_pointer_v<T>, std::string> strf(const T& v) {
		std::ostringstream stm;
		stm << (uintptr_t)v;
		return stm.str();
	}

}


#endif // DEVA_FRAMEWORK_CORE_CONFIG_HPP
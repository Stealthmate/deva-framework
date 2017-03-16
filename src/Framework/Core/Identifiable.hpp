#ifndef DEVA_FRAMEWORK_CORE_IDENTIFIABLE_HPP
#define DEVA_FRAMEWORK_CORE_IDENTIFIABLE_HPP

#include "Config.hpp"

namespace DevaFramework {

	template<typename IDType>
	class Identifiable {
	public:

		DEVA_FRAMEWORK_API virtual IDType getUUID() const = 0;

	};

}

#endif // DEVA_FRAMEWORK_CORE_IDENTIFIABLE_HPP
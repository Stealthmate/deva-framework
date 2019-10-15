#ifndef DEVA_FRAMEWORK_UTIL_CSTRUCT_DELETER_HPP
#define DEVA_FRAMEWORK_UTIL_CSTRUCT_DELETER_HPP

#include "Config.hpp"

#include <vector>
#include <functional>
#include <memory>

namespace DevaFramework {

	template <typename T>
	struct CStructDeleter {
		T obj;
		std::vector<std::shared_ptr<void>> ptrs;
		
		CStructDeleter(std::initializer_list<std::shared_ptr<void>> ptrs)
		{
			for (auto & ptr : ptrs) {
				this->ptrs.push_back(ptr);
			}
		}

		CStructDeleter& operator=(std::initializer_list<std::shared_ptr<void>> ptrs)
		{
			CStructDeleter o(ptrs);
			this->obj = o.obj;
			this->ptrs = o.ptrs;
		}

	};

}

#endif //DEVA_FRAMEWORK_UTIL_CSTRUCT_DELETER_HPP
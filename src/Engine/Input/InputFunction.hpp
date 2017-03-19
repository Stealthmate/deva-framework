#ifndef DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP
#define DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP

#include "../Config.hpp"

#include <functional>

namespace DevaEngine
{
	class InputFunction
	{
	public:
		typedef bool(*rawfunc)();
		typedef std::function<bool()> lambdafunc;

	private:
		rawfunc vk;

	public:

		DEVA_ENGINE_API InputFunction();
		DEVA_ENGINE_API InputFunction(rawfunc vk);
		DEVA_ENGINE_API InputFunction(lambdafunc& vk);

		DEVA_ENGINE_API 
			bool operator()();
	};
}

#endif //DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP
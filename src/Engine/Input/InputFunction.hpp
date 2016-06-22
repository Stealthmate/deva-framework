#ifndef DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP
#define DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP

#include "../Config.hpp"

namespace DevaEngine
{
	class InputFunction
	{
	public:
		typedef bool(*rawfunc)();
		typedef std::function<bool()> lambdafunc;

	private:
		rawfunc f;

	public:

		DEVA_ENGINE_API InputFunction();
		DEVA_ENGINE_API InputFunction(rawfunc f);
		DEVA_ENGINE_API InputFunction(lambdafunc& f);

		DEVA_ENGINE_API virtual bool operator()();
	};
}

#endif //DEVA_ENGINE_INPUT_INPUT_FUNCTION_HPP
#ifndef DEVA_ENGINE_INPUT_CONFIG_HPP
#define DEVA_ENGINE_INPUT_CONFIG_HPP

#include "../Config.hpp"

#include <DevaFramework/Include/Window.hpp>

namespace DevaEngine
{
	class InputFunction
	{
	public:
		virtual bool operator()() = 0;
	};
}


#endif //DEVA_ENGINE_INPUT_CONFIG_HPP
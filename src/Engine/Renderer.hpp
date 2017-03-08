#ifndef DEVA_ENGINE_RENDERER_HPP
#define DEVA_ENGINE_RENDERER_HPP

#include "Config.hpp"

namespace DevaEngine
{
	class Renderer
	{
	public:
		Renderer();

		virtual void renderExample() = 0;

		virtual ~Renderer() {}
	};
}

#endif //DEVA_ENGINE_REDNERER_HPP
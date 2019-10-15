#ifndef DEVA_ENGINE_GRAPHICS_SCREEN_RENDERER_HPP
#define DEVA_ENGINE_GRAPHICS_SCREEN_RENDERER_HPP

#include "Config.hpp"

#include "Renderer.hpp"

namespace DevaEngine {

	class ScreenRenderer : public Renderer {
	public:
		ScreenRenderer(
			const Preferences &prefs,
			std::unique_ptr<RenderAPI> api,
			const DevaFramework::Window &wnd);
	};

}

#endif //DEVA_ENGINE_GRAPHICS_SCREEN_RENDERER_HPP
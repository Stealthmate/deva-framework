#ifndef DEVA_ENGINE_GRAPHICS_RENDER_API_HPP
#define DEVA_ENGINE_GRAPHICS_RENDER_API_HPP

#include "Config.hpp"

#include <DevaFramework\Include\Math.hpp>

namespace DevaFramework {
	class Window;
	struct Image;
	class Model;
	class Uuid;
}

namespace DevaEngine {

	class Preferences;

	struct RenderObject {
		const DevaFramework::Model *model;
		DevaFramework::vec4 frontVector;
	};
	typedef DevaFramework::Uuid RenderObjectID;
	typedef DevaFramework::Uuid ImageID;

	class RenderAPI {
	public:

		virtual void onInit(const Preferences &prefs) = 0;
		virtual void onSetupRenderTargetWindow(const DevaFramework::Window &wnd) = 0;
		virtual void onSetupRenderTargetImage(const DevaFramework::Image &img) = 0;
		virtual void onDestroy() = 0;

		virtual void loadObject(const RenderObjectID &id, const RenderObject &ro) = 0;
		virtual void updateObjectMVP(const RenderObjectID &roid, const DevaFramework::mat4 &mvp) = 0;
		virtual void unloadObject(const RenderObjectID &roid) = 0;
		virtual ImageID loadImage(const DevaFramework::Image &img) = 0;

		virtual void drawScene() = 0;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_RENDER_API_HPP
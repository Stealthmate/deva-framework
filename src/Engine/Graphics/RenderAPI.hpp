#ifndef DEVA_ENGINE_GRAPHICS_RENDER_API_HPP
#define DEVA_ENGINE_GRAPHICS_RENDER_API_HPP

#include "Config.hpp"

#include <DevaFramework\Include\Math.hpp>

namespace DevaFramework {
	class Window;
	struct Image;
	struct Mesh;
	class Uuid;
}

namespace DevaEngine {

	class Preferences;
	struct Model;

	struct RenderObject {
		std::shared_ptr<DevaFramework::Mesh> model;
		DevaFramework::vec4 frontVector;
	};
	typedef DevaFramework::Uuid RenderObjectID;
	typedef DevaFramework::Uuid ShaderID;

	class RenderAPI {
	public:

		virtual void onInit(const Preferences &prefs) = 0;
		virtual void onSetupRenderTargetWindow(const DevaFramework::Window &wnd) = 0;
		virtual void onSetupRenderTargetImage(const DevaFramework::Image &img) = 0;
		virtual void onDestroy() = 0;

		//virtual ShaderID loadShader() = 0;
		//virtual void unloadShader(const ShaderID &id);

		virtual RenderObjectID loadMesh(const DevaFramework::Mesh &mesh) = 0;
		virtual void unloadMesh(const RenderObjectID &id) = 0;
		virtual void setMeshMVP(const RenderObjectID &id, const DevaFramework::mat4 &mvp) = 0;

		virtual RenderObjectID loadTexture(const DevaFramework::Image &tex) = 0;
		virtual void unloadTexture(const RenderObjectID &id) = 0;

		virtual void bindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) = 0;
		virtual void unbindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) = 0;

		virtual void drawScene() = 0;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_RENDER_API_HPP
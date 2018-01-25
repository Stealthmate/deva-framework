#ifndef DEVA_ENGINE_RENDERER_HPP
#define DEVA_ENGINE_RENDERER_HPP

#include "Config.hpp"

#include "Scene.hpp"

#include<DevaFramework\Graphics\Image.hpp>
#include<DevaFramework\Graphics\Model.hpp>
#include "../Preferences.hpp"

namespace DevaEngine
{
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

		virtual void loadObject(const RenderObjectID &id, const RenderObject &ro) = 0;
		virtual void updateObjectMVP(const RenderObjectID &roid, const DevaFramework::mat4 &mvp) = 0;
		virtual void unloadObject(const RenderObjectID &roid) = 0;
		virtual ImageID loadImage(const DevaFramework::Image &img) = 0;

		virtual void drawScene() = 0;
	};

	class Renderer
	{
	public:
		class ImplSceneUpdateListener;
		friend class ImplSceneUpdateListener;

		DEVA_ENGINE_API Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI);

		DEVA_ENGINE_API void loadImage(const DevaFramework::Image& img);

		DEVA_ENGINE_API void prepareScene(std::shared_ptr<Scene> scene);
		DEVA_ENGINE_API void render();
		virtual ~Renderer() {}


		DEVA_ENGINE_API void loadDrawableObject(const SceneObjectID &id, const DrawableObject & object);
		DEVA_ENGINE_API void updateDrawableObjectMVP(const SceneObjectID &id, const DevaFramework::mat4 &mvp);
		DEVA_ENGINE_API void unloadDrawableObject(const SceneObjectID &id);

	protected:

		std::unique_ptr<RenderAPI> api;

		std::shared_ptr<Scene> currentScene;
		std::shared_ptr<ImplSceneUpdateListener> sceneListener;


		std::unordered_map<RenderObjectID, RenderObject> renderObjects;
		std::unordered_map<RenderObjectID, DevaFramework::mat4> renderObjectMVPs;
	};

	class ScreenRenderer : public Renderer {
	public:
		ScreenRenderer(
			const Preferences &prefs,
			std::unique_ptr<RenderAPI> api,
			const DevaFramework::Window &wnd);
	private:

	};
}

#endif //DEVA_ENGINE_REDNERER_HPP
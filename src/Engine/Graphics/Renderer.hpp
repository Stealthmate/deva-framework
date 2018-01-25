#ifndef DEVA_ENGINE_RENDERER_HPP
#define DEVA_ENGINE_RENDERER_HPP

#include "Config.hpp"

#include "Scene.hpp"

#include<DevaFramework\Graphics\Image.hpp>
#include<DevaFramework\Graphics\Model.hpp>

#include "RenderAPI.hpp"
#include "../Preferences.hpp"

namespace DevaEngine
{
	class Renderer
	{
	public:
		class ImplSceneUpdateListener;
		friend class ImplSceneUpdateListener;

		DEVA_ENGINE_API Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI);

		DEVA_ENGINE_API void loadImage(const DevaFramework::Image& img);

		DEVA_ENGINE_API void prepareScene(std::shared_ptr<Scene> scene);
		DEVA_ENGINE_API void render();

		DEVA_ENGINE_API void loadDrawableObject(const SceneObjectID &id, const DrawableObject & object);
		DEVA_ENGINE_API void updateDrawableObjectMVP(const SceneObjectID &id, const DevaFramework::mat4 &mvp);
		DEVA_ENGINE_API void unloadDrawableObject(const SceneObjectID &id);

	protected:

		std::unique_ptr<RenderAPI> api;

	private:
		std::shared_ptr<Scene> currentScene;
		std::shared_ptr<ImplSceneUpdateListener> sceneListener;
	};
}

#endif //DEVA_ENGINE_REDNERER_HPP
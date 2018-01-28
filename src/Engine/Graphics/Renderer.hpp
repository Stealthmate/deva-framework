#ifndef DEVA_ENGINE_RENDERER_HPP
#define DEVA_ENGINE_RENDERER_HPP

#include "Config.hpp"

#include "../Preferences.hpp"

namespace DevaFramework {
	struct Mesh;
	struct Image;
}

namespace DevaEngine
{
	class Scene;
	class SceneObject;
	struct Model;
	class RenderAPI;

	class Renderer
	{
	public:
		typedef DevaFramework::Uuid ModelID;
		typedef DevaFramework::Uuid MeshID;
		typedef DevaFramework::Uuid TextureID;

		DEVA_ENGINE_API Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI);

		DEVA_ENGINE_API std::shared_ptr<Scene> unloadCurrentScene();
		DEVA_ENGINE_API void prepareScene(std::shared_ptr<Scene> scene);
		DEVA_ENGINE_API void render();

		DEVA_ENGINE_API void loadSceneObject(std::shared_ptr<SceneObject> obj);
		DEVA_ENGINE_API void unloadSceneObject(std::shared_ptr<SceneObject> obj);

	protected:

		std::unique_ptr<RenderAPI> api;

	private:

		std::shared_ptr<Scene> currentScene;
		
		std::pair<MeshID, TextureID> loadModel(const Model &model);
		void unloadModel(const Model &model);

		class ImplSceneObjectObserver;
		friend class ImplSceneObjectObserver;
		class ImplSceneObserver;
		friend class ImplSceneObserver;
		std::shared_ptr<ImplSceneObserver> sceneListener;
		std::shared_ptr<ImplSceneObjectObserver> sceneObjectObserver;

		std::unordered_map<const SceneObject*, std::pair<MeshID, TextureID>> modelHandles;
		std::unordered_map<std::shared_ptr<const DevaFramework::Mesh>, std::pair<MeshID, uint32_t>> meshMap;
		std::unordered_map<std::shared_ptr<const DevaFramework::Image>, std::pair<TextureID, uint32_t>> texMap;

	};
}

#endif //DEVA_ENGINE_REDNERER_HPP
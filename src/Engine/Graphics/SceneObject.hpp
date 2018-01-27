#ifndef DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP

#include "Config.hpp"

#include <DevaFramework\Math\Matrix.hpp>

namespace DevaFramework {
	class Mesh;
	class Image;
}

namespace DevaEngine {

	class Model;

	class SceneObject;
	namespace Observers {
		class SceneObjectObservedMessage;
		class SceneObjectObserver : public DevaFramework::Observer<SceneObjectObservedMessage> {
		public:

			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onModelChanged(const SceneObject &object, const Model &model) = 0;
			virtual void onMVPChanged(const SceneObject &object, const DevaFramework::mat4 &mvp) = 0;
		};
	}

	struct Model {

		Model(
			std::shared_ptr<DevaFramework::Mesh> mesh,
			std::shared_ptr<DevaFramework::Image> texture,
			const DevaFramework::vec4 &frontVector) : mesh(mesh), texture(texture), frontVector(frontVector) {}

		const std::shared_ptr<const DevaFramework::Mesh> mesh;
		const std::shared_ptr<const DevaFramework::Image> texture;
		const DevaFramework::vec4 frontVector;
	};

	class SceneObject : public DevaFramework::Observable<Observers::SceneObjectObservedMessage> {
	public:
		class SceneObjectUpdate {
		public:
			DEVA_ENGINE_API SceneObjectUpdate& setModel(std::shared_ptr<Model> model);
			DEVA_ENGINE_API SceneObjectUpdate& setMVP(const DevaFramework::mat4 &mvp);
			
			DEVA_ENGINE_API void commit();

		private:

			DEVA_ENGINE_API SceneObjectUpdate(SceneObject &target);

			SceneObject& object;
			std::pair<bool, DevaFramework::mat4> newMVP;
			std::pair<bool, std::shared_ptr<Model>> newModel;

			friend class SceneObject;
		};

		DEVA_ENGINE_API SceneObjectUpdate update();

		DEVA_ENGINE_API const Model& model() const;
		DEVA_ENGINE_API const DevaFramework::mat4& mvp() const;

	private:

		friend class SceneObjectUpdate;

		std::shared_ptr<Model> mModel;
		DevaFramework::mat4 mMVP;
	};

	class Scene1;
	namespace Observers {
		class Scene1ObservedMessage;
		class Scene1Observer : public DevaFramework::Observer<Scene1ObservedMessage> {
		public:

			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onObjectsAdded(const Scene1 &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) = 0;
			virtual void onObjectRemoved(const Scene1 &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) = 0;
		};
	}

	class Scene1 : public DevaFramework::Observable<Observers::Scene1ObservedMessage> {
	public:
		class SceneUpdate {

			DEVA_ENGINE_API SceneUpdate(Scene1 &scene);

			DEVA_ENGINE_API SceneUpdate& addObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs);
			DEVA_ENGINE_API SceneUpdate& removeObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs);

			DEVA_ENGINE_API void commit();

		private:
			Scene1 & scene;
			std::unordered_set<std::shared_ptr<SceneObject>> newObjs;
			std::unordered_set<std::shared_ptr<SceneObject>> delObjs;
			friend class Scene1;
		};

		DEVA_ENGINE_API SceneUpdate update();
		DEVA_ENGINE_API const std::unordered_set<std::shared_ptr<SceneObject>>& getAllObjects() const;

	private:

		friend class SceneUpdate;

		std::unordered_set<std::shared_ptr<SceneObject>> objects;
	};

}

#endif //DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
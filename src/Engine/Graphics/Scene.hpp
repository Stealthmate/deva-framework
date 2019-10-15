#ifndef DEVA_ENGINE_SCENE_HPP
#define DEVA_ENGINE_SCENE_HPP

#include "Config.hpp"
#include <DevaFramework\Include\Util.hpp>
#include <DevaFramework\Include\Math.hpp>
#include "Camera.hpp"

#include <unordered_set>

namespace DevaFramework {
	struct Mesh;
}

namespace DevaEngine
{
	class SceneObject;

	class Scene;

	namespace Observers {
		class SceneObservedMessage;
		class SceneObserver : public DevaFramework::Observer<SceneObservedMessage> {
		public:

			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onObjectsAdded(const Scene &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) = 0;
			virtual void onObjectRemoved(const Scene &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) = 0;
		};
	}

	class Scene : public DevaFramework::Observable<Observers::SceneObservedMessage> {
	public:
		class SceneUpdate {
		public:
			DEVA_ENGINE_API SceneUpdate(Scene &scene);

			DEVA_ENGINE_API SceneUpdate& addObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs);
			DEVA_ENGINE_API SceneUpdate& removeObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs);

			DEVA_ENGINE_API void commit();

		private:
			Scene & scene;
			std::unordered_set<std::shared_ptr<SceneObject>> newObjs;
			std::unordered_set<std::shared_ptr<SceneObject>> delObjs;
			friend class Scene;
		};

		DEVA_ENGINE_API Scene();

		DEVA_ENGINE_API SceneUpdate update();
		DEVA_ENGINE_API const std::unordered_set<std::shared_ptr<SceneObject>>& getAllObjects() const;

	private:

		friend class SceneUpdate;

		std::unordered_set<std::shared_ptr<SceneObject>> objects;
	};


}


#endif //DEVA_ENGINE_SCENE_HPP
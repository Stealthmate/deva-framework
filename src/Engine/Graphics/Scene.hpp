#ifndef DEVA_ENGINE_SCENE_HPP
#define DEVA_ENGINE_SCENE_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Model.hpp>
#include "Camera.hpp"

#include <set>

namespace DevaEngine
{
	class Scene
	{
	public:
		typedef DevaFramework::Uuid ObjectID;

		class SceneUpdateListener {
		public:
			virtual void onNewObject(const ObjectID &id, const DevaFramework::Model &object) = 0;
			virtual void onObjectUpdated(const ObjectID &id, const DevaFramework::Model &object) = 0;
			virtual void onObjectRemoved(const ObjectID &id, const DevaFramework::Model &object) = 0;
		};


		DEVA_ENGINE_API Scene();

		DEVA_ENGINE_API const DevaFramework::Model& getObject(const ObjectID &id) const;
		DEVA_ENGINE_API const std::unordered_map<ObjectID, std::unique_ptr<DevaFramework::Model>>& getAllObjects() const { return objects; }

		DEVA_ENGINE_API ObjectID addObject(std::unique_ptr<DevaFramework::Model> object);
		DEVA_ENGINE_API Scene& updateObject(const ObjectID &id);
		DEVA_ENGINE_API std::unique_ptr<DevaFramework::Model> removeObject(const ObjectID &id);

		/*DEVA_ENGINE_API const Camera& getPrimaryCamera() const { return Camera(); }

		DEVA_ENGINE_API Camera& getPrimaryCamera() { return Camera(); }

		DEVA_ENGINE_API ObjectID addCamera(std::unique_ptr<Camera> camera) { return DevaFramework::Uuid(); }
		DEVA_ENGINE_API void setPrimaryCamera(ObjectID cameraID) {}
		DEVA_ENGINE_API void destroyCamera(ObjectID cameraID) {}*/

		DEVA_ENGINE_API void registerUpdateListener(std::shared_ptr<SceneUpdateListener> lstnr) const;
		DEVA_ENGINE_API void unregisterUpdateListener(std::shared_ptr<SceneUpdateListener> lstnr) const;

	private:

		std::unordered_map<ObjectID, std::unique_ptr<DevaFramework::Model>> objects;
		std::unordered_map<ObjectID, Camera> cameras;

		mutable std::set<std::shared_ptr<SceneUpdateListener>> mUpdateListeners;

	};
}


#endif //DEVA_ENGINE_SCENE_HPP
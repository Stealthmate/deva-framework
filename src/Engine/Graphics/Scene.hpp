#ifndef DEVA_ENGINE_SCENE_HPP
#define DEVA_ENGINE_SCENE_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Model.hpp>
#include <DevaFramework\Include\Util.hpp>
#include <DevaFramework\Include\Math.hpp>
#include "DrawableObject.hpp"
#include "Camera.hpp"

#include <unordered_set>
#include <set>

namespace DevaEngine
{
	class Scene;
	typedef DevaFramework::Uuid SceneObjectID;

	namespace Observers {
		class SceneObservedMessage;
		class SceneObserver : public DevaFramework::Observer<SceneObservedMessage> {
		public:

			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onNewObject(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) = 0;
			virtual void onObjectUpdated(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) = 0;
			virtual void onObjectRemoved(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) = 0;
		};
	}

	class Scene : public DevaFramework::Observable<Observers::SceneObservedMessage>
	{
	public:
		typedef Observers::SceneObserver SceneUpdateObserver;
		typedef std::shared_ptr<DrawableObject> ObjectPtr;

		DEVA_ENGINE_API Scene();

		DEVA_ENGINE_API std::unordered_set<SceneObjectID> getAllObjectIDs() const;

		DEVA_ENGINE_API SceneObjectID addObject(ObjectPtr object);
		DEVA_ENGINE_API DrawableObject& getObject(const SceneObjectID &id);
		DEVA_ENGINE_API const DrawableObject& getObject(const SceneObjectID &id) const;

		DEVA_ENGINE_API const DevaFramework::mat4& getObjectTransform(const SceneObjectID &id) const;
		DEVA_ENGINE_API void setObjectTransform(const SceneObjectID &id, const DevaFramework::mat4 &transform);

		DEVA_ENGINE_API ObjectPtr removeObject(const SceneObjectID &id);

	private:

		std::unordered_map<SceneObjectID, ObjectPtr> objects;
		std::unordered_map<SceneObjectID, DevaFramework::mat4> objectTransforms;
		std::shared_ptr<DrawableObject::DrawableObjectUpdateObserver> objectObserver;
	};


}


#endif //DEVA_ENGINE_SCENE_HPP
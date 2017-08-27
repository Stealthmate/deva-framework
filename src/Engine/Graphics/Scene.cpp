#include "Scene.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

class DevaEngine::Observers::SceneObservedMessage {
public:
	enum Event {
		NEW_OBJECT,
		OBJECT_UPDATED,
		OBJECT_REMOVED
	};

	SceneObservedMessage(Event evt, const Scene &scene, const SceneObjectID &id, const DrawableObject &object)
		: evt(evt), scene(scene), id(id), object(object) {}

	const Event evt;
	const Scene& scene;
	const SceneObjectID& id;
	const DrawableObject& object;
};

using DevaEngine::Observers::SceneObserver;
using SceneEvent = DevaEngine::Observers::SceneObservedMessage;
using SceneEventType = SceneEvent::Event;

namespace {

	void ensureHasObject(const SceneObjectID &id, const std::unordered_map<SceneObjectID, Scene::ObjectPtr> &map) {
		if (map.find(id) == map.end()) {
			throw DevaProgrammerErrorException(strformat("Scene does not contain object with id: {}", (std::string)id));
		}
	}

	class SceneObjectUpdateObserver : public DrawableObject::DrawableObjectUpdateObserver {
		Scene& scene;
	public:

		SceneObjectUpdateObserver(Scene& scene) : scene(scene) {}

		virtual void onObjectUpdated(const DrawableObject &object) override {

		};
		virtual void onVerticesChanged(const DrawableObject &object) override {
			scene.notifyObservers(SceneEvent(SceneEventType::OBJECT_UPDATED, scene, scene.findObjectID(object), object));
		};
	};
}

void SceneObserver::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
	switch (msg.evt) {
	case SceneEventType::NEW_OBJECT:
		onNewObject(msg.scene, msg.id, msg.object);
		break;
	case SceneEventType::OBJECT_REMOVED:
		onObjectRemoved(msg.scene, msg.id, msg.object);
		break;
	case SceneEventType::OBJECT_UPDATED:
		onObjectUpdated(msg.scene, msg.id, msg.object);
		break;
	default:
		throw DevaException("Received invalid message");
	}
}

Scene::Scene() : objectObserver(std::make_shared<SceneObjectUpdateObserver>(*this)) {}

SceneObjectID Scene::addObject(Scene::ObjectPtr object) {
	SceneObjectID id;
	::registerObserver(*object, *objectObserver);
	objects.insert({ id, std::move(object) });
	notifyObservers(SceneEvent(SceneEventType::NEW_OBJECT, *this, id, *objects.find(id)->second));
	return id;
}


std::unordered_set<SceneObjectID> Scene::getAllObjectIDs() const {
	std::unordered_set<SceneObjectID> ids;
	for (auto kv : objects)
		ids.insert(kv.first);
	return ids;
}

DrawableObject& Scene::getObject(const SceneObjectID &id) {
	auto i = objects.find(id);
	if (i == objects.end()) {
		throw DevaInvalidArgumentException(strformat("ObjectID {} does not exist in scene", id.str()));
	}

	return *i->second;
}

const DrawableObject& Scene::getObject(const SceneObjectID &id) const {
	auto i = objects.find(id);
	if (i == objects.end()) {
		throw DevaInvalidArgumentException(strformat("ObjectID {} does not exist in scene", id.str()));
	}

	return *i->second;
}

SceneObjectID Scene::findObjectID(const DrawableObject &obj) const {
	for (auto i : objects) {
		if (i.second.get() == &obj) return i.first;
	}

	throw DevaInvalidArgumentException("Object is not part of Scene");
}

Scene::ObjectPtr Scene::removeObject(const SceneObjectID &id) {
	ensureHasObject(id, objects);
	Scene::ObjectPtr obj = std::move(objects.find(id)->second);
	objects.erase(id);
	notifyObservers(SceneEvent(SceneEventType::OBJECT_REMOVED, *this, id, *obj));
	return obj;
}
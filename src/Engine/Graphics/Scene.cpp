#include "Scene.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

using SceneUpdate = Scene::SceneUpdate;
using SceneEvent = Observers::SceneObservedMessage;


struct Observers::SceneObservedMessage {
	enum Type {
		OBJECTS_ADDED = 0, OBJECTS_REMOVED = 1
	};

	Type type;
	Scene& scene;
	std::unordered_set<std::shared_ptr<SceneObject>> objs;
};

void Observers::SceneObserver::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
	switch (msg.type) {
	case SceneEvent::Type::OBJECTS_ADDED: {
		onObjectsAdded(msg.scene, msg.objs);
	}break;
	case SceneEvent::Type::OBJECTS_REMOVED: {
		onObjectRemoved(msg.scene, msg.objs);
	} break;
	default: {
		throw DevaException("Invalid SceneObjectObservedMessage type");
	}
	}
}

SceneUpdate::SceneUpdate(Scene &scene) : scene(scene) {}

SceneUpdate& SceneUpdate::addObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs) {
	newObjs.insert(objs.begin(), objs.end());
	return *this;
}

SceneUpdate& SceneUpdate::removeObjects(const std::unordered_set<std::shared_ptr<SceneObject>> &objs) {
	delObjs.insert(objs.begin(), objs.end());
	return *this;
}

void SceneUpdate::commit() {
	scene.objects.insert(newObjs.begin(), newObjs.end());
	scene.notifyObservers({ SceneEvent::OBJECTS_ADDED, scene, newObjs });
	for (auto o : delObjs) {
		auto i = scene.objects.find(o);
		if (i != scene.objects.end()) scene.objects.erase(i);
	}
	scene.notifyObservers({ SceneEvent::OBJECTS_REMOVED, scene, delObjs });
}

Scene::Scene() {}

SceneUpdate Scene::update() {
	return SceneUpdate(*this);
}

const std::unordered_set<std::shared_ptr<SceneObject>>& Scene::getAllObjects() const {
	return objects;
}
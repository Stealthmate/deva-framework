#include "Scene.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

namespace {

	enum Event {
		NEW_OBJECT,
		OBJECT_UPDATED,
		OBJECT_REMOVED
	};

	void alertListenersNewObject(std::set<std::shared_ptr<Scene::SceneUpdateListener>> &listeners, const Scene::ObjectID &id, const Model &object, Event evt)
	{
		for (auto lstnr : listeners) {
			switch (evt) {
			case NEW_OBJECT:
				lstnr->onNewObject(id, object);
				break;
			case OBJECT_UPDATED:
				lstnr->onObjectUpdated(id, object);
				break;
			case OBJECT_REMOVED:
				lstnr->onObjectRemoved(id, object);
				break;
			}
		}
	}

	void ensureHasObject(const Scene::ObjectID &id, const std::unordered_map<Scene::ObjectID, std::unique_ptr<Model>> &map) {
		if (map.find(id) == map.end()) {
			throw DevaProgrammerErrorException(strformat("Scene does not contain object with id: {}", (std::string)id));
		}
	}
}

Scene::Scene() = default;

Scene::ObjectID Scene::addObject(std::unique_ptr<DevaFramework::Model> object) {
	ObjectID id;
	objects.insert({ id, std::move(object) });
	alertListenersNewObject(mUpdateListeners, id, *objects.find(id)->second, NEW_OBJECT);

	return id;
}

const Model& Scene::getObject(const ObjectID &id) const {
	auto i = objects.find(id);
	if (i == objects.end()) {
		throw DevaInvalidArgumentException(strformat("ObjectID {} does not exist in scene", id.str()));
	}

	return *i->second;
}

std::unique_ptr<Model> Scene::removeObject(const ObjectID &id) {
	ensureHasObject(id, objects);
	std::unique_ptr<Model> obj = std::move(objects.find(id)->second);
	objects.erase(id);
	alertListenersNewObject(mUpdateListeners, id, *obj, OBJECT_REMOVED);
	return obj;
}

void Scene::registerUpdateListener(std::shared_ptr<Scene::SceneUpdateListener> lstnr) const {
	mUpdateListeners.insert(lstnr);
}

void Scene::unregisterUpdateListener(std::shared_ptr<Scene::SceneUpdateListener> lstnr) const {
	mUpdateListeners.erase(lstnr);
}
#include "SceneObject.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

using SceneObjectUpdate = SceneObject::SceneObjectUpdate;

struct Observers::SceneObjectObservedMessage {
	enum Type {
		MODEL_CHANGED, MVP_CHANGED
	};

	Type type;
	SceneObject &obj;
};

using Event = Observers::SceneObjectObservedMessage;

void Observers::SceneObjectObserver::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
	switch (msg.type) {
	case Event::Type::MODEL_CHANGED: {
		onModelChanged(msg.obj, msg.obj.model());
	}break;
	case Event::Type::MVP_CHANGED: {
		onMVPChanged(msg.obj, msg.obj.mvp());
	} break;
	default: {
		throw DevaException("Invalid SceneObjectObservedMessage type");
	}
	}
}

SceneObjectUpdate::SceneObjectUpdate(SceneObject &target)
	: object(target),
	newModel({ false, nullptr }),
	newMVP({ false, mat4() }) {}

SceneObjectUpdate& SceneObjectUpdate::setModel(std::shared_ptr<Model> model) {
	newModel = { true, model };
	return *this;
}

SceneObjectUpdate& SceneObjectUpdate::setMVP(const mat4 &mvp) {
	newMVP = { true, mvp };
	return *this;
}

void SceneObjectUpdate::commit() {
	if (newModel.first) {
		object.mModel = newModel.second;
		object.notifyObservers({ Event::MODEL_CHANGED, object });
	}
	if (newMVP.first) {
		object.mMVP = newMVP.second;
		object.notifyObservers({ Event::MVP_CHANGED, object });
	}
}


SceneObjectUpdate SceneObject::update() {
	return SceneObjectUpdate(*this);
}

const Model& SceneObject::model() const {
	return *mModel;
}

const mat4& SceneObject::mvp() const {
	return mMVP;
}



//



using SceneUpdate = Scene1::SceneUpdate;
using SceneEvent = Observers::Scene1ObservedMessage;


struct Observers::Scene1ObservedMessage {
	enum Type {
		OBJECTS_ADDED = 0, OBJECTS_REMOVED = 1
	};

	Type type;
	Scene1& scene;
	std::unordered_set<std::shared_ptr<SceneObject>> objs;
};

void Observers::Scene1Observer::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
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

SceneUpdate::SceneUpdate(Scene1 &scene) : scene(scene) {}

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

SceneUpdate Scene1::update() {
	return SceneUpdate(*this);
}

const std::unordered_set<std::shared_ptr<SceneObject>>& Scene1::getAllObjects() const {
	return objects;
}
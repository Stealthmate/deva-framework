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

SceneObject::SceneObject(std::shared_ptr<Model> model) : mModel(model) {
	
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
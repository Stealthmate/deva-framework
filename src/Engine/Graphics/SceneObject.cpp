#include "SceneObject.hpp"
#include <variant>
using namespace DevaFramework;
using namespace DevaEngine;

using SceneObjectUpdate = SceneObject::SceneObjectUpdate;

struct Observers::SceneObjectObservedMessage {
	enum Type {
		MODEL_CHANGED, MVP_CHANGED
	};

	Type type;
	SceneObject &obj;
	std::variant<std::shared_ptr<Model>, mat4> old;
};

using Event = Observers::SceneObjectObservedMessage;

void Observers::SceneObjectObserver::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
	switch (msg.type) {
	case Event::Type::MODEL_CHANGED: {
		onModelChanged(msg.obj, std::get<std::shared_ptr<Model>>(msg.old), msg.obj.model());
	}break;
	case Event::Type::MVP_CHANGED: {
		onMVPChanged(msg.obj, std::get<mat4>(msg.old), msg.obj.mvp());
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
		auto old = object.mModel;
		object.mModel = newModel.second;
		object.notifyObservers({ Event::MODEL_CHANGED, object, old });
	}
	if (newMVP.first) {
		auto old = object.mMVP;
		object.mMVP = newMVP.second;
		object.notifyObservers({ Event::MVP_CHANGED, object, old });
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
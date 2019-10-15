#include "GraphicObject.hpp"

#include <variant>

using namespace DevaFramework;
using namespace DevaEngine;

struct Observers::GraphicObjectObservedMessage {
	enum Type {
		MODEL_CHANGED, MVP_CHANGED
	};

	Type type;
	GraphicObject &obj;
	std::variant<std::shared_ptr<Model>, mat4> old;
};

using Event = Observers::GraphicObjectObservedMessage;

void Observers::GraphicObjectObserver::onNotify(ObservedObject &obj, const ObservedMessage &msg) {
	switch (msg.type) {
	case Event::Type::MODEL_CHANGED: {
		onModelChanged(msg.obj, std::get<std::shared_ptr<Model>>(msg.old), *msg.obj.model());
	}break;
	case Event::Type::MVP_CHANGED: {
		onMVPChanged(msg.obj, std::get<mat4>(msg.old), msg.obj.mvp());
	} break;
	default: {
		throw DevaException("Invalid GraphicObjectObservedMessage type");
	}
	}
}

GraphicObject::GraphicObject(std::shared_ptr<Model> model, const mat4 &mvp)
	: mModel(model), mMvp(mvp) {}

void GraphicObject::model(std::shared_ptr<Model> model) {
	mModel = model;
}

std::shared_ptr<Model> GraphicObject::model() const {
	return mModel;
}

void GraphicObject::mvp(const mat4 &mvp) {
	mMvp = mvp;
}

mat4 GraphicObject::mvp() const {
	return mMvp;
}
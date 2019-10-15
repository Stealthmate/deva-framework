#include "SceneObject.hpp"
#include <variant>
using namespace DevaFramework;
using namespace DevaEngine;

/*using SceneObjectUpdate = SceneObject::SceneObjectUpdate;

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
*/

SceneObject::SceneObject(std::shared_ptr<GraphicObject> model) : graphic(model) {
	
}

std::shared_ptr<GraphicObject> SceneObject::graphicPart() const {
	return graphic;
}
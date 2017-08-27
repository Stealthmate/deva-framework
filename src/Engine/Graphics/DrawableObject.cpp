#include "DrawableObject.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

class DevaEngine::Observers::DrawableObjectObservedMessage {
public:
	enum MessageType {
		OBJECT_CHANGED,
		VERTICES_CHANGED
	};

	MessageType type;
	DrawableObject &obj;
};

typedef Observers::DrawableObjectObservedMessage::MessageType MessageType;


void Observers::DrawableObjectObserver::onNotify(Observable<DrawableObjectObservedMessage> &o, const DrawableObjectObservedMessage &msg) {
	switch (msg.type) {
	case MessageType::OBJECT_CHANGED:
		onObjectUpdated(msg.obj);
		break;
	case MessageType::VERTICES_CHANGED:
		onVerticesChanged(msg.obj);
		break;
	default:
		throw DevaException("Wrong DrawableObjectObservedMessage");
	}
}

DrawableObject::DrawableObject(Model model) : model(std::move(model)) {}

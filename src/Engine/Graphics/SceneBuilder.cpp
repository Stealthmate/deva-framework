#include "SceneBuilder.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

SceneBuilder& SceneBuilder::addObject(const SceneObjectID &objectID, std::unique_ptr<Mesh> model) {

	if (objects.find(objectID) != objects.end()) {
		throw DevaProgrammerErrorException(strformat("Object with ID {} already exists!", (std::string)objectID));
	}

	objects.insert({ objectID, std::move(model) });

	return *this;
}

Scene SceneBuilder::build() {
	return Scene();
}
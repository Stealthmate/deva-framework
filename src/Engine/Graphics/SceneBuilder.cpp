#include "SceneBuilder.hpp"

#include <DevaFramework\Graphics\Mesh.hpp>

#include "Scene.hpp"
#include "SceneObject.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

SceneBuilder& SceneBuilder::addObject(std::shared_ptr<SceneObject> objectID, std::unique_ptr<Mesh> model) {

	if (objects.find(objectID) != objects.end()) {
		throw DevaProgrammerErrorException(strformat("Object with ID {} already exists!", (intptr_t)&*objectID));
	}

	objects.insert({ objectID, std::move(model) });

	return *this;
}

Scene SceneBuilder::build() {
	return Scene();
}
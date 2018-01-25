#include "Renderer.hpp"

using namespace DevaEngine;
using namespace DevaFramework;

class Renderer::ImplSceneUpdateListener : public Scene::SceneUpdateObserver {
public:

	Renderer & renderer;

	ImplSceneUpdateListener(Renderer& renderer) : renderer(renderer) {}

	virtual void onNewObject(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) {
		renderer.loadDrawableObject(id, object);
	}
	virtual void onObjectUpdated(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) {
		renderer.updateDrawableObjectMVP(id, scene.getObjectTransform(id));
	}
	virtual void onObjectRemoved(const Scene &scene, const SceneObjectID &id, const DrawableObject &object) {
		renderer.unloadDrawableObject(id);
	}
};

Renderer::Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI)
	: api(std::move(renderAPI)), sceneListener(new ImplSceneUpdateListener(*this))
{
	api->onInit(prefs);
}

void Renderer::loadDrawableObject(const SceneObjectID &id, const DrawableObject &obj) {
	RenderObject robj;
	robj.model = &obj.model;
	robj.frontVector = obj.frontVector;
	api->loadObject(id, robj);
}

void Renderer::updateDrawableObjectMVP(const SceneObjectID &id, const mat4 &mvp) {
	api->updateObjectMVP(id, mvp);
}

void Renderer::unloadDrawableObject(const SceneObjectID &id) {
	api->unloadObject(id);
}

void Renderer::prepareScene(std::shared_ptr<Scene> scene) {

	if (currentScene)
		::unregisterObserver(*currentScene, *sceneListener);
	::registerObserver(*scene, *sceneListener);

	auto &objs = scene->getAllObjectIDs();
	GuidGenerator ggen;
	for (auto &object : objs) {
		loadDrawableObject(object, scene->getObject(object));
	}
}

void Renderer::render() {
	api->drawScene();
}

ScreenRenderer::ScreenRenderer(
	const Preferences &prefs,
	std::unique_ptr<RenderAPI> api,
	const DevaFramework::Window &wnd)
	: Renderer(prefs, std::move(api)) {
	this->api->onSetupRenderTargetWindow(wnd);
}
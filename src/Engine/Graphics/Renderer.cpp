#include "Renderer.hpp"

#include <DevaFramework\Graphics\Mesh.hpp>
#include <DevaFramework\Graphics\Image.hpp>

#include "Scene.hpp"
#include "SceneObject.hpp"
#include "RenderAPI.hpp"


using namespace DevaEngine;
using namespace DevaFramework;

using ModelID = Renderer::ModelID;
using MeshID = Renderer::MeshID;
using TextureID = Renderer::TextureID;

class Renderer::ImplSceneObserver : public Observers::SceneObserver {
public:

	Renderer & renderer;

	ImplSceneObserver(Renderer& renderer) : renderer(renderer) {}


	virtual void onObjectsAdded(const Scene &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) {
		for (auto o : objects) {
			renderer.loadSceneObject(o);
		}
	}
	virtual void onObjectRemoved(const Scene &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) {
		for (auto o : objects) {
			renderer.unloadSceneObject(o);
		}
 	}
};

class Renderer::ImplSceneObjectObserver : public Observers::SceneObjectObserver {
public:
	Renderer & renderer;

	ImplSceneObjectObserver(Renderer& renderer) : renderer(renderer) {}

	virtual void onModelChanged(const SceneObject &object, const Model &model) {
		//TODO
	}
	virtual void onMVPChanged(const SceneObject &object, const DevaFramework::mat4 &mvp) {
		renderer.api->setMeshMVP(renderer.meshMap.find(object.model().mesh)->second.first, mvp);
	}
};

Renderer::Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI)
	: api(std::move(renderAPI)), sceneListener(new ImplSceneObserver(*this)), sceneObjectObserver(new ImplSceneObjectObserver(*this)), texMap()
{
	api->onInit(prefs);
}

void Renderer::loadSceneObject(std::shared_ptr<SceneObject> obj) {

	RenderObjectID meshid;
	auto mi = meshMap.find(obj->model().mesh);
	if (mi != meshMap.end()) {
		meshid = mi->second.first;
		mi->second.second++;
	}
	else {
		meshid = api->loadMesh(*obj->model().mesh);
		meshMap.insert({ obj->model().mesh, {meshid, 1} });
	}
	api->setMeshMVP(meshid, obj->mvp());

	RenderObjectID texid;
	auto ti = texMap.find(obj->model().texture);
	if (ti != texMap.end()) {
		texid = ti->second.first;
		ti->second.second++;
	}
	else {
		texid = api->loadTexture(*obj->model().texture);
		texMap.insert({ obj->model().texture,{ texid, 1 } });
	}

	::registerObserver(*obj, *sceneObjectObserver);

	modelHandles.insert({ obj, {meshid, texid} });
}

void Renderer::unloadSceneObject(std::shared_ptr<SceneObject> obj) {
	auto i = modelHandles.find(obj);
	if (i == modelHandles.end()) return;
	//TODO
	api->unloadMesh(i->second.first);
	api->unloadTexture(i->second.second);

	modelHandles.erase(i);
}

std::shared_ptr<Scene> Renderer::unloadCurrentScene() {

	if (currentScene)
		::unregisterObserver(*currentScene, *sceneListener);


	auto o = modelHandles.begin();
	while (o != modelHandles.end()) {
		api->unloadMesh(o->second.first);
		api->unloadTexture(o->second.second);
		o = modelHandles.erase(o);
	}
	meshMap.clear();
	texMap.clear();

	return std::move(currentScene);
}

void Renderer::prepareScene(std::shared_ptr<Scene> scene) {
	unloadCurrentScene();

	::registerObserver(*scene, *sceneListener);

	auto &objs = scene->getAllObjects();
	GuidGenerator ggen;
	for (auto &object : objs) {
		loadSceneObject(object);
	}
}

void Renderer::render() {
	api->drawScene();
}


#include "ScreenRenderer.hpp"
ScreenRenderer::ScreenRenderer(
	const Preferences &prefs,
	std::unique_ptr<RenderAPI> api,
	const DevaFramework::Window &wnd)
	: Renderer(prefs, std::move(api)) {
	this->api->onSetupRenderTargetWindow(wnd);
}
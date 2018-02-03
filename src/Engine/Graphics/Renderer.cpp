#include "Renderer.hpp"

#include <DevaFramework\Graphics\Mesh.hpp>
#include <DevaFramework\Graphics\Image.hpp>

#include "Scene.hpp"
#include "GraphicObject.hpp"
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
			renderer.loadGraphicObject(o->graphicPart());
		}
	}
	virtual void onObjectRemoved(const Scene &scene, const std::unordered_set<std::shared_ptr<SceneObject>> &objects) {
		for (auto o : objects) {
			renderer.unloadGraphicObject(o->graphicPart());
		}
	}
};

class Renderer::ImplGraphicObjectObserver : public Observers::GraphicObjectObserver {
public:
	Renderer & renderer;

	ImplGraphicObjectObserver(Renderer& renderer) : renderer(renderer) {}

	virtual void onModelChanged(const GraphicObject &object, std::shared_ptr<Model> oldModel, const Model &newModel) {
		auto ids = renderer.loadModel(newModel);
		renderer.modelHandles.insert_or_assign(&object, ids);
		renderer.unloadModel(*oldModel);
	}
	virtual void onMVPChanged(const GraphicObject &object, const DevaFramework::mat4 &oldMVP, const DevaFramework::mat4 &newMVP) {
		renderer.api->setMeshMVP(renderer.modelHandles.find(&object)->second.first, newMVP);
	}
};

Renderer::Renderer(const Preferences &prefs, std::unique_ptr<RenderAPI> renderAPI)
	: api(std::move(renderAPI)), sceneListener(new ImplSceneObserver(*this)), graphicObjectObserver(new ImplGraphicObjectObserver(*this)), texMap()
{
	api->onInit(prefs);
}

std::pair<MeshID, TextureID> Renderer::loadModel(const Model &model) {
	RenderObjectID meshid;
	auto mi = meshMap.find(model.mesh);
	if (mi != meshMap.end()) {
		meshid = mi->second.first;
		mi->second.second++;
	}
	else {
		meshid = api->loadMesh(*model.mesh);
		meshMap.insert({ model.mesh,{ meshid, 1 } });
	}

	RenderObjectID texid = Uuid::NULL_ID;
	if (model.texture) {
		auto ti = texMap.find(model.texture);
		if (ti != texMap.end()) {
			texid = ti->second.first;
			ti->second.second++;
		}
		else {
			texid = api->loadTexture(*model.texture);
			texMap.insert({ model.texture,{ texid, 1 } });
		}
	}

	api->bindMeshTexture(meshid, texid);

	return { meshid, texid };
}

void Renderer::unloadModel(const Model &model) {

	auto mi = meshMap.find(model.mesh);
	auto ti = texMap.find(model.texture);

	api->unbindMeshTexture(mi->second.first, ti->second.first);

	if (mi->second.second == 1) {
		api->unloadMesh(mi->second.first);
		meshMap.erase(mi);
	}

	if (ti->second.second == 1) {
		api->unloadTexture(ti->second.first);
		texMap.erase(ti);
	}
}

void Renderer::loadGraphicObject(std::shared_ptr<GraphicObject> obj) {

	auto ids = loadModel(*obj->model());
	api->setMeshMVP(ids.first, obj->mvp());

	::registerObserver(*obj, *graphicObjectObserver);

	modelHandles.insert({ obj.get(), {ids.first, ids.second} });
}

void Renderer::unloadGraphicObject(std::shared_ptr<GraphicObject> obj) {
	auto i = modelHandles.find(obj.get());
	if (i == modelHandles.end()) return;

	::unregisterObserver(*obj, *graphicObjectObserver);

	unloadModel(*obj->model());

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
		loadGraphicObject(object->graphicPart());
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
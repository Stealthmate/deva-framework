#ifndef DEVA_ENGINE_SCENE_HPP
#define DEVA_ENGINE_SCENE_HPP

#include "Config.hpp"
#include "GraphicsObject.hpp"
#include "Camera.hpp"

namespace DevaEngine
{
	class Scene
	{
	public:

		typedef uint32_t ObjectID;

		DEVA_ENGINE_API Scene();

		DEVA_ENGINE_API const GraphicsObject& getObject(uint32_t id) const { return GraphicsObject({}); }
		DEVA_ENGINE_API const std::unordered_map<ObjectID, std::unique_ptr<GraphicsObject>>& getAllObjects() const { return std::unordered_map<ObjectID, std::unique_ptr<GraphicsObject>>(); }

		DEVA_ENGINE_API const Camera& getPrimaryCamera() const { return Camera(); }

		DEVA_ENGINE_API Camera& getPrimaryCamera() { return Camera(); }

		DEVA_ENGINE_API ObjectID addCamera(std::unique_ptr<Camera> camera) { return 0; }
		DEVA_ENGINE_API void setPrimaryCamera(ObjectID cameraID) {}
		DEVA_ENGINE_API void destroyCamera(ObjectID cameraID) {}

	private:

		std::unordered_map<ObjectID, GraphicsObject> objects;
		std::unordered_map<ObjectID, Camera> cameras;

	};
}


#endif //DEVA_ENGINE_SCENE_HPP
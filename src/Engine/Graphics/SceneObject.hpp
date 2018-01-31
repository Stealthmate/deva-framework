#ifndef DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP

#include "Config.hpp"

#include "GraphicObject.hpp"

namespace DevaEngine {


	class SceneObject {
	public:

		DEVA_ENGINE_API SceneObject(std::shared_ptr<GraphicObject> model);

		DEVA_ENGINE_API std::shared_ptr<GraphicObject> graphicPart() const;

	private:

		SceneObject& operator=(const SceneObject&obj);
		SceneObject& operator=(SceneObject &&obj);

		std::shared_ptr<GraphicObject> graphic;
		DevaFramework::mat4 mMVP;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
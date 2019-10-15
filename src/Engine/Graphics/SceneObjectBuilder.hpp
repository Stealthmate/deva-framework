#ifndef DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP
#define DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP

#include "Config.hpp"

#include <DevaFramework\Math\Matrix.hpp>

namespace DevaEngine {

	class Model;
	class SceneObject;

	class SceneObjectBuilder {
	public:
		DEVA_ENGINE_API virtual SceneObject build() = 0;
	};

	class BasicSceneObjectBuilder : public SceneObjectBuilder {
	public:

		DEVA_ENGINE_API virtual SceneObject build() override;

		DEVA_ENGINE_API BasicSceneObjectBuilder& withModel(std::shared_ptr<Model> model);
		DEVA_ENGINE_API BasicSceneObjectBuilder& withMVP(const DevaFramework::mat4 &mvp);

	private:
		std::shared_ptr<Model> model;
		DevaFramework::mat4 mvp;
		
	};

}

#endif //DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP
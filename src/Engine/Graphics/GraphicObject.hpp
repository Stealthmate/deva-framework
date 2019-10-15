#ifndef DEVA_ENGINE_API_GRAPHICS_GRAPHIC_OBJECT_HPP
#define DEVA_ENGINE_API_GRAPHICS_GRAPHIC_OBJECT_HPP

#include "Config.hpp"

#include <DevaFramework\Math\Matrix.hpp>

namespace DevaFramework {
	struct Mesh;
	struct Image;
}

namespace DevaEngine {


	struct Model {

		Model(
			std::shared_ptr<DevaFramework::Mesh> mesh,
			std::shared_ptr<DevaFramework::Image> texture,
			const DevaFramework::vec4 &frontVector) : mesh(mesh), texture(texture), frontVector(frontVector) {}

		const std::shared_ptr<const DevaFramework::Mesh> mesh;
		const std::shared_ptr<const DevaFramework::Image> texture;
		const DevaFramework::vec4 frontVector;
	};

	class GraphicObject;

	namespace Observers {
		struct GraphicObjectObservedMessage;
		class GraphicObjectObserver : public DevaFramework::Observer<GraphicObjectObservedMessage> {
		public:
			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onModelChanged(const GraphicObject &object, std::shared_ptr<Model> oldModel, const Model &newModel) = 0;
			virtual void onMVPChanged(const GraphicObject &object, const DevaFramework::mat4 &oldMVP, const DevaFramework::mat4 &newMVP) = 0;
		};
	}


	class GraphicObject : public DevaFramework::Observable<Observers::GraphicObjectObservedMessage> {
	public:

		DEVA_ENGINE_API GraphicObject(std::shared_ptr<Model> model, const DevaFramework::mat4 &mvp = DevaFramework::mat4());

		DEVA_ENGINE_API std::shared_ptr<Model> model() const;
		DEVA_ENGINE_API void model(std::shared_ptr<Model> model);
		DEVA_ENGINE_API DevaFramework::mat4 mvp() const;
		DEVA_ENGINE_API void mvp(const DevaFramework::mat4 &mvp);
			
	private:
		std::shared_ptr<Model> mModel;
		DevaFramework::mat4 mMvp;
	};

}

#endif //DEVA_ENGINE_API_GRAPHICS_GRAPHIC_OBJECT_HPP
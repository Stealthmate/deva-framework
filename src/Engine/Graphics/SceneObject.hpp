#ifndef DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP

#include "Config.hpp"

#include <DevaFramework\Math\Matrix.hpp>

namespace DevaFramework {
	struct Mesh;
	struct Image;
}

namespace DevaEngine {

	struct Model;

	class SceneObject;
	namespace Observers {
		struct SceneObjectObservedMessage;
		class SceneObjectObserver : public DevaFramework::Observer<SceneObjectObservedMessage> {
		public:

			DEVA_ENGINE_API virtual void onNotify(ObservedObject &obj, const ObservedMessage &message) override final;

			virtual void onModelChanged(const SceneObject &object, const Model &model) = 0;
			virtual void onMVPChanged(const SceneObject &object, const DevaFramework::mat4 &mvp) = 0;
		};
	}

	struct Model {

		Model(
			std::shared_ptr<DevaFramework::Mesh> mesh,
			std::shared_ptr<DevaFramework::Image> texture,
			const DevaFramework::vec4 &frontVector) : mesh(mesh), texture(texture), frontVector(frontVector) {}

		const std::shared_ptr<const DevaFramework::Mesh> mesh;
		const std::shared_ptr<const DevaFramework::Image> texture;
		const DevaFramework::vec4 frontVector;
	};

	class SceneObject : public DevaFramework::Observable<Observers::SceneObjectObservedMessage> {
	public:
		class SceneObjectUpdate {
		public:
			DEVA_ENGINE_API SceneObjectUpdate& setModel(std::shared_ptr<Model> model);
			DEVA_ENGINE_API SceneObjectUpdate& setMVP(const DevaFramework::mat4 &mvp);
			
			DEVA_ENGINE_API void commit();

		private:

			DEVA_ENGINE_API SceneObjectUpdate(SceneObject &target);

			SceneObject& object;
			std::pair<bool, DevaFramework::mat4> newMVP;
			std::pair<bool, std::shared_ptr<Model>> newModel;

			friend class SceneObject;
		};

		DEVA_ENGINE_API SceneObjectUpdate update();

		DEVA_ENGINE_API SceneObject(std::shared_ptr<Model> model);

		DEVA_ENGINE_API const Model& model() const;
		DEVA_ENGINE_API const DevaFramework::mat4& mvp() const;

	private:

		SceneObject& operator=(const SceneObject&obj);
		SceneObject& operator=(SceneObject &&obj);

		friend class SceneObjectUpdate;

		std::shared_ptr<Model> mModel;
		DevaFramework::mat4 mMVP;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_SCENE_OBJECT_HPP
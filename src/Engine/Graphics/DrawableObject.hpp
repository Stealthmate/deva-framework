#ifndef DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_HPP

#include "Config.hpp"
#include <DevaFramework\Include\Math.hpp>
#include <DevaFramework\Include\Util.hpp>
#include <DevaFramework\Graphics\Model.hpp>
#include <DevaFramework\Util\MultiTypeVector.hpp>

namespace DevaEngine {

	class DrawableObject;

	namespace Observers {

		class DrawableObjectObservedMessage;

		class DrawableObjectObserver : public DevaFramework::Observer<DrawableObjectObservedMessage> {
		public:
			virtual void onObjectUpdated(const DrawableObject &object) = 0;
			virtual void onVerticesChanged(const DrawableObject &object) = 0;
		protected:
			DEVA_ENGINE_API virtual void onNotify(DevaFramework::Observable<DrawableObjectObservedMessage> &obj, const DrawableObjectObservedMessage &message) override;
		};
	}

	class DrawableObject : public DevaFramework::Observable<Observers::DrawableObjectObservedMessage> {
	public:
		typedef Observers::DrawableObjectObserver DrawableObjectUpdateObserver;

		DEVA_ENGINE_API DrawableObject(DevaFramework::Mesh model);
		DrawableObject& operator=(const DrawableObject &obj) = delete;
		DrawableObject& operator=(DrawableObject &&obj) = delete;

	//private:
		DevaFramework::Mesh model;
		DevaFramework::vec4 frontVector;

	};
}

#endif // DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_HPP
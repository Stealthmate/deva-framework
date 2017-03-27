#ifndef DEVA_FRAMEWORK_UTIL_OBSERVER_HPP
#define DEVA_FRAMEWORK_UTIL_OBSERVER_HPP

#include "Config.hpp"
#include <unordered_set>
#include <functional>

namespace DevaFramework {

	template<typename ObserverType>
	class ObservableSubject {
	public:
		typedef std::weak_ptr<ObserverType> ObserverPtr;
	private:
		class ObserverPtrHasher {
		public:
			typedef ObserverPtr arg_t;
			size_t operator()(const arg_t &arg) const {
				return (uintptr_t)&arg;
			}
		};
		class ObserverPtrEqualto {
		public:
			typedef ObserverPtr arg_t;
			bool operator()(const arg_t &lhs, const arg_t &rhs) const {
				return &lhs == &rhs;
			}
		};
	public:
		void registerObserver(ObserverPtr observer) const {
			mObservers.insert(observer);
		}
		void unregisterObserver(ObserverPtr observer) const {
			mObservers.erase(observer);
		}

		void purge() const {
			for (auto o = mObservers.begin(); o != mObservers.end();) {
				if (o->expired()) o = mObservers.erase(o);
				else o++;
			}
		}

		const std::unordered_set<ObserverPtr, ObserverPtrHasher, ObserverPtrEqualto>& getObservers() const {
			return mObservers;
		}

		virtual ~ObservableSubject() {}

	private:
		mutable std::unordered_set<ObserverPtr, ObserverPtrHasher, ObserverPtrEqualto> mObservers;

	};
}

#endif // DEVA_FRAMEWORK_UTIL_OBSERVER_INTERFACE_HPP
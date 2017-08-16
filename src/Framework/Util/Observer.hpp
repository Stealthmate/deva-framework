#ifndef DEVA_FRAMEWORK_UTIL_OBSERVER_HPP
#define DEVA_FRAMEWORK_UTIL_OBSERVER_HPP

#include "Config.hpp"
#include <unordered_set>
#include <functional>

namespace DevaFramework {

	template<typename T> class Observable;
	template<typename T> class Observer;
	template<typename T> void registerObserver(Observable<T> &observable, Observer<T> &observer) {
		observable.registerObserver(observer);
		observer.addTarget(observable);
	}
	template<typename T> void unregisterObserver(Observable<T> &observable, Observer<T> &observer) {
		observable.unregisterObserver(observer);
		observer.removeTarget(observable);
	}

	template<typename ObservableType>
	class Observer {
	public:
		virtual ~Observer() {
			for (auto & t : targets) {
				unregisterObserver(*t, *this);
			}
		}
		
		void onObservableDestroy(Observable<ObservableType> *o) {
			targets.erase(std::find(targets.begin(), targets.end(), o));
		}
	private:
		std::list<Observable<ObservableType>*> targets;

		void addTarget(Observable<ObservableType> &t) {
			targets.push_back(&t);
		}

		void removeTarget(Observable<ObservableType> &t) {
			targets.erase(std::find(targets.begin(), targets.end(), &t));
		}

		friend void DevaFramework::registerObserver(Observable<ObservableType>&, Observer<ObservableType>&);
		friend void DevaFramework::unregisterObserver(Observable<ObservableType> &, Observer<ObservableType>&);
	};

	template<typename ObservableType>
	class Observable {
	public:
		typedef Observer<ObservableType>* ObserverPtr;

		const std::list<ObserverPtr>& getObservers() const {
			return mObservers;
		}

		virtual ~Observable() {
			for (auto o : mObservers) {
				o->onObservableDestroy(this);
			}
		}

	private:
		std::list<ObserverPtr> mObservers;

		void registerObserver(Observer<ObservableType> &o) {
			mObservers.push_back(&o);
		}
		void unregisterObserver(const Observer<ObservableType> &o) {
			mObservers.erase(std::find(mObservers.begin(), mObservers.end(), &o));
		}

		friend void DevaFramework::registerObserver(Observable<ObservableType>&, Observer<ObservableType>&);
		friend void DevaFramework::unregisterObserver(Observable<ObservableType> &, Observer<ObservableType>&);
	};
}

#endif // DEVA_FRAMEWORK_UTIL_OBSERVER_INTERFACE_HPP
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

	template<typename ObservedMessageType>
	class Observer {
	public:

		typedef ObservedMessageType ObservedMessage;
		typedef Observable<ObservedMessageType> ObservedObject;

		virtual ~Observer() {
			while(targets.size() > 0) {
				unregisterObserver(**targets.begin(), *this);
			}
		}

		virtual void onObservableDestroy(Observable<ObservedMessageType> *o) {}

		virtual void onNotify(ObservedObject &o, const ObservedMessageType & msg) = 0;

	private:
		std::list<Observable<ObservedMessageType>*> targets;

		void addTarget(Observable<ObservedMessageType> &t) {
			targets.push_back(&t);
		}

		void removeTarget(Observable<ObservedMessageType> &t) {
			targets.erase(std::find(targets.begin(), targets.end(), &t));
		}

		void onObservableDestroyInternal(Observable<ObservedMessageType> *o) {

			targets.erase(std::find(targets.begin(), targets.end(), o));
		}

		friend void DevaFramework::registerObserver(Observable<ObservedMessageType>&, Observer<ObservedMessageType>&);
		friend void DevaFramework::unregisterObserver(Observable<ObservedMessageType> &, Observer<ObservedMessageType>&);
		friend class Observable<ObservedMessageType>;
	};

	template<typename ObservedMessageType>
	class Observable {
	public:
		typedef Observer<ObservedMessageType>* ObserverPtr;

		const std::list<ObserverPtr>& getObservers() const {
			return mObservers;
		}

		virtual ~Observable() {
			for (auto o : mObservers) {
				o->onObservableDestroy(this);
			}
		}

		void notifyObservers(const ObservedMessageType &message) {
			for (auto o : mObservers) {
				o->onNotify(*this, message);
			}
		}

	private:
		std::list<ObserverPtr> mObservers;

		void registerObserver(Observer<ObservedMessageType> &o) {
			mObservers.push_back(&o);
		}
		void unregisterObserver(const Observer<ObservedMessageType> &o) {
			mObservers.erase(std::find(mObservers.begin(), mObservers.end(), &o));
		}

		friend void DevaFramework::registerObserver(Observable<ObservedMessageType>&, Observer<ObservedMessageType>&);
		friend void DevaFramework::unregisterObserver(Observable<ObservedMessageType> &, Observer<ObservedMessageType>&);
	};
}

#endif // DEVA_FRAMEWORK_UTIL_OBSERVER_INTERFACE_HPP
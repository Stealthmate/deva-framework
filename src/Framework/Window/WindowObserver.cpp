#include "WindowObserver.hpp"

using namespace DevaFramework;

DevaFramework::WindowObserver::WindowObserver() : event_listeners() {}

void DevaFramework::WindowObserver::attachListener(WindowEvent evt, std::shared_ptr<WindowEventListener>&& evtlstnr)
{
	auto evt_key = this->event_listeners.find(evt);
	if (evt_key == this->event_listeners.end())
	{
		this->event_listeners.insert({ evt, std::vector<std::shared_ptr<WindowEventListener>>(0) });
		evt_key = this->event_listeners.find(evt);
	}
	std::vector<std::shared_ptr<WindowEventListener>> &evt_listener_list = evt_key->second;
	evt_listener_list.push_back(std::move(evtlstnr));
}

void DevaFramework::WindowObserver::attachListener(
	std::initializer_list<WindowEvent> evts, 
	std::shared_ptr<WindowEventListener>&& evtlstnr)
{
	for (auto evt : evts)
	{
		auto evt_key = this->event_listeners.find(evt);
		if (evt_key == this->event_listeners.end())
		{
			this->event_listeners.insert({ evt, std::vector<std::shared_ptr<WindowEventListener>>(0) });
			evt_key = this->event_listeners.find(evt);
		}
		std::vector<std::shared_ptr<WindowEventListener>> &evt_listener_list = evt_key->second;
		evt_listener_list.push_back(evtlstnr);
	}
}

void DevaFramework::WindowObserver::fire(std::shared_ptr<WindowEventStruct> evt)
{
	WindowEvent evttype = evt->evt;
	
	auto i = event_listeners.find(evttype);
	if (i == event_listeners.end()) return;

	auto& listener_list = i->second;

	switch (evttype)
	{
	case WindowEvent::EVENT_KEY_UP:
	case WindowEvent::EVENT_KEY_DOWN:
		{
			for (std::shared_ptr<WindowEventListener> &lstnr : listener_list)
			{
				lstnr->onKeyEvent(*reinterpret_cast<WindowEventStruct_KeyEvent*>(evt.get()));
			}
		}
	}
}

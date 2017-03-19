#include "Time.hpp"

#include <chrono>

using namespace DevaFramework;

namespace {
	typedef std::chrono::microseconds Microseconds;
	typedef std::chrono::milliseconds Milliseconds;
	typedef std::chrono::seconds Seconds;
}

size_t DevaFramework::getSystemTime(TimeUnit unit) {

	using Clock = std::chrono::steady_clock;

	auto instant = Clock::now();

	switch (unit) {
	case MICROSECONDS: return std::chrono::time_point_cast<Microseconds>(instant).time_since_epoch().count();
	case MILLISECONDS: return std::chrono::time_point_cast<Milliseconds>(instant).time_since_epoch().count();
	case SECONDS: return std::chrono::time_point_cast<Seconds>(instant).time_since_epoch().count();
	default: {
		LOG.w("getSystemTime: Invalid TimeUnit specified. Defaulting to milliseconds");
		return std::chrono::time_point_cast<Milliseconds>(instant).time_since_epoch().count();
	}
	}
}
#ifndef DEVA_FRAMEWORK_CORE_UUID_HPP
#define DEVA_FRAMEWORK_CORE_UUID_HPP

#include "Config.hpp"

#include <guid.h>

namespace DevaFramework {
	class Uuid {
	public:
		DEVA_FRAMEWORK_API static const Uuid NULL_ID;

		DEVA_FRAMEWORK_API Uuid();

		DEVA_FRAMEWORK_API operator std::string() const;

		inline std::string str() const { return (std::string) *this; }

	private:
		Guid uuid;

		Uuid(Guid guid);
	};

	inline bool operator==(const Uuid &lhs, const Uuid &rhs) { return (std::string) lhs == (std::string)rhs; }
	inline bool operator!=(const Uuid &lhs, const Uuid &rhs) { return !(lhs == rhs); }
	inline bool operator<(const DevaFramework::Uuid& lhs, const DevaFramework::Uuid &rhs) { return (std::string)lhs < (std::string)rhs; }
	inline bool operator<=(const DevaFramework::Uuid& lhs, const DevaFramework::Uuid &rhs) { return !(rhs < lhs); }
	inline bool operator>(const DevaFramework::Uuid& lhs, const DevaFramework::Uuid &rhs) { return !(lhs <= rhs); }
	inline bool operator>=(const DevaFramework::Uuid& lhs, const DevaFramework::Uuid &rhs) { return !(lhs < rhs); }
}

namespace std
{
	template<> struct hash<DevaFramework::Uuid>
	{
		typedef DevaFramework::Uuid argument_type;
		typedef std::size_t result_type;
		inline result_type operator()(argument_type const& arg) const { return std::hash<std::string>()(arg); }
	};
	template<> struct hash<const DevaFramework::Uuid>
	{
		typedef const DevaFramework::Uuid argument_type;
		typedef std::size_t result_type;
		inline result_type operator()(argument_type const& arg) const { return std::hash<std::string>()(arg); }
	};

}


#endif // DEVA_FRAMEWORK_CORE_UUID_HPP
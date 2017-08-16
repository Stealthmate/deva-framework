#ifndef DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIALIZABLE_HPP
#define DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIALIZABLE_HPP

#include "Config.hpp"

namespace DevaFramework {

	template <typename T>
	struct SerialFixedSize {
		static constexpr size_t v = 0;
		static_assert(SerialFixedSize<T>::v, "Type does not define fixed serial size");
	};

	template <typename Type> struct BinarySerializer {
		void operator()(const Type &t, ByteOutputStream &buffer) const {
			static_assert(false, "No serializer found for type");
		}
	};

	template <typename Type> struct BinaryDeserializer {
		Type operator()(ByteInputStream &bis) const {
			static_assert(false, "No deserializer found for type");
		}
	};
}

#endif // DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIALIZABLE_HPP
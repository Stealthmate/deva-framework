#ifndef DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
#define DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP

#include "Config.hpp"
#include "ByteBuffer.hpp"
#include "../Core/Serializable.hpp"
#include <vector>
#include <tuple>
#include <string>

namespace DevaFramework {

	namespace internal {
		template < typename ... Types >
		struct SizeOfVariadicTypes;

		template < typename TFirst >
		struct SizeOfVariadicTypes < TFirst >
		{
			static const auto Value = (sizeof(TFirst));
		};

		template < typename TFirst, typename ... TRemaining >
		struct SizeOfVariadicTypes < TFirst, TRemaining ... >
		{
			static const auto v = (sizeof(TFirst) + SizeOfVariadicTypes<TRemaining...>::Value);
		};

		template <typename... T, std::size_t... I>
		auto subtuple_(const std::tuple<T...>& t, std::index_sequence<I...>) {
			return std::make_tuple(std::get<I>(t)...);
		}

		template <int Trim, typename... T>
		auto subtuple(const std::tuple<T...>& t) {
			return subtuple_(t, std::make_index_sequence<sizeof...(T)-Trim>());
		}
	}

	template<typename First, typename ... Types>
	using Pack = std::tuple<First, Types...>;

	template<typename First, typename ... Types>
	struct Packsize {
		constexpr static size_t v = sizeof(First) + DevaFramework::SizeOfVariadicTypes<Types...>::Value;
	};

	template <typename First, typename ... Types>
	struct Serializer<Pack<First, Types...>> {

		static size_t constexpr N_TYPES = 1 + sizeof...(Types);

		void operator()(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {
			serialize<0>(pack, buf);
		}

	private:

		template<size_t i>
		void serialize(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {
			buf << std::get<i>(pack);
			serialize<i + 1>(pack, buf);
		}

		template <>
		void serialize<N_TYPES>(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {}
	};

	template<typename First, typename ... Types>
	struct Deserializer<Pack<First, Types...>> {
		static size_t constexpr N_TYPES = 1 + sizeof...(Types);
		using PackType = Pack<First, Types...>;

		mutable PackType pack;

		PackType operator()(ByteInputStream &buf) const {
			return deserialize<0>(buf);
		}

	private:

		template<size_t i>
		PackType deserialize(ByteInputStream &buf) const {
			buf >> std::get<i>(pack);
			return deserialize<i + 1>(buf);
		}

		template <>
		PackType deserialize<N_TYPES>(ByteInputStream &buf) const {
			return pack;
		}
	};

	template<typename T, size_t OBJSIZE>
	class SerialVector {
	public:
		SerialVector() : SerialVector(0) {}
		SerialVector(size_t size) : array(size * OBJSIZE), currentSize(0), currentCapacity(size) {}

		void push_back(const T& obj) {

			if (currentCapacity == 0) {
				reserve(1);
			}

			if (currentSize == currentCapacity) {
				reserve((size_t)(currentSize * 3.0 / 2.0) + 1);
			}

			auto ptr = array.asWriteOnly(currentSize * OBJSIZE, currentCapacity * OBJSIZE, false).lock();

			Serializer<T>()(obj, *ptr);
			currentSize += 1;
		}

		/**
			@desc Returns COPY of value!!!
		
		**/
		T operator[](size_t i) const {
			if (i > currentSize) {
				throw DevaInvalidArgumentException("Index out of bounds " + strm(i));
			}

			auto ptr = array.asReadOnly(i * OBJSIZE, (i + 1) * OBJSIZE).lock();
			return Deserializer<T>()(*ptr);
		}

		size_t capacity() const {
			return currentCapacity;
		}

		size_t size() const {
			return currentSize;
		}

		void reserve(size_t capacity) {
			if (currentCapacity < capacity) {
				array.resize((size_t)(capacity * OBJSIZE));
				currentCapacity = capacity;
			}
		}

	private:


		ByteBuffer array;
		size_t currentSize;
		size_t currentCapacity;
	};

	template<typename First, typename ...Rest>
	using PackedVector = SerialVector<Pack<First, Rest...>, internal::SizeOfVariadicTypes<First, Rest...>::v>;

}

#endif // DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
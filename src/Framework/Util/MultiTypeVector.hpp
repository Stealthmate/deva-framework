#ifndef DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
#define DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP

#include "Config.hpp"
#include "ByteBufferStream.hpp"
#include "../Core/Serialization/Binary/BinarySerializable.hpp"
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
			static const auto v = (sizeof(TFirst));
		};

		template < typename TFirst, typename ... TRemaining >
		struct SizeOfVariadicTypes < TFirst, TRemaining ... >
		{
			static const auto v = (sizeof(TFirst) + SizeOfVariadicTypes<TRemaining...>::v);
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
		constexpr static size_t v = sizeof(First) + internal::SizeOfVariadicTypes<Types...>::v;
	};

	template<typename First, typename ... Rest>
	struct SerialFixedSize<Pack<First, Rest...>> {
		static constexpr size_t v = Packsize<First, Rest...>::v;
	};

	template <typename First, typename ... Types>
	struct BinarySerializer<Pack<First, Types...>> {

		static size_t constexpr N_TYPES = 1 + sizeof...(Types);

		void operator()(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {
			serializeBinary<0>(pack, buf);
		}

	private:

		template<size_t i>
		void serializeBinary(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {
			buf << std::get<i>(pack);
			serializeBinary<i + 1>(pack, buf);
		}

		template <>
		void serializeBinary<N_TYPES>(const Pack<First, Types...> &pack, ByteOutputStream &buf) const {}
	};

	template<typename First, typename ... Types>
	struct BinaryDeserializer<Pack<First, Types...>> {
		static size_t constexpr N_TYPES = 1 + sizeof...(Types);
		using PackType = Pack<First, Types...>;

		mutable PackType pack;

		PackType operator()(ByteInputStream &buf) const {
			return deserializeBinary<0>(buf);
		}

	private:

		template<size_t i>
		PackType deserializeBinary(ByteInputStream &buf) const {
			buf >> std::get<i>(pack);
			return deserializeBinary<i + 1>(buf);
		}

		template <>
		PackType deserializeBinary<N_TYPES>(ByteInputStream &buf) const {
			return pack;
		}
	};


	template<typename T, size_t OBJSIZE = SerialFixedSize<T>::v>
	class FixedSizeSerialVector : public DataHolder<ByteBuffer> {
	public:
		FixedSizeSerialVector() : FixedSizeSerialVector(0) {}
		FixedSizeSerialVector(size_t size) : array(size * OBJSIZE), currentSize(0), currentCapacity(size) {}

		void push_back(const T& obj) {

			if (currentCapacity == 0) {
				reserve(1);
			}

			if (currentSize == currentCapacity) {
				reserve((size_t)(currentSize * 3.0 / 2.0) + 1);
			}

			write_element(obj, currentSize);
			currentSize += 1;
		}

		/**
			@desc Returns COPY of value!!!
		
		**/
		T operator[](size_t i) const {
			if (i > currentSize) {
				throw DevaInvalidArgumentException("Index out of bounds " + strf(i));
			}

			return read_element(i);
		}

		void replace(size_t i, const T& obj) {
			if (i > currentSize) {
				throw DevaInvalidArgumentException("Index out of bounds " + str(i));
			}


			write_element(i, currentSize);
			currentSize += 1;
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

	protected:

		virtual ByteBuffer onRelease() override {
			return std::move(array.release());
		}

	private:

		void write_element(const T& el, size_t pos) {
			auto ostr = ByteBufferOutputStream(array);
			ostr.setPosition(pos*OBJSIZE);
			BinarySerializer<T>()(el, ostr);
		}

		T read_element(size_t pos) const {
			auto istr = ByteBufferInputStream(const_cast<ByteBuffer&>(array));
			istr.setPosition(pos * OBJSIZE);
			return BinaryDeserializer<T>()(istr);
		}


		ByteBuffer array;
		size_t currentSize;
		size_t currentCapacity;
	};

	template<typename First>
	using TypedPackedVector = FixedSizeSerialVector<First>;

	template<typename First, typename ...Rest>
	using PackedVector = FixedSizeSerialVector<Pack<First, Rest...>>;

}

#endif // DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
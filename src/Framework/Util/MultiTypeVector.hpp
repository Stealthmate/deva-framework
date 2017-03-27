#ifndef DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
#define DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP

#include "Config.hpp"
#include <vector>
#include <tuple>
#include <string>

namespace DevaFramework {

	constexpr size_t sizeOfVariadicTypes() {
		return 0;
	}

	template<typename First, typename ...Rest>
	constexpr size_t sizeOfVariadicTypes(const First &first, const Rest&...rest) {
		return sizeof head + sizeOfVariadicTypes(rest...);
	}

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
		static const auto Value = (sizeof(TFirst) + SizeOfVariadicTypes<TRemaining...>::Value);
	};

	template <typename... T, std::size_t... I>
	auto subtuple_(const std::tuple<T...>& t, std::index_sequence<I...>) {
		return std::make_tuple(std::get<I>(t)...);
	}

	template <int Trim, typename... T>
	auto subtuple(const std::tuple<T...>& t) {
		return subtuple_(t, std::make_index_sequence<sizeof...(T)-Trim>());
	}

	template<typename First, typename ... Types>
	class MultiTypeVector {
		static_assert(std::negation_v<std::is_same<void, First>>);
		static_assert(std::disjunction<std::negation<std::is_same<void, Types>>...>::value, "Cannot use void as type");
		constexpr static size_t N_TYPES = sizeof...(Types);
		static_assert(N_TYPES < 2, "Cannot use MultiTypeVector with less than 2 data types");
		constexpr static size_t SIZE_TYPES = SizeOfVariadicTypes<Types...>::Value;

	public:

		template<typename First>
		void push_back(const First &first) {
			push_back_bytes(first);
		}

		void push_back(const std::tuple<typename First, typename Types...> &items) {
			push_back_bytes(std::get<0>(items));
			push_back(subtuple<sizeof...(Types)>(items));
		}

		std::tuple<typename First&, typename Types&...> operator[](size_t index) {
			return elementAtIndex<0, First, Types...>(index);
		}

	private:

		template<typename T>
		void push_back_bytes(const T& item) {
			const byte_t* data = reinterpret_cast<const byte_t*>(&item);
			size_t size = sizeof(T);
			for (size_t j = 0;j < size;j++) {
				bytes.push_back(data[j]);
			}
		}

		template<size_t offset>
		std::tuple<> elementAtIndex(size_t index) {
			return {};
		}

		template<size_t offset, typename eFirst, typename ...eRest>
		std::tuple<eFirst&, eRest&...> elementAtIndex(size_t index) {
			byte_t* el = &bytes[index * SIZE_TYPES];
			eFirst& first = *reinterpret_cast<eFirst*>(el + offset);
			return std::tuple_cat(std::tuple<eFirst&>(first), elementAtIndex<offset + sizeof(eFirst), eRest...>(index));
		}

		std::vector<byte_t> bytes;
	};

}

#endif // DEVA_FRAMEWORK_UTIL_MULTI_TYPE_VECTOR_HPP
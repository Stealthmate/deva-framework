#ifndef DEVA_FRAMEWORK_CORE_SERIALIZABLE_HPP
#define DEVA_FRAMEWORK_CORE_SERIALIZABLE_HPP

#include "Config.hpp"
#include "DevaLogger.hpp"
#include "../Util/ByteBuffer.hpp"


namespace DevaFramework {

	template <typename> class BinarySerialContainer;

	namespace internal {

		template<typename T>
		class BinaryContainer {

			friend class BinarySerialContainer<T>;

			mutable ByteBuffer buffer;
		public:
			ByteBuffer& getBuffer() const {
				return buffer;
			}
		private:
			BinaryContainer(ByteBuffer &&buf) : buffer(buf) {}
		};
	}

	template <typename Type> struct Serializer {
		void operator()(const Type &t, ByteOutputStream &buffer) const {
			static_assert(false, "No serializer found for type");
		}
	};

	template <typename Type> struct Deserializer {
		Type operator()(ByteInputStream &bis) const {
			static_assert(false, "No deserializer found for type");
		}
	};

	template <typename Type>
	BinarySerialContainer<Type> serialize(const Type &t) {
		ByteBuffer buf(sizeof Type);
		Serializer<Type>()(t, *buf.asWriteOnly(0, buf.size(), true).lock());
		return BinarySerialContainer<Type>(std::move(buf));
	}

	template <typename Type>
	Type deserialize(const BinarySerialContainer<Type> &bsc) {
		return Deserializer<Type>()(*bsc.getBC().getBuffer().asReadOnly(0, bsc.getBC().getBuffer().size()).lock());
	}

	template <typename Type>
	class BinarySerialContainer {
	public:
		friend BinarySerialContainer<Type> DevaFramework::serialize(const Type &t);
		friend Type DevaFramework::deserialize(const BinarySerialContainer<Type> &bsc);

	private:
		internal::BinaryContainer<Type> bc;

		BinarySerialContainer(ByteBuffer &&buf) : bc(std::move(buf)) {}

		const internal::BinaryContainer<Type>& getBC() const {
			return bc;
		}
	};


	template <typename Type>
	BinarySerialContainer<Type[]> serialize(const std::vector<Type> &items) {
		ByteBuffer buf(sizeof Type * items.size());
		auto ptr = buf.asWriteOnly(0, buf.size(), true);
		for (int i = 0;i < items.size(); i++)
		{
			Serializer<Type>()(items[i], *ptr.lock());
		}
		return BinarySerialContainer<Type[]>(std::move(buf));
	}

	template <typename Type>
	std::vector<Type> deserialize(const BinarySerialContainer<Type[]> &bsc) {
		std::vector<Type> vec;
		auto ptr = bsc.getBC().getBuffer().asReadOnly(0, bsc.getBC().getBuffer().size()).lock();
		while (ptr->available() > 0) {
			vec.push_back(Deserializer<Type>()(*ptr));
		}
		return vec;
	}

	template <typename Type>
	class BinarySerialContainer<Type[]> {
	public:
		friend BinarySerialContainer<Type[]> DevaFramework::serialize(const std::vector<Type> &t);
		friend std::vector<Type> DevaFramework::deserialize(const BinarySerialContainer<Type[]> &bsc);

	private:
		mutable internal::BinaryContainer<Type[]> bc;

		BinarySerialContainer(ByteBuffer &&buf) : bc(std::move(buf)) {}

		internal::BinaryContainer<Type[]>& getBC() const {
			return bc;
		}
	};

}

#endif // DEVA_FRAMEWORK_CORE_SERIALIZABLE_HPP
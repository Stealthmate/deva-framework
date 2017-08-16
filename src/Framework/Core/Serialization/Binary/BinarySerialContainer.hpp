#ifndef DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIAL_CONTAINER_HPP
#define DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIAL_CONTAINER_HPP

#include "Config.hpp"
#include "BinarySerialContainer.hpp"

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


	template <typename Type>
	BinarySerialContainer<Type> serializeBinary(const Type &t) {
		ByteBuffer buf(sizeof Type);
		BinarySerializer<Type>()(t, *buf.asWriteOnly(0, buf.size(), true).lock());
		return BinarySerialContainer<Type>(std::move(buf));
	}

	template <typename Type>
	Type deserializeBinary(const BinarySerialContainer<Type> &bsc) {
		return BinaryDeserializer<Type>()(*bsc.getBC().getBuffer().asReadOnly(0, bsc.getBC().getBuffer().size()).lock());
	}

	template <typename Type>
	class BinarySerialContainer {
	public:
		friend BinarySerialContainer<Type> DevaFramework::serializeBinary(const Type &t);
		friend Type DevaFramework::deserializeBinary(const BinarySerialContainer<Type> &bsc);

	private:
		internal::BinaryContainer<Type> bc;

		BinarySerialContainer(ByteBuffer &&buf) : bc(std::move(buf)) {}

		const internal::BinaryContainer<Type>& getBC() const {
			return bc;
		}
	};


	template <typename Type>
	BinarySerialContainer<Type[]> serializeBinary(const std::vector<Type> &items) {
		ByteBuffer buf(sizeof Type * items.size());
		auto ptr = buf.asWriteOnly(0, buf.size(), true);
		for (int i = 0;i < items.size(); i++)
		{
			BinarySerializer<Type>()(items[i], *ptr.lock());
		}
		return BinarySerialContainer<Type[]>(std::move(buf));
	}

	template <typename Type>
	std::vector<Type> deserializeBinary(const BinarySerialContainer<Type[]> &bsc) {
		std::vector<Type> vec;
		auto ptr = bsc.getBC().getBuffer().asReadOnly(0, bsc.getBC().getBuffer().size()).lock();
		while (ptr->available() > 0) {
			vec.push_back(BinaryDeserializer<Type>()(*ptr));
		}
		return vec;
	}

	template <typename Type>
	class BinarySerialContainer<Type[]> {
	public:
		friend BinarySerialContainer<Type[]> DevaFramework::serializeBinary(const std::vector<Type> &t);
		friend std::vector<Type> DevaFramework::deserializeBinary(const BinarySerialContainer<Type[]> &bsc);

	private:
		mutable internal::BinaryContainer<Type[]> bc;

		BinarySerialContainer(ByteBuffer &&buf) : bc(std::move(buf)) {}

		internal::BinaryContainer<Type[]>& getBC() const {
			return bc;
		}
	};

}


#endif //DEVA_FRAMEWORK_CORE_SERIALIZATION_BINARY_BINARY_SERIAL_CONTAINER_HPP
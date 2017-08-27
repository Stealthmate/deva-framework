#ifndef DEVA_FRAMEWORK_CORE_DATA_HOLDER_HPP
#define DEVA_FRAMEWORK_CORE_DATA_HOLDER_HPP

#include "Config.hpp"

namespace DevaFramework {

	template<typename DataType>
	class DataHolder {
	public:

		DataType release() {
			mIsDataValid = false;
			return onRelease();
		}

		
		explicit DataHolder(const DataHolder<DataType> &holder) = default;
		DataHolder<DataType>& operator=(const DataHolder<DataType> &holder) = default;

		DataHolder(DataHolder<DataType> &&holder) = default;
		DataHolder<DataType>& operator=(DataHolder<DataType> &&holder) = default;

	protected:
		DataHolder() : mIsDataValid(true) {}

		virtual DataType onRelease() = 0;

		bool isDataValid() const {
			return mIsDataValid;
		}

	private:
		bool mIsDataValid;
	};

}

#endif //DEVA_FRAMEWORK_CORE_DATA_HOLDER_HPP
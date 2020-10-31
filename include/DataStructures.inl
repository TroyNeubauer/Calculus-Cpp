#include "DataStructures.hpp"
#pragma once



namespace calc
{
	template<typename T>
	inline Buffer<T>::Buffer(T* begin, T* end)
		: m_Begin(begin), m_End(end)
	{
	}

	template<typename T>
	inline T& Buffer<T>::Get(std::size_t index)
	{
		CheckRange(index);
		return m_Begin[index];
	}

	template<typename T>
	inline const T& Buffer<T>::Get(std::size_t index) const
	{
		CheckRange(index);
		return m_Begin[index];
	}

	template<typename T>
	inline void Buffer<T>::CheckRange(std::size_t triedIndex)
	{
		if (triedIndex >= Size())
		{
			throw "Element out of range!";
		}
	}


	template<typename T>
	inline Vector<T>::Vector(T* data, T* capacity)
		: Buffer(data, data), m_Cap(capacity)
	{
	}

	template<typename T>
	inline void Vector<T>::Remove(std::size_t index)
	{
		CheckRange(index);
		T* toRemove = Begin() + index;
		toRemove->~();

		std::copy(toRemove + 1, End(), toRemove);
		m_End--;
	}



	template<typename T, std::size_t SIZE>
	inline SmallVector<T, SIZE>::SmallVector()
		: Vector(m_Store, SIZE)
	{
	}

}


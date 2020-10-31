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
	inline void Buffer<T>::CheckRange(std::size_t triedIndex) const
	{
		if (triedIndex >= Size())
		{
			throw "Element out of range!";
		}
	}


	template<typename T>
	inline Vector<T>::Vector(T* data, T* capacity)
		: Buffer(data, data), m_Capacity(capacity)
	{
	}

	template<typename T>
	inline void Vector<T>::Remove(std::size_t index)
	{
		CheckRange(index);
		T* toRemove = Begin() + index;
		//(*toRemove)~();

		std::copy(toRemove + 1, End(), toRemove);
		m_End--;
	}


	template<typename T>
	inline void Vector<T>::Clear()
	{
		const T* const end = End();
		for (T* current = Begin(); current != end; current++)
		{
			current->~T();
		}

		m_End = m_Begin;
	}


	template<typename T, std::size_t SIZE>
	inline SmallVector<T, SIZE>::SmallVector()
		: Vector(m_Store, m_Store + SIZE)
	{
	}

	template<typename T, std::size_t SIZE>
	inline void SmallVector<T, SIZE>::Reserve(std::size_t minCapacity)
	{
		if (minCapacity > Capacity())
		{
			if (IsSmall())
			{
				//Move from internal buffer to the heap
				T* oldBegin = m_Begin;
				T* oldEnd = m_End;
				T* oldCap = m_Capacity;
				std::size_t size = oldEnd - oldBegin;
				if (minCapacity < SIZE * 2)
				{
					//In case we're growing by 1 element above what the internal capacity can hold, allocate a bit more storage
					//to avoid having to copy when the next element is added
					minCapacity = SIZE * 2;
				}
				m_Begin = new T[minCapacity];
				m_End = m_Begin + size;
				m_Capacity = m_Begin + minCapacity;

				for (T *old = oldBegin, *current = m_Begin; current != m_End; old++, current++)
				{
					//Move construct new values
					new (current) T(std::move(*old));
				}
			}
		}
	}


	template<typename T, std::size_t SIZE>
	inline void SmallVector<T, SIZE>::CopyFrom(const T* begin, const T* end)
	{
		Clear();
		std::size_t newSize = end - begin;
		Reserve(newSize);
		std::copy(begin, end, m_Begin);
		m_End = m_Begin + newSize;
	}

	template<typename T, std::size_t SIZE>
	inline T& SmallVector<T, SIZE>::Add(const T& value)
	{
		Reserve(Size() + 1);
		T* newElem = m_End;

		return *newElem;
	}
	
	
	template<typename T, std::size_t SIZE>
	inline T& SmallVector<T, SIZE>::Add(T&& value)
	{
		Reserve(Size() + 1);
		T* newElem = m_End;

		return *newElem;
	}


	template<typename T, std::size_t SIZE>
	inline SmallVector<T, SIZE>::~SmallVector()
	{
		if (m_Begin != m_Store)
		{
			//Clear again here because otherwise the elements will be deconstructed after the memory is freed
			//Clear will be called again in Vector::~Vector but this will be cheap because the size will already be 0
			Clear();
			delete[] m_Begin;
		}
	}


}


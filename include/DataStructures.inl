
namespace calc
{
	template<typename T>
	Buffer<T>::Buffer(T* begin, T* end)
		: m_Begin(begin), m_End(end)
	{
	}

	template<typename T>
	T& Buffer<T>::Get(std::size_t index)
	{
		this->CheckRange(index);
		return this->m_Begin[index];
	}

	template<typename T>
	const T& Buffer<T>::Get(std::size_t index) const
	{
		this->CheckRange(index);
		return this->m_Begin[index];
	}

	template<typename T>
	void Buffer<T>::CheckRange(std::size_t triedIndex) const
	{
		if (triedIndex >= this->Size())
		{
			throw "Element out of range!";
		}
	}


	template<typename T>
	Vector<T>::Vector()
		: Buffer<T>(nullptr, nullptr), m_Capacity(nullptr)
	{
	}


	template<typename T>
	Vector<T>::Vector(T* data, T* capacity)
		: Buffer<T>(data, data), m_Capacity(capacity)
	{
	}

	template<typename T>
	void Vector<T>::Remove(std::size_t index)
	{
		this->CheckRange(index);
		T* toRemove = this->Begin() + index;
		//(*toRemove)~();

		std::copy(toRemove + 1, this->End(), toRemove);
		this->m_End--;
	}


	template<typename T>
	void Vector<T>::Clear()
	{
		const T* const end = this->End();
		for (T* current = this->Begin(); current != end; current++)
		{
			current->~T();
		}

		this->m_End = this->m_Begin;
	}


	template<typename T, std::size_t SIZE>
	SmallVector<T, SIZE>::SmallVector()
		: Vector<T>(m_Store, m_Store + SIZE)
	{
	}

	template<typename T, std::size_t SIZE>
	SmallVector<T, SIZE>::SmallVector(std::initializer_list<T> list)
		: Vector<T>()
	{
		CopyFrom(list.begin(), list.end());
	}

	template<typename T, std::size_t SIZE>
	void SmallVector<T, SIZE>::Reserve(std::size_t minCapacity)
	{
		if (minCapacity > this->Capacity())
		{
			if (this->IsSmall())
			{
				//Move from internal buffer to the heap
				T* oldBegin = this->m_Begin;
				T* oldEnd = this->m_End;
				T* oldCap = this->m_Capacity;
				std::size_t size = oldEnd - oldBegin;

				if (minCapacity < SIZE * 2)
				{
					//In case we're growing by 1 element above what the internal capacity can hold, allocate a bit more storage
					//to avoid having to copy when the next element is added
					minCapacity = SIZE * 2;
				}
				this->m_Begin = new T[minCapacity];
				this->m_End = this->m_Begin + size;
				this->m_Capacity = this->m_Begin + minCapacity;

				for (T *old = oldBegin, *current = this->m_Begin; current != this->m_End; old++, current++)
				{
					//Move construct new values
					new (current) T(std::move(*old));
				}
			}
		}
	}


	template<typename T, std::size_t SIZE>
	void SmallVector<T, SIZE>::CopyFrom(const T* begin, const T* end)
	{
		std::size_t newSize = end - begin;
		this->Clear();
		this->Reserve(newSize);

		std::copy(begin, end, this->m_Begin);
		this->m_End = this->m_Begin + newSize;
	}

	template<typename T, std::size_t SIZE>
	T& SmallVector<T, SIZE>::Add(const T& value)
	{
		this->Reserve(this->Size() + 1);
		T* newElem = this->m_End;

		return *newElem;
	}
	
	
	template<typename T, std::size_t SIZE>
	T& SmallVector<T, SIZE>::Add(T&& value)
	{
		this->Reserve(this->Size() + 1);
		T* newElem = this->m_End;

		return *newElem;
	}


	template<typename T, std::size_t SIZE>
	SmallVector<T, SIZE>::~SmallVector()
	{
		if (this->m_Begin != this->m_Store)
		{
			//Clear again here because otherwise the elements will be deconstructed after the memory is freed
			//Clear will be called again in Vector::~Vector but this will be cheap because the size will already be 0
			this->Clear();
			delete[] this->m_Begin;
		}
	}


}


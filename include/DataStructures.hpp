#pragma once

#include <cstdint>

namespace calc {

	//Represents a contigious fixed block of memory
	template<typename T>
	class Buffer
	{
	public:
		Buffer(T* begin, T* end);
		inline Buffer(T* data, std::size_t capacity) : Buffer(data, data + capacity) { }

		T& Get(std::size_t index);
		const T& Get(std::size_t index) const;

		T& operator[](std::size_t index) { return this->Get(index); }
		const T& operator[](std::size_t index) const { return this->Get(index); }

		inline std::size_t Size() const { return this->m_End - this->m_Begin; }

		inline T* Data() { return this->m_Begin; }
		inline const T* Data() const { return this->m_Begin; }

		inline T* Begin() { return this->m_Begin; }
		inline const T* Begin() const { return this->m_Begin; }

		inline T* End() { return this->m_End; }
		inline const T* End() const { return this->m_End; }

		inline T* begin() { return this->m_Begin; }
		inline const T* begin() const { return this->m_Begin; }

		inline T* end() { return this->m_End; }
		inline const T* end() const { return this->m_End; }

		virtual ~Buffer() {}

	protected:
		void CheckRange(std::size_t index) const;

	protected:
		T* m_Begin;
		T* m_End;
	};

	template<typename T>
	class Vector : public Buffer<T>
	{
	protected:
		//Only called internally when we know we are about to assign these pointers anyway
		explicit Vector();

	public:
		Vector(T* begin, T* end, T* capacity);
		Vector(T* begin, T* end);

		inline std::size_t Capacity() const { return this->m_Capacity - this->m_Begin; }

		virtual void Reserve(std::size_t minCapacity) = 0;

		virtual void CopyFrom(const T* begin, const T* end) = 0;

		virtual T& Add(const T& value) = 0;
		virtual T& Add(T&& value) = 0;

		virtual void Remove(std::size_t index);

		void Clear();

		virtual ~Vector() { Clear(); }

	protected:
		T* m_Capacity;//Where the storage ends
	};


	template<typename T, std::size_t SIZE>
	class SmallVector : public Vector<T>
	{
	public:
		SmallVector();
		inline SmallVector(std::initializer_list<T> list);

		virtual void Reserve(std::size_t minCapacity) override;

		virtual void CopyFrom(const T* begin, const T* end) override;

		virtual T& Add(const T& value) override;
		virtual T& Add(T&& value) override;

		virtual ~SmallVector();


	private:
		inline bool IsSmall() const { return this->m_Begin == this->m_Store; }

	private:
		T m_Store[SIZE];
	};

}


#include "DataStructures.inl"

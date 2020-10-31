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

		T& operator[](std::size_t index) { return Get(index); }
		const T& operator[](std::size_t index) const { return Get(index); }

		inline std::size_t Size() const { return m_End - m_Begin; }

		inline T* Data() { return m_Begin; }
		inline const T* Data() const { return m_Data; }

		inline T* Begin() { return m_Begin; }
		inline const T* Begin() const { return m_Data; }

		inline T* End() { return m_End; }
		inline const T* End() const { return m_End; }

		inline T* begin() { return m_Begin; }
		inline const T* begin() const { return m_Data; }

		inline T* end() { return m_End; }
		inline const T* end() const { return m_End; }

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
		explicit Vector() : Buffer(nullptr, nullptr), m_Capacity(nullptr) {}

	public:
		Vector(T* begin, T* end, T* capacity);
		inline Vector(T* begin, T* end);

		std::size_t Capacity() const { return m_Capacity - m_Begin; }

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
		inline SmallVector(std::initializer_list<T> list) { CopyFrom(list.begin(), list.end()); }

		virtual void Reserve(std::size_t minCapacity);

		virtual void CopyFrom(const T* begin, const T* end);

		virtual T& Add(const T& value);
		virtual T& Add(T&& value);

		virtual ~SmallVector();


	private:
		inline bool IsSmall() const { return m_Begin == m_Store; }

	private:
		T m_Store[SIZE];
	};

}


#include "DataStructures.inl"

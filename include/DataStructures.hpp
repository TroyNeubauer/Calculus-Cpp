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

	protected:
		void CheckRange(std::size_t index);

	private:
		T* m_Begin;
		T* m_End;
	};

	template<typename T>
	class Vector : public Buffer<T>
	{
	public:
		Vector(T* data, T* capacity);
		inline Vector(T* data, std::size_t capacity) : Vector(data, data + capacity) {}

		virtual T& Add(const T& value) = 0;
		virtual T& Add(T&& value) = 0;

		virtual void Remove(std::size_t index);

	private:
		T* m_Cap;//Where the storage ends
	};


	template<typename T, std::size_t SIZE>
	class SmallVector : public Vector<T>
	{
	public:
		SmallVector();

		virtual T& Add(const T& value);
		virtual T& Add(T&& value);


	private:
		T m_Store[SIZE];
	};

}


#include "DataStructures.inl"

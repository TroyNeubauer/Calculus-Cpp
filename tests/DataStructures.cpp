
#include <catch2/catch.hpp>

#include "DataStructures.hpp"

using namespace calc;

TEST_CASE("Buffer reports correct size #1", "[buffer]")
{
	int data = 0;
	Buffer<int> buf1(&data, &data);
	REQUIRE(buf1.Size() == 0);


	Buffer<int> buf2(&data, static_cast<std::size_t>(0));
	REQUIRE(buf2.Size() == 0);

}


TEST_CASE("Buffer reports correct size #2", "[buffer]")
{
	int data = 0;
	Buffer<int> buf1(&data, &data + 1);
	REQUIRE(buf1.Size() == 1);

	Buffer<int> buf2(&data, static_cast<std::size_t>(1));
	REQUIRE(buf2.Size() == 1);

}


TEST_CASE("Buffer reports correct size #3", "[buffer]")
{
	std::uint8_t data[16] = {};
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);

	Buffer<std::uint8_t> buf1(data, data + capacity);
	REQUIRE(buf1.Size() == capacity);

	Buffer<std::uint8_t> buf2(data, capacity);
	REQUIRE(buf2.Size() == capacity);

}



TEST_CASE("Buffer shows correct data #1", "[buffer]")
{
	int data1 = 0;
	Buffer<int> buf1(&data1, &data1 + 1);

	REQUIRE(buf1[0] == 0);
	REQUIRE(buf1.Get(0) == 0);


	int data2 = 69;
	Buffer<int> buf2(&data2, &data2 + 1);

	REQUIRE(buf2[0] == 69);
	REQUIRE(buf2.Get(0) == 69);

}


TEST_CASE("Buffer shows correct data #2", "[buffer]")
{
	int data[4] = { 2, 4, 6, 9 };
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);

	Buffer<int> buf(data, data + capacity);

	REQUIRE(buf[0] == 2);
	REQUIRE(buf[1] == 4);
	REQUIRE(buf[2] == 6);
	REQUIRE(buf[3] == 9);

	REQUIRE(buf.Get(0) == 2);
	REQUIRE(buf.Get(1) == 4);
	REQUIRE(buf.Get(2) == 6);
	REQUIRE(buf.Get(3) == 9);

}


TEST_CASE("Buffer const correctness #1", "[buffer]")
{
	int data[4] = { 10, 10, 10, 10 };
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);
	Buffer<int> nonConstBuf(data, data + capacity);
	
	const auto& buf = nonConstBuf;

	REQUIRE(buf[0] == 10);
	REQUIRE(buf.Get(0) == 10);
	REQUIRE(buf.Get(0) == 10);
	REQUIRE(buf.Size() == capacity);

}


TEST_CASE("Buffer old iterators #1", "[buffer]")
{
	int data[4] = { 10, 10, 10, 10 };
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);
	Buffer<int> buf(data, data + capacity);

	int i = 0;
	for (auto it = buf.begin(); it != buf.end(); it++)
	{
		REQUIRE(*it == data[i++]);
	}

}

TEST_CASE("Buffer iterators #1", "[buffer]")
{
	int data[4] = { 15, 20, 25, 30 };
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);
	Buffer<int> buf(data, data + capacity);

	int i = 0;
	for (const auto value : buf)
	{
		REQUIRE(value == data[i++]);
	}
	constexpr bool tr = std::is_trivially_copy_constructible<double>::value;
}

/*
TEST_CASE("Buffer doesn't destruct elements", "[buffer]")
{

	struct DestructChecker
	{
		bool CanDestruct = false;

		~DestructChecker()
		{
			REQUIRE(CanDestruct);
		}
	};


	DestructChecker data[4] = { };
	constexpr const std::size_t capacity = sizeof(data) / sizeof(data[0]);

	{
		Buffer<DestructChecker> buf(data, data + capacity);
		for (const auto& value : buf)
		{
			REQUIRE(value.CanDestruct == false);
		}

	}

	for (int i = 0; i < 4; i++)
	{
		data[i].CanDestruct == true;
	}

}
*/


TEST_CASE("Const correctness #1", "[vector]")
{
	SmallVector<int, 4> nonConstVec({ 5 });

	const auto& vec = nonConstVec;

	REQUIRE(vec[0] == 5);
	REQUIRE(vec.Get(0) == 5);
	REQUIRE(vec.Size() == 1);

}

TEST_CASE("Can remove elements in a vector #1", "[vector]")
{
	SmallVector<int, 4> vec({ 5 });

	REQUIRE(vec[0] == 5);
	REQUIRE(vec.Size() == 1);
	vec.Remove(0);
	REQUIRE(vec.Size() == 0);
}

TEST_CASE("Can remove elements in a vector #2", "[vector]")
{
	SmallVector<int, 4> vec({ 5, 4, 3, 2, 1 });

	REQUIRE(vec.Size() == 5);

	vec.Remove(0);
	REQUIRE(vec.Size() == 4);
	REQUIRE(vec[0] == 4);
	REQUIRE(vec[1] == 3);
	REQUIRE(vec[2] == 2);
	REQUIRE(vec[3] == 1);

	vec.Remove(0);
	REQUIRE(vec.Size() == 3);
	REQUIRE(vec[0] == 3);
	REQUIRE(vec[1] == 2);
	REQUIRE(vec[2] == 1);

	vec.Remove(0);
	REQUIRE(vec.Size() == 2);
	REQUIRE(vec[0] == 2);
	REQUIRE(vec[1] == 1);

	vec.Remove(0);
	REQUIRE(vec.Size() == 1);
	REQUIRE(vec[0] == 1);

	vec.Remove(0);
	REQUIRE(vec.Size() == 0);
}

TEST_CASE("Can add elements to a vector #1", "[vector]")
{
	SmallVector<int, 4> vec;

	REQUIRE(vec.Size() == 0);

	vec.Add(1);
	REQUIRE(vec.Size() == 1);
	REQUIRE(vec[0] == 1);

}


TEST_CASE("Can add elements to a vector #2", "[vector]")
{
	SmallVector<int, 2> vec;

	vec.Add(5);
	REQUIRE(vec[0] == 5);
	REQUIRE(vec.Size() == 1);

	vec.Add(4);
	REQUIRE(vec.Size() == 2);
	REQUIRE(vec[0] == 5);
	REQUIRE(vec[1] == 4);

	vec.Add(3);
	REQUIRE(vec.Size() == 3);
	REQUIRE(vec[0] == 5);
	REQUIRE(vec[1] == 4);
	REQUIRE(vec[2] == 3);

	vec.Add(2);
	REQUIRE(vec.Size() == 4);
	REQUIRE(vec[0] == 5);
	REQUIRE(vec[1] == 4);
	REQUIRE(vec[2] == 3);
	REQUIRE(vec[3] == 2);

	vec.Add(1);
	REQUIRE(vec.Size() == 5);
	REQUIRE(vec[0] == 5);
	REQUIRE(vec[1] == 4);
	REQUIRE(vec[2] == 3);
	REQUIRE(vec[3] == 2);
	REQUIRE(vec[4] == 1);
}


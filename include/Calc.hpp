#pragma once

#include <memory>
#include <type_traits>
#include <vector>
#include <cassert>

//#include "DataStructures.hpp"

namespace calc {

	// An atom is a single indivisible "value"
	// Either a constant, variable, or binary operation and two other atoms
	template<typename T>
	class Atom
	{
	public:
		Atom() = default;
		Atom(const Atom<T>& other) = default;

		//Returns the value of this atom
		virtual T Get() const = 0;

		virtual ~Atom() {}
	};


	template<typename T>
	class ParametersBase
	{
	public:
		virtual T operator[](std::size_t index) const = 0;

		//Returns the first operand
		virtual T A() const = 0;

		//Returns the second operand
		virtual T B() const = 0;

	};


	template<typename T, typename VecType>
	class VectorParameters : public ParametersBase<T>
	{
	public:
		virtual T operator[](std::size_t index) const
		{
			return m_Params[index]->Get();
		}

		//Returns the first operand
		virtual T A() const
		{
			return m_Params[0]->Get();
		}

		//Returns the second operand
		virtual T B() const
		{
			return m_Params[1]->Get();
		}

	public:
		VecType& GetImpl() { return m_Params; }

	private:
		VecType m_Params;
	};


	template<typename T, std::size_t SIZE>
	using OwnedParameters = VectorParameters<T, std::vector<std::unique_ptr<Atom<T>>>>;

	//2 in 1 out normal binary opperation (addition, mutplication, etc.)
	//is also enough for unary operations like sin(), sqrt(), tan() ect
	template<typename T>
	using DefaultParameters = OwnedParameters<T, 2>;

	template<typename T>
	struct GeneralOperation
	{
		std::add_pointer_t<T(const ParametersBase<T>&)> Evaluate;
	};


	namespace operations
	{
		namespace internal
		{
			template<typename T> T AddImpl(const ParametersBase<T>& params) 		{ return params.A() + params.B(); }
			template<typename T> T SubtractImpl(const ParametersBase<T>& params) 	{ return params.A() - params.B(); }
			template<typename T> T MultiplyImpl(const ParametersBase<T>& params) 	{ return params.A() * params.B(); }
			template<typename T> T DivideImpl(const ParametersBase<T>& params) 		{ return params.A() / params.B(); }
		}

		template<typename T> GeneralOperation<T> Add = { internal::AddImpl };
		template<typename T> GeneralOperation<T> Subtract = { internal::SubtractImpl };
		template<typename T> GeneralOperation<T> Multiply = { internal::MultiplyImpl };
		template<typename T> GeneralOperation<T> Divide = { internal::DivideImpl };
	}



	template<typename T>
	class ConstantAtom : public Atom<T>
	{
	public:
		ConstantAtom(const T& value) : m_Value(value) {}
		ConstantAtom(T&& value) : m_Value(value) {}

		virtual T Get() const { return m_Value; };

	private:
		T m_Value;
	};


	template<typename T>
	class VariableAtom : public Atom<T>
	{
	//The same as ConstantAtom, users simply construct this atom with the value they need. Actual variables will come in time
	public:
		VariableAtom(const T& value) : m_Value(value) {}
		VariableAtom(T&& value) : m_Value(value) {}

		virtual T Get() const { return m_Value; };

	private:
		T m_Value;
	};


	template<typename T>
	class OperationAtom : public Atom<T>
	{
		using Operation = GeneralOperation<T>;
	//The same as ConstantAtom, users simply construct this atom with the value they need. Actual variables will come in time
	public:

		OperationAtom(const Operation& operation, DefaultParameters<T>&& args)
			: m_Operation(operation), m_Args(std::move(args)) {}


		OperationAtom(const Operation& operation, const std::initializer_list<Atom<T>*>& args)
			: m_Operation(operation)
		{
			for (Atom<T>* arg : args)
			{
				m_Args.GetImpl().emplace_back(arg);
			}
		}

		virtual T Get() const { return m_Operation.Evaluate(m_Args); }

	private:
		const Operation& m_Operation;
		DefaultParameters<T> m_Args;
	};

}

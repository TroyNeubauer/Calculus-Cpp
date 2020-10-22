#pragma once

#include <memory>
#include <type_traits>

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
	};

	template<typename T>
	using BinaryEvaluateFunc = std::add_pointer_t<T(const Atom<T>&, const Atom<T>&)>;

	template<typename T>
	struct BinaryOperation
	{
		BinaryEvaluateFunc<T> Evaluate;
	};

	namespace operations
	{
		namespace internal
		{
			template<typename T>
			T AddImpl(const Atom<T>& a, const Atom<T>& b) { return a.Get() + b.Get(); }

		}

		template<typename T>
		BinaryOperation<T> Add = { internal::AddImpl };
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
	class BinaryOperationAtom : public Atom<T>
	{
	//The same as ConstantAtom, users simply construct this atom with the value they need. Actual variables will come in time
	public:

		BinaryOperationAtom(const BinaryOperation<T>& operation, std::unique_ptr<Atom<T>>&& a, std::unique_ptr<Atom<T>>&& b)
			: m_Operation(operation), m_A(a), m_B(b) {}

		BinaryOperationAtom(const BinaryOperation<T>& operation, Atom<T>* a, Atom<T>* b)
			: m_Operation(operation), m_A(a), m_B(b) {}


		virtual T Get() const { return m_Operation.Evaluate(*m_A.get(), *m_B.get()); };

	private:
		const BinaryOperation<T>& m_Operation;
		std::unique_ptr<Atom<T>> m_A;
		std::unique_ptr<Atom<T>> m_B;
	};



	using DAtom = Atom<double>;
	using DConstantAtom = ConstantAtom<double>;
	using DVariableAtom = VariableAtom<double>;
	using DBinaryOperationAtom = BinaryOperationAtom<double>;

	using DBinaryEvaluateFunc = BinaryEvaluateFunc<double>;
	using DBinaryOperation = BinaryOperation<double>;


}

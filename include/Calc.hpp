#pragma once

#include <memory>
#include <type_traits>
#include <vector>

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
	using OperationParameters = std::vector<std::unique_ptr<Atom<T>>>;

	template<typename T>
	struct GeneralOperation
	{
		std::add_pointer_t<T(const OperationParameters<T>&)> Evaluate;
	};




	namespace operations
	{
		namespace internal
		{
			
			template<typename T> T AddImpl(const OperationParameters<T>& params) 		{ return params[0]->Get() + params[1]->Get(); }
			template<typename T> T SubtractImpl(const OperationParameters<T>& params) 	{ return params[0]->Get() - params[1]->Get(); }
			template<typename T> T MultiplyImpl(const OperationParameters<T>& params) 	{ return params[0]->Get() * params[1]->Get(); }
			template<typename T> T DivideImpl(const OperationParameters<T>& params) 	{ return params[0]->Get() / params[1]->Get(); }

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

		OperationAtom(const Operation& operation, OperationParameters<T>&& args)
			: m_Operation(operation), m_Args(args) {}


		OperationAtom(const Operation& operation, const std::initializer_list<Atom<T>*>& args)
			: m_Operation(operation)
		{
			m_Args.reserve(args.size());
			for (const auto& arg : args)
			{
				m_Args.emplace_back(arg);
			}
		}

		virtual T Get() const { return 0.0; } // m_Operation.Evaluate(*m_A.get(), *m_B.get())

	private:
		const Operation& m_Operation;
		OperationParameters<T> m_Args;
	};



	using DAtom = Atom<double>;
	using DConstantAtom = ConstantAtom<double>;
	using DVariableAtom = VariableAtom<double>;
	using DOperationAtom = OperationAtom<double>;



}

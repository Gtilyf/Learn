#pragma once
#ifndef _statck_
#define _statck_

#include "LinkedLineraList.hpp"

namespace DS
{
	template<typename T, typename ContainerType>
	class stack;

	template<typename T, typename ContainerType>
	void swap(stack<T, ContainerType>& s1, stack<T, ContainerType>& s2)
	{
		swap(sl._container, s2._container);
	}

	template<typename T, typename ContainerType = LinkedList<T>>
	class stack
	{
	public:
		typedef typename ContainerType::size_type size_type;
		typedef T& reference;
		typedef const T& const_reference;

		stack()
			: _container()
		{}

		explicit stack(const ContainerType& c)
			: _container(c)
		{}

		explicit stack(ContainerType&& rc)
			:_container(std::move(rc))
		{}

		stack(const stack& s)
			: _container(s._container)
		{}

		stack(stack&& rs)
			:_container(std::move(rs._container))
		{
			rs._container = ContainerType();
		}

		stack operator=(stack s)
		{
			swap(*this, s);
			return (*this);
		}

		void push(const T& val)
		{
			_container.push_back(val);
		}

		void push(T&& rval)
		{
			_container.push_back(std::forward<T>(rval));
		}

		void emplace(T&& rval)
		{
			_container.emplace_back(std::forward<T>(rval));
		}

		bool empty() const
		{
			return (_container.empty());
		}

		size_type size() const
		{
			return (_container.size());
		}

		reference top()
		{
			return (_container.back());
		}

		const_reference top() const
		{
			return (_container.back());
		}

		T pop()
		{
			return (_container.pop_back());
		}

		friend void swap <>(stack&, stack&);

	private:
		ContainerType _container;
	};
}

#endif
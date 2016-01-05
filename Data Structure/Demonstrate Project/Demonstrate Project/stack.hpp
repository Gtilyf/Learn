#pragma once
#include "LinkedLineraList.hpp"

namespace DS
{
	template<typename T, typename ContainerType = LinkedList<T>>
	class stack
	{
		typedef ContainerType::size_type size_type;
		typedef T& reference;
		typedef const T& const_reference;
	public:
		void push(const T& val)
		{
			_container.push_back(val);
		}

		void push(T&& rval)
		{
			_container.push_back(std::forward(rval));
		}

		void emplace(T&& rval)
		{
			_container.emplace_back(std::forward(rval));
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

	private:
		ContainerType _container;
	};
}
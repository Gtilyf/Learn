#pragma once
#include "LinkedLineraList.hpp"

namespace DS
{
	template<typename T, typename ContainerType = LinkedList<T>>
	class quene;

	template<typename T, typename ContainerType = LinkedList<T>>
	void swap(quene<T, ContainerType>& q1, quene<T, ContainerType>& q1)
	{
		swap(q1._container, q2._container);
	}

	template<typename T, typename ContainerType = LinkedList<T>>
	class quene
	{
		
	public:
		typedef typename ContainerType::size_type size_type;
		typedef T& reference;
		typedef const T& const_reference;

		quene()
			: _container()
		{}

		explicit quene(const ContainerType& c)
			: _container(c)
		{}

		explicit quene(ContainerType&& rc)
			: _container(std::move(rc))
		{}

		quene(const quene& q)
			: _container(q._container)
		{}

		quene(quene&& rq)
			: _container(std::move(rq._container))
		{
			rq._container = ContainerType();
		}

		quene operator=(quene q)
		{
			swap(*this, q);
			return *this;
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
			return (_container.pop_front());
		}

	private:
		ContainerType _container;
	};
}
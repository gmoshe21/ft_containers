#include "../list/list.hpp"

namespace ft
{
	template<class T, class Container = ft::list<T> >
	class queue
	{
		private:
			Container cont;
		public:

			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		
		explicit queue( const Container& conts = Container() ) : cont(conts) { }
		virtual ~queue(){}
		queue& operator=( const queue& other )
		{
			cont = other.cont;
			return (*this);
		}
		bool empty() const
		{
			return this->cont.empty();
		}
		size_type size() const
		{
			return this->cont.size();
		}
		reference top()
		{
			return this->cont.back();
		}
		const_reference top() const
		{
			return this->cont.back();
		}
		void push (const value_type& val)
		{
			this->cont.push_back(val);
		}
		void pop()
		{
			this->cont.pop_front();
		}
		void swap( queue& other )
		{
			cont.swap(other.cont);
		}
		reference front()
		{
			return this->cont.front();
		}
		const_reference front() const
		{
			return this->cont.front();
		}
		reference back()
		{
			return this->cont.back();
		}
		const_reference back() const
		{
			return this->cont.back();
		}
		friend bool	operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
		return (lhs.cont == rhs.cont);
		}
		friend bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return (lhs.cont != rhs.cont);
		}
		friend bool	operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return (lhs.cont < rhs.cont);
		}
		friend bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return (lhs.cont > rhs.cont);
		}
		friend bool	operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return (lhs.cont <= rhs.cont);
		}
		friend bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return (lhs.cont >= rhs.cont);
		}
	};
};
#include "../list/list.hpp"

namespace ft
{
	template<class T, class Container = ft::list<T> >
	class stack
	{
		private:
			Container cont;
		public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		
		explicit stack( const Container& conts = Container() ) : cont(conts) { }
		virtual ~stack(){}
		stack& operator=( const stack& other )
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
		value_type& top()
		{
			return this->cont.back();
		}
		const value_type& top() const
		{
			return this->cont.back();
		}
		void push (const value_type& val)
		{
			this->cont.push_back(val);
		}
		void pop()
		{
			this->cont.pop_back();
		}
		void swap( stack& other )
		{
			cont.swap(other.cont);
		}
		friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
		return (lhs.cont == rhs.cont);
		}
		friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs.cont != rhs.cont);
		}
		friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs.cont < rhs.cont);
		}
		friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs.cont > rhs.cont);
		}
		friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs.cont <= rhs.cont);
		}
		friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs.cont >= rhs.cont);
		}
	};
};
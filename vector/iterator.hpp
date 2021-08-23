#pragma once

#include <iostream>

namespace ft
{
	template <class Iterator1, class Iterator2>
	bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	
	template<typename _Tp>
	class iterator
	{
	protected:
		_Tp* _i;
	public:
		typedef _Tp			value_type;
		typedef	_Tp*		pointer;
		typedef _Tp&		reference;
		typedef std::ptrdiff_t	difference_type;
	
		iterator() : _i(0)
		{}
		iterator(pointer const &other)
		{
			*this = other;
		}
		iterator &operator=(pointer const &other)
		{
			_i = other;
			return (*this);
		}
		~iterator()
		{}
		iterator operator++()
		{
			++_i;
			return (*this);
		}
		iterator operator++(int)
		{
			iterator tmp(*this);
			++(*this);
			return (tmp);
		}
		iterator operator--(int)
		{
			iterator tmp(*this);
			--(*this);
			return (tmp);
		}
		iterator &operator--()
		{
			--_i;
			return (*this);
		}
		iterator operator+(difference_type _n)
		{
			iterator tmp(*this);
			tmp += _n;
			return (tmp);
		}
		iterator& operator+=(difference_type _n)
		{
			_i += _n;
			return (*this);
		}
		iterator& operator-=(difference_type _n)
		{
			_i -= _n;
			return (*this);
		}
		difference_type operator-(iterator const &_n)
		{
			iterator tmp(*this);
			return (tmp._i - _n._i);
		}
		iterator operator-(difference_type _n)
		{
			iterator tmp(*this);
			tmp -= _n;
			return (tmp);
		}
		reference operator*() const
		{
			return (*_i);
		}
		bool operator==(iterator const &next)
		{
			return (_i == next._i);
		}
		bool operator<(iterator const &next)
		{
			return (_i < next._i);
		}
		bool operator!=(iterator const &next)
		{
			return (_i != next._i);
		}
		bool operator>(iterator const &next)
		{
			return (_i > next._i);
		}
		bool operator>=(iterator const &next)
		{
			return (_i >= next._i);
		}
		bool operator<=(iterator const &next)
		{
			return (_i <= next._i);
		}
	};

	template<class Iter>
	class reverse_iterator
	{
	protected:
    	Iter current;
	public:
		typedef Iter							iterator_type;
		typedef typename Iter::difference_type	difference_type;
		typedef typename Iter::reference		reference;
		typedef typename Iter::pointer			pointer;

		Iter base() const
		{
			return current;
		}
		reverse_iterator(Iter const &other)
		{
			current = other;
		}
		reverse_iterator(reverse_iterator const &other)
		{
			current = other.current;
		}
		reference operator*() const
		{
			Iter tmp = current;
			return *(--tmp);
		}
		reverse_iterator& operator++()
		{
			--current;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--current;
			return (tmp);
		}
		reverse_iterator& operator--()
		{
			++current;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++current;
			return (tmp);
		}
		reverse_iterator operator+(difference_type _n)
		{
			return (reverse_iterator(current - _n));
		}
		reverse_iterator& operator+=(difference_type _n)
		{
			current -= _n;
			return (*this);
		}
		reverse_iterator operator-(difference_type _n)
		{
			return (reverse_iterator(current + _n));
		}
		reverse_iterator& operator-=(difference_type _n)
		{
			current += _n;
			return (*this);
		}
		reference operator[](difference_type _n)const
		{
			return (*(*this + _n));
		}
	};
}
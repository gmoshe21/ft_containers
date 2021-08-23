#pragma once

#include <iostream>

namespace ft
{
	template<typename Type>
	struct list_node
	{
		Type element;
		list_node *__next_;
		list_node *__prev_;
		list_node(list_node *__prev_, list_node *__next_)
				: __prev_(__prev_), __next_(__next_) {}
	};
	
	template<typename _node, typename _T>
	class iterator
	{
		protected:
			_node*	__ptr_;
		public:
			typedef	_T*			pointer;
			typedef	_T&			reference;
			typedef std::ptrdiff_t	difference_type;

			iterator() : __ptr_(NULL){}
			iterator(iterator const &other){	*this = other;	}
			iterator(_node &current)
			{
				__ptr_ = &current;
			}
			_node* node_cast()
			{
				return __ptr_;
			}
			iterator& operator=(_node const &current)
			{
				__ptr_ = current;
			}
			iterator& operator=(iterator const &other)
			{
				__ptr_ = other.__ptr_;
				return *this;
			}
			iterator& operator++()
			{
				__ptr_ = __ptr_->__next_;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp(*this);
				++(*this);
				return tmp;
			}
			iterator& operator--()
			{
				__ptr_ = __ptr_->__prev_;
				return *this;
			}
			iterator operator--(int)
			{
				iterator tmp(*this);
				--(*this);
				return tmp;
			}
			_node* operator->()
			{
				return *this;
			}
			reference operator*() const	{	return __ptr_->element;	}
			bool operator==(iterator const &x){	return this->__ptr_ == x.__ptr_;	}
			bool operator!=(iterator const &x){	return !(*this == x);	}
	};
	template<class T>
	class list_reverse_iterator
	{
		private:
			T current;
		public:
			typedef typename T::pointer			pointer;
			typedef typename T::reference		reference;
			typedef typename T::difference_type	difference_type;
			
			T base() {	return current;	}
			list_reverse_iterator(list_reverse_iterator const &other) {	current = other.current;	}
			list_reverse_iterator(T const &other) {	current = other;	}
			reference operator*() { T tmp(current); return *(--tmp);	}
			list_reverse_iterator& operator++() { --current; return *this;}
			list_reverse_iterator operator++(int) { list_reverse_iterator tmp(*this); --current; return tmp;}
			list_reverse_iterator& operator--() { ++current; return *this;}
			list_reverse_iterator operator--(int) { list_reverse_iterator tmp(*this); ++current; return tmp;}
			bool operator==(list_reverse_iterator const &x){	return current == x.current;	}
			bool operator!=(list_reverse_iterator const &x){	return !(*this == x);	}
	};
}
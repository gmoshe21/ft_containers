#pragma once

# include "list_iterator.hpp"

template<typename T>
bool Compare(const T &a, const T &b) { return (a < b);}

namespace ft
{
	template<typename Type>
	class list_base
	{
		public:
		typedef list_node<Type> node;
		protected:
			node		*__head_;
			node		*__tail_;
		public:
			list_base()
			{
				__head_ = NULL;
				__tail_ = __head_;
			}
	};
	template<typename Type>
	class list : list_base<Type>
	{
		public:
			typedef Type							value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef list_node<Type>					node;
			typedef list_base<Type>					node_base;
			typedef iterator<node, Type>			iterator;
			typedef list_reverse_iterator<iterator> reverse_iterator;
			typedef const iterator					const_iterator;
			typedef size_t							size_type;
			typedef std::ptrdiff_t					difference_type;
		private:
			size_type	__length_;
			iterator convert (const_iterator &x){iterator tmp = begin(); while(tmp != x) ++tmp; return tmp;}
		public:
			list()
			{
				node_base::__head_ = new node(NULL, NULL);
				node_base::__tail_ = node_base::__head_;
				__length_ = 0;
			}
			list(list const &other) : __length_(other.__length_)
			{
				node_base::__head_ = new node(NULL, NULL);
				node_base::__tail_ = node_base::__head_;
				__length_ = 0;
				iterator start = other.begin();
				while (start != other.end())
					push_back((start++).node_cast()->element);
			}
			list(size_type count, value_type const &value)
			{
				node_base::__head_ = new node(NULL, NULL);
				node_base::__tail_ = node_base::__head_;
				__length_ = 0;
				for (size_type i = 0; i  < count; i++)
					push_back(value);
			}
			list(iterator first, iterator last)
			{
				node_base::__head_ = new node(NULL, NULL);
				node_base::__tail_ = node_base::__head_;
				__length_ = 0;
				while (first != last)
					push_back((first++).node_cast()->element);
			}
			list& operator=(list const &other)
			{
				if (node_base::__head_)
					while (node_base::__head_)
					{
						delete[] node_base::__head_;
						node_base::__head_ = node_base::__head_->__next_;
						--__length_;
					}
				node_base::__head_ = new node(NULL, NULL);
				node_base::__head_->element = 0;
				node_base::__tail_ = node_base::__head_;
				__length_ = other.__length_;
				iterator start = other.begin();
				iterator last = other.end();
				while (start != last)
					push_back((start++).node_cast()->element);
				node_base::__tail_->__next_ = NULL;
				return *this;
			}

			iterator begin() const		{	return *ft::list_base<Type>::__head_;	}
			iterator end() const		{	return *ft::list_base<Type>::__tail_;	}
			reverse_iterator rbegin() const		{	return reverse_iterator(end());	}
			reverse_iterator rend() const		{	return reverse_iterator(begin());	}
			bool empty() const			{	return begin() == end();	}
			size_type max_size() const	{	return 768614336404564650;	}

			reference       front()
			{
				return node_base::__head_->element;
			}

			const_reference       front() const
			{
				return node_base::__head_->element;
			}

			reference       back()
			{
				if (node_base::__tail_->__prev_)
					return node_base::__tail_->__prev_->element;
				return node_base::__tail_->element;
			}

			const_reference       back() const
			{
				if (node_base::__tail_->__prev_)
					return node_base::__tail_->__prev_->element;
				return node_base::__tail_->element;
			}

			void push_back(value_type const &value)
			{
				node	*next_element = new node( node_base::__tail_, NULL );
				node_base::__tail_->element = value;
				node_base::__tail_->__next_ = next_element;
				node_base::__tail_ = next_element;
				++__length_;
			}
			void push_front(value_type const &value)
			{
				node	*next_element = new node( NULL, node_base::__head_ );
				node_base::__head_->__prev_ = next_element;
				node_base::__head_ = next_element;
				node_base::__head_->element = value;
				++__length_;
			}
			void pop_back()
			{
				node_base::__tail_ = node_base::__tail_->__prev_;
				delete[] node_base::__tail_->__next_;
				node_base::__tail_->__next_ = NULL;
				--__length_;
			}
			void pop_front()
			{
				node_base::__head_ = node_base::__head_->__next_;
				delete[] node_base::__head_->__prev_;
				node_base::__head_->__prev_ = NULL;
				--__length_;
			}
			iterator insert( iterator pos, const value_type &value )
			{
				++__length_;
				if (pos == begin())
				{
					push_front(value);
					return begin();
				}
				else
				{
					node *prev = pos.node_cast()->__prev_;
					node	*next_element = new node( prev, prev->__next_ );
					next_element->element = value;
					pos.node_cast()->__prev_ = next_element;
					prev->__next_ = next_element;
					return --pos;
				}
			}
			void insert( iterator pos, size_type count, const value_type &value )
			{
				while(count--)
					insert(pos, value);
			}
			void insert( iterator pos, iterator first, iterator last )
			{
				while (first != last)
					insert(pos, *first++);
			}
			iterator erase( iterator pos )
			{
				if (pos == begin())
				{
					pop_front();
					return begin();
				}
				else if (pos == end())
				{
					pop_back();
					return end();
				}
				iterator pos_next = pos;
				++pos_next;
				delete[] pos.node_cast()->__prev_->__next_;
				pos.node_cast()->__prev_->__next_ = pos.node_cast()->__next_;
				pos.node_cast()->__next_->__prev_ = pos.node_cast()->__prev_;
				--__length_;
				return pos_next;
			}
			iterator erase( iterator first, iterator last )
			{
				iterator ret;
				while (first != last)
					ret = erase(first++);
				return ret;
			}
			void clear()
			{
				while (__length_)
					pop_back();
			}
			size_type size() const
			{
				return __length_;
			}
			void resize( size_type count, value_type value )
			{
				while (__length_ < count)
					push_back(value);
				while (__length_ > count)
					pop_back();
			}
			void swap( list& other )
			{
				std::swap(__length_, other.__length_);
				std::swap(node_base::__head_, other.__head_);
				std::swap(node_base::__tail_, other.__tail_);
			}
			void reverse()
			{
				iterator first = begin();
				iterator last = end();
				for (size_type i = size(); i > 1; i -= 2)
					std::swap((first++).node_cast()->element, (--last).node_cast()->element);
			}
			void assign( size_type count, value_type const &value )
			{
				clear();
				for(;count ;count--)
					push_back(value);
			}
			void assign( iterator first, iterator last )
			{
				clear();
				while (first != last)
					push_back((first++).node_cast()->element);
			}
			void sort()
			{
				iterator first = begin();
				iterator last = end();
				for (iterator first = begin(); first != end(); first++)
					for (iterator last = --end(); last != first; last--)
						if (last.node_cast()->element < last.node_cast()->__prev_->element)
							std::swap(last.node_cast()->element, last.node_cast()->__prev_->element);
			}
			template< class Compare > 
			void sort( Compare comp )
			{
				iterator first = begin();
				iterator last = end();
				for (iterator first = begin(); first != end(); first++)
					for (iterator last = --end(); last != first; last--)
						if (comp(last.node_cast()->element, last.node_cast()->__prev_->element))
							std::swap(last.node_cast()->element, last.node_cast()->__prev_->element);
			}
			void splice( const_iterator pos, list& other )
			{
				iterator start = convert(pos);
				__length_ += other.size();
				node *other_first = other.begin().node_cast()->__next_->__prev_;
				node *other_last = other.end().node_cast()->__prev_->__next_;
				if (start == begin())
					node_base::__head_ = other_first;
				else
				{
					start.node_cast()->__prev_->__next_ = other_first;
					other_first->__prev_ = start.node_cast()->__prev_;
				}
				if (start == end())
					other_last->__prev_->__next_ = node_base::__tail_;
				else
					other_last->__prev_->__next_ = start.node_cast()->__next_->__prev_;
				start.node_cast()->__prev_ = other_last->__prev_;
				other.__head_ = other.__tail_;
				other.__tail_->__prev_ = NULL;
				other.__length_ = 0;
			}
			void splice( iterator pos, list& other, iterator it )
			{
				node *other_start = other.__head_;
				while (other_start->__next_ != it.node_cast()->__next_)
					other_start = other_start->__next_;
				node *old;
				if (pos.node_cast()->__next_ == node_base::__head_->__next_)
					node_base::__head_ = other_start;
				if (other_start == other.__head_)
					other.__head_ = other.__head_->__next_;
				if (other_start->__prev_)
					other_start->__prev_->__next_ = other_start->__next_;
				if (other_start->__next_)
					other_start->__next_->__prev_ = other_start->__prev_;
				if (pos.node_cast()->__prev_)
				{
					pos.node_cast()->__prev_->__next_ = other_start;
					other_start->__prev_ = pos.node_cast()->__prev_;
				}
				else
				{
					other_start->__prev_ = NULL;
					pos.node_cast()->__prev_ = other_start;
				}
				if (pos.node_cast()->__next_)
				{
					other_start->__next_ = pos.node_cast()->__next_->__prev_;
					pos.node_cast()->__prev_ = other_start;
				}
				else
				{
					other_start->__next_ = NULL;
					pos.node_cast()->__prev_ = other_start;
				}
				if (pos.node_cast()->__next_ == node_base::__tail_->__next_)
					other_start->__next_ = node_base::__tail_;
				++__length_;
				--other.__length_;
			}
			void splice( iterator pos, list& other, iterator first, iterator last)
			{
				iterator save;
				while (first != last)
				{
					save = first++;
					splice(pos, other, save);
				}
			}
			void unique()
			{
				iterator start = ++begin();
				iterator prev = begin();
				iterator last = end();
				while (start != last)
				{
					if (start.node_cast()->element == prev.node_cast()->element)
						erase(prev);
					prev = start++;
				}
			}
			template< class BinaryPredicate >
			void unique( BinaryPredicate p )
			{
				iterator start = ++begin();
				iterator prev = begin();
				iterator last = end();
				while (start != last)
				{
					if (p(start.node_cast()->element, prev.node_cast()->element))
						erase(prev);
					prev = start++;
				}
			}
			void remove( const value_type &value )
			{
				iterator start = begin();
				iterator last = end();
				iterator current;
				while (start != last)
				{
					current = start++;
					if (current.node_cast()->element == value)
						erase(current);
				}
			}
			template< class UnaryPredicate >
			void remove_if( UnaryPredicate p )
			{
				iterator start = begin();
				iterator last = end();
				iterator current;
				while (start != last)
				{
					current = start++;
					if (p(current.node_cast()->element))
						erase(current);
				}
			}
			void merge(list& x)
			{
				iterator first = begin();
				iterator last = end();
				iterator x_first = x.begin();
				iterator x_last = x.end();
				iterator save_other;

				while (first != last || x_first != x_last)
				{
					if (*first > *x_first && x_first != x_last)
						{
							save_other = x_first++;
							splice(first, x, save_other);
						}
					else if (first != last)
						++first;
					else if (first == last)
					{
						save_other = x_first++;
						splice(first, x, save_other);
					}
				}
			}
			template <class Compare> 
			void merge( list& x, Compare comp )
			{
				iterator first = begin();
				iterator last = end();
				iterator x_first = x.begin();
				iterator x_last = x.end();
				iterator save_other;

				while (first != last || x_first != x_last)
				{
					if (comp(*first, *x_first) && x_first != x_last)
						{
							save_other = x_first++;
							splice(first, x, save_other);
						}
					else if (first != last)
						++first;
					else if (first == last)
					{
						save_other = x_first++;
						splice(first, x, save_other);
					}
				}
			}
			~list()
			{
				while (node_base::__head_)
				{
					delete node_base::__head_;
					node_base::__head_ = node_base::__head_->__next_;
					--__length_;
				}
			}
	};
	template< class T>
	bool operator==( const list<T>& x, const list<T>& y )
	{
		bool i = true;
		ft::list<int>::iterator x_begin = x.begin();
		ft::list<int>::iterator y_begin = y.begin();
		if (x.size() != y.size())
			return false;
		while (x_begin != x.end())
		{
			if (*x_begin != *y_begin)
			{
				i = false;
				break;
			}
			x_begin++;
			y_begin++;
		}
		return (i);
	}
	
	template< class T>
	bool operator!=( const list<T>& x, const list<T>& y )
	{
		return !(x == y);
	}
	
	template< class T>
	bool operator<( const list<T>& x, const list<T>& y )
	{
		bool i = true;
		ft::list<int>::iterator x_begin = x.begin();
		ft::list<int>::iterator y_begin = y.begin();
		while (x_begin != x.end() && y_begin != y.end())
		{
			if (*x_begin < *y_begin)
				return true;
			x_begin++;
			y_begin++;
		}
		if (x.size() >= y.size())
			return false;
		return (i);
	}
	
	template< class T>
	bool operator>( const list<T>& x, const list<T>& y )
	{
		return (y < x);
	}

	template< class T>
	bool operator<=( const list<T>& x, const list<T>& y )
	{
		return !(y < x);
	}

	template< class T>
	bool operator>=( const list<T>& x, const list<T>& y )
	{
		return !(x < y);
	}
}

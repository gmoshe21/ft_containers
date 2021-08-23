#pragma once

# include "iterator.hpp"
# include <exception>

# define ALLOC_MEM 8

namespace ft
{
	template<typename Type>
	class gmoshe
	{
		public:
			typedef Type value_type;
		protected:
			value_type *allocator;
		public:
			gmoshe() : allocator(NULL){}
	};
	template<typename Type>
	class vector : public gmoshe<Type>
	{
	public:
		typedef Type							value_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef iterator<value_type>			iterator;
		typedef const iterator			const_iterator;
		typedef reverse_iterator<iterator>	reverse_iterator;
		typedef std::ptrdiff_t					difference_type;
		typedef size_t							size_type;
	private:
		// value_type	*allocator;
		size_type		memory;
		pointer		__begin_;
		pointer		__end_;
	public:
		vector() : memory(ALLOC_MEM)
		{
			gmoshe<value_type>::allocator = new value_type[ALLOC_MEM];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
		}
		explicit vector( size_type count ) : memory(count)
		{
			gmoshe<value_type>::allocator = new value_type[count];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
		}
		vector(vector const &vec)
		{
			// gmoshe<value_type>::allocator = new value_type[memory];
			// __begin_ = gmoshe<value_type>::allocator;
			// __end_ = gmoshe<value_type>::allocator;
			// for (unsigned long i = 0; i < vec.size(); i++)
			// 	*__end_++ = vec[i];
			*this = vec;		
		}
		vector(iterator first, iterator last)
		{
			difference_type size = last - first;
			gmoshe<value_type>::allocator = new value_type[size];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
			while (first != last)
				*__end_++ = *first++;
		}
		vector(size_type _n, const value_type &x) : memory(ALLOC_MEM)
		{
			while (_n >= memory)
				memory += ALLOC_MEM;
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
			while (_n-- != 0)
				*__end_++ = x;
		}
		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max();
		}
		iterator begin() const
		{
			return (__begin_);
		}
		iterator end() const
		{
			return (__end_);
		}
		reverse_iterator rbegin() const
		{
			return reverse_iterator(__end_);
		}
		reverse_iterator rend() const
		{
			return reverse_iterator(__begin_);
		}

		unsigned long size() const
		{
			return (__end_ - __begin_);
		}

		reference operator[](size_type _n) const
		{
			return *(__begin_ + _n);
		}

		void allocated_memory()
		{
			pointer	old = gmoshe<value_type>::allocator;
			
			memory += ALLOC_MEM;
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator + (memory - ALLOC_MEM);
			for (unsigned long i = 0; i < memory - ALLOC_MEM; i++)
				gmoshe<value_type>::allocator[i] = old[i];
			delete[] old;
		} 

		size_t capacity()
		{
			return (memory);
		}
		
		bool empty() const
		{
			return (!(this->size()));
		}

		void assign(size_t _n, const value_type &_x)
		{
			if (_n > 0)
			{
				delete[]	gmoshe<value_type>::allocator;
				while (memory <= _n)
					memory += ALLOC_MEM;
				gmoshe<value_type>::allocator = new value_type[memory];
				__begin_ = gmoshe<value_type>::allocator;
				__end_ = gmoshe<value_type>::allocator + _n;
				for (unsigned long i = 0; i <= _n; i++)
					gmoshe<value_type>::allocator[i] = _x;
			}
		}

		void assign(iterator first, iterator last)
		{
			delete[] gmoshe<value_type>::allocator;
			difference_type size = last - first;
			while (static_cast<long>(memory) <= size)
				memory += ALLOC_MEM;
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator + size;
			for (unsigned long i = 0; first != last; i++)
				gmoshe<value_type>::allocator[i] = *(first++);
		}

		vector &operator=(vector const &other)
		{
			if(!gmoshe<value_type>::allocator)
				gmoshe<value_type>::allocator = new value_type[1];
			memory = other.memory;
			assign(other.begin(), other.end());
			return (*this);
		}

		void push_back(value_type const &val)
		{
			if (__end_ - __begin_ == static_cast<long>(memory))
				allocated_memory();
			*__end_ = val;
			__end_++;
		}

		void pop_back()
		{
			pointer	old = gmoshe<value_type>::allocator;
			unsigned long count = size() - 1;
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator + count;
			for (unsigned long i = 0; i < count; i++)
				gmoshe<value_type>::allocator[i] = old[i];
			delete[] old;			
		}

		iterator insert(iterator position, const value_type& val)
		{
			if (__end_ - __begin_ == memory)
				allocated_memory();
			pointer old = gmoshe<value_type>::allocator;
			iterator start = begin();
			iterator last = end();
			gmoshe<value_type>::allocator = new value_type[memory];
			__end_ = gmoshe<value_type>::allocator;
			__begin_ = gmoshe<value_type>::allocator;
			for (unsigned long i = 0; start != position; i++)
			{
				gmoshe<value_type>::allocator[i] = old[i];
				start++;
				__end_++;
			}
			iterator New = __end_;
			*__end_ = val;
			__end_++;
			while (position != last)
			{
				*__end_ = *position;
				__end_++;
				position++;
			}
			delete[] old;
			return New;			
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			while ((__end_ - __begin_) + n >= memory)
				memory += ALLOC_MEM;
			pointer old = gmoshe<value_type>::allocator;
			iterator old_begin = begin();
			iterator old_end = end();
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
			while (old_begin != position)
				*__end_++ = *old_begin++;
			for (size_type i = 0; i < n; i++)
				*__end_++ = val;
			while (old_begin != old_end)
				*__end_++ = *old_begin++;
			delete[] old;
		}

		// template <class InputIterator>
		void insert (iterator position, iterator first, iterator last)
		{
			while ((__end_ - __begin_) + (last - first) >= static_cast<long>(memory))
				memory += ALLOC_MEM;
			pointer old = gmoshe<value_type>::allocator;
			iterator old_begin = begin();
			iterator old_end = end();
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
			while (old_begin != position)
				*__end_++ = *old_begin++;
			while (first != last)
				*__end_++ = *first++;
			while (old_begin != old_end)
				*__end_++ = *old_begin++;
			delete[] old;
		}

		iterator erase(iterator pos)
		{
			iterator	ret = pos;
			--__end_;
			while (pos != __end_)
			{
				*pos = *(pos + 1);
				pos++;
			}
			*__end_ = 0;//дописать
			return ret;
		}
		
		iterator erase(iterator first, iterator last )
		{
			iterator		ret = first;
			while (last != __end_)
				*(first++) = *(last++);
			while (first != __end_)
				*(--__end_) = 0;//дописать
			return ret;
		}
		
		void swap (vector &vec)
		{
			std::swap(gmoshe<value_type>::allocator, vec.allocator);
			std::swap(__begin_, vec.__begin_);
			std::swap(__end_, vec.__end_);
			// pointer old = allocator;
			// allocator = vec.allocator;
			// vec.allocator = old;
			// old = __begin_;
			// __begin_ = vec.__begin_;
			// vec.__begin_ = old;
			// old = __end_;
			// __end_ = vec.__end_;
			// vec.__end_ = old;
		}

		void clear()
		{
			delete[] gmoshe<value_type>::allocator;
			gmoshe<value_type>::allocator = new value_type[ALLOC_MEM];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator + 1;
		}

		reference at(size_type _n)
		{
			if (_n >= size())
				throw std::out_of_range("vector");
			return __begin_[_n];
		}

		const_reference at (size_type _n) const
		{
			if (_n >= size())
				throw std::out_of_range("vector");
			return __begin_[_n];
		}

		reference       front()
		{
			return *__begin_;//доделать и тесты
		}

		const_reference       front() const
		{
			return *__begin_;
		}

		reference       back()
		{
			return *(__end_ - 1);
		}

		const_reference       back() const
		{
			return *(__end_ - 1);
		}

		void reserve(size_type new_cap)
		{
			if (new_cap <= memory)
				return;
			pointer old = gmoshe<value_type>::allocator;
			iterator next = begin();
			iterator last = end();
			while(memory < new_cap)
				memory += ALLOC_MEM;
			gmoshe<value_type>::allocator = new value_type[memory];
			__begin_ = gmoshe<value_type>::allocator;
			__end_ = gmoshe<value_type>::allocator;
			while (next != last)
				*__end_++ = *next++;
			delete[] old;
		}

		void resize(size_type count)
		{
			while (size() < count)
				push_back(0);
			while (size() > count)
				pop_back();
		}

		void resize(size_type count, value_type value)
		{
			while (size() < count)
				push_back(value);
			while (size() > count)
				pop_back();
		}
		
		~vector()
		{
			delete[] gmoshe<value_type>::allocator;
		}
	};

	template <typename Type>
	bool operator==(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Type>
	bool operator!=(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Type>
	bool operator<(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Type>
	bool operator<=(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename Type>
	bool operator>(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Type>
	bool operator>=(const vector<Type> &lhs, const vector<Type> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Type>
	void swap(vector<Type> &lhs, vector<Type> &rhs)
	{
		rhs.swap(lhs);
	}
}

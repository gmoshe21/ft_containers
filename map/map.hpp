#pragma once
#include <memory>
#include "map_iterator.hpp"

namespace ft
{	
	template<class Pair, class KeyComp>
    struct p_k_comp
    {
        KeyComp _kcomp;

        p_k_comp(const KeyComp& kc = KeyComp()) : _kcomp(kc) {}

        bool operator()(const Pair& p1, const Pair& p2) const
        {
            return _kcomp(p1.first,p2.first);
        }
    };

	template<typename Key, typename Type,  class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, Type> > >
	class map
	{
		public:
			typedef Key									key_type;
			typedef Type								mapped_type;
			typedef	std::pair<const Key, Type>			value_type;
			typedef map_iterator<value_type>			iterator;
			typedef map_const_iterator<value_type>		const_iterator;
			typedef map_reverse_iterator<iterator>		reverse_iterator;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			typedef typename allocator_type::template	rebind<tree_node<value_type> >::other node_allocator_type;
			typedef p_k_comp<value_type, key_compare>	value_compare;
			
		private:
			red_black_tree<value_type>	tree;
			size_type					_size;
			key_compare					_compare;
			allocator_type				_allocator;
			node_allocator_type			_node_allocator;

			tree_node<value_type> *node_search(tree_node<value_type> *start, value_type const &value) const
			{
				if (start && start->element.first > value.first)
					start = node_search(start->left, value);
				else if (start && value.first > start->element.first)
					start = node_search(start->right, value);
				else if (start && start->element.first == value.first)
					return (start);
				else if (!start)
					return (NULL);
				return (start);
			}
			
		public:
			map(const Compare& comp=Compare())
			{ _size = 0; _compare = comp; }
			map(map const &other)
			{
				_size = 0;
				for (const_iterator it = other.begin(); it != other.end(); it++)
					insert(*it);
			}
			map(iterator first, iterator last, const Compare& comp = Compare())
			{
				_size = 0;
				_compare = comp;
				insert(first, last);
			}
			std::pair<iterator, bool> insert(value_type const &value)
			{
				tree_node<value_type> *start = node_search(tree.begin(), value);
				
				_size++;
				if (!start || start->element.first != value.first)
				{
					iterator new_node = tree.adding_node(value);
					return std::pair<iterator, bool>(new_node, true);
				}
				else
					return std::pair<iterator, bool>(end(), false);
			}

			iterator insert( iterator hint, value_type const &value )
			{
				if (NULL == begin().get_the_node())
					return tree.adding_node(value);
				if (hint != begin())
				{
					if ((--hint)->first > value.first)
						return insert(hint, value);
					else
						++hint;
				}
				if (hint != --end() && hint != end())
				{
					if ((++hint)->first < value.first)
						return insert(hint, value);
					else
						--hint;
				}
				_size++;
				return tree.under_the_tree_adding_node(hint.get_the_node(), value);
			}
			template<class Iterator>
			void insert( Iterator first, Iterator last )
			{
				while (first != last)
					insert(*first++);
			}
			
			iterator begin()
			{
				tree_node<value_type> *start = tree.begin();
				if (!start)
					return end();
				while (start && start->left)
					start = start->left;
				return start;
			}

			const_iterator begin() const
			{
				tree_node<value_type> *start = tree.begin();
				if (!start)
					return end();
				while (start && start->left)
					start = start->left;
				return start;
			}

			iterator end()
			{
				return tree.end();
			}

			const_iterator end() const
			{
				return tree.end();
			}

			reverse_iterator rbegin()
			{
				return end();
			}

			reverse_iterator rend()
			{
				return begin();
			}

			size_type erase( const key_type& key )
			{
				tree_node<value_type> *start = node_search(tree.begin(), std::pair<key_type, Type>(key, 0));
				if (!start)
					return (0);
				tree.remove(start->element);
				_size--;
				return (1);
			}

			void erase( iterator pos )
			{
				erase(pos->first);
			}

			void erase( iterator first, iterator last )
			{
				iterator prev;
				while (first != last)
				{
					prev = first++;
					erase(prev->first);
				}
			}

			void clear()
			{
				erase(begin(), end());
			}

			void swap( map& other )
			{
				red_black_tree<value_type>	tmp;
				tree = other.tree;
				other.tree = tmp;
			}

			bool empty() const
			{
				return (begin() == end());
			}

			size_type max_size() const
			{
				return _node_allocator.max_size();
			}

			size_type size() const
			{
				return _size;
			}

			size_type count( const Key& key ) const
			{
				if (node_search(tree.begin(), std::pair<key_type, Type>(key, 0)))
					return 1;
				return 0;
			}
			
			iterator find( const Key& key )
			{
				iterator start = node_search(tree.begin(), std::pair<key_type, Type>(key, 0));
				if (start.get_the_node())
					return start;
				return end();
			}

			const_iterator find( const Key& key ) const
			{
				return const_iterator(find(key));
			}

			iterator lower_bound( const Key& key )
			{
				iterator start = begin();
				
				while (start != end() && start->first < key)
					start++;
				return start;
			}

			const_iterator lower_bound( const Key& key ) const
			{
				const_iterator start = begin();
				
				while (start != end() && start->first < key)
					start++;
				return start;
			}

			iterator upper_bound( const Key& key )
			{
				iterator start = begin();
				
				while (start != end() && start->first <= key)
					start++;
				return start;
			}

			const_iterator upper_bound( const Key& key ) const
			{
				const_iterator start = begin();
				
				while (start != end() && start->first <= key)
					start++;
				return start;
			}

			std::pair<iterator,iterator> equal_range( const Key& key )
			{
				return std::pair<iterator,iterator>(lower_bound(key), upper_bound(key));
			}

			std::pair<const_iterator, const_iterator> equal_range( const Key& key ) const
			{
				return std::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}
			
			Type& operator[]( const key_type& key )
			{
				tree_node<value_type> *start = node_search(tree.begin(), std::pair<key_type, Type>(key, Type()));
				if (start)
					return start->element.second;
				return insert(std::pair<key_type, Type>(key, Type())).first->second;
			}

			key_compare key_comp() const
			{
				return _compare;
			}

			value_compare value_comp() const
			{
				return _compare;
			}

			template<typename K, typename T, typename C, typename A>
			friend bool operator==(const map<K, T, C, A>& x, const map<K, T, C, A>& y);
			
			template<typename K, typename T, typename C, typename A>
			friend bool operator!=(const map<K, T, C, A>& x, const map<K, T, C, A>& y);
			
			
	};
		template<typename K, typename T, typename C, typename A>
		bool operator==(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			typename map<K, T, C>::const_iterator x_it = x.begin();
			typename map<K, T, C>::const_iterator x_end = x.end();
			typename map<K, T, C>::const_iterator y_it = y.begin();
			typename map<K, T, C>::const_iterator y_end = y.end();
			while (x_it != x_end && y_it != y_end && *x_it == *y_it)
			{
				++x_it; ++y_it;
			}
			return x_it == x_end && y_it == y_end;
		}

		template<typename K, typename T, typename C, typename A>
		bool operator<(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			typename map<K, T, C>::const_iterator x_it = x.begin();
			typename map<K, T, C>::const_iterator x_end = x.end();
			typename map<K, T, C>::const_iterator y_it = y.begin();
			typename map<K, T, C>::const_iterator y_end = y.end();
			while (x_it != x_end && y_it != y_end && *x_it == *y_it)
			{
				++x_it; ++y_it;
			}
			return (x_it == x_end && y_it != y_end) || *x_it < *y_it;
		}
		
		template<typename K, typename T, typename C, typename A>
		bool operator!=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			return !(x == y);
		}

		template<typename K, typename T, typename C, typename A>
		bool operator>(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			return (y < x);
		}

		template<typename K, typename T, typename C, typename A>
		bool operator<=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			return (!(y < x));
		}

		template<typename K, typename T, typename C, typename A>
		bool operator>=(const map<K, T, C, A>& x, const map<K, T, C, A>& y)
		{
			return (!(x < y));
		}
}
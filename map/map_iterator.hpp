#pragma once
#include "red_black_tree.hpp"

namespace ft
{
	template<typename Type>
	class map_iterator
	{
		public:
			typedef tree_node<Type>	node;
			typedef Type*	pointer;
			typedef Type&	reference;
		private:
			node	*ptr;

			void previous()
			{
				if (this->ptr->left)
				{
					this->ptr = this->ptr->left;
					while (this->ptr->right)
						this->ptr = this->ptr->right;
				}
				else
				{
					node *tmp = this->ptr;
					this->ptr = this->ptr->parent;
						while (this->ptr->right != tmp)
						{
							tmp = this->ptr;
							this->ptr = this->ptr->parent;
						}
				}
			}
			
			void next()
			{
				if (this->ptr->right)
				{
					this->ptr = this->ptr->right;
					while (this->ptr->left)
						this->ptr = this->ptr->left;
				}
				else
				{
					node *tmp = this->ptr;
					this->ptr = this->ptr->parent;
						while (this->ptr->left != tmp)
						{
							tmp = this->ptr;
							this->ptr = this->ptr->parent;
						}
				}
			}
			
		public:
			map_iterator(){}
			map_iterator(node *current){ ptr = current;}
			template<typename map_const_iterator>
			map_iterator(map_const_iterator const &other) {ptr = other.get_the_node();}
			map_iterator& operator=(map_iterator const &current){ ptr = current.ptr; return *this;}
			pointer operator->(){ return &ptr->element;}
			reference operator*() { return (this->ptr->element);}
			node *get_the_node() const { return ptr;}
			
			map_iterator &operator++()
			{
				next();
				return *this;
			}

			map_iterator operator++(int)
			{
				map_iterator tmp(*this);
				next();
				return (tmp);
			}

			map_iterator operator--(int)
			{
				map_iterator tmp(*this);
				previous();
				return (tmp);
			}
			map_iterator &operator--()
			{
				previous();
				return (*this);
			}
			bool operator==(map_iterator const &next)
			{
				return (ptr == next.ptr);
			}
			bool operator!=(map_iterator const &next)
			{
				return (ptr != next.ptr);
			}
	};

	template<typename Type>
	class map_const_iterator
	{
		public:
			typedef tree_node<Type>	node;
			typedef const Type*	pointer;
			typedef const Type&	reference;
		private:
			node	*ptr;

			void previous()
			{
				if (this->ptr->left)
				{
					this->ptr = this->ptr->left;
					while (this->ptr->right)
						this->ptr = this->ptr->right;
				}
				else
				{
					node *tmp = this->ptr;
					this->ptr = this->ptr->parent;
						while (this->ptr->right != tmp)
						{
							tmp = this->ptr;
							this->ptr = this->ptr->parent;
						}
				}
			}
			
			void next()
			{
				if (this->ptr->right)
				{
					this->ptr = this->ptr->right;
					while (this->ptr->left)
						this->ptr = this->ptr->left;
				}
				else
				{
					node *tmp = this->ptr;
					this->ptr = this->ptr->parent;
						while (this->ptr->left != tmp)
						{
							tmp = this->ptr;
							this->ptr = this->ptr->parent;
						}
				}
			}
			
		public:
			map_const_iterator(){}
			map_const_iterator(node *current){ ptr = current;}
			map_const_iterator(map_const_iterator const &current){ ptr = current.get_the_node();}
			map_const_iterator(map_iterator<Type> const &current){ ptr = current.get_the_node();}
			map_const_iterator& operator=(map_const_iterator const &current){ ptr = current.ptr; return *this;}
			pointer operator->(){ return &ptr->element;}
			reference operator*() { return (this->ptr->element);}
			node *get_the_node() const { return ptr;}
			
			map_const_iterator &operator++()
			{
				next();
				return *this;
			}

			map_const_iterator operator++(int)
			{
				map_const_iterator tmp(*this);
				next();
				return (tmp);
			}

			map_const_iterator operator--(int)
			{
				map_const_iterator tmp(*this);
				previous();
				return (tmp);
			}
			map_const_iterator &operator--()
			{
				previous();
				return (*this);
			}
			bool operator==(map_const_iterator const &next)
			{
				return (ptr == next.ptr);
			}
			bool operator!=(map_const_iterator const &next)
			{
				return (ptr != next.ptr);
			}
	};

	template<typename Type>
	class map_reverse_iterator
	{
		public:
			typedef typename Type::pointer			pointer;
			typedef typename Type::reference		reference;
			// typedef typename Type::difference_type	difference_type;
		private:
			Type	ptr;

		public:
			map_reverse_iterator(){}
			map_reverse_iterator(map_reverse_iterator const &other) {ptr = other.ptr;}
			map_reverse_iterator(Type const &other) {ptr = other;}
			map_reverse_iterator& operator=(map_reverse_iterator const &current){ ptr = current.ptr; return *this;}
			reference operator*() { Type temp = ptr; return *(--temp);}
			pointer operator->(){ return &operator*();}
			// node *get_the_node() { return ptr;}
			
			map_reverse_iterator &operator++()
			{
				--ptr;
				return *this;
			}

			map_reverse_iterator operator++(int)
			{
				map_reverse_iterator tmp(*this);
				--ptr;
				return (tmp);
			}

			map_reverse_iterator operator--(int)
			{
				map_reverse_iterator tmp(*this);
				++ptr;
				return (tmp);
			}
			map_reverse_iterator &operator--()
			{
				++ptr;
				return (*this);
			}
			bool operator==(map_reverse_iterator const &next)
			{
				return (ptr == next.ptr);
			}
			bool operator!=(map_reverse_iterator const &next)
			{
				return (ptr != next.ptr);
			}
	};
};
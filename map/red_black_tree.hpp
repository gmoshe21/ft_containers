#pragma once

#include <iostream>

enum e_color{RED, BLACK};

namespace ft
{

	template<class Type>
	struct tree_node
	{
		Type element;

		tree_node *parent;
		tree_node *right;
		tree_node *left;
		e_color color;
		tree_node(tree_node *parent, tree_node *right, tree_node *left, e_color color, Type value)
				: parent(parent), right(right), left(left), color(color), element(value) {}
		tree_node *link(int i)
		{
			if (i)
				return right;
			return left;
		}
		
		void changing_pointers(int i, tree_node *ptr, tree_node *p)
		{
			if (i)
				right = ptr;
			else
				left = ptr;
			if (ptr)
				ptr->parent = p;
		}
	};

	template<class Type>
	class red_black_tree
	{
		public:
			typedef tree_node<Type>	node;
		private:
			node *root;
			node *end_node;
			node *alloc_node(Type const &value)
			{
				node *new_node = new node(NULL, NULL, NULL, RED, value);
				return new_node;
			}

			void connect_disconnect_end_node(int i)
			{
				node *start = root;
				while (start && start->right && start->right != end_node)
					start = start->right;
				if (start && i)
				{
					start->right = end_node;
					end_node->parent = start;
				}
				else if (start)
					start->right = NULL;
			}
			
			node *connected_element(node *parent, node *new_node)
			{
				new_node->parent = parent;
				return new_node;
			}

			node *grandparent(node *n)
			{
				if ((n != NULL) && (n->parent != NULL))
					return n->parent->parent;
				else
					return NULL;
			}

			node *uncle(node *n)
			{
				node *g = grandparent(n);
				if (g == NULL)
					return NULL;
				if (n->parent == g->left)
					return g->right;
				else
					return g->left;
			}

			void rotate_left(node *n)
			{
				node *pivot = n->right;
				
				if (n->parent == NULL)
					root = pivot;
				pivot->parent = n->parent;
				if (n->parent != NULL) {
					if (n->parent->left==n)
						n->parent->left = pivot;
					else
						n->parent->right = pivot;
				}		
				
				n->right = pivot->left;
				if (pivot->left != NULL)
					pivot->left->parent = n;

				n->parent = pivot;
				pivot->left = n;
			}

			void rotate_right(node *n)
			{
				node *pivot = n->left;
				
				if (n->parent == NULL)
					root = pivot;
				pivot->parent = n->parent;
				if (n->parent != NULL) {
					if (n->parent->left==n)
						n->parent->left = pivot;
					else
						n->parent->right = pivot;
				}		
				
				n->left = pivot->right;
				if (pivot->right != NULL)
					pivot->right->parent = n;

				n->parent = pivot;
				pivot->right = n;
			}
			
			node *sibling(node *n)
			{
				if (n == n->parent->left)
					return n->parent->right;
				else
					return n->parent->left;
			}

			void replace_node(node* n, node* child)
			{
				child->parent = n->parent;
				if (n == n->parent->left)
					n->parent->left = child;
				else
					n->parent->right = child;
			}

			void delete_one_child(node *n)
			{
				node *child = is_leaf(n->right) ? n->left : n->right;
				
				replace_node(n, child);
				if (n->color == BLACK) {
					if (child->color == RED)
						child->color = BLACK;
					else
						delete_case1(child);
				}
				free(n);
			}

			node *replacement_node_search(node *removing_node)
			{
				if (removing_node->left && removing_node->left != end_node)
				{
					removing_node = removing_node->left;
					while (removing_node->right && removing_node->right != end_node)
						removing_node = removing_node->right;
					return removing_node;
				}
				else if (removing_node->right != end_node)
					return removing_node->right;
				return removing_node;
			}

			void swap_parent(node *insert, node *deletion)
			{
				if (insert->parent == deletion)
				{
					node *temp = deletion->parent;
					deletion->parent = insert;
					insert->parent = temp;
					if (insert->parent && insert->parent->left == deletion)
						insert->parent->left = insert;
					else if (insert->parent && insert->parent->right == deletion)
						insert->parent->right = insert;
				}
				else
				{
					if (insert->parent && insert->parent != end_node)
					{
						if (insert->parent->left == insert)
							insert->parent->left = deletion;
						else
							insert->parent->right = deletion;
					}
					if (deletion->parent && deletion->parent != end_node)
					{
						if (deletion->parent->left == deletion)
							deletion->parent->left = insert;
						else
							deletion->parent->right = insert;
					}
					std::swap(insert->parent, deletion->parent);
				}
			}

			void swap_left(node *insert, node *deletion)
			{
				if (deletion->left == insert)
				{
					node *temp = insert->left;
					insert->left = deletion;
					deletion->left = temp;
					if (deletion->left)
						deletion->left->parent = deletion;
				}
				else
				{
					if (insert->left && insert->left != end_node)
						insert->left->parent = deletion;
					if (deletion->left && deletion->left != end_node)
						deletion->left->parent = insert;
					std::swap(insert->left, deletion->left);
				}
			}

			void swap_right(node *insert, node *deletion)
			{
				if (deletion->right == insert)
				{
					node *temp = insert->right;
					insert->right = deletion;
					deletion->right = temp;
					if (deletion->right)
						deletion->right->parent = deletion;
				}
				else
				{
					if (insert->right && insert->right != end_node)
						insert->right->parent = deletion;
					if (deletion->right && deletion->right != end_node)
						deletion->right->parent = insert;
					std::swap(insert->right, deletion->right);
				}
			}

			int is_red (node *root)
			{
				return root != NULL && root->color == RED;
			}
			
			node *left_right(node *block, int dir)
			{
				if (dir)
					return block->right;
				return block->left;
			}

			node *rot_single (node *root, int dir)
			{
				node *save = left_right(root, !dir);

				if (dir)
				{
					root->left = left_right(save, dir);
					if (root->left)
					root->left->parent = root;
				}
				else
				{
					root->right = left_right(save, dir);
					if (root->right)
					root->right->parent = root;
				}
				root->parent = save;
				if (dir)
					save->right = root;
				else
					save->left = root;
				root->color = RED;
				save->color = BLACK;
				return save;
			}

			node *rot_double (node *root, int dir)
			{
				node *permutation = rot_single (left_right(root, !dir), !dir);
				permutation->parent = root;
				if (dir)
					root->left = permutation;
				else
					root->right = permutation;
				return rot_single (root, dir);
			}
			
		public:
			red_black_tree()
			{
				Type v;
				end_node = new node(NULL, NULL, NULL, BLACK, v);
				root = NULL;
			}
			// ~red_black_tree();
			
			node *begin() const {	return root;}
			node *end() const {	return end_node;}

			node *node_search(node *start, Type const &value)
			{
				if (start && start->element > value)
					start = node_search(start->left, value);
				else if (start && value > start->element)
					start = node_search(start->right, value);
				else if (start && start->element == value)
					return (start);
				return (NULL);
			}
			
			node *adding_node(Type const &value)
			{
				node *new_node = alloc_node(value);
				if (root == NULL)
					root = new_node;
				else
				{
					connect_disconnect_end_node(0);
					motion_depth(root, new_node);
				}
				insert_case1(new_node);
				connect_disconnect_end_node(1);
				return new_node;
			}

			node *under_the_tree_adding_node(node *_root, Type const &value)
			{
				node *new_node = alloc_node(value);
				if (_root == end_node)
					_root = _root->parent;
				connect_disconnect_end_node(0);
				motion_depth(_root, new_node);
				insert_case1(new_node);
				connect_disconnect_end_node(1);
				return new_node;
			}

			void motion_depth(node *root, node *new_node)
			{
				if (new_node->element < root->element)
				{
					if (root->left)
						motion_depth(root->left, new_node);
					else
						root->left = connected_element(root, new_node);
				}
				else
				{
					if (root->right)
						motion_depth(root->right, new_node);
					else
						root->right = connected_element(root, new_node);
				}
			}

			void insert_case1(node *n)
			{
				if (n->parent == NULL)
					n->color = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(node *n)
			{
				if (n->parent->color == BLACK)
					return;
				else
					insert_case3(n);
			}

			void insert_case3(node *n)
			{
				node *u = uncle(n), *g;

				if ((u != NULL) && (u->color == RED))
				{
					n->parent->color = BLACK;
					u->color = BLACK;
					g = grandparent(n);
					g->color = RED;
					insert_case1(g);
				} 
				else
					insert_case4(n);
			}
			
			void insert_case4(node *n)
			{
				node *g = grandparent(n);

				if ((n == n->parent->right) && (n->parent == g->left))
				{
					rotate_left(n->parent);
					n = n->left;
				}
				else if ((n == n->parent->left) && (n->parent == g->right))
				{
					rotate_right(n->parent);
					n = n->right;
				}
				insert_case5(n);
			}

			void insert_case5(node *n)
			{
				node *g = grandparent(n);

				n->parent->color = BLACK;
				g->color = RED;
				if ((n == n->parent->left) && (n->parent == g->left))
					rotate_right(g);
				else
					rotate_left(g);
			}

			void delete_node(Type const &value)
			{
				node *removing_node = node_search(root, value);
				node *replacement_node = replacement_node_search(removing_node);
				swap_parent(replacement_node, removing_node);
				swap_left(replacement_node, removing_node);
				swap_right(replacement_node, removing_node);
				std::swap(removing_node->color, replacement_node->color);
				delete_case1(removing_node);
			}
		
			void delete_case1(node *n)
			{
				if (n->parent != NULL)
					delete_case2(n);
			}

			void delete_case2(node *n)
			{
				node *s = sibling(n);

				if (s->color == RED) {
					n->parent->color = RED;
					s->color = BLACK;
					if (n == n->parent->left)
						rotate_left(n->parent);
					else
						rotate_right(n->parent);
				} 
				delete_case3(n);
			}

			void delete_case3(node *n)
			{
				node *s = sibling(n);

				if ((n->parent->color == BLACK) &&
					(s->color == BLACK) &&
					(s->left->color == BLACK) &&
					(s->right->color == BLACK)) {
					s->color = RED;
					delete_case1(n->parent);
				} else
					delete_case4(n);
			}

			void delete_case4(node *n)
			{
				node *s = sibling(n);

				if ((n->parent->color == RED) &&
					(s->color == BLACK) &&
					(s->left->color == BLACK) &&
					(s->right->color == BLACK)) {
					s->color = RED;
					n->parent->color = BLACK;
				} else
					delete_case5(n);
			}

			void delete_case5(node *n)
			{
				node *s = sibling(n);

				if  (s->color == BLACK) { /* this if statement is trivial, 
			due to case 2 (even though case 2 changed the sibling to a sibling's child, 
			the sibling's child can't be red, since no red parent can have a red child). */
			/* the following statements just force the red to be on the left of the left of the parent, 
			or right of the right, so case six will rotate correctly. */
					if ((n == n->parent->left) &&
						(s->right->color == BLACK) &&
						(s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
						s->color = RED;
						s->left->color = BLACK;
						rotate_right(s);
					} else if ((n == n->parent->right) &&
							(s->left->color == BLACK) &&
							(s->right->color == RED)) {/* this last test is trivial too due to cases 2-4. */
						s->color = RED;
						s->right->color = BLACK;
						rotate_left(s);
					}
				}
				delete_case6(n);
			}

			void delete_case6(node *n)
			{
				node *s = sibling(n);

				s->color = n->parent->color;
				n->parent->color = BLACK;

				if (n == n->parent->left) {
					s->right->color = BLACK;
					rotate_left(n->parent);
				} else {
					s->left->color = BLACK;
					rotate_right(n->parent);
				}
			}
			
			int remove (Type data)
			{
				connect_disconnect_end_node(0);
				node *t = root->right;
				if (root != NULL)
				{
					node head(NULL,NULL,NULL,BLACK,data); /* False tree root */
					node *q, *p, *g; /* Helpers */
					node *f = NULL;  /* Found item */
					int dir = 1;

					/* Set up helpers */
					q = &head;
					g = p = NULL;
					q->right = root;

					/* Search and push a red down */
					while (q->link (dir) != NULL)
					{
						int last = dir;

						/* Update helpers */
						g = p, p = q;
						q = q->link (dir);
						dir = q->element < data;

						/* Save found node */
						if (q->element == data)
							f = q;
						if (!is_red (q) && !is_red (q->link (dir)))
						{
							if (is_red (q->link (!dir)))
							{
								p->changing_pointers(last, rot_single (q, dir), p);
								p = p->link (last);
							}
							else if (!is_red (q->link (!dir)))
							{
								node *s = p->link (!last);
								if (s != NULL)
								{
									if (!is_red (s->link (!last)) && !is_red (s->link (last)))
									{
										p->color = BLACK;
										s->color = RED;
										q->color = RED;
									}
									else
									{
										int dir2 = g->link (1) == p;
										if (is_red (s->link (last)))
											g->changing_pointers (dir2, rot_double (p, last), g);
										else if (is_red (s->link (!last)))
											g->changing_pointers (dir2, rot_single (p, last), g);
										q->color = g->link (dir2)->color = RED;
										g->link (dir2)->link (0)->color = BLACK;
										g->link (dir2)->link (1)->color = BLACK;
									}
								}
							}
						}
					}
					if (f != NULL)
					{
						swap_parent(q, f);
						swap_left(q, f);
						swap_right(q, f);
						std::swap(q->color, f->color);
						if (q->left)
							q->changing_pointers(q->right == f, f->link (f->left == NULL), q);
						else
							p->changing_pointers(p->right == q, q->link (q->left == NULL), p);
						free (q);
					}
					root = head.link(1);
					if (root != NULL)
					{
						root->color = BLACK;
						root->parent = NULL;
					}
				}
				connect_disconnect_end_node(1);
				return 1;
			}
	};
}
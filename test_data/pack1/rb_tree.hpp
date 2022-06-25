#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <algorithm>
# include <iostream>
# include "ft_templates.hpp"

namespace ft
{
	template< class T >
	struct rb_node
	{
		rb_node	*left;
		rb_node	*right;
		rb_node	*parent;
		bool	is_red;
		T		value;
		rb_node(const T& value, rb_node *left = NULL, rb_node *right = NULL,
			rb_node *parent = NULL, bool is_red = true) :
			left(left), right(right), parent(parent), is_red(is_red), value(value) {}
	};

	template< class T >
	class	rb_tree_Iterator;

	template< class T >
	class	rb_tree_ConstIterator;

	template< class T, class Compare = std::less< T >, class Allocator = std::allocator< T > >
	class rb_tree
	{
		public:
			typedef	T						value_type;
			typedef unsigned long			size_type;
			typedef Allocator				allocator_type;
			typedef Compare					comparator_type;
			typedef rb_tree_Iterator< T >		iterator;
			typedef rb_tree_ConstIterator< T >	const_iterator;
			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			typedef typename allocator_type::template rebind< rb_node< T > >::other	node_allocator_type;

		private:
			rb_node< T > *	_root;
			size_type		_size;
			allocator_type	_alloc;
			comparator_type	_comp;

		public:
			rb_tree() : _root(NULL), _size(0), _alloc() {}

			explicit rb_tree( const Compare& comp, const Allocator& alloc = Allocator() )
				: _comp(comp), _alloc(alloc), _root(NULL), _size(0) {}

			rb_tree( const rb_tree & other )
			{
				_copy_tree_recursive(_root, NULL, other._root);
				_size = other._size;
			}

			~rb_tree()
			{
				_clear_tree_recursive(_root);
			}

			rb_tree& operator=( const rb_tree& other )
			{
				rb_node< T >	*tmp = NULL;
				_copy_tree_recursive(tmp, NULL, other._root);
				_clear_tree_recursive(_root);
				_root = tmp;
				_size = other._size;
				return *this;
			}

			allocator_type get_allocator() const
			{
				return _alloc;
			}

			bool empty() const
			{
				return _root == NULL;
			}

			size_type size() const
			{
				return _size;
			}

			size_type max_size() const
			{
				return (node_allocator_type().max_size());
			}

			iterator begin()
			{
				rb_node< T > *begn = _root;
				if (begn)
				{
					while (begn->left)
						begn = begn->left;
				}
				return iterator(begn, _root);
			}

			const_iterator	begin() const
			{
				rb_node< T > *begn = _root;
				if (begn)
				{
					while (begn->left)
						begn = begn->left;
				}
				return const_iterator(begn, _root);
			}

			iterator end()
			{
				return iterator(NULL, _root);
			}

			const_iterator	end() const
			{
				return const_iterator(NULL, _root);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			ft::pair< iterator, bool > insert( const value_type& value )
			{
				ft::pair<rb_node< T > *, bool>	tmp = _insert_to_tree(&_root, value);
				return ft::make_pair(iterator(tmp.first, _root), tmp.second);
			}

			iterator insert( iterator hint, const value_type& value )
			{
				(void) hint;
				ft::pair<rb_node< T > *, bool>	tmp = _insert_to_tree(&_root, value);
				return iterator(tmp.first, _root);
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{
				for (InputIt it = first; it != last; ++it)
					insert(*it);
			}

			void erase( iterator pos )
			{
				_erase_node(pos.node);
			}

			void erase( iterator first, iterator last )
			{
				for (; first != last; )
					_erase_node((first++).node);
			}

			size_type erase( const value_type& key )
			{
				rb_node< T > *node = _find_node(key);
				if (node)
				{
					_erase_node(node);
					return (1);
				}
				return (0);
			}

			iterator find( const value_type& key )
			{
				return iterator(_find_node(key), _root);
			}

			const_iterator find( const value_type& key ) const
			{
				return const_iterator(_find_node(key), _root);
			}

			ft::pair<iterator,iterator> equal_range( const value_type& key )
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}

			ft::pair<const_iterator,const_iterator> equal_range( const value_type& key ) const
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}

			iterator lower_bound( const value_type& key )
			{
				rb_node< T > *curr = _root;
				rb_node< T > *res = NULL;

				while (curr)
				{
					if (_comp(key, curr->value))
					{
						res = curr;
						curr = curr->left;
					} 
					else if (not _comp(curr->value, key))
					{
						res = curr;
						curr = curr->left;
					}
					else
						curr = curr->right;
				}
				return iterator(res, _root);
			}

			const_iterator lower_bound( const value_type& key ) const
			{
				rb_node< T > *curr = _root;
				rb_node< T > *res = NULL;

				while (curr)
				{
					if (_comp(key, curr->value))
					{
						res = curr;
						curr = curr->left;
					} 
					else if (not _comp(curr->value, key))
					{
						res = curr;
						curr = curr->left;
					}
					else
						curr = curr->right;
				}
				return const_iterator(res, _root);
			}

			iterator upper_bound( const value_type& key )
			{
				rb_node< T > *curr = _root;
				rb_node< T > *res = NULL;

				while (curr)
				{
					if (_comp(key, curr->value))
					{
						res = curr;
						curr = curr->left;
					}
					else
						curr = curr->right;
				}
				return iterator(res, _root);
			}

			const_iterator upper_bound( const value_type& key ) const
			{
				rb_node< T > *curr = _root;
				rb_node< T > *res = NULL;

				while (curr)
				{
					if (_comp(key, curr->value))
					{
						res = curr;
						curr = curr->left;
					}
					else
						curr = curr->right;
				}
				return const_iterator(res, _root);
			}

			void	swap(rb_tree& other)
			{
				ft::swap(other._root, _root);
				ft::swap(other._size, _size);
			}

			void clear()
			{ 
				_clear_tree_recursive(_root);
				_root = NULL;
			}

		private:
			rb_node< T > *	_get_new_node(const T& value, rb_node< T > *parent = NULL, rb_node< T > *left = NULL,
				rb_node< T > *right = NULL, bool is_red = true)
			{
				rb_node< T >	* tmp = node_allocator_type().allocate(1);
				node_allocator_type().construct(tmp, rb_node< T >(value, left, right, parent, is_red));
				_size++;
				return tmp;
			}

			void _remove_node(rb_node< T >	*node)
			{
				node_allocator_type().destroy(node);
				node_allocator_type().deallocate(node, 1);
				_size--;
			}

			bool _is_red(rb_node< T > *node)
			{
				return node == NULL ? false : node->is_red;
			}

			rb_node< T > *	_find_node(const T & key) const
			{
				rb_node< T >	* tmp = _root;

				while (tmp != NULL)
				{
					if (_comp(key, tmp->value))
						tmp = tmp->left;
					else if (_comp(tmp->value, key))
						tmp = tmp->right;
					else
						return tmp;
				}
				return NULL;
			}

			ft::pair< rb_node< T >*, bool >	_insert_to_tree(rb_node< T > **tree, const T & key)
			{
				rb_node< T >	*parent = *tree == NULL ? NULL : (*tree)->parent;

				while (*tree != NULL)
				{
					if (_comp(key, (*tree)->value))
					{
						parent = *tree;
						tree = &((*tree)->left);
					}
					else if (_comp((*tree)->value, key))
					{
						parent = *tree;
						tree = &((*tree)->right);
					}
					else
						return ft::make_pair(*tree, false);
				}
				*tree = _get_new_node(key, parent);
				_fix_tree_after_insert(*tree);
				return ft::make_pair(*tree, true);
			}

			void _fix_tree_after_insert(rb_node< T > *node)
			{
				rb_node<T> *parent = node->parent;
				while (node != _root  && parent->is_red == true)
				{
					rb_node<T> *gparent = parent->parent;
					if (gparent->left == parent)
					{
						rb_node<T> *uncle = gparent->right;
						if (uncle != NULL && uncle->is_red == true)
						{
							parent->is_red = false;
							uncle->is_red = false;
							gparent->is_red = true;
							node = gparent;
							parent = node->parent;
						}
						else
						{
							if (parent->right == node)
							{
								_leftRotate(parent);
								std::swap(node, parent);
							}
							_rightRotate(gparent);
							gparent->is_red = true;
							parent->is_red = false;
							break;
						}
					}
					else
					{
						rb_node<T> *uncle = gparent->left;
						if (uncle != NULL && uncle->is_red == true)
						{
							gparent->is_red = true;
							parent->is_red = false;
							uncle->is_red = false;
							node = gparent;
							parent = node->parent;
						}
						else
						{
							if (parent->left == node)
							{
								_rightRotate(parent);
								std::swap(parent, node);
							}
							_leftRotate(gparent);
							parent->is_red = false;
							gparent->is_red = true;
							break;
						}
					}
				}
				_root->is_red = false;
			}

			void _copy_tree_recursive(rb_node< T > *&current, rb_node< T > *curr_parent, rb_node< T > *other_node)
			{
				if (other_node == NULL)
					return ;
				current = _get_new_node(other_node->value,
										curr_parent);
				_copy_tree_recursive(current->left, current, other_node->left);
				_copy_tree_recursive(current->right, current, other_node->right);
			}

			void _clear_tree_recursive(rb_node< T > *current)
			{
				if (current == NULL)
					return ;
				_clear_tree_recursive(current->left);
				_clear_tree_recursive(current->right);
				_remove_node(current);
			}

			void _leftRotate(rb_node< T > * node)
			{
				rb_node< T >	*tmp = node->right;

				node->right = tmp->left;
				if (tmp->left)
					tmp->left->parent = node;
				tmp->left = node;
				tmp->parent = node->parent;
				node->parent = tmp;
				if (tmp->parent)
				{
					if (tmp->parent->right == tmp->left)
						tmp->parent->right = tmp;
					else
						tmp->parent->left = tmp;
				}
				else
					_root = tmp;
			}

			void _rightRotate(rb_node< T > * node)
			{
				rb_node< T >	*tmp = node->left;

				node->left = tmp->right;
				if (tmp->right)
					tmp->right->parent = node;
				tmp->right = node;
				tmp->parent = node->parent;
				node->parent = tmp;
				if (tmp->parent)
				{
					if (tmp->parent->left == tmp->right)
						tmp->parent->left = tmp;
					else
						tmp->parent->right = tmp;
				}
				else
					_root = tmp;
			}

			void _erase_node(rb_node< T > *node)
			{
				rb_node< T >	*to_del = node;

				if (node->left and node->right)
				{
					to_del = node->right;
					while (to_del->left)
						to_del = to_del->left;
					_swap_nodes(node, to_del);
					_erase_node(node);
				}
				else if (node->left)
				{
					node->left->is_red = false;
					node->left->parent = node->parent;
					if (node->parent)
					{
						if (node->parent->left == node)
							node->parent->left = node->left;
						else
							node->parent->right = node->left;
					}
					else
						_root = node->left;
					_remove_node(to_del);
					return ;
				}
				else if (node->right)
				{
					node->right->is_red = false;
					node->right->parent = node->parent;
					if (node->parent)
					{
						if (node->parent->right == node)
							node->parent->right = node->right;
						else
							node->parent->left = node->right;
					}
					else
						_root = node->right;
					_remove_node(to_del);
					return ;
				}
				else
				{
					if (node->is_red)
					{
						rb_node< T >	**tmp;
						if (node->parent->right == node)
							tmp = &node->parent->right;
						else
							tmp = &node->parent->left;
						_remove_node(*tmp);
						*tmp = NULL;
					}
					else
					{
						rb_node< T >	**tmp;
						rb_node< T >    *parent = node->parent;
						if (node->parent)
						{
							if (node->parent->right == node)
								tmp = &node->parent->right;
							else
								tmp = &node->parent->left;
						}
						else
							tmp = &_root;
						_remove_node(*tmp);
						*tmp = NULL;
						_fix_tree_after_remove(tmp, parent);
					}
				}
			}

			void _swap_nodes(rb_node< T > *nd1, rb_node< T > *nd2)
			{
				ft::swap(nd1->is_red, nd2->is_red);
				if (nd1->left)
					nd1->left->parent = nd2;
				if (nd2->left)
					nd2->left->parent = nd1;
				ft::swap(nd1->left, nd2->left);

				if (nd1->right)
					nd1->right->parent = nd2;
				if (nd2->right)
					nd2->right->parent = nd1;
				ft::swap(nd1->right, nd2->right);

				if (nd1->parent)
				{
					if (nd1->parent->left == nd1)
						nd1->parent->left = nd2;
					else
						nd1->parent->right = nd2;
				}
				else
					_root = nd2;
				if (nd2->parent)
				{
					if (nd2->parent->left == nd2)
						nd2->parent->left = nd1;
					else
						nd2->parent->right = nd1;
				}
				else
					_root = nd1;
				ft::swap(nd1->parent, nd2->parent);
			}

			void _fix_tree_after_remove(rb_node< T > **removed, rb_node< T > *parent)
			{
				while (parent != NULL)
				{
					if (&parent->right == removed)
					{
						if (_is_red(parent))
						{
							if (_is_red(parent->left->right))
							{
								parent->is_red = false;
								_leftRotate(parent->left);
							}
							_rightRotate(parent);
							return ;
						}
						else
						{
							if (_is_red(parent->left))
							{
								if (_is_red(parent->left->right->left))
								{
									parent->left->right->left->is_red = false;
									_leftRotate(parent->left);
									_rightRotate(parent);
								}
								else if (_is_red(parent->left->right->right))
								{
									ft::swap(parent->left->right->is_red,
												parent->left->right->right->is_red);
									_leftRotate(parent->left->right);
									parent->left->right->left->is_red = false;
									_leftRotate(parent->left);
									_rightRotate(parent);
								}
								else
								{
									parent->left->is_red = false;
									parent->left->right->is_red = true;
									_rightRotate(parent);
								}
								return;
							}
							else
							{
								if (_is_red(parent->left->right))
								{
									parent->left->right->is_red = false;
									_leftRotate(parent->left);
									_rightRotate(parent);
									return ;
								}
								else if (_is_red(parent->left->left))
								{
									parent->left->left->is_red = false;
									_rightRotate(parent);
									return ;
								}
								parent->left->is_red = true;
								if (parent->parent)
								{
									if (parent->parent->left == parent)
										removed = &parent->parent->left;
									else
										removed = &parent->parent->right;
								}
								parent = parent->parent;
							}
						}
					}
					else
					{
						if (_is_red(parent))
						{
							if (_is_red(parent->right->left))
							{
								parent->is_red = false;
								_rightRotate(parent->right);
							}
							_leftRotate(parent);
							return ;
						}
						else
						{
							if (_is_red(parent->right))
							{
								if (_is_red(parent->right->left->right))
								{
									parent->right->left->right->is_red = false;
									_rightRotate(parent->right);
									_leftRotate(parent);
								}
								else if (_is_red(parent->right->left->left))
								{
									ft::swap(parent->right->left->is_red,
												parent->right->left->left->is_red);
									_rightRotate(parent->right->left);
									parent->right->left->right->is_red = false;
									_rightRotate(parent->right);
									_leftRotate(parent);
								}
								else
								{
									parent->right->is_red = false;
									parent->right->left->is_red = true;
									_leftRotate(parent);
								}
								return;
							}
							else
							{
								if (_is_red(parent->right->left))
								{
									parent->right->left->is_red = false;
									_rightRotate(parent->right);
									_leftRotate(parent);
									return ;
								}
								else if (_is_red(parent->right->right))
								{
									parent->right->right->is_red = false;
									_leftRotate(parent);
									return ;
								}
								parent->right->is_red = true;
								if (parent->parent)
								{
									if (parent->parent->right == parent)
										removed = &parent->parent->right;
									else
										removed = &parent->parent->left;
								}
								parent = parent->parent;
							}
						}
					}
				}
			}

		public:
			void print_details()
			{
				if (_root == NULL)
					std::cout << "empty rb_tree\n";
				else
					print_details(_root);
			}

			void print_details(rb_node<T>* node)const
			{
				if (node == NULL)
					return;
				std::cout << node->value << "(";
				if (node->is_red == 0)
					std::cout << "black";
				else
					std::cout << "red";
				if (node->parent == NULL)
					std::cout << ") is root" << std::endl;
				else if(node->parent->left==node)
					std::cout << ") is "<<node->parent->value<<"'s "<<"left child" << std::endl;
				else
					std::cout << ") is "<<node->parent->value<<"'s "<<"right child" << std::endl;
				print_details(node->left);
				print_details(node->right);
			}

			void print_tree()
			{
				if (_root == NULL)
					std::cout << "empty rb_tree";
				else
					print_tree(_root);
			}

			void print_tree(rb_node<T>* tree)const
			{
				if (tree != NULL)
				{
					std::cout << tree->value << " ";
					print_tree(tree->left);
					print_tree(tree->right);
				}
			}

			void print_in_order()
			{
				if (_root == NULL)
					std::cout << "empty rb_tree";
				else
					print_in_order(_root);
			}

			void print_in_order(rb_node<T>* tree) const
			{
				if (tree != NULL)
				{
					print_in_order(tree->left);
					std::cout << tree->value << " ";
					print_in_order(tree->right);
				}
			}

	};

	template <class T>
	class	rb_tree_Iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			rb_node< T >	*node;
			rb_node< T >	*root;

			rb_tree_Iterator(rb_node< T > * node, rb_node< T > *root) : node(node), root(root) {}

			rb_tree_Iterator() {}

			rb_tree_Iterator(const rb_tree_Iterator & other) : node(other.node), root(other.root) {}

			rb_tree_Iterator &	operator=(const rb_tree_Iterator & other)
			{
				node = other.node;
				return *this;
			}

			T &	operator*()
			{
				return node->value;
			}

			T *	operator->()
			{
				return &(node->value);
			}

			rb_tree_Iterator &	operator++()
			{
				if (node == NULL)
				{
					if (root == NULL)
						return *this;
					node = root;
					while (node->left)
						node = node->left;
					return *this;
				}
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				else
				{
					while (node->parent and node->parent->right == node)
						node = node->parent;
					node = node->parent;
				}
				return *this;
			}

			rb_tree_Iterator	operator++(int) 
			{
				rb_tree_Iterator tmp(*this);
				++(*this);
				return tmp;
			}

			rb_tree_Iterator &	operator--()
			{
				if (node == NULL)
				{
					if (root == NULL)
						return *this;
					node = root;
					while (node->right)
						node = node->right;
					return *this;
				}
				if (node->left)
				{
					node = node->left;
					while (node->right)
						node = node->right;
				}
				else
				{
					while (node->parent and node->parent->left == node)
						node = node->parent;
					node = node->parent;
				}
				return *this;
			}

			rb_tree_Iterator	operator--(int)
			{
				rb_tree_Iterator tmp(*this);
				--(*this);
				return tmp;
			}

			operator rb_tree_ConstIterator< T >() const
			{
				return rb_tree_ConstIterator< T >(node, root);
			}

			friend bool operator==(rb_tree_Iterator lhs, rb_tree_Iterator rhs)
			{
				return lhs.node == rhs.node;
			}

			friend bool operator!=(rb_tree_Iterator lhs, rb_tree_Iterator rhs)
			{
				return lhs.node != rhs.node;
			}
	};

	template <class T>
	class	rb_tree_ConstIterator :
			public ft::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
	{
		public:
			const rb_node< T >	*node;
			const rb_node< T >	*root;

			rb_tree_ConstIterator(rb_node< T > * node, rb_node< T > *root) : node(node), root(root) {}

			rb_tree_ConstIterator() {}

			rb_tree_ConstIterator(const rb_tree_ConstIterator & other) : node(other.node), root(other.root) {}

			rb_tree_ConstIterator &	operator=(const rb_tree_ConstIterator & other)
			{
				node = other.node;
				return *this;
			}

			const T & operator*() const
			{
				return node->value;
			}

			const T *	operator->() const
			{
				return &(node->value);
			}

			rb_tree_ConstIterator &	operator++()
			{
				if (node == NULL)
				{
					if (root == NULL)
						return *this;
					node = root;
					while (node->left)
						node = node->left;
					return *this;
				}
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				else
				{
					while (node->parent and node->parent->right == node)
						node = node->parent;
					node = node->parent;
				}
				return *this;
			}

			rb_tree_ConstIterator	operator++(int)
			{
				rb_tree_ConstIterator tmp(*this);
				++(*this);
				return tmp;
			}

			rb_tree_ConstIterator &	operator--()
			{
				if (node == NULL)
				{
					if (root == NULL)
						return *this;
					node = root;
					while (node->right)
						node = node->right;
					return *this;
				}
				if (node->left)
				{
					node = node->left;
					while (node->right)
						node = node->right;
				}
				else
				{
					while (node->parent and node->parent->left == node)
						node = node->parent;
					node = node->parent;
				}
				return *this;
			}

			rb_tree_ConstIterator operator--(int)
			{
				rb_tree_ConstIterator tmp(*this);
				--(*this);
				return tmp;
			}

			friend bool operator==(rb_tree_ConstIterator lhs, rb_tree_ConstIterator rhs)
			{
				return lhs.node == rhs.node;
			}

			friend bool operator!=(rb_tree_ConstIterator lhs, rb_tree_ConstIterator rhs)
			{
				return lhs.node != rhs.node;
			}
	};

} // namespace ft

#endif

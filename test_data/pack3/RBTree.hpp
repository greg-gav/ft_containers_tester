#ifndef RBTree_hpp
# define RBTree_hpp
# include <memory>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft {
	template<typename T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RBTree{
	public:
		typedef T													value_type;
		typedef Compare												value_compare;
		typedef Alloc												allocator_type;
		typedef typename Alloc::template rebind<Node<T> >::other	node_allocator;
		typedef	typename node_allocator::pointer					node_pointer;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef std::ptrdiff_t										difference_type;
		typedef std::size_t											size_type;
		typedef ft::TreeIter<T>										iterator;
		typedef ft::TreeIter<const T>								const_iterator;
		typedef	ft::reverse_iterator<iterator> 						reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
		
		/* Constructors */
		
		RBTree(const Compare& comp, const allocator_type& a = allocator_type())
		:_alloc(a),
		_node_alloc(node_allocator()),
		_compare(comp),
		_root(0),
		_size(0) {
			_init_buildin();
			_root = _head;
		}

		RBTree()
		:_alloc(allocator_type()),
		_node_alloc(node_allocator()),
		_compare(value_compare()),
		_root(0),
		_size(0) {
			_init_buildin();
			_root = _head;
		}

		RBTree(const RBTree& src)
		:_compare(src._compare),
		_root(NULL) {
			*this = src;
		}
		
		template<class InputIt>
		RBTree(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
		   const value_compare& comp, const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_node_alloc(node_allocator()),
		_compare(comp) {
			_init_buildin();
			_root = _head;
			for (; first != last; ++first)
				insert(*first);
		}
		
		~RBTree() {
			clear_node(_root);
			_alloc.destroy(_head->value);
			_alloc.deallocate(_head->value, 1);
			_node_alloc.deallocate(_nil, 1);
			_node_alloc.deallocate(_head, 1);
		}
		
		/* Assignment operator */
	
		RBTree& operator=(const RBTree& src) {
			if (this == &src)
				return *this;
			_node_alloc = src._node_alloc;
			_alloc = src._alloc;
			_compare = src._compare;
			if (_root == NULL)
				_init_buildin();
			else
				clear_node(_root);
			if (src._size == 0)
				_root = _head;
			else {
				_root = copy_node(src._root);
				copy_child(_root, src._root);
			}
			_size = src._size;
			return *this;
		}
		
		/* Iterators */
		
		iterator				end() 			{ return iterator(_head); }
		const_iterator			end() const 	{ return const_iterator(_head); }
		iterator				begin()			{ return iterator(_size == 0 ? _head : iterator(_tree_min(_root))); }
		const_iterator			begin() const	{ return const_iterator(_size == 0 ? _head : const_iterator(_tree_min(_root))); }
		reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }
		reverse_iterator		rend()			{ return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }
		
		

		pointer	create_value(const value_type &value) {
			pointer new_val = _alloc.allocate(1);
			_alloc.construct(new_val, value);
			return new_val;
		}
		
		node_pointer copy_node(node_pointer other) {
			node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Node<T>());
			new_node->color = other->color;
			new_node->is_nil = other->is_nil;
			if (other->value) {
				new_node->value = _alloc.allocate(1);
				_alloc.construct(new_node->value, *other->value);
			}
			return (new_node);
		}
	
		void	copy_child(node_pointer my_node, node_pointer other) {
			if (other->left->is_nil)
				my_node->left = _nil;
			else {
				my_node->left = copy_node(other->left);
				my_node->left->parent = my_node;
				copy_child(my_node->left, other->left);
			}
			if (other->right->is_nil)
				my_node->right = _nil;
			else if (other->right->right == NULL) {
				my_node->right = _head;
				_head->parent = my_node;
			} else {
				my_node->right = copy_node(other->right);
				my_node->right->parent = my_node;
				copy_child(my_node->right, other->right);
			}
		}

		node_pointer	search(const value_type &key, node_pointer node) const
		{
			if (!node || _is_nil(node))
				return NULL;
			if (_compare(key, *node->value))
				return search(key, node->left);
			if (_compare(*node->value, key))
				return search(key, node->right);
			return node;
		}

		iterator	find(const value_type& key) {
			node_pointer res = search(key, _root);
			return (res ? iterator(res) : end());
		}

		const_iterator	find(const value_type& key) const {
			node_pointer res = search(key, _root);
			return (res == NULL ? end() : const_iterator(res));
		}
		
		/* Insert */
		
		ft::pair<iterator, bool> insert(const value_type &key) {
			node_pointer find_val = search(key, _root);
			if (find_val)
				return ft::pair<iterator, bool>(iterator(find_val), false);
			node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Node<value_type>(create_value(key)));
			new_node->left = _nil;
			new_node->right = _nil;
			_insert(new_node);
			_insert_rebalance(new_node);
			ft::pair<iterator, bool> res(iterator(new_node), true);
			++_size;
			new_node = _tree_max(_root);
			new_node->right = _head;
			_head->parent = new_node;
			return res;
		}

		iterator insert(iterator position, const value_type& key) {
			(void)position;
			node_pointer new_node = search(key,_root);
			if (new_node)
				return iterator(new_node);
			new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Node<value_type>(create_value(key)));
			new_node->left = _nil;
			new_node->right = _nil;
			_insert(new_node);
			_insert_rebalance(new_node);
			++_size;
			node_pointer max_of_tree = _tree_max(_root);
			max_of_tree->right = _head;
			_head->parent = max_of_tree;
			return iterator(new_node);
		}
		
		template<class InputIt>
		void insert(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
		for (; first != last; ++first)
			insert(*first);
		}

		/* Erase */

		void erase(iterator pos) {
			node_pointer y = pos.node(), x, for_free = y;
			bool y_original_color = y->color;
			if (_is_nil(y->left)) {
				x = y->right;
				_transplant(y, y->right);
			}
			else if (_is_nil(y->right)) {
				x = y->left;
				_transplant(y, y->left);
			}
			else {
				node_pointer z = y;
				y = _tree_min(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent != z) {
					_transplant(y, y->right);
					y->right = z->right;
					z->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			free_node(for_free);
			if (y_original_color)
				erase_rebalanse(x);
			--_size;
			_nil->parent = NULL;
			if (_size == 0)
				_root = _head;
			else {
				if (_size != 1)
					x = _tree_max(_root);
				else
					x = _root;
				x->right = _head;
				_head->parent = x;
			}
		}

		size_type erase(const value_type& value) {
			node_pointer res = search(value, _root);
			if (res)
				erase(iterator(res));
			return (res != NULL);
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		void erase_rebalanse(node_pointer node) {
			node_pointer brother;
			while (node != _root && node->color == BLACK) {
				brother = node->Brother();
				if (node == node->parent->left) {
					if (brother->color == RED) {
						brother->color = BLACK;
						node->parent->color = RED;
						_rotate_left(node->parent);
						brother = node->parent->right;
					}
					if (brother->left->color == BLACK && brother->right->color == BLACK) {
						brother->color = RED;
						node = node->parent;
					} else {
						if (brother->right->color == BLACK) {
							brother->left->color = BLACK;
							brother->color = RED;
							_rotate_right(brother);
							brother = node->parent->right;
						}
						brother->color = node->parent->color;
						node->parent->color = BLACK;
						brother->right->color = BLACK;
						_rotate_left(node->parent);
						node = _root;
					}
				}
				else{
					if (brother->color == RED) {
						brother->color = BLACK;
						node->parent->color = RED;
						_rotate_right(node->parent);
						brother = node->parent->left;
					}
					if (brother->right->color == BLACK && brother->left->color == BLACK) {
						brother->color = RED;
						node = node->parent;
					} else {
						if (brother->left->color == BLACK) {
							brother->right->color = BLACK;
							brother->color = RED;
							_rotate_left(brother);
							brother = node->parent->left;
						}
						brother->color = node->parent->color;
						node->parent->color = BLACK;
						brother->left->color = BLACK;
						_rotate_right(node->parent);
						node = _root;
					}
				}
			}
		}
		
		size_type		size() const		{ return _size;				}
		size_type		max_size() const	{ return _alloc.max_size(); }
		bool			empty() const		{ return (_size == 0);		}
		value_compare	value_comp() const	{ return _compare;			}
		
		void clear() {
			clear_node(_root);
			_root = _head;
			_head->parent = NULL;
			_size = 0;
		}
		
		size_type count(const value_type& value) const {
			return (find(value) != end());
		}
		
		/* Bound operations */

		iterator lower_bound(const value_type& key) {
			node_pointer curr = _root, prev = NULL;
			
			while (!_is_nil(curr)) {
				prev = curr;
				if (_compare(*curr->value, key))
					curr = curr->right;
				else if (_compare(key, *curr->value))
					curr = curr->left;
				else
					break;
			}
			if (prev == NULL)
				return this->end();
			else if (_compare(*prev->value, key))
				return ++iterator(prev);
			else
				return iterator(prev);
		}
		
		const_iterator lower_bound(const value_type& key) const {
			node_pointer curr = _root, prev = NULL;
			
			while (!_is_nil(curr)) {
				prev = curr;
				if (_compare(*curr->value, key))
					curr = curr->right;
				else if (_compare(key, *curr->value))
					curr = curr->left;
				else
					break;
			}
			if (prev == NULL)
				return this->end();
			else if (_compare(*prev->value, key))
				return ++const_iterator(prev);
			else
				return const_iterator(prev);
		}

		iterator upper_bound(const value_type& key) {
			node_pointer curr = _root, prev = NULL;
			
			while (!_is_nil(curr)) {
				prev = curr;
				if (_compare(*curr->value, key))
					curr = curr->right;
				else if (_compare(key, *curr->value))
					curr = curr->left;
				else
					break;
			}
			if (prev == NULL)
				return end();
			else if (_compare(key, *prev->value))
				return iterator(prev);
			else
				return ++iterator(prev);
		}

		const_iterator upper_bound(const value_type& key) const {
			node_pointer curr = _root, prev = NULL;
			
			while (!_is_nil(curr)) {
				prev = curr;
				if (_compare(*curr->value, key))
					curr = curr->right;
				else if (_compare(key, *curr->value))
					curr = curr->left;
				else
					break;
			}
			if (prev == NULL)
				return end();
			else if (_compare(key, *prev->value))
				return const_iterator(prev);
			else
				return ++const_iterator(prev);
		}

		void swap(RBTree &other) {
			std::swap(_root, other._root);
			std::swap(_nil, other._nil);
			std::swap(_head, other._head);
			std::swap(_size, other._size);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_alloc, other._alloc);
			std::swap(_compare, other._compare);
		}

		ft::pair<iterator, iterator> equal_range(const value_type &value) {
			return (ft::make_pair(lower_bound(value), upper_bound(value)));
		}
		
		allocator_type get_allocator() const{
			return (_alloc);
		}
		
	private:
		allocator_type				_alloc;
		node_allocator				_node_alloc;
		value_compare 				_compare;
		node_pointer				_nil;
		node_pointer				_head;
		node_pointer				_root;
		size_type					_size;
		
		node_pointer	_tree_min(node_pointer n) const {
			if (n) {
				while (!_is_nil(n->left))
					n = n->left;
			}
			return n;
		}
		
		node_pointer	_tree_max(node_pointer n) const {
			if (n)
				while (!_is_nil(n->right))
					n = n->right;
			return n;
		}
			
		void 	_rotate_right(node_pointer y) {
			node_pointer x = y->left;
			y->left = x->right;
			if (x->right != _nil)
				x->right->parent = y;
			x->parent = y->parent;
			if (y->parent == NULL)
				_root = x;
			else if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
			x->right = y;
			y->parent = x;
		}
	
		void 	_rotate_left(node_pointer x) {
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		
		node_pointer _insert(node_pointer new_node) {
			if (_root == _head)
				_root = new_node;
			else
				_insert(_root, new_node);
			return (new_node);
		}

		node_pointer _insert(node_pointer root, node_pointer new_node) {
			if (_compare(*new_node->value, *root->value)) {
				if (!_is_nil(root->left))
					return _insert(root->left, new_node);
				root->left = new_node;
			} else {
				if (!_is_nil(root->right))
					return _insert(root->right, new_node);
				root->right = new_node;
			}
			new_node->parent = root;
			return new_node;
		}

		void _insert_rebalance(node_pointer node) {
			if (node != _root && node->parent != _root) {
				while (node != _root && node->parent->color == RED) {
					node_pointer uncle = node->Uncle();
					if (uncle->color == RED) {
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node->parent == node->parent->parent->left) {
							if (node == node->parent->right) {
								node = node->parent;
								_rotate_left(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_rotate_right(node->parent->parent);
						} else {
							if (node == node->parent->left) {
								node = node->parent;
								_rotate_right(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_rotate_left(node->parent->parent);
						}
					}
				}
			}
			_root->color = BLACK;
		}

		bool _is_nil(node_pointer node) const {
			return (node == _nil || node == _head);
		}

		void clear_node(node_pointer node) {
			if (node && !_is_nil(node)) {
				clear_node(node->right);
				clear_node(node->left);
				_alloc.destroy(node->value);
				_alloc.deallocate(node->value, 1);
				_node_alloc.deallocate(node, 1);
			}
		}
	
		void _init_buildin() {
			_nil = _node_alloc.allocate(1);
			_node_alloc.construct(_nil, Node<T>());
			_nil->color = BLACK;
			_nil->is_nil = true;
			_head = _node_alloc.allocate(1);
			_node_alloc.construct(_head, Node<T>());
			_head->value = _alloc.allocate(1);
			_alloc.construct(_head->value, T());
			_head->color = BLACK;
		}
		
		void _transplant(node_pointer pos, node_pointer node) {
			if (pos == _root)
				_root = node;
			else if (pos == pos->parent->left)
				pos->parent->left = node;
			else
				pos->parent->right = node;
			node->parent = pos->parent;
		}
			
		void free_node(node_pointer node) {
			_alloc.destroy(node->value);
			_alloc.deallocate(node->value, 1);
			_node_alloc.deallocate(node, 1);
		}

	};

	template<class Content, class Compare, class Alloc>
	bool operator<(const RBTree<Content, Compare, Alloc>& lhs,  const RBTree<Content, Compare, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Content, class Compare, class Alloc>
	bool operator>(const RBTree<Content, Compare, Alloc>& lhs,  const RBTree<Content, Compare, Alloc>& rhs) {
		return (lhs < rhs);
	}

	template<class Content, class Compare, class Alloc>
	bool operator==(const RBTree<Content, Compare, Alloc>& lhs, const RBTree<Content, Compare, Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Content, class Compare, class Alloc>
	void swap(const  RBTree<Content, Compare, Alloc>& lhs, const  RBTree<Content, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif /* RBTree_h */

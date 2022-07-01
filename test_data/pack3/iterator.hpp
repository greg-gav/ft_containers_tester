#ifndef iterator_hpp
# define iterator_hpp
# include "utils.hpp"
# define RED false
# define BLACK true


namespace ft
{

/* iterator template */

	template<typename C,
			 typename T,
			 typename Dist = ptrdiff_t,
			 typename Pt = T*,
			 typename Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

/* iterator traits */

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};


	template <typename T>
	class Iterator : public iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef T																iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef	typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef std::size_t														size_type;
		
		Iterator()
		:_ptr(NULL) {}
		
		Iterator(pointer const ptr)
		:_ptr(ptr) {}
		
		template <typename _T>
		Iterator(const Iterator<_T>& x)
		:_ptr(x.getPtr()) {}
		
		Iterator&				operator=	(const Iterator& x)					{ _ptr = x._ptr; return *this;					}
		Iterator&				operator=	(Iterator<remove_const<T> >& x)		{ _ptr = x._ptr; return *this;					}
		Iterator&				operator+=	(int n)								{ _ptr += n; return *this;						}
		Iterator&				operator-=	(int n)								{ _ptr -= n; return *this;						}
		Iterator&				operator++	()									{ _ptr++; return (*this);						}
		Iterator&				operator--	()									{ _ptr--; return (*this);						}
		Iterator				operator++	(int)								{ Iterator<T> x(*this); _ptr++; return x;		}
		Iterator				operator--	(int)								{ Iterator<T> x(*this); _ptr--; return x;		}
		Iterator				operator+	(int n) const						{ return (_ptr + n); 							}
		Iterator				operator-	(int n) const						{ return (_ptr - n); 							}
		difference_type			operator-	(const Iterator& x) const			{ return (_ptr - x._ptr);						}
		reference				operator[]	(size_type n) const					{ return *(_ptr + n); 							}
		reference				operator*	() const							{ return *_ptr; 								}
		pointer					operator->	() const							{ return _ptr; 									}
		pointer					getPtr() const									{ return _ptr;									}
	private:
		pointer					_ptr;
	};

	template<typename T>				bool	operator==	(const Iterator<T>& x, const Iterator<T>& y) 	{ return (x.getPtr() == y.getPtr()); 	}
	template<typename T>				bool	operator!=	(const Iterator<T>& x, const Iterator<T>& y)	{ return (x.getPtr() != y.getPtr()); 	}
	template<typename T>				bool	operator<	(const Iterator<T>& x, const Iterator<T>& y)	{ return (x.getPtr() < y.getPtr()); 	}
	template<typename T>				bool	operator>	(const Iterator<T>& x, const Iterator<T>& y)	{ return (x.getPtr() > y.getPtr()); 	}
	template<typename T>				bool	operator<=	(const Iterator<T>& x, const Iterator<T>& y)	{ return (x.getPtr() <= y.getPtr()); 	}
	template<typename T>				bool	operator>=	(const Iterator<T>& x, const Iterator<T>& y)	{ return (x.getPtr() >= y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator==	(const Iterator<T1>& x, const Iterator<T2>& y) 	{ return (x.getPtr() == y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator!=	(const Iterator<T1>& x, const Iterator<T2>& y)	{ return (x.getPtr() != y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator<	(const Iterator<T1>& x, const Iterator<T2>& y)	{ return (x.getPtr() < y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator>	(const Iterator<T1>& x, const Iterator<T2>& y)	{ return (x.getPtr() > y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator<=	(const Iterator<T1>& x, const Iterator<T2>& y)	{ return (x.getPtr() <= y.getPtr()); 	}
	template<typename T1, typename T2>	bool	operator>=	(const Iterator<T1>& x, const Iterator<T2>& y)	{ return (x.getPtr() >= y.getPtr()); 	}


	template<typename Iter>
	class reverse_iterator
	: public iterator<typename iterator_traits<Iter>::iterator_category,
					  typename iterator_traits<Iter>::value_type,
					  typename iterator_traits<Iter>::difference_type,
					  typename iterator_traits<Iter>::pointer,
					  typename iterator_traits<Iter>::reference>
	{

	public:
		/* member types */
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		
		reverse_iterator()
		:current() {}
		
		explicit reverse_iterator(iterator_type x)
		:current(x) {}
		
		reverse_iterator(const reverse_iterator& x)
		:current(x.current) {}
		
		template <class U>
		reverse_iterator(const reverse_iterator<U>& other)
		:current(other.current) {}


		iterator_type			base		(void) const				{ return (current); }
		
		reference				operator*	(void) const 				{ Iter tmp(current); return *(--tmp); }
		pointer					operator->	(void) const 				{ return &(operator*()); }
		reverse_iterator&		operator++	(void) 						{ --current; return *this; }
		reverse_iterator&		operator--	(void)						{ ++current; return *this; }
		reverse_iterator		operator++	(int) 						{ reverse_iterator tmp(*this); --current; return tmp; }
		reverse_iterator		operator--	(int)						{ reverse_iterator tmp(*this); ++current; return tmp; }
		reverse_iterator		operator+	(difference_type n) const	{ return reverse_iterator(current - n); }
		reverse_iterator		operator-	(difference_type n) const	{ return reverse_iterator(current + n); }
		reverse_iterator&		operator+=	(difference_type n)			{ current -= n;	return *this; }
		reverse_iterator&		operator-=	(difference_type n)			{ current += n; return *this; }
		reference				operator[]	(difference_type n) const	{ return *(*this + n); }
	protected:
		Iter					current;
	};

	template<typename It>
	inline bool	operator==	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return (x.base() == y.base()); }
	template<typename It>
	inline bool operator<	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return (y.base() < x.base()); }
	template<typename It>
	inline bool	operator!=	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return !(x == y); }
	template<typename It>
	inline bool	operator>	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return (y < x); }
	template<typename It>
	inline bool	operator<=	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return !(y < x); }
	template<typename It>
	inline bool	operator>=	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)		{ return !(x < y); }

	template<typename ItL, typename ItR>
	inline bool	operator==	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return (x.base() == y.base()); }
	template<typename ItL, typename ItR>
	inline bool	operator<	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return (y.base() < x.base()); }
	template<typename ItL, typename ItR>
	inline bool	operator!=	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return !(x == y); }
	template<typename ItL, typename ItR>
	inline bool	operator>	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return (y < x); }
	template<typename ItL, typename ItR>
	inline bool	operator<=	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return !(y < x); }
	template<typename ItL, typename ItR>
	inline bool	operator>=	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y)	{ return !(x < y); }
	template<typename It>
	inline typename reverse_iterator<It>::difference_type
	operator-	(const reverse_iterator<It>& x, const reverse_iterator<It>& y)	{ return (y.base() - x.base()); }
	template<typename ItL, typename ItR>
	inline typename reverse_iterator<ItL>::difference_type
	operator-	(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) { return (y.base() - x.base()); }

	template<typename It>
	inline reverse_iterator<It>
	operator+	(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& x)
	{
		return (reverse_iterator<It>(x.base() - n));
	}



	/* tree */

	template<class T>
	struct Node {
		typedef T				value_type;
		typedef T*				pointer;
	public:
		explicit Node(T* value = 0)
		:value(value),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(RED),
		is_nil(false) {}

		Node(const Node& other)
		:value(other.value),
		parent(other.parent),
		left(other.left),
		right(other.right),
		color(other.color),
		is_nil(other.is_nil) {}

		Node& operator=(const Node& other){
			color = other.color;
			value = other.value;
			is_nil = other.is_nil;
			parent = other.parent;
			right = other.right;
			left = other.left;
			return *this;
		}
		
		inline Node* Parent() {
			return parent;
		}
		
		inline Node* Parent(const Node* node) {
			return (parent = node);
		}
		
		inline Node* Grandparent() {
			if (parent == NULL)
				return NULL;
			return parent->parent;
		}
		
		inline Node* Grandparent(const Node* node) {
			if (parent == NULL)
				return NULL;
			return (parent->parent = node);
		}
		
		inline Node* Uncle() {
			if (parent == NULL || parent->parent == NULL)
				return NULL;
			if (parent->parent->left == parent)
				return parent->parent->right;
			else
				return parent->parent->left;
		}
		
		inline Node* Uncle(const Node* node) {
			if (parent == NULL || parent->parent == NULL)
				return NULL;
			if (parent->parent->left == parent)
				return (parent->parent->right = node);
			else
				return (parent->parent->left = node);
		}
		
		inline Node* Brother() {
			if (parent == NULL)
				return NULL;
			if (this == parent->left)
				return parent->right;
			else
				return parent->left;
		}
		
		virtual ~Node(){}
		
		pointer	value;
		Node*	parent;
		Node*	left;
		Node*	right;
		bool	color;
		bool	is_nil;
	};

	template<typename T>
	class TreeIter {
	public:
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef Node<typename ft::remove_const<value_type>::type>*	node_pointer;

	private:
		node_pointer _node;

		node_pointer tree_min(node_pointer n) const {
			while(n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_pointer tree_max(node_pointer n) const {
			while (!n->right->is_nil)
				n = n->right;
			return n;
		}

	public:
		TreeIter() {}

		TreeIter(void *node): _node(static_cast<node_pointer>(node)) {}

		TreeIter(const TreeIter<typename ft::remove_const<value_type>::type > & other)
		{
			*this = other;
		}

		TreeIter& operator=(const TreeIter<typename ft::remove_const<value_type>::type>& other) {
			this->_node = other.node();
			return *this;
		}

		reference	operator*() const { return *(_node->value); }
		pointer		operator->() const { return _node->value; }

		TreeIter& operator++() {
			if (_node->right && !_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		TreeIter operator++(int) {
			TreeIter<value_type> temp = *this;
			if (!_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return temp;
		}

		TreeIter& operator--() {
			if (_node->left && !_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		TreeIter operator--(int) {
			TreeIter<value_type> temp = *this;
			if (_node->left && !_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return temp;
		}

		node_pointer node() const {
			return _node;
		}
	};

	template<typename A, typename B>
	bool operator==(const TreeIter<A> & lhs, const TreeIter<B> & rhs) {
			return (lhs.node() == rhs.node());
	}

	template<typename A, typename B>
	bool operator!=(const TreeIter<A> & lhs, const TreeIter<B> & rhs) {
			return (lhs.node() != rhs.node());
	}
}
#endif

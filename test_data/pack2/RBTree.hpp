#ifndef RBTREE_HPP
# define RBTREE_HPP

# define RED false
# define BLACK true

# include <memory>
# include <stddef.h>
# include "ft_utilities.hpp"

# include <string>
# include <iostream>


namespace ft {

template<class T>
class RBTreeNode;

template<typename> struct is_rbtree_node : ft::false_type {};
template<class T> struct is_rbtree_node<RBTreeNode<T> > : ft::true_type {};

template<class T>
class RBTreeNode {
    /*
    ** Member types
    */
    public:
        typedef T                                       value_type;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef T*                                      pointer;

    /*
    ** Public fields
    */
    public:
        bool                                            is_nil;
        bool                                            color;
        pointer                                         value;
        RBTreeNode*                                     left;
        RBTreeNode*                                     right;
        RBTreeNode*                                     p;
        
        RBTreeNode()
            : is_nil(false), color(is_nil), value(NULL), left(NULL), right(NULL), p(NULL) {}

        explicit RBTreeNode(pointer value) : is_nil(false), color(RED), value(value), left(NULL), right(NULL), p(NULL) {}

        ~RBTreeNode() {}

        RBTreeNode(const RBTreeNode& other)
            : is_nil(other.is_nil), color(other.color), value(other.value), left(other.left), right(other.right), p(other.p) {}

        RBTreeNode&     operator=(const RBTreeNode& other) {
            if (this != &other) {
                is_nil = other.is_nil;
                color = other.color;
                value = other.value;
                left = other.left;
                right = other.right;
                p = other.p;
            }
            return (*this);
        }
    
    /*
    ** Helper functions
    */
    public:
        static RBTreeNode*     tree_min(RBTreeNode* head) {
            if (!head->is_nil) {
                while (!head->left->is_nil) {
                    head = head->left;
                }
            }
            return (head);
        }

        static RBTreeNode*     tree_max(RBTreeNode* head) {
            if (!head->is_nil) {
                while (!head->right->is_nil) {
                    head = head->right;
                }
            }
            return (head);
        }

        bool    is_left_son() const {
            return (this == this->p->left);
        }
        
        bool    is_right_son() const {
            return (this == this->p->right);
        }

    /*
    ** Member functions
    */
    public:
        const RBTreeNode*     successor() const {
            // if there is right subtree
            if (!right->is_nil) {
                return (tree_min(right));
            }
            if (this->is_left_son()) {
                return (this->p);
            }

            const RBTreeNode*     tmp = this;
            const RBTreeNode*     y = tmp->p;
            while (!y->is_nil && tmp == y->right) {
                tmp = y;
                y = y->p;
            }
            return (y);
        }
        
        RBTreeNode*     successor() {
            // if there is right subtree
            if (!right->is_nil) {
                return (tree_min(right));
            }
            if (this->is_left_son()) {
                return (this->p);
            }

            RBTreeNode*     tmp = this;
            RBTreeNode*     y = tmp->p;
            while (!y->is_nil && tmp == y->right) {
                tmp = y;
                y = y->p;
            }
            return (y);
        }

        const RBTreeNode*     predecessor() const {
            // if there is left subtree
            if (!left->is_nil) {
                return (tree_max(left));
            }
            if (this->is_right_son()) {
                return (this->p);
            }

            const RBTreeNode*     tmp = this;
            const RBTreeNode*     y = tmp->p;
            while (!y->is_nil && tmp == y->left) {
                tmp = y;
                y = y->p;
            }
            return (y);
        }
        
        RBTreeNode*     predecessor() {
            // if there is left subtree
            if (!left->is_nil) {
                return (tree_max(left));
            }
            if (this->is_right_son()) {
                return (this->p);
            }

            RBTreeNode*     tmp = this;
            RBTreeNode*     y = tmp->p;
            while (!y->is_nil && tmp == y->left) {
                tmp = y;
                y = y->p;
            }
            return (y);
        }

        template<class Type>
        friend std::ostream	&operator << (std::ostream &o, RBTreeNode<Type> const &obj);
};

template<class Type>
std::ostream	&operator << (std::ostream &o, RBTreeNode<Type> const &obj) {
    if (obj.color == RED) {
        o << "\e[0;31m";
    }

    o << "Node(";

    if (obj.is_nil) {
        o << "NIL)";
    }
    else {
        o << *(obj.value) << ")";
    }
    o << "\e[0m";
    return (o);
}

template <class T, bool is_const>
class RBTreeIterator {
    /*
    ** Member types
    */
    public:
        typedef RBTreeNode<T>                                            node_type;
        typedef typename std::bidirectional_iterator_tag                 iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type             value_type;
        typedef typename ft::iterator_traits<T*>::difference_type        difference_type;
        typedef typename choose<
            is_const,
            typename ft::iterator_traits<const T*>::pointer,
            typename ft::iterator_traits<T*>::pointer
        >::type                                                             pointer;
        typedef typename choose<
            is_const,
            typename ft::iterator_traits<const T*>::reference,
            typename ft::iterator_traits<T*>::reference
        >::type                                                             reference;
        typedef RBTreeNode<typename ft::non_const<value_type>::type>*       node_pointer;
        
    /*
    ** Member fields
    */
    protected:
        node_pointer      _p;

    /*
    ** Member functions
    */
    public:
        // Constructors
        RBTreeIterator() : _p(NULL) {}
        RBTreeIterator(node_pointer p) : _p(p) {}
        RBTreeIterator(const RBTreeIterator<T, false>& other) : _p( other.getNodePtr() ) {}

        // Destructor
        virtual ~RBTreeIterator() {}

        // Operators
        RBTreeIterator&     operator=(const RBTreeIterator& other) {
            if (this != &other) {
                this->_p = other._p;
            }
            return (*this);
        }

        // Access operators
        reference           operator*() const { return (*(_p->value)); }
        pointer             operator->() const { return (_p->value); }

        // Increment/Decrement
        RBTreeIterator&     operator++() {
            _p = _p->successor();
            return (*this);
        }

        RBTreeIterator      operator++(int) {
            RBTreeIterator  tmp(*this);
            _p = _p->successor();
            return (tmp);
        }
       
        RBTreeIterator&     operator--() {
            _p = _p->predecessor();
            return (*this);
        }

        RBTreeIterator      operator--(int) {
            RBTreeIterator  tmp(*this);
            _p = _p->predecessor();
            return (tmp);
        }

        node_pointer        getNodePtr() const {
            return (_p);
        }

        
        // Comparison operators 
        friend bool    operator==(const RBTreeIterator& lhs,
                                  const RBTreeIterator& rhs) {
            return (lhs._p == rhs._p);
        }

        friend bool    operator!=(const RBTreeIterator& lhs,
                                  const RBTreeIterator& rhs) {
            return (lhs._p != rhs._p);
        }
};

template <
    class Key,
    class Allocator = std::allocator<Key>,
    class Compare = std::less<Key>
> class RBTree {
    /*
    ** Member types
    */
    public:
        typedef Key                                     value_type;
        typedef Allocator                               allocator_type;
        typedef Compare                                 comparator_type;
        typedef RBTreeNode<value_type>                  node_type;
        typedef typename allocator_type::
            template rebind<node_type>::other           node_allocator_type;
        typedef typename node_allocator_type::pointer   node_pointer;
        typedef std::size_t                             size_type;
        typedef std::ptrdiff_t                          difference_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef typename allocator_type::pointer        pointer;
        typedef typename allocator_type::const_pointer  const_pointer;
        typedef ft::RBTreeIterator<value_type, false>   iterator;
        typedef ft::RBTreeIterator<value_type, true>    const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    private:
        node_pointer                    _nil;
        node_pointer                    _root;
        size_type                       _size;
        allocator_type                  _value_allocator;
        node_allocator_type             _node_allocator;
        comparator_type                 _comparator;

    /*
    ** Member functions
    */
    public:
        // Constructors
        RBTree(
            const allocator_type& key_alloc = allocator_type(),
            const comparator_type& compar = comparator_type()
        ) : _size(0), _value_allocator(key_alloc), _node_allocator(node_allocator_type()), _comparator(compar) {
            _nil = _new_nil();
            _root = _nil;
        }
        RBTree(const RBTree& other)
            : _size(0), _value_allocator(other._value_allocator),
              _node_allocator(other._node_allocator), _comparator(other._comparator) {
            _nil = _new_nil();
            _root = _nil;
            for (const_iterator it = other.begin(); it != other.end(); it++) {
                insert(*it);
            }
            _nil->left = _max(_root);
            _nil->right = _min(_root);
        }
        // Destructor
        ~RBTree() {
            _destroyTree(this->_root);
            _destroyNil();
        }

        // Operators
        RBTree&     operator=(const RBTree& other) {
            if (this != &other) {
                _destroyTree(this->_root);
                this->_root = this->_nil;
                this->_size = 0;
                this->_value_allocator = other._value_allocator;
                this->_node_allocator = other._node_allocator;
                this->_comparator = other._comparator;
                for (const_iterator it = other.begin(); it != other.end(); it++) {
                    insert(*it);
                }
                this->_nil->left = _max(_root);
                this->_nil->right = _min(_root);
            }
            return (*this);
        }

        iterator  insert(const_reference val) {
            node_pointer  node;
            pointer  val_copy = _value(val);
            node = _node_allocator.allocate(1);
            _node_allocator.construct(node, node_type(val_copy));
            _insertNode(node);
            _size++;
            return (iterator(node));
        }

        iterator    search(const_reference val) const { return (_searchValue(this->_root, val)); }

        bool        remove(const_reference val) {
            node_pointer    to_delete = _iterativeSearch(this->_root, val);
            return (_deleteNode(to_delete));
        }

        void        remove(iterator pos) {
            node_pointer    to_delete = pos.getNodePtr();
            _deleteNode(to_delete);
        }

        void        remove(const_iterator pos) {
            node_pointer    to_delete = pos.getNodePtr();
            _deleteNode(to_delete);
        }

        void        remove(iterator first, iterator last) {
            node_pointer    current = first.getNodePtr();
            node_pointer    finish = (--last).getNodePtr();

            while (current != finish) {
                node_pointer    next = current->successor();
                _deleteNode(current);
                current = next;
            }
            _deleteNode(finish);
        }

        void        remove(const_iterator first, const_iterator last) {
            node_pointer    current = first.getNodePtr();
            node_pointer    finish = (--last).getNodePtr();

            while (current != finish) {
                node_pointer    next = current->successor();
                _deleteNode(current);
                current = next;
            }
            _deleteNode(finish);
        }

        void        clear() {
            _destroyTree(this->_root);
            this->_root = this->_nil;
            this->_nil->left = NULL;
            this->_nil->right = NULL;
            this->_size = 0;
        }
        
        iterator            end() {
            return (iterator(_nil));
        }

        const_iterator      end() const {
            return (const_iterator(_nil));
        }

        iterator            begin() {
            if (_size == 0) {
                return (iterator(_nil)); 
            }
            return(iterator(_nil->right));
        }

        const_iterator           begin() const {
            if (_size == 0) {
                return (const_iterator(_nil)); 
            }
            return(const_iterator(_nil->right));
        }

        reverse_iterator        rbegin() {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator  rbegin() const {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator        rend() {
            return (reverse_iterator(begin()));
        }	

        const_reverse_iterator  rend() const {
            return (const_reverse_iterator(begin()));
        }

        /*
        ** Comparision operators (non-member)
        */
        template<class value, class comparator, class allocator>
        friend bool operator==(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );
        
        template<class value, class comparator, class allocator>
        friend bool operator!=(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );
        
        template<class value, class comparator, class allocator>
        friend bool operator<(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );

        template<class value, class comparator, class allocator>
        friend bool operator<=(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );
        
        template<class value, class comparator, class allocator>
        friend bool operator>(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );

        template<class value, class comparator, class allocator>
        friend bool operator>=(
            const RBTree<value,comparator,allocator>& lhs,
            const RBTree<value,comparator,allocator>& rhs
        );

        size_type   size() const {
            return (_size);
        }

        void        swap(RBTree& other) {
            std::swap(_nil, other._nil);
            std::swap(_root, other._root);
            std::swap(_size, other._size);
            std::swap(_value_allocator, other._value_allocator);
            std::swap(_node_allocator, other._node_allocator);
            std::swap(_comparator, other._comparator);
        }

    /*
    ** Helper functions
    */
    private:
        node_pointer    _new_nil() {
            node_pointer nil = _node_allocator.allocate(1);
            _node_allocator.construct(nil, node_type());
            nil->is_nil = true;
            nil->color = BLACK;
            return (nil);
        }

        void            _destroyNil() {
            _node_allocator.destroy(this->_nil);
            _node_allocator.deallocate(this->_nil, 1);
        }
   
        void    _destroyTree(node_pointer head) {
            if (head->is_nil) {
                return ;
            }
            _destroyTree(head->left);
            _destroyTree(head->right);
            _value_allocator.destroy(head->value);
            _value_allocator.deallocate(head->value, 1);
            _node_allocator.destroy(head);
            _node_allocator.deallocate(head, 1);
        }

        iterator    _searchValue(node_pointer head, const_reference val) const {
            return (iterator(_iterativeSearch(head, val)));
        }

        node_pointer    _iterativeSearch(node_pointer head, const_reference val) const {
            while (!head->is_nil) {
                if (!(_comparator(val, *(head->value))) && !_comparator(*(head->value), val)) {
                    break ;
                }
                if (_comparator(val, *(head->value))) {
                    head = head->left;
                } else {
                    head = head->right;
                }
            }
            return (head);
        }

        void    _transplant(node_pointer u, node_pointer v) {
            if (u->p->is_nil) {
                this->_root = v;
            } else if (u == u->p->left) {
                u->p->left = v;
            } else {
                u->p->right = v;
            }
            v->p = u->p;
        }

        void    _leftRotate(node_pointer node) {
			node_pointer y = node->right;
			node->right = y->left;

			if (!y->left->is_nil)
				y->left->p = node;

			y->p = node->p;

			if (node->p->is_nil)
				this->_root = y;
			else if (node == node->p->left)
				node->p->left = y;
			else
				node->p->right = y;
			y->left = node;
			node->p = y;
		}

        void    _rightRotate(node_pointer node) {
			node_pointer y;

			y = node->left;
			node->left = y->right;
			if (!y->right->is_nil)
				y->right->p = node;
			y->p = node->p;
			if (node->p->is_nil)
				this->_root = y;
			else if (node == node->p->left)
				node->p->left = y;
			else
				node->p->right = y;
			y->right = node;
			node->p = y;
		}
        
        void    _insertFixup(node_pointer z) {
            while (z->p->color == RED) {
                if (z->p == z->p->p->left) {
                    node_pointer   uncle = z->p->p->right;
                    if (uncle->color == RED) {
                        z->p->color = BLACK;
                        uncle->color = BLACK;
                        z->p->p->color = RED;
                        z = z->p->p;
                    } else {
                        if (z == z->p->right) {
                            z = z->p;
                            _leftRotate(z);
                        }
                        z->p->color = BLACK;
                        z->p->p->color = RED;
                        _rightRotate(z->p->p);
                    }
                } else {
                    node_pointer   uncle = z->p->p->left;
                    if (uncle->color == RED) {
                        z->p->color = BLACK;
                        uncle->color = BLACK;
                        z->p->p->color = RED;
                        z = z->p->p;
                    } else {
                        if (z == z->p->left) {
                            z = z->p;
                            _rightRotate(z);
                        }
                        z->p->color = BLACK;
                        z->p->p->color = RED;
                        _leftRotate(z->p->p);
                    }
                }
            }
            this->_root->color = BLACK;
        }

        void    _insertNode(node_pointer to_insert) {
            node_pointer   previous = this->_nil;
            node_pointer   current = this->_root;

            while (!current->is_nil) {
                previous = current;
                if (_comparator(*(to_insert->value), *(current->value))) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            
            to_insert->p = previous;

            if (previous->is_nil) {
                this->_root = to_insert;
            } else if (_comparator(*(to_insert->value), *(previous->value))) {
                previous->left = to_insert;
            } else {
                previous->right = to_insert;
            }
            to_insert->left = this->_nil;
            to_insert->right = this->_nil;
            to_insert->color = RED;

            if (_size == 0) {
                this->_nil->right = to_insert;  // min element
                this->_nil->left = to_insert;  // max element
            } else {
                // if greater then maximum element
                if (to_insert == _nil->left->right) {
                    this->_nil->left = to_insert;
                } else if (to_insert == _nil->right->left) {
                    this->_nil->right = to_insert;
                }
            }

            _insertFixup(to_insert);
        }

        pointer   _value(const_reference val) {
            pointer     created = _value_allocator.allocate(1);
            try {
                _value_allocator.construct(created, val);
            } catch (...) {
                _value_allocator.deallocate(created, 1);
                throw ;
            }
            return (created);
        }


        node_pointer   _min(node_pointer head) const {
            return (node_type::tree_min(head));
        }

        node_pointer   _max(node_pointer head) const {
            return (node_type::tree_max(head));
        }

        bool    _deleteNode(node_pointer to_delete) {
            if (!to_delete->is_nil) {
                if (to_delete == _nil->right) {
                    _nil->right = _nil->right->successor();
                } else if (to_delete == _nil->left) {
                    _nil->left = _nil->left->predecessor();
                }
                _removeNode(to_delete);
                _value_allocator.destroy(to_delete->value);
                _value_allocator.deallocate(to_delete->value, 1);
                _node_allocator.destroy(to_delete);
                _node_allocator.deallocate(to_delete, 1);
                _size--;
                return (true);
            }
            return (false);
        }

        void    _removeNode(node_pointer to_delete) {
            node_pointer   x;
            node_pointer   y = to_delete;
            bool    y_original_color = y->color;

            if (to_delete->left->is_nil) {
                x = to_delete->right;
                _transplant(to_delete, x);
            } else if (to_delete->right->is_nil) {
                x = to_delete->left;
                _transplant(to_delete, x);
            } else {
                y = _min(to_delete->right);
                y_original_color = y->color;
                x = y->right;
                if (y->p == to_delete) {
                    x->p = y;
                } else {
                    _transplant(y, y->right);
                    y->right = to_delete->right;
                    y->right->p = y;
                }
                _transplant(to_delete, y);
                y->left = to_delete->left;
                y->left->p = y;
                y->color = to_delete->color;
            }

            if (y_original_color == BLACK) {
                _deleteFixup(x);
            }
            // If the removed element is the last
            if (_size == 1) {
                this->_root = this->_nil;
            }
        }

        void    _deleteFixup(node_pointer x) {
            while (x != this->_root && x->color == BLACK) {
                if (x == x->p->left) {
                    node_pointer   w = x->p->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color = RED;
                        _leftRotate(x->p);
                        w = x->p->right;
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            _rightRotate(w);
                            w = x->p->right;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        w->right->color = BLACK;
                        _leftRotate(x->p);
                        x = this->_root;
                    }
                } else {
                    node_pointer   w = x->p->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color = RED;
                        _rightRotate(x->p);
                        w = x->p->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            _leftRotate(w);
                            w = x->p->left;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        w->left->color = BLACK;
                        _rightRotate(x->p);
                        x = this->_root;
                    }
                }
            }
            x->color = BLACK;
        }
        
};


template<class value, class comparator, class allocator>
bool operator<(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class value, class comparator, class allocator>
bool operator>(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    return (rhs < lhs);
}

template<class value, class comparator, class allocator>
bool operator==(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    if (lhs.size() == rhs.size()) {
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    return (false);
}

template<class value, class comparator, class allocator>
bool operator!=(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    return (!(lhs == rhs));
}

template<class value, class comparator, class allocator>
bool operator<=(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    return (!(rhs < lhs));
}


template<class value, class comparator, class allocator>
bool operator>=(
    const RBTree<value,comparator,allocator>& lhs,
    const RBTree<value,comparator,allocator>& rhs
) {
    return (!(lhs < rhs));
}

}  // Namespace brace

#endif
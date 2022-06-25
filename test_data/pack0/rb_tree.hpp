#ifndef _RB_TREE_
#define _RB_TREE_

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"

typedef enum { BLACK, RED } nodeColor;
#define NIL sentinel
#define END f_end

namespace ft
{
	/* node class */
    template <class T>
    struct Node
    {
        Node*			left;
		Node*				right;
		Node*				parent;
        nodeColor		color;
        T				data;

		Node(const T& value) : left(), right(), parent(), color(BLACK), data(value) {}
		~Node() {}
    };
    
	/* iterator class */
	template <class Node, class Tree, class T>
	class tree_iterator {
	public:
		typedef T										value_type;
		typedef Node									node_pointer;
		typedef Tree&									tree_ref;
        typedef std::ptrdiff_t 							difference_type;
		typedef value_type*							 	pointer;
        typedef value_type&							 	reference;
        typedef typename std::bidirectional_iterator_tag iterator_category;
	
	protected:
		node_pointer		node;
		tree_ref			rbt;
		node_pointer		root;
		node_pointer		nil;
		node_pointer		end;
	
	public:
		tree_iterator() { }
		~tree_iterator() { }

		explicit tree_iterator(node_pointer node, tree_ref tree)
		 : node(node), rbt(tree) { 
			 root = rbt.get_root();
			 nil = rbt.get_nil();
			 end = rbt.get_end();
		 }

		template <class OtherNode, class OtherTree, class OtherT>
		tree_iterator(const tree_iterator<OtherNode, OtherTree, OtherT> &other)
		 : node(other.getNode()), rbt(other.getTree()) {
			 root = rbt.get_root();
			 nil = rbt.get_nil();
			 end = rbt.get_end();
		}

		template <class OtherNode, class OtherTree, class OtherT>
		tree_iterator& operator=(const tree_iterator<OtherNode, OtherTree, OtherT> &other) {
			
			node = other.getNode();
			rbt = other.getTree();
			 root = rbt.get_root();
			 nil = rbt.get_nil();
			 end = rbt.get_end();
			return *this;
		}

		reference operator*() const { return const_cast<reference>(node->data); }
		pointer operator->() const { return &(operator*()); }

		tree_iterator& operator++() {
			if (node->right != nil) {
				node = min(node->right);
			}
			else {
				while (node->parent != end && node == node->parent->right)
					node = node->parent;
				node = node->parent;
			}
			return *this; 
		}

		tree_iterator operator++(int) { tree_iterator tmp(*this); operator++(); return tmp; }

		tree_iterator& operator--() { 
			if (node->left != nil && node->left != end)
				node = max(node->left);
			else {
				node_pointer p = node->parent;
				while (p != end && node == p->left) {
					node = p;
					p = p->parent;
				}
				node = node->parent;
			} 
			return *this; 
		}

		tree_iterator operator--(int) { tree_iterator tmp(*this); operator--(); return tmp; }

		node_pointer min(node_pointer node) {
			while(node->left != nil)
				node = node->left;
			return node;
		}

		node_pointer max(node_pointer node) {
			while (node->right != nil)
				node = node->right;
			return node;
		}

		bool operator==(const tree_iterator& iter) const { return node == iter.node; }
		bool operator!=(const tree_iterator& iter) const { return !(operator==(iter)); }

		node_pointer	getNode() const { return node; }
		tree_ref		getTree() const { return rbt; }
	};
	
	/* tree class */
	template <class T, class Compare, class Alloc>
	class RBTree
	{
	public:
		typedef RBTree*											self;
		typedef T 												value_type;
		typedef struct Node<value_type> 						node;
		typedef struct Node<value_type>*						nodePtr;
		typedef typename Alloc::template rebind<node>::other 	node_allocator;
		typedef typename node_allocator::pointer				pointer;
		typedef typename node_allocator::const_pointer			const_pointer;
		typedef typename Alloc::difference_type					difference_type;
		typedef ft::tree_iterator<pointer, RBTree&, T>					iterator;
		typedef ft::tree_iterator<const_pointer, const RBTree&, T>		const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename Alloc::reference						reference;
		typedef typename Alloc::const_reference					const_reference;
		typedef typename Alloc::size_type						size_type;

		Compare 		cmp;
		node_allocator 	alloc;
		pointer 		root;
		pointer 		sentinel;
		pointer			f_end;
		size_type 		size;

		RBTree() : cmp(Compare()) {
			sentinel = createNode();
			sentinel->color = BLACK;
			sentinel->parent = NIL;
			sentinel->left = NIL;
			sentinel->right = NIL;

			f_end = createNode();
			f_end->color = BLACK;
			f_end->right = NIL;
			f_end->left = root;
			f_end->parent = END;

			root = NIL;
			root->parent = END;
			size = 0;
		}

		~RBTree() {
			Destructor(root);
			freeNode(NIL);
			freeNode(END);
		}

		RBTree(const RBTree& other) { 
			*this = other;
		}

		RBTree& operator=(const RBTree& other) {
			if (this != &other) { 
				clear();
				//allocate and copy other tree
				alloc = other.alloc;
				cmp = other.cmp;
				clone(other.root, other.NIL);
				root->parent = END;
				END->left = root;
			}
			return *this;
		}

		void	swap(RBTree& other) {
			std::swap(cmp, other.cmp);
			std::swap(alloc, other.alloc);
			std::swap(root, other.root);
			std::swap(NIL, other.NIL);
			std::swap(END, other.END);
			std::swap(size, other.size);
		}

		void clear() {
			if (root != NIL)
			{
				Destructor(root);
				size = 0;
				root = NIL;
			}
		}

		iterator		begin() { return iterator(min(), *this); }
		iterator		end() { return iterator(END, *this); }
		const_iterator	begin() const { return const_iterator(min(), *this); }
		const_iterator	end() const { return const_iterator(END, *this); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }


		size_type	getSize() const { return size; }
		size_type	max_size() const { return alloc.max_size(); }
		pointer		get_root() const { return root; }
		pointer		get_nil() const { return NIL; }
		pointer		get_end() const { return END; }
		

	/*  find node containing data  */
	pointer findNode(const T& data) const {
		pointer current = root;
		while(current != NIL) {
			if (cmp(data, current->data))
				current = current->left;
			else if (cmp(current->data, data))
				current = current->right;
			else
				return current;
			}
		return(NULL);
	}

    /*  allocate node for data and insert in tree  */
	pair<iterator, bool> insertNode(const T& data) {
    pointer current, parent, x;

    /* find where node belongs */
    current = root;
    parent = END;
    while (current != NIL) {
        if ((data == current->data)) return (ft::make_pair(iterator(current, *this), false));
        parent = current;
        current = cmp(data, current->data) ?
            current->left : current->right;
    }
	x = createNode(data);
    x->parent = parent;

    /* insert node in tree */
    if(parent != END) {
        if(cmp(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        root = x;
    }

    insertFixup(x);
	++size;
    return ft::make_pair(iterator(x, *this), true);
}

	void erase(iterator it) {
    	deleteNode(findNode(it.getNode()->data));
    }

    void erase(iterator first, iterator last) {
    	while (first != last) {
			erase(first);
            ++first;
        }
    }

    size_type erase(const T &data)
    {
		pointer node = findNode(data);
		if (node == NULL)
        	return 0;
		deleteNode(node);
        return 1;
    }

private:
	
	void clone (pointer r, pointer n) {
		if (r != n)
		{
			insertNode(r->data);
			clone(r->left, n);
			clone(r->right, n);
		}
	}

	pointer	createNode(const T& value = T()) {
		pointer	newNode = alloc.allocate(1);
		alloc.construct(newNode, value);
		newNode->parent = END;
		newNode->left = NIL;
		newNode->right = NIL;
		newNode->color = RED;
		return newNode;
	}

	void	Destructor(pointer node) {
		if (node != NIL) {
			Destructor(node->left);
			Destructor(node->right);
			freeNode(node);
		}
	}

	pointer		min() const {
		pointer		tmp = root;
		if (size == 0) return END;
		while (tmp != NIL && tmp->left != NIL)
			tmp = tmp->left;
		return tmp;
	}

    /*  maintain Red-Black tree balance  *
    *  after deleting node x            */
	void deleteFixup(pointer x) {	
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            pointer w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (x->parent);
                x = root;
            }
        } else {
            pointer w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
	root->parent = END;
	END->left = root;
}

    /*  delete node z from tree  */
	void deleteNode(pointer z) {

    pointer x, y;
    if (!z || z == NIL  || z == END) return;

    if (z->left == NIL || z->right == NIL) {
    	/* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent != NIL && y->parent != END)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
	{
        root = x;
		x->parent = END;
		x->parent->left = root;
	}

    if (y != z) {
		z->data = y->data;
	}

	--size;
    if (y->color == BLACK)
        deleteFixup (x);
    freeNode (y);
}

	void freeNode(pointer node) {
		alloc.destroy(node);
		alloc.deallocate(node, 1);
	}

    /*  maintain Red-Black tree balance  *
    *  after inserting node x           */
	void insertFixup(pointer x) {

    /* check Red-Black properties */
    while (x != root && x->parent->color == RED) {
        /* we have a violation */
        if (x->parent == x->parent->parent->left) {
            pointer y = x->parent->parent->right;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->right) {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        } else {

            /* mirror image of above code */
            pointer y = x->parent->parent->left;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
	root->parent = END;
	END->left = root;
	}

    /*  rotate node x to left */
	void rotateLeft(pointer x) {
    	
		pointer y = x->right;
    	/* establish x->right link */
    	x->right = y->left;
    	if (y->left != NIL)
			y->left->parent = x;

    	/* establish y->parent link */
    	if (y != NIL) y->parent = x->parent;
    	if (x->parent != END) {
    	    if (x == x->parent->left)
    	        x->parent->left = y;
    	    else
    	        x->parent->right = y;
    	} else {
    	    root = y;
    	}

    	/* link x and y */
    	y->left = x;
    	if (x != NIL) x->parent = y;
	}

    /*  rotate node x to right  */
	void rotateRight(pointer x) {

    	pointer y = x->left;

    	/* establish x->left link */
    	x->left = y->right;
    	if (y->right != NIL) 
			y->right->parent = x;

    	/* establish y->parent link */
    	if (y != NIL) y->parent = x->parent;
    	if (x->parent != END) {
    	    if (x == x->parent->right)
    	        x->parent->right = y;
    	    else
    	        x->parent->left = y;
    	} else {
    	    root = y;
    	}

    	/* link x and y */
    	y->right = x;
    	if (x != NIL) x->parent = y;
	}

};
}

#endif

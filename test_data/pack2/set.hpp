#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "RBTree.hpp"

namespace ft {

template <class T,
          class Compare = std::less<T>,
          class Alloc = std::allocator<T>
> class set {
    
    /*
    ** Member types
    */
    public:
        typedef T                                           key_type;
        typedef T                                           value_type;
        typedef Compare                                     key_compare;
        typedef Compare                                     value_compare;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;

    private:
        typedef RBTree<value_type, allocator_type, value_compare>   tree_type;
    public:
        typedef typename tree_type::const_iterator          iterator;
        typedef typename tree_type::const_iterator          const_iterator;
        typedef typename tree_type::const_reverse_iterator  reverse_iterator;
        typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;
    private:
        tree_type                                           _tree;
        allocator_type                                      _alloc;
        value_compare                                       _comp;
        
    /*
    ** Member functions
    */
    public:
        // Constructors
        explicit set(
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()
        ) : _tree(tree_type(alloc, comp)), _alloc(alloc), _comp(comp) {}
        
        template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _tree(tree_type(alloc, comp)), _alloc(alloc), _comp(comp) {
            for (; first != last; first++) {
                _tree.insert(*first);
            }
        }
        	
        set(const set& x)
            : _tree(tree_type(x._tree)), _alloc(x._alloc), _comp(x._comp) {}

        ~set() {}

        set& operator= (const set& other) {
            if (this != &other) {
                this->_tree = other._tree;
            }
            return (*this);
        }

        /*
        ** Iterators
        */
        iterator                    begin() {
            return (_tree.begin());
        }

        const_iterator              begin() const {
            return (_tree.begin());
        }

        reverse_iterator            rbegin() {
            return (_tree.rbegin());
        }

        const_reverse_iterator      rbegin() const {
            return (_tree.rbegin());
        }

        iterator                    end() {
            return (_tree.end());
        }
        const_iterator              end() const {
            return (_tree.end());
        }

        reverse_iterator            rend() {
            return (_tree.rend());
        }
        const_reverse_iterator      rend() const {
            return (_tree.rend());
        }
        
        /*
        ** Capacity
        */
        bool             empty() const {
            return (size() == 0);
        }
        size_type        size() const {
            return (_tree.size());
        }

        size_type        max_size() const {
                return (_alloc.max_size());
        }

        /*
        ** Modifiers
        */
        // Single element	
        ft::pair<iterator,bool>     insert(const value_type& val) {
            iterator found = _tree.search(val);
            if (found != end()) {
                return (ft::pair<iterator,bool>(found, false));
            }
            found = _tree.insert(val);
            return (ft::pair<iterator,bool>(found, true));
        }

        // With hint
        iterator                    insert(iterator position, const value_type& val) {
            (void)position;
            iterator inserted = _tree.search(val);
            if (inserted != end()) {
                return (inserted);
            }
            return(_tree.insert(val));
        }
        
        // Range	
        template <class InputIterator>
        void                        insert(InputIterator first, InputIterator last) {
            for (; first != last; first++) {
                insert(*first);
            }
        }

        void        erase(
            iterator position,
            typename ft::enable_if<!ft::is_integral<iterator>::value>::type* = 0
        ) {
            _tree.remove(position);
        }

        size_type   erase(const key_type& k) {
            if (_tree.remove(k)) {
                return (1);
            }
            return (0);
        }
        
        void        erase(iterator first, iterator last) {
            _tree.remove(first, last);
        }

        void        swap (set& x) {
            _tree.swap(x._tree);
            std::swap(_comp, x._comp);
            std::swap(_alloc, x._alloc);
        }

        void        clear() {
            _tree.clear();
        }

        /*
        ** Observers
        */
        value_compare   value_comp() const {
            return (_comp);
        }

        key_compare     key_comp() const {
            return (value_comp());
        }
  
        /*
        ** Operations
        */
        iterator            find(const key_type& k) const {
            return (_tree.search(k));
        }

        size_type           count(const key_type& k) const {
            const_iterator  found = find(k);
            if (found != end()) {
                return (1);
            }
            return (0);
        }

        iterator                                lower_bound(const key_type& k) const {
            iterator it = begin();
            while (it != end() && _comp(*it, k)) {
                it++;
            }
            return (it);
        }

        iterator                                upper_bound(const key_type& k) const {
            iterator it = begin();
            while (it != end() && !(_comp(k, *it))) {
                it++;
            }
            return (it);
        }

        ft::pair<iterator,iterator>             equal_range(const key_type& k) const {
            iterator    lower = lower_bound(k);
            if (lower != end()) {
                if (!_comp(k, *lower))
                    return (ft::make_pair(lower, ++lower));
            }
            return (ft::make_pair(lower, lower));
        }

        allocator_type  get_allocator() const {
            return (_alloc);
        }

        /*
        ** Comparision operators (non-member)
        */
        template<class key, class compare, class alloc>
        friend bool operator==(const ft::set<key, compare, alloc>& lhs,
                               const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        friend bool operator!=(const ft::set<key, compare, alloc>& lhs,
                               const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        friend bool operator<(const ft::set<key, compare, alloc>& lhs,
                              const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        friend bool operator<=(const ft::set<key, compare, alloc>& lhs,
                               const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        friend bool operator>(const ft::set<key, compare, alloc>& lhs,
                              const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        friend bool operator>=(const ft::set<key, compare, alloc>& lhs,
                               const ft::set<key, compare, alloc>& rhs);

        template<class key, class compare, class alloc>
        void swap(const ft::set<key, compare, alloc>& lhs,
                  const ft::set<key, compare, alloc>& rhs);
};


template<class key, class compare, class alloc>
bool operator==(const ft::set<key, compare, alloc>& lhs,
                const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree == rhs._tree);
}

template<class key, class compare, class alloc>
bool operator!=(const ft::set<key, compare, alloc>& lhs,
                const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree != rhs._tree);
}

template<class key, class compare, class alloc>
bool operator<(const ft::set<key, compare, alloc>& lhs,
               const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree < rhs._tree);
}

template<class key, class compare, class alloc>
bool operator<=(const ft::set<key, compare, alloc>& lhs,
                const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree <= rhs._tree);
}

template<class key, class compare, class alloc>
bool operator>(const ft::set<key, compare, alloc>& lhs,
               const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree > rhs._tree);
}

template<class key, class compare, class alloc>
bool operator>=(const ft::set<key, compare, alloc>& lhs,
                const ft::set<key, compare, alloc>& rhs) {
    return (lhs._tree >= rhs._tree);
}

template<class key, class compare, class alloc>
void swap(const ft::set<key, compare, alloc>& lhs,
          const ft::set<key, compare, alloc>& rhs) {
    lhs.swap(rhs);
}

} // namespace brace

#endif
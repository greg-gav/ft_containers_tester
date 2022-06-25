#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "ft_utilities.hpp"
# include "RBTree.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key,T> >
> class map {

    /*
    ** Member types, part I
    */
    public:
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const key_type, mapped_type>       value_type;
        typedef Compare                                     key_compare;
        typedef Alloc                                       allocator_type;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
    /*
    ** Nested value_comp class
    */
    private:
        class value_comp : public std::binary_function<value_type, value_type, bool> {
            protected:
                Compare                                     comp;
            public:
                typedef bool                                result_type;
                typedef value_type                          first_argument_type;
                typedef value_type                          second_argument_type;

                value_comp(Compare c) : comp(c) {}
                bool operator() (const value_type& x, const value_type& y) const {
                    return comp(x.first, y.first);
                }
        };
    /*
    ** Member types, part II
    */
    public:
        typedef value_comp                              value_compare;
    private:
        typedef RBTree<value_type, allocator_type, value_compare>   tree_type;
    public:
        typedef typename tree_type::iterator                iterator;
        typedef typename tree_type::const_iterator          const_iterator;
        typedef typename tree_type::reverse_iterator        reverse_iterator;
        typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;
    /*
    ** Private fields
    */
    private:
        tree_type                                       _tree;
        key_compare                                     _comparator;
        allocator_type                                  _allocator;

    public:
        // Default constructor
        explicit map(
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()
        ) : _tree(tree_type(alloc, comp)), _comparator(comp), _allocator(alloc) {}

        // Range constructor
        template <class InputIterator>
        map(
            InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()
        ) : _tree(tree_type(alloc, comp)), _comparator(comp), _allocator(alloc) {
            for (; first != last; first++) {
                _tree.insert(*first);
            }
        }

        // Copy constructor
        map(const map& other)
            : _tree(tree_type(other._allocator, other._comparator)),
              _comparator(other._comparator), _allocator(other._allocator) {
            for (const_iterator it = other.begin(); it != other.end(); it++) {
                _tree.insert(*it);
            }
        }
        
        // Destructor (all allocations/deallocations are done in the tree)
        ~map() {}

        // Assignation operator
        map& operator= (const map& other) {
            if (this != &other) {
                this->_allocator = other._allocator;
                this->_comparator = other._comparator;
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
                return (_allocator.max_size());
        }

        /*
        ** Element access
        */
        mapped_type&    operator[](const key_type& k) {
            return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
        }

        mapped_type& at( const key_type& key ) {
            iterator found = _tree.search(ft::make_pair(key, mapped_type()));
            if (found != end()) {
                return (found->second);
            }
            throw std::out_of_range("No element with such key in map!");
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
            if (_tree.remove(ft::make_pair(k, mapped_type()))) {
                return (1);
            }
            return (0);
        }
        
        void        erase(iterator first, iterator last) {
            _tree.remove(first, last);
        }

        void        swap (map& x) {
            _tree.swap(x._tree);
            std::swap(_comparator, x._comparator);
            std::swap(_allocator, x._allocator);
        }

        void        clear() {
            _tree.clear();
        }

        /*
        ** Observers
        */
        key_compare     key_comp() const {
            return (_comparator);
        }

        value_compare value_comp() const {
            return (value_compare(_comparator));
        }

        /*
        ** Operations
        */
        iterator            find(const key_type& k) {
            value_type      entry = ft::make_pair(k, mapped_type());
            return (_tree.search(entry));
        }

        const_iterator      find(const key_type& k) const {
            value_type      entry = ft::make_pair(k, mapped_type());
            return (const_iterator(_tree.search(entry)));
        }

        size_type           count(const key_type& k) const {
            const_iterator  found = find(k);
            if (found != end()) {
                return (1);
            }
            return (0);
        }

        iterator                                lower_bound(const key_type& k) {
            iterator it = begin();
            while (it != end() && _comparator(it->first, k)) {
                it++;
            }
            return (it);
        }

        const_iterator                          lower_bound(const key_type& k) const {
            const_iterator it = begin();
            while (it != end() && _comparator(it->first, k)) {
                it++;
            }
            return (it);
        }

        iterator                                upper_bound(const key_type& k) {
            iterator it = begin();
            while (it != end() && !(_comparator(k, it->first))) {
                it++;
            }
            return (it);
        }

        const_iterator                          upper_bound(const key_type& k) const{
            const_iterator it = begin();
            while (it != end() && !(_comparator(k, it->first))) {
                it++;
            }
            return (it);
        }

        ft::pair<iterator,iterator>             equal_range(const key_type& k) {
            iterator    lower = lower_bound(k);
            if (lower != end()) {
                if (!_comparator(k, lower->first))
                    return (ft::make_pair(lower, ++lower));
            }
            return (ft::make_pair(lower, lower));
        }

        ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
            const_iterator    lower = lower_bound(k);
            if (lower != end()) {
                if (!_comparator(k, lower->first))
                    return (ft::make_pair(lower, ++lower));
            }
            return (ft::make_pair(lower, lower));
        }

        allocator_type  get_allocator() const {
            return (_allocator);
        }
        
        /*
        ** Comparision operators (non-member)
        */
        template<class key, class value, class comparator, class allocator>
        friend bool operator==(const ft::map<key, value, comparator, allocator>& lhs,
                               const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        friend bool operator!=(const ft::map<key, value, comparator, allocator>& lhs,
                               const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        friend bool operator<(const ft::map<key, value, comparator, allocator>& lhs,
                              const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        friend bool operator<=(const ft::map<key, value, comparator, allocator>& lhs,
                               const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        friend bool operator>(const ft::map<key, value, comparator, allocator>& lhs,
                              const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        friend bool operator>=(const ft::map<key, value, comparator, allocator>& lhs,
                               const ft::map<key, value, comparator, allocator>& rhs);

        template<class key, class value, class comparator, class allocator>
        void swap(const ft::map<key, value, comparator, allocator>& lhs,
                  const ft::map<key, value, comparator, allocator>& rhs);
};


template<class key, class value, class comparator, class allocator>
bool operator==(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree == rhs._tree);
}

template<class key, class value, class comparator, class allocator>
bool operator!=(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree != rhs._tree);
}

template<class key, class value, class comparator, class allocator>
bool operator<(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree < rhs._tree);
}

template<class key, class value, class comparator, class allocator>
bool operator<=(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree <= rhs._tree);
}

template<class key, class value, class comparator, class allocator>
bool operator>(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree > rhs._tree);
}

template<class key, class value, class comparator, class allocator>
bool operator>=(const ft::map<key, value, comparator, allocator>& lhs,
                const ft::map<key, value, comparator, allocator>& rhs) {
    return (lhs._tree >= rhs._tree);
}

template<class key, class value, class comparator, class allocator>
void swap(const ft::map<key, value, comparator, allocator>& lhs,
          const ft::map<key, value, comparator, allocator>& rhs) {
    lhs.swap(rhs);
}

} // Namespace brace

#endif
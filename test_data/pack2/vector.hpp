#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <stddef.h>
# include "ft_utilities.hpp"

namespace ft {

template <class T, bool is_const>
class vector_iterator {
    /*
    ** Member types
    */
    public:
        typedef typename std::random_access_iterator_tag              iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type          value_type;
        typedef typename ft::iterator_traits<T*>::difference_type     difference_type;
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
        typedef pointer                                                     iterator_type;
        
    protected:
        pointer      _p;

    /*
    ** Member functions
    */
    public:
        // Constructors
        vector_iterator() : _p(NULL) {}
        vector_iterator(pointer p) : _p(p) {}
        vector_iterator(const vector_iterator<T, false>& other) : _p( &(*other) ) {}
        
        // Destructor
        virtual ~vector_iterator() {}

        // Operators
        vector_iterator&    operator=(const vector_iterator& other) {
            if (this != &other) {
                this->_p = other._p;
            }
            return (*this);
        }

        // Access operators
        reference           operator*() const { return *_p; }
        pointer             operator->() const { return _p; }
        reference           operator[](const difference_type n) const { return (*(_p + n)); }

        // Increment/Decrement
        vector_iterator&    operator++() {
            ++_p;
            return (*this);
        }

        vector_iterator     operator++(int) {
            vector_iterator tmp(*this);
            ++_p;
            return (tmp);
        }

        vector_iterator&    operator--() {
            --_p;
            return (*this);
        }

        vector_iterator     operator--(int) {
            vector_iterator tmp(*this);
            --_p;
            return (tmp);
        }

        vector_iterator     operator+(const difference_type n) const {
            return (vector_iterator(_p + n));
        }

        vector_iterator     operator-(const difference_type n) const {
            return (vector_iterator(_p - n));
        }

        difference_type     operator-(const vector_iterator& other) const {
            return (_p - other._p);
        }

        vector_iterator&     operator+=(const difference_type n) {
            _p += n;
            return (*this);
        }

        vector_iterator     operator-=(const difference_type n) {
            _p -= n;
            return (*this);
        }

        // Comparison operators 
        
        friend bool    operator==(const vector_iterator& lhs,
                                  const vector_iterator& rhs) {
            return (lhs._p == rhs._p);
        }

        friend bool    operator!=(const vector_iterator& lhs,
                                  const vector_iterator& rhs) {
            return (lhs._p != rhs._p);
        }

        friend bool    operator>=(const vector_iterator& lhs,
                                  const vector_iterator& rhs) {
            return (lhs._p >= rhs._p);
        }

        friend bool    operator<=(const vector_iterator& lhs,
                                  const vector_iterator& rhs) {
            return (lhs._p <= rhs._p);
        }

        friend bool    operator>(const vector_iterator& lhs,
                                 const vector_iterator& rhs) {
            return (lhs._p > rhs._p);
        }

        friend bool    operator<(const vector_iterator& lhs,
                                 const vector_iterator& rhs) {
            return (lhs._p < rhs._p);
        }
};

template <
    class T,
    class Allocator = std::allocator<T>
> class vector {
    /*
    ** Member types
    */
    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ft::vector_iterator<T, false>               iterator;
        typedef ft::vector_iterator<T, true>                const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    /*
    ** Private fields
    */
    private:
        pointer                                 _array;
        size_type                               _capacity;
        size_type                               _size;
        allocator_type                          _allocator;

    /*
    ** Member functions
    */
    public:
        // Default constructor
        explicit vector(const allocator_type& alloc = allocator_type()) :
            _capacity(0), _size(0), _allocator(alloc) {
            _array = _allocator.allocate(_capacity);
        }
        
        
        // Fill constructor
        explicit vector(
            size_type n,
            const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type()
        ) : _capacity(n), _size(n), _allocator(alloc) {
            _array = _allocator.allocate(_capacity);
            size_type i = 0;
            try {
                while (i < _size) {
                    _allocator.construct(_array + i, val);
                    i++;
                }
            } catch (...) {
                while (--i >= 0) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
        }

        // Range constructor
        template <class InputIterator>
        vector(
            InputIterator first,
            InputIterator last,
            const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0
        ) : _allocator(alloc) {
            difference_type     diff = std::distance(first, last);
            _size = static_cast<size_type>(diff);
            _capacity = static_cast<size_type>(diff);
            _array = _allocator.allocate(_capacity);
            size_type i = 0;
            try {
                while (first != last) {
                    _allocator.construct(_array + i, *first);
                    first++;
                    i++;
                }
            } catch (...) {
                while (--i >= 0) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
        }

        // Copy constructor
        vector(const vector& x) :
            _capacity(x._capacity), _size(x._size), _allocator(x._allocator) {
            _array = _allocator.allocate(_capacity);
            
            size_type i = 0;
            try {
                while (i < _size) {
                    _allocator.construct(_array + i, x[i]);
                    i++;
                }
            } catch (...) {
                while (--i >= 0) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
        }
        
        // Operator=
        vector& operator= (const vector& x) {
            if (this == &x)
                return (*this);

            allocator_type      old_alloc = _allocator;
             _allocator = x._allocator;

            for (size_type i = 0; i < _size; i++) {
                old_alloc.destroy(_array + i);
            }

            _size = x._size;
            if (_capacity < _size) {
                old_alloc.deallocate(_array, _capacity);
                _capacity = _size;
                _array = _allocator.allocate(_capacity);
            }

            size_type i = 0;
            try {
                while (i < _size) {
                    _allocator.construct(_array + i, x[i]);
                    i++;
                }
            } catch (...) {
                while (--i >= 0) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
            return (*this);
        }

        ~vector() {
            for (size_type i = 0; i < _size; i++) {
                _allocator.destroy(_array + i);
            }
            _allocator.deallocate(_array, _capacity);
        }

        /*
        ** Iterators
        */
        iterator                 begin() {
            return (iterator(_array));
        }

        const_iterator           begin() const {
            return (const_iterator(_array));
        }
        
        iterator                 end() {
            return (iterator(_array + _size));
        }

        const_iterator           end() const {
            return (const_iterator(_array + _size));
        }

        reverse_iterator     rbegin() {
            return ( reverse_iterator(end()) );
        }

        const_reverse_iterator     rbegin() const {
            return ( const_reverse_iterator(end()) );
        }

        reverse_iterator     rend() {
            return ( reverse_iterator(begin()) );
        }

        const_reverse_iterator     rend() const {
            return ( const_reverse_iterator(begin()) );
        }

        /*
        ** Capacity
        */
        size_type   size() const {
            return (_size);
        }

        void        resize(size_type n, value_type val = value_type()) {
            if (n == _size)
                return ;
            
            if (n < _size) {
                // reduces to its first n elements, destroying elements beyond
                for (size_type i = _size - 1; i > n - 1; --i) {
                    _allocator.destroy(_array + i);
                }
            } else {
                if (n > _capacity) {
                    // reallocates the storage to fit n elements
                    reserve(n);
                }
                // content expanded, inserting n-_size elements at the end (copies of val)
                
                size_type i = _size;
                try {
                    while (i < n) {
                        _allocator.construct(_array + i, val);
                        i++;
                    }
                } catch (...) {
                    while (--i >= 0) {
                        _allocator.destroy(_array + i);
                    }
                    _allocator.deallocate(_array, _capacity);
                    throw ;
                }
            }
            _size = n;
        }

        size_type   max_size() const {
            return (_allocator.max_size());
        }

        size_type   capacity() const {
            return (_capacity);
        }

        bool        empty() const {
            return (_size == 0);
        }

        void        reserve(size_type n) {
            if (n <= _capacity)
                return ;
            
            pointer new_array = _allocator.allocate(n);
            try {
                _uninit_copy(_array, _array + _size, new_array);
            } catch (...) {
                _allocator.deallocate(new_array, n);
                throw;
            }

            for (size_type i = 0; i < _size; i++) {
                _allocator.destroy(_array + i);
            }
            _allocator.deallocate(_array, _capacity);

            _capacity = n;
            _array = new_array;
        }   

        /*
        ** Element access
        */
        reference       operator[] (size_type n) {
			return(_array[n]);
		}

		const_reference operator[] (size_type n) const {
			return(_array[n]);
		}

        reference at (size_type n) {
            if (n >= _size)
                throw std::out_of_range("No element with such index!");
            return (_array[n]);
        }

        const_reference at (size_type n) const {
            if (n >= _size)
                throw std::out_of_range("No element with such index!");
            return (_array[n]);
        }

        reference front() {
            return (*_array);
        }

        const_reference front() const {
            return (*_array);
        }

        reference back() {
            return ( *(_array + _size - 1) );
        }

        const_reference back() const {
            return ( *(_array + _size - 1) );
        }

        pointer         data() const {
            return (_array);
        }
        
        /*
        ** Modifiers
        */
        template <class InputIterator>
        void       assign (
            InputIterator first,
            InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0
        ) {
            clear();

            size_type   new_size = static_cast<size_type>(std::distance(first, last));

            if (new_size > _capacity) {
                _allocator.deallocate(_array, _capacity);
                _array = _allocator.allocate(new_size);
                _capacity = new_size;
            }
            try {
                _uninit_copy(first, last, _array);
            } catch (...) {
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
            _size = new_size;
        }
        
        void    assign (size_type n, const value_type& val) {
            clear();
            _size = n;

            if (n > _capacity) {
                _allocator.deallocate(_array, _capacity);
                _array = _allocator.allocate(n);
                _capacity = n;
            }

            size_type i = 0;
            try {
                while (i < _size) {
                    _allocator.construct(_array + i, val);
                    i++;
                }
            } catch (...) {
                while (--i >= 0) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);
                throw ;
            }
        }
    
        void    clear() {
            for (size_type i = 0; i < _size; i++) {
                _allocator.destroy(_array + i);
            }
            _size = 0;
        }

        void    push_back (const value_type& val) {
            if (_size == _capacity) {
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            }
            _allocator.construct(_array + _size, val);
            _size++;
        }

        void    pop_back() {
            _allocator.destroy(_array + _size - 1);
            _size--;
        }

        // Insert single element
        iterator    insert(iterator position, const value_type& val) {
            if (position < begin() || position > end())
                throw std::out_of_range("inserting position is out of range");

            size_type   border = static_cast<size_type>(position - begin());

            if (_size < _capacity) {
                size_type   i = _size;
                while (i > border) {
                    --i;
                    _allocator.construct(_array + i + 1, *(_array + i));
                    _allocator.destroy(_array + i);
                }
                _allocator.construct(_array + i, val);
            } else {  // _size == _capacity, needs to reallocate array
                size_type   new_capacity =  (_capacity == 0) ? 1 : _capacity * 2;
                pointer new_array = _allocator.allocate(new_capacity);

                try {
                    _uninit_copy(begin(), position, new_array);
                    _allocator.construct(new_array + border, val);
                    _uninit_copy(position, end(), new_array + border + 1);
                } catch (...) {
                    _allocator.destroy(new_array + border);
                    _allocator.deallocate(new_array, new_capacity);
                    throw ;
                }

                for (size_type i = 0; i < _size; i++) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);

                _array = new_array;
                _capacity = new_capacity;
            }
            _size++;

            return (begin() + border);
        }

        // Fill-type insert
        void        insert(iterator position, size_type n, const value_type& val) {
            if (position < begin() || position > end())
                throw std::out_of_range("inserting position is out of range");

            size_type   border = static_cast<size_type>(position - begin());

            if (_size + n <= _capacity) {
                size_type i = _size; // index of the last element
                while (i > border) {
                    _allocator.construct(_array + i + n - 1, *(_array + i - 1));
                    _allocator.destroy(_array + i + n - 1);
                    i--;
                }
                i = 0;
                while (i < n) {
                    _allocator.construct(_array + border + i, val);
                    i++;
                }
            } else {
                // reallocate, construct new array
                size_type   new_capacity;
                pointer     new_array;

                new_capacity = (_capacity * 2 < _capacity + n) ?
                               _capacity + n : _capacity * 2;

                new_array = _allocator.allocate(new_capacity);
                try {
                    _uninit_copy(begin(), position, new_array);
                    for (size_type i = border; i < border + n; i++) {
                        _allocator.construct(new_array + i, val);
                    }
                    _uninit_copy(position, end(), new_array + border + n);
                } catch (...) {
                    _allocator.deallocate(new_array, new_capacity);
                    throw ;
                }
                
                for (size_type i = 0; i < _size; i++) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);

                _array = new_array;
                _capacity = new_capacity;
            }
            _size += n;
        }

        // Range-type insert
        template <class InputIterator>
        void        insert(
            iterator position,
            InputIterator first,
            InputIterator last,
            typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0)
        {
            if (position < begin() || position > end())
                throw std::out_of_range("inserting position is out of range");
                
            size_type   border = static_cast<size_type>(position - begin());
            size_type   n = static_cast<size_type>(std::distance(first, last));

            if (_size + n <= _capacity) {
                size_type i = _size; // index of the last element
                while (i > border) {
                    _allocator.construct(_array + i + n - 1, *(_array + i - 1));
                    _allocator.destroy(_array + i + n - 1);
                    i--;
                }
                i = 0;
                while (i < n) {
                    _allocator.construct(_array + border + i, *first);
                    i++;
                    first++;
                }
            } else {
                // reallocate and fill range
                size_type   new_capacity;
                pointer     new_array;

                new_capacity = (_capacity * 2 < _capacity + n) ?
                               _capacity + n : _capacity * 2;

                new_array = _allocator.allocate(new_capacity);
                try {
                    _uninit_copy(begin(), position, new_array);
                    _uninit_copy(first, last, new_array + border);
                    _uninit_copy(position, end(), new_array + border + n);
                } catch (...) {
                    _allocator.deallocate(new_array, new_capacity);
                    throw ;
                }
                
                for (size_type i = 0; i < _size; i++) {
                    _allocator.destroy(_array + i);
                }
                _allocator.deallocate(_array, _capacity);

                _array = new_array;
                _capacity = new_capacity;
            }
            _size += n;
        }

        iterator erase (iterator first, iterator last) {
            size_type   left_border = static_cast<size_type>(first - begin());
            size_type   right_border = static_cast<size_type>(last - begin());
            size_type   n = static_cast<size_type>(std::distance(first, last));

            size_type   i = left_border;
            for (; i < right_border; i++) {
                _allocator.destroy(_array + i);
            }

            try {
                for (; i < _size; i++) {
                    _allocator.construct(_array + i - n, *(_array + i));
                    _allocator.destroy(_array + i);
                }
            } catch (...) {
                for (; i >= right_border; i--) {
                    _allocator.destroy(_array + i - n);
                }
                throw ;
            }

            _size -= n;
            return (begin() + left_border);
        }

        iterator erase (iterator position) {
            return erase(position, position + 1);
        }

        void swap (vector& x) {
			std::swap(_array, x._array);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_allocator, x._allocator);
        }

        
        /*
        ** Allocator
        */
        allocator_type get_allocator() const {
            return (_allocator);
        }
    
    /*
    ** Helper functions
    */
    private:
        template< class InputIt, class NoThrowForwardIt >
        void _uninit_copy(InputIt first, InputIt last,
                          NoThrowForwardIt d_first) {
            NoThrowForwardIt    current = d_first;
            try {
                for (; first != last; ++first, ++current) {
                    _allocator.construct(
                        const_cast<pointer>(static_cast<const volatile pointer>(
                            &(*current))
                        ),
                        *first
                    );
                }
            } catch (...) {
                for (; d_first != current; ++d_first) {
                    _allocator.destroy(
                        const_cast<pointer>(static_cast<const volatile pointer>(
                            &(*d_first))
                        )
                    );
                }
                throw ;
            }
        }
};

/*
** Non-member function implementation
*/
template <class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    if (lhs.size() != rhs.size()) {
        return (false);
    }
    typename ft::vector<T, Alloc>::const_iterator  lhs_it, rhs_it;
    lhs_it = lhs.begin();
    rhs_it = rhs.begin();
    while (lhs_it != lhs.end() || rhs_it != rhs.end()) {
        if (*lhs_it != *rhs_it) {
            return (false);
        }
        lhs_it++; rhs_it++;
    }
    return (true);
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (!(lhs < rhs));
}

template <class T, class Alloc>
void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
    x.swap(y);
}

}  // namespace brace

#endif
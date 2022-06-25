#ifndef REVERSE_ITERATOR
# define REVERSE_ITERATOR

# include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator {
    /*
    ** Member types
    */
    public:
        typedef Iterator                                                    iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;
    
    /*
    ** Protected fields
    */
    protected:
        iterator_type                                               _base;

    /*
    ** Member functions
    */
    public:
        // Default constructor
        reverse_iterator() : _base() {}

        // Initialization
        explicit reverse_iterator(iterator_type it) : _base(it) {}

        // Copy constructor
        template <class OhterIter>
        reverse_iterator(const reverse_iterator<OhterIter>& other) { *this = other; }

        // Assignation operator
        template <class OhterIter>
        reverse_iterator&   operator=(const reverse_iterator<OhterIter>& other) {
            if (this != &other)
                _base = other._base;
            return (*this);
	    };

        virtual ~reverse_iterator() {}

        iterator_type       base() const { return (_base); }

        reference           operator*() const {
            Iterator    tmp = _base;
            return (*--tmp);
        }


        reverse_iterator    operator+ (difference_type n) const {
            return (reverse_iterator(_base - n));
        }
        
        reverse_iterator&   operator++() {
            _base--;
            return (*this);
        }

        reverse_iterator    operator++(int) {
            reverse_iterator temp = *this;
            ++(*this);
            return (temp);
        }

        reverse_iterator&   operator+= (difference_type n) {
            _base -= n;
            return (*this);
        }

        reverse_iterator    operator-(difference_type n) const {
            return (reverse_iterator(_base + n));
        }

        reverse_iterator&   operator--() {
            _base++;
            return (*this);
        }

        reverse_iterator    operator--(int) {
            reverse_iterator temp = *this;
            --(*this);
            return (temp);
        }

        reverse_iterator&   operator-= (difference_type n) {
            _base += n;
            return (*this);
        }

        pointer             operator->() const { return &(operator*()); }

        reference           operator[] (difference_type n) const {
            return (_base[-n - 1]);
        }
};

/*
**  Non-member functions
*/
template <class Iterator>
bool    operator==(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() == rhs.base());
}
        
template <class Iterator>
bool    operator!=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() != rhs.base());
}

template <class Iterator>
bool    operator<(const reverse_iterator<Iterator>& lhs,
                  const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() > rhs.base());
}

template <class Iterator>
bool    operator<=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool    operator>(const reverse_iterator<Iterator>& lhs,
                  const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() < rhs.base());
}

template <class Iterator>
bool    operator>=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator>                              operator+ (
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it
) {
    return (rev_it + n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type    operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs
) {
    return (rhs.base() - lhs.base());
}

} // namespace brace

#endif
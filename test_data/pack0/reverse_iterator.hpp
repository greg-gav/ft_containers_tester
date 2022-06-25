#ifndef _REVERSE_ITERATOR_
#define _REVERSE_ITERATOR_

#include "iterator_traits.hpp"

namespace ft 
{
 template <class Iter>
 class reverse_iterator : 
                public std::iterator<typename iterator_traits<Iter>::iterator_category,
                                typename iterator_traits<Iter>::value_type,
                                typename iterator_traits<Iter>::difference_type,
                                typename iterator_traits<Iter>::pointer,
                                typename iterator_traits<Iter>::reference>
 {
   protected:
     Iter current;

   public:
     typedef Iter     iterator_type;
     typedef typename iterator_traits<Iter>::reference       reference;
     typedef typename iterator_traits<Iter>::pointer         pointer;
     typedef typename iterator_traits<Iter>::difference_type difference_type;

     reverse_iterator() : current() {}
     explicit reverse_iterator(Iter x) : current(x) {}
     template<class U> reverse_iterator (const reverse_iterator<U>& x) : 
                                                            current(x.base()) {}
     Iter base() const { return current; }

     reference operator* () const {Iter tmp = current; return *--tmp; }
     pointer operator-> () const { return &(operator*()); }
     reference operator[] (difference_type n) const { return *(*this + n); }

     reverse_iterator& operator++ () { --current; return *this; }
     reverse_iterator operator++ (int) {reverse_iterator t = current; --current; return t; }
     reverse_iterator& operator-- () { ++current; return *this; }
     reverse_iterator operator-- (int) {reverse_iterator t = current; ++current; return t; }

     reverse_iterator operator+ (difference_type n) const { return reverse_iterator(current - n); }
     reverse_iterator& operator+= (difference_type n) { current -= n; return *this; }
     reverse_iterator operator- (difference_type n) const { return reverse_iterator(current + n); }
     reverse_iterator& operator-= (difference_type n) { current += n; return *this; }
 };
     template <class Iter1, class Iter2>
     typename reverse_iterator<Iter1>::difference_type
     operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
      return y.base() - x.base();
    }
}

#endif

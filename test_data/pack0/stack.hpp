#ifndef _STACK_HPP_
#define _STACK_HPP_

#include "vector.hpp"

namespace ft
{
   template<class T, class C = vector<T> >
   class stack
   {
    protected:
     C c;
    
    public:
     typedef C                                        container_type;
     typedef typename container_type::value_type      value_type;
     typedef typename container_type::reference       reference;
     typedef typename container_type::const_reference const_reference;
     typedef typename container_type::size_type       size_type;

     explicit stack (const C& a = C()) : c(a) { }
     stack(const stack& q) : c(q.c) { }
     stack& operator=(const stack& q) { c = q.c; return *this; }

     bool empty () const { return c.empty(); }
     size_type size () const { return c.size(); }

     reference top () { return c.back(); }
     const reference top () const { return c.back(); }

     void push (const value_type& x) { c.push_back(x); }
     void pop () { c.pop_back(); }

        template <class Tn, class ContainerN>
        friend bool operator==(const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
         template <class Tn, class ContainerN>
        friend bool operator< (const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
         template <class Tn, class ContainerN>
        friend bool operator!=(const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
         template <class Tn, class ContainerN>
        friend bool operator> (const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
         template <class Tn, class ContainerN>
        friend bool operator>=(const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
         template <class Tn, class ContainerN>
        friend bool operator<=(const stack<Tn, ContainerN>& x, const stack<Tn, ContainerN>& y);
   };

   template <class T, class Container>
  bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
  { return x.c == y.c; }
   template <class T, class Container>
  bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
  { return x.c < y.c; }
   template <class T, class Container>
  bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
  { return !(x == y); }
   template <class T, class Container>
  bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
  { return y < x; }
   template <class T, class Container>
  bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
  { return !(x < y); }
   template <class T, class Container>
  bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
  {return !(y < x); }
  
}

#endif

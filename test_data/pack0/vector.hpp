#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <memory>
#include "reverse_iterator.hpp"
#include "equal_compare.hpp"
#include "enable_if.hpp"

namespace ft
{

template<class T, class A = std::allocator<T> > 
 class vector
 {
 public:
   /* types */
   typedef T                                    value_type;
   typedef A                                    allocator_type;
   typedef typename A::size_type                size_type;
   typedef typename A::difference_type          difference_type;

   typedef T*                                   iterator;
   typedef const T*                             const_iterator;
   typedef ft::reverse_iterator<iterator>       reverse_iterator;
   typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
   
   typedef typename A::pointer                  pointer;
   typedef typename A::const_pointer            const_pointer;
   typedef typename A::reference                reference;
   typedef typename A::const_reference          const_reference;

   /* iterators */
   inline iterator begin () { return v; }
   inline const_iterator begin () const { return v; }
   inline iterator end () { return v + size (); }
   inline const_iterator end () const { return v + size(); }

   reverse_iterator rbegin () { return reverse_iterator(end()); }
   const_reverse_iterator rbegin () const { return const_reverse_iterator(end()); }
   reverse_iterator rend () { return reverse_iterator(begin()); }
   const_reverse_iterator rend () const { return const_reverse_iterator(begin()); }

   /* element access */
   reference operator[] (size_type n) { return v[n]; }
   const_reference operator[] (size_type n) const { return v[n]; }
   reference at (size_type n) { 
     if (n >= size()) throw std::out_of_range("Out of range");
     return v[n];
    }
   const_reference at (size_type n) const {
     if (n >= size()) throw std::out_of_range("Out of range");
     return v[n];
    }
   reference front () { return *v; }
   const_reference front () const { return *v; }
   reference back () { iterator last = end() - 1; return *last; }
   const_reference back () const { const_iterator last = end() - 1; return *last; }

   /* constructors, etc.*/
   explicit vector (const A& a = A()) 
    : alloc(a), N(0), C(0) { 
      v = alloc.allocate(C);
   }

   explicit vector (size_type n, const T& val = T(), const A& a = A())
    : alloc(a), N(n), C(n) {
      v = alloc.allocate(C);
      for (iterator p = v; p < v + n; ++p) alloc.construct (p, val);
    }

   ~vector() { 
     for (iterator p = v; p < v + size(); ++p) alloc.destroy (p);
     alloc.deallocate(v, C); 
    }

   template <typename In>
   vector (In first, In last, const A& a = A(), 
     typename ft::enable_if<!ft::is_integral<In>::value, In>::type* = NULL) : alloc(a) {
     difference_type n = std::distance(first, last);
     C = n; N = n;
     v = alloc.allocate(C);
     for (iterator p = v; p < v + size(); ++p) {
      alloc.construct (p, *first++);
    }
   }
   
   vector(const vector& x) : alloc(x.alloc), N(x.N), C(x.C)  {
     v = alloc.allocate(C);
     for (iterator p = v, it = x.v; p < v + size(); ++p) {
      alloc.construct (p, *it++);
    }
   }

   vector& operator= (const vector& x) {
     if (this != &x) {
       assign(x.begin(), x.end());
     } 
     return *this;
   }

   void assign (size_type n, const T& val)
   {
     clear();
     if (n > capacity ()) {
       size_type n_c = n > capacity() * 2 ? n : capacity() * 2; 
       reserve(n_c);
     }
     iterator q = v;
     while(q < v + n)
        alloc.construct(q++, val);
     N = n;
   }

   template <typename In>
   void assign (In first, In last,
   typename ft::enable_if<!ft::is_integral<In>::value, In>::type* = NULL) {
     clear();
     difference_type n = std::distance(first, last);
     if ((size_type) n > capacity ()) {
       size_type n_c = (size_type)n > capacity() * 2 ? (size_type)n : capacity() * 2; 
       reserve(n_c);
     }
     iterator q = v;
     while (q < v + n)
        alloc.construct(q++, *first++); 
     N = n;
   }

   /* stack operations */
   void push_back (const T& x) { resize(size() + 1, x); }
   void pop_back () { resize(size() - 1); }

   /* list-like operations */
   iterator insert (iterator pos, const T& x) {
       difference_type diff = std::distance(begin(), pos);
       if (size() == capacity ()) { reserve(capacity() * 2); }
       iterator q = begin() + diff;
       memmove(q + 1, q, (end() - q) * sizeof(value_type));
       alloc.construct(q, x);
       ++N;
       return q;
   }

   void insert (iterator pos, size_type n, const T& x) {
       difference_type diff = std::distance(begin(), pos);
       if (size() + n >= capacity ()) { 
        size_type n_c = (size() + n) > capacity() * 2 ? (size() + n) : capacity() * 2; 
        reserve(n_c);
        }
       iterator q = begin() + diff;
       memmove(q + n, q, (end() - q) * sizeof(value_type));
       for (iterator p = q; p < q + n; ++p) { alloc.construct(p, x); }
       N += n;
   }

   template <typename In>
   void insert (iterator pos, In first, In last,
   typename ft::enable_if<!ft::is_integral<In>::value, In>::type* = NULL) {
       difference_type diff = std::distance(begin(), pos);
       difference_type n = std::distance(first, last);
       if (size() + n >= capacity ()) { 
        size_type n_c = (size() + n) > capacity() * 2 ? (size() + n) : capacity() * 2; 
        reserve(n_c);
        }
       iterator q = begin() + diff;
       memmove(q + n, q, (end() - q) * sizeof(value_type));
       for (iterator p = q; p < q + n; ++p) { alloc.construct(p, *first++);}
       N += n;
   }

   iterator erase (iterator pos){
     if (pos == end()) return end();
     alloc.destroy(pos);
     memmove(pos, pos + 1, (end() - pos) * sizeof(value_type));
     --N;
     return pos;
   }

   iterator erase (iterator first, iterator last){
     if (last <= first || last > end()) return last;
     for(iterator q = first; q != last; ++q) alloc.destroy(q);
     memmove(first, last, (end() - last) * sizeof(value_type));
     N -= last - first;
     return first;
   }
   
   inline void clear () { 
     erase(begin(), end()); 
    }

   /* capacity */
   inline size_type size () const { return N; };
   inline bool empty () const { return size() == 0; }
   inline size_type max_size () const { return std::allocator_traits<allocator_type>::max_size(alloc); }
   inline size_type capacity () const { return C; }
   void resize (size_type sz, T val = T()) {
     if (sz > max_size()) return;
     if (sz <= size()){ 
       iterator q = v + sz;
       while (q < v + size()) alloc.destroy(q++);
       N = sz; 
       return; }
     if (sz > capacity ()) {
       size_type n_c = sz > capacity() * 2 ? sz : capacity() * 2; 
       reserve(n_c);
     }
     iterator q = v + size();
     while(q < v + sz) alloc.construct(q++, val);
     N = sz;
   }
   void reserve (size_type n) {
     if (n < capacity()) return;
     iterator p = alloc.allocate(n);
     iterator q = v;
     while(q < v + size()){
       alloc.construct(p++, *q);
       alloc.destroy(q++);
     }
     alloc.deallocate(v, capacity());
     v = p - size();
     C = n;
   }

   /* other */
   void swap (vector& x) {
	  std::swap(v, x.v);
	  std::swap(N, x.N);
	  std::swap(C, x.C);
	  std::swap(alloc, x.alloc);
   }
   
   allocator_type get_allocator () const { return alloc; }

private:
   A alloc;
   iterator v;
   size_type N;
   size_type C;
 };
   
   template<class T, class A>
   bool operator== (const vector<T, A>& x, const vector<T, A>& y){
    return (x.size() == y.size()) && ft::equal(x.begin(), x.end(), y.begin());
   }

   template<class T, class A>
   bool operator< (const vector<T, A>& x, const vector<T, A>& y){
    return ft::lexicographical_compare (x.begin(), x.end(), y.begin(), y.end());
   }
   
   template<class T, class A>
   bool operator> (const vector<T, A>& x, const vector<T, A>& y) {
     return y < x;
   }
   template<class T, class A>
   bool operator!= (const vector<T, A>& x, const vector<T, A>& y) {
    return !(x == y); 
   }
   template<class T, class A>
   bool operator>= (const vector<T, A>& x, const vector<T, A>& y) {
     return !(x < y);
   }
   template<class T, class A>
   bool operator<= (const vector<T, A>& x, const vector<T, A>& y) {
     return !(y < x);
   }

   template<class T, class A>
   void swap(vector<T,A>& x, vector<T,A>& y){
    x.swap(y);
   }
}

#endif

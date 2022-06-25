#ifndef _SET_HPP_
#define _SET_HPP_

#include <functional>
#include <memory>
#include "rb_tree.hpp"
#include "equal_compare.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"

namespace ft
{
 template <class Key, class Cmp=std::less<Key>, class A=std::allocator<Key> >
 class set
 {
  public:
    /* types */
    typedef Key                                          value_type;
    typedef Key                                          key_type;

    typedef Cmp                                          value_compare;
    typedef Cmp                                          key_compare;
    typedef A                                            allocator_type;
    typedef ft::Node<value_type>									node_type;
    typedef node_type*                                   node_pointer;

    typedef typename A::reference                        reference;
    typedef typename A::const_reference                  const_reference;
    typedef typename A::size_type                        size_type;
    typedef typename A::difference_type                  difference_type;
    typedef typename A::pointer                          pointer;
    typedef typename A::const_pointer                    const_pointer;

    typedef ft::RBTree<value_type, key_compare, allocator_type>   tree_type;
    typedef typename tree_type::iterator                          iterator;
    typedef typename tree_type::const_iterator                    const_iterator;
    typedef typename ft::reverse_iterator<iterator>               reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>         const_reverse_iterator;
    
   private:
    tree_type        tree;
    key_compare      cmp;
    allocator_type   alloc;

   public:
    /* iterators */
    inline iterator begin () { return tree.begin(); }
    inline const_iterator begin () const { return tree.begin(); }
    inline iterator end () { return tree.end(); }
    inline const_iterator end () const { return tree.end(); }

    inline reverse_iterator rbegin () { return tree.rbegin(); }
    inline const_reverse_iterator rbegin () const { return tree.rbegin(); }
    inline reverse_iterator rend () { return tree.rend(); }
    inline const_reverse_iterator rend () const { return tree.rend(); }

    /* constructors, etc. */
    explicit set (const Cmp& c=Cmp(), const A& a= A()) 
     : tree(), cmp(c), alloc(a) { }

    template<class In>
    set (In first, In last, const Cmp& c=Cmp(), const A& a= A()) { 
       cmp = c;
       alloc = a;
       for (In tmp = first; tmp != last; ++tmp)
         tree.insertNode(*tmp);
    }

    set (const set<Key, Cmp, A>& other) { *this = other; }
    ~set() { }

    set& operator= (const set& other) { 
       if (*this != other) {
          tree = other.tree;
          alloc = other.alloc;
          cmp = other.cmp;
       }
       return *this;
    }

    key_compare key_comp() const { return cmp; }
    value_compare value_comp() const { return cmp; }

    /* lookups */
    iterator find (const key_type& k) {
       node_pointer found = tree.findNode(k);
       if (found != NULL) return iterator(found, tree);
       return end();
    }

    const_iterator find (const key_type& k) const { 
      node_pointer found = tree.findNode(k);
       if (found != NULL) return const_iterator(found, tree);
       return end();
    }

    size_type count (const key_type& k) const {
       if (tree.findNode(k) != NULL)
         return 1;
       return 0;
    }

    iterator lower_bound (const key_type& k) {
       for (iterator it = begin(); it != end(); ++it)
         if (cmp(k, it.getNode()->data) || !cmp(it.getNode()->data, k))
            return it;
       return end();
    }

    const_iterator lower_bound (const key_type& k) const { 
       for (const_iterator it = begin(); it != end(); ++it)
         if (cmp(k, it.getNode()->data) || !cmp(it.getNode()->data, k))
            return it;
       return end();
    }

    iterator upper_bound (const key_type& k) {
       for (iterator it = begin(); it != end(); ++it)
         if (cmp(k, it.getNode()->data))
            return it;
       return end();
    }

    const_iterator upper_bound (const key_type& k) const { 
       for (const_iterator it = begin(); it != end(); ++it)
         if (cmp(k, it.getNode()->data))
            return it;
       return end();
    }

    pair <iterator, iterator> equal_range (const key_type& k) { 
       return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    pair <const_iterator, const_iterator> 
    equal_range (const key_type& k) const {
      return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    /* list operations */
    pair <iterator, bool> insert (const value_type& val) { 
       return tree.insertNode(val);
    }

    iterator insert (iterator pos, const value_type& val) { 
       (void) pos;
       return tree.insertNode(val).first;
    }

    template<class In> 
    void insert (In first, In last) {
       for (In tmp = first; tmp != last; )
         tree.insertNode(*(tmp++));
    }

    void erase (iterator pos) {
       tree.erase(pos);
    }

    size_type erase (const key_type& k) {
       iterator found = find(k);
       if (found != end()) {
          tree.erase(found);
          return 1;
       }
       return 0;
    }

    void erase (iterator first, iterator last) { 
       for (iterator it = first; it != last;)
         tree.erase(it++);
    }

    void clear () { tree.clear(); }

    /* capacity */
    size_type size () const { return tree.getSize(); }
    size_type max_size () const { return tree.max_size(); }
    bool empty () const { return tree.getSize() == 0; }
    
    void swap (set& other) {
       std::swap(alloc, other.alloc);
       std::swap(cmp, other.cmp);
       tree.swap(other.tree);
    }

    allocator_type get_allocator() const { return alloc; }

 };

    template<class Key, class Cmp, class A>
    bool operator== (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       if (x.size() != y.size()) return false;
       return ft::equal(x.begin(), x.end(), y.begin());
    }

    template<class Key, class Cmp, class A>
    bool operator!= (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       return !(x == y);
    }

    template<class Key, class Cmp, class A>
    bool operator< (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template<class Key, class Cmp, class A>
    bool operator> (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       return y < x;
    }

    template<class Key, class Cmp, class A>
    bool operator<= (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       return !(y < x);
    }

    template<class Key, class Cmp, class A>
    bool operator>= (const set<Key,Cmp,A>& x, const set<Key,Cmp,A>& y) {
       return !(x > y);
    }


    template<class Key, class Cmp, class A>
    void swap (set<Key,Cmp,A>& x, set<Key,Cmp,A>& y) { 
       x.swap(y);
    }
}

#endif

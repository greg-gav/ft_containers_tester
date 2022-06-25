#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <functional>
#include <memory>
#include "rb_tree.hpp"
#include "equal_compare.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"

namespace ft
{
 template <class Key, class T, class Cmp=std::less<Key>, 
            class A=std::allocator<pair<const Key, T> > >
 class map
 {
  public:
    class value_compare;
    /* types */
    typedef Key                           key_type;
    typedef T                             mapped_type;
    typedef pair<const Key, T>            value_type;

    typedef Cmp                           key_compare;
    typedef ft::Node<value_type>          node_type;
    typedef node_type*                    node_pointer;
    typedef A                             allocator_type;
    typedef typename A::reference         reference;
    typedef typename A::const_reference   const_reference;
    typedef typename A::size_type         size_type;
    typedef typename A::difference_type   difference_type;

    typedef ft::RBTree<value_type, value_compare, allocator_type>    tree_type;
    typedef typename tree_type::iterator                             iterator;
    typedef typename tree_type::const_iterator                       const_iterator;
    typedef ft::reverse_iterator<iterator>                           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;

    /* iterators */
    inline iterator begin () { return tree.begin(); }
    inline const_iterator begin () const { return tree.begin(); }
    inline iterator end () { return tree.end(); }
    inline const_iterator end () const { return tree.end(); }
 
    inline reverse_iterator rbegin () { return tree.rbegin(); }
    inline const_reverse_iterator rbegin () const { return tree.rbegin(); }
    inline reverse_iterator rend () { return tree.rend(); }
    inline const_reverse_iterator rend () const { return tree.rend(); }

    /* element access */
    mapped_type& operator[] (const key_type& k) {
       iterator res(find(k));
       if (res != end())
         return res->second;
       else {
          insert(ft::make_pair(k, mapped_type()));
          iterator res(find(k));
          return res->second;
       }
    }

    mapped_type& at (const key_type& k) { 
       iterator res = find(k);
       if (res != end())
         return res->second;
       else { throw std::out_of_range("Out of range"); }
    }

    const mapped_type& at (const key_type& k) const { 
       const_iterator res(find(k));
       if (res != end())
         return res->second;
       else { throw std::out_of_range("Out of range"); }
    }

    /* constructors, etc. */
    explicit map (const Cmp& c=Cmp(), const A& a= A())
     : tree(), cmp(c), alloc(a), val_cmp(value_compare()){ }

    template<class In> 
    map (In first, In last, const Cmp& c=Cmp(), const A& a=A()) {
       cmp = c;
       alloc = a;
       val_cmp = value_compare();
       for (In tmp = first; tmp != last; ++tmp)
         tree.insertNode(*tmp);
    }

    map (const map& other) { *this = other; }

    ~map() { }

    map& operator= (const map& other) {
       if (*this != other){
          tree = other.tree;
          alloc = other.alloc;
          cmp = other.cmp;
          val_cmp = other.val_cmp;
       }
       return *this;
    }

    /* comparisons */
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
     friend class map;
    protected:
     Cmp cmp;
   public:
     value_compare(Cmp c = Cmp()) : cmp(c) { }
     bool operator() (const value_type& x, const value_type& y) const
        { return cmp(x.first, y.first); }
    };

    key_compare key_comp () const { return cmp; }
    value_compare value_comp () const { return val_cmp; }

    /* lookups */
    iterator find (const key_type& k) {
       node_pointer found = tree.findNode(ft::make_pair(k, mapped_type()));
       if (found != NULL) return iterator(found, tree);
       return end();
    }

    const_iterator find (const key_type& k) const { 
      node_pointer found = tree.findNode(ft::make_pair(k, mapped_type()));
       if (found != NULL) return const_iterator(found, tree);
       return end();
    }

    size_type count (const key_type& k) const {
       if (tree.findNode(ft::make_pair(k, mapped_type())) != NULL)
         return 1;
       return 0;
    }

    iterator lower_bound (const key_type& k) {
       for (iterator it = begin(); it != end(); ++it)
         if (val_cmp(ft::make_pair(k, mapped_type()), it.getNode()->data)
         || !val_cmp(it.getNode()->data, ft::make_pair(k, mapped_type())))
            return it;
       return end();
    }

    const_iterator lower_bound (const key_type& k) const { 
       for (const_iterator it = begin(); it != end(); ++it)
         if (val_cmp(ft::make_pair(k, mapped_type()), it.getNode()->data)
         || !val_cmp(it.getNode()->data, ft::make_pair(k, mapped_type())))
            return it;
       return end();
    }

    iterator upper_bound (const key_type& k) {
       for (iterator it = begin(); it != end(); ++it)
         if (val_cmp(ft::make_pair(k, mapped_type()), it.getNode()->data))
            return it;
       return end();
    }

    const_iterator upper_bound (const key_type& k) const { 
       for (const_iterator it = begin(); it != end(); ++it)
         if (val_cmp(ft::make_pair(k, mapped_type()), it.getNode()->data))
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
        {
            tree.insertNode(*tmp);
            ++tmp;
        }
    }

    void erase (iterator pos) {
       tree.erase(pos);
    }

    size_type erase (const key_type& k) {
       iterator found(find(k));
       if (found == end()) { return 0; }
       tree.erase(found);
       return 1;
    }

    void erase (iterator first, iterator last) { 
       for (iterator it = first; it != last;)
         tree.erase((it++));
    }

    void clear () { tree.clear(); }

    /* capacity */
    size_type size () const { return tree.getSize(); }
    size_type max_size () const { return tree.max_size(); }
    bool empty () const { return tree.getSize() == 0; }
    
    void swap (map& other) {
       std::swap(alloc, other.alloc);
       std::swap(cmp, other.cmp);
       std::swap(val_cmp, other.val_cmp);
       tree.swap(other.tree);
    }
    
    allocator_type get_allocator() const { return alloc; }

   private:
      tree_type         tree;
      key_compare       cmp;
      allocator_type    alloc;
      value_compare     val_cmp;
 };

    template<class Key, class T, class Cmp, class A>
    bool operator== (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       if (x.size() != y.size()) return false;
       return ft::equal(x.begin(), x.end(), y.begin());
    }

    template<class Key, class T, class Cmp, class A>
    bool operator!= (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       return !(x == y);
    }

    template<class Key, class T, class Cmp, class A>
    bool operator< (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template<class Key, class T, class Cmp, class A>
    bool operator> (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       return y < x;
    }

    template<class Key, class T, class Cmp, class A>
    bool operator<= (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       return !(y < x);
    }

    template<class Key, class T, class Cmp, class A>
    bool operator>= (const map<Key,T,Cmp,A>& x, const map<Key,T,Cmp,A>& y) {
       return !(x > y);
    }

    template<class Key, class T, class Cmp, class A>
    void swap (map<Key,T,Cmp,A>& x, map<Key,T,Cmp,A>& y) {
       x.swap(y);
    }
}

#endif

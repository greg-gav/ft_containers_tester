#ifndef _EQUAL_COMPARE_HPP_
#define _EQUAL_COMPARE_HPP_

namespace ft
{
 /* equal */
 template <class InputIterator1, class InputIterator2>
 inline bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
 {
   while (first1 != last1) {
    if (!(*first1 == *first2))
        return false;
    ++first1; 
    ++first2;
   }
   return true;
 }

 template <class InputIterator1, class InputIterator2, class BinaryPredicate>
 inline bool equal ( InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, BinaryPredicate pred )
 {
   while (first1 != last1) {
    if (!pred(*first1, *first2))
        return false;
    ++first1;
    ++first2;
   }
   return true;
 }

 /* lexicographical_compare */
 template<class InputIt1, class InputIt2>
 inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
 {
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
 }

 template<class InputIt1, class InputIt2, class Compare>
 inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp)
 {
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
 }
}

#endif

#ifndef _PAIR_HPP_
#define _PAIR_HPP_

namespace ft
{
 template <typename T1, typename T2> struct pair 
 {
     typedef typename std::remove_const<T1>::type first_type;
     typedef typename std::remove_const<T2>::type second_type;
     
     first_type first;
     second_type second;

     pair() : first(T1()), second(T2()) { }
     pair(const T1& x, const T2& y) : first(x), second(y) { }
     pair& operator=(pair const& p) {
        first = p.first;
        second = p.second;
        return *this;
     }
     
     template <typename U, typename V>
     pair(const pair<U, V>&p) : first(p.first), second(p.second) { }  //pair type change

    operator const std::pair<T1,T2>() const {
        return std::pair<T1,T2>(first, second);
    }
    operator std::pair<T1,T2>() {
        return std::pair<T1,T2>(first, second);
    }

  };
 
  template<typename T1, typename T2> 
   pair<T1, T2> make_pair(T1 t1, T2 t2){
      return pair<T1, T2>(t1, t2);
  }
  template <typename T1, typename T2>
  inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y){
      return x.first == y.first && x.second == y.second;
  }

  template <typename T1, typename T2>
  inline bool operator==(const std::pair<T1, T2>& x, const pair<T1, T2>& y){
      return x.first == y.first && x.second == y.second;
  }
  
  template <typename T1, typename T2>
  inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y){
      return !(x == y);
  }
  
  template <typename T1, typename T2>
  inline bool operator!=(const std::pair<T1, T2>& x, const pair<T1, T2>& y){
      return !(x == y);
  }

  template <typename T1, typename T2>
  inline bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y){
      return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
  }
  
  template <typename T1, typename T2>
  inline bool operator> (const pair<T1, T2>& x, const pair<T1,T2>& y){
      return y < x;
  }
  
  template <typename T1, typename T2>
  inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y){
      return !(x < y);
  }
 
  template <typename T1, typename T2>
  inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y){
      return !(y < x);
  }
}

 #endif

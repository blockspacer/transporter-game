//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2008.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP
#define BOOST_INTERPROCESS_DETAIL_MPL_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

//#include <functional>

namespace boost {
namespace interprocess { 
namespace detail {

template <class T, T val>
struct integral_constant
{
   static const T value = val;
   typedef integral_constant<T,val> type;
};

template< bool C_ >
struct bool_ : integral_constant<bool, C_>
{
   static const bool value = C_;
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

typedef true_  true_type;
typedef false_ false_type;

typedef char yes_type;
struct no_type
{
   char padding[8];
};

template <bool B, class T = void>
struct enable_if_c {
  typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};

template <class T, class U>
class is_convertible
{
   typedef char true_t;
   class false_t { char dummy[2]; };
   static true_t dispatch(U);
   static false_t dispatch(...);
   static T trigger();
   public:
   enum { value = sizeof(dispatch(trigger())) == sizeof(true_t) };
};

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename T1
    , typename T2
    , typename T3
    >
struct if_
{
   typedef typename if_c<0 != T1::value, T2, T3>::type type;
};


template <class Pair>
struct select1st 
//   : public std::unary_function<Pair, typename Pair::first_type> 
{
   const typename Pair::first_type& operator()(const Pair& x) const 
   {  return x.first;   }

   const typename Pair::first_type& operator()(const typename Pair::first_type& x) const 
   {  return x;   }
};

// identity is an extension: it is not part of the standard.
template <class T>
struct identity 
//   : public std::unary_function<T,T> 
{
   const T& operator()(const T& x) const 
   { return x; }
};

}  //namespace detail { 
}  //namespace interprocess { 
}  //namespace boost {

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP


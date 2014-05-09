// Copyright Christian Neumüller 2012. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_STD_SHAREDPTR_CONVERTER_HPP_INCLUDED
#define LUABIND_STD_SHAREDPTR_CONVERTER_HPP_INCLUDED                           \
  LUABIND_STD_SHAREDPTR_CONVERTER_HPP_INCLUDED

#include <boost/config.hpp>

#include <luabind/shared_ptr_converter.hpp>
#include <memory> // shared_ptr

#include <luabind/detail/has_get_pointer.hpp>

#include <boost/get_pointer.hpp>

namespace luabind {
namespace detail {
namespace has_get_pointer_ {
template <class T> struct impl<std::shared_ptr<T>> {
  BOOST_STATIC_CONSTANT(bool, value = true);
  typedef boost::mpl::bool_<value> type;
};

template <class T>
struct impl<const std::shared_ptr<T>> : impl<std::shared_ptr<T>> {};

template <class T>
struct impl<volatile std::shared_ptr<T>> : impl<std::shared_ptr<T>> {};

template <class T>
struct impl<const volatile std::shared_ptr<T>> : impl<std::shared_ptr<T>> {};
}
}
using boost::get_pointer;
}

#endif
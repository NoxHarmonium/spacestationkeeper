// Copyright Daniel Wallin 2009. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Modified by Sean Dawson for std::shared_ptr 10/may/2014

#ifndef LUABIND_STD_SHARED_PTR_CONVERTER_090211_HPP
# define LUABIND_STD_SHARED_PTR_CONVERTER_090211_HPP

# include <luabind/get_main_thread.hpp>
# include <luabind/handle.hpp>
# include <luabind/detail/policy.hpp>
# include <memory>

namespace luabind {
  
  namespace detail
  {
    
    struct std_shared_ptr_deleter
    {
      std_shared_ptr_deleter(lua_State* L, int index)
      : life_support(get_main_thread(L), L, index)
      {}
      
      void operator()(void const*)
      {
        handle().swap(life_support);
      }
      
      handle life_support;
    };
    
  } // namespace detail
  
  template <class T>
  struct default_converter<std::shared_ptr<T> >
  : default_converter<T*>
  {
    template <class U>
    int match(lua_State* L, U, int index)
    {
      return default_converter<T*>::match(
                                          L, LUABIND_DECORATE_TYPE(T*), index);
    }
    
    template <class U>
    std::shared_ptr<T> apply(lua_State* L, U, int index)
    {
      T* raw_ptr = default_converter<T*>::apply(
                                                L, LUABIND_DECORATE_TYPE(T*), index);
      if (!raw_ptr)
        return std::shared_ptr<T>();
      return std::shared_ptr<T>(
                                  raw_ptr, detail::std_shared_ptr_deleter(L, index));
    }
    
    void apply(lua_State* L, std::shared_ptr<T> const& p)
    {
      if (detail::std_shared_ptr_deleter* d =
          std::get_deleter<detail::std_shared_ptr_deleter>(p))
      {
        d->life_support.push(L);
      }
      else
      {
        detail::value_converter().apply(L, p);
      }
    }
    
    template <class U>
    void converter_postcall(lua_State*, U const&, int)
    {}
  };
  
  template <class T>
  struct default_converter<std::shared_ptr<T> const&>
  : default_converter<std::shared_ptr<T> >
  {};
  
} // namespace luabind

#endif // LUABIND_SHARED_PTR_CONVERTER_090211_HPP

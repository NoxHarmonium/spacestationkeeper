// Copyright Daniel Wallin 2007. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is a copy of iterator_policy.hpp but modified to work with pointers so it will work with values returned from functions. The original one will break with memory errors if you return an iterator from a function, presumably because the object goes out of scope and LuaBind keeps the references to the deleted object in the form of iterators. This version allows you to use shared_ptr.  objects to maintain the object in memory. You still need to hold a reference to the iterated object in memory somewhere so it doesn't get cleaned up (a field in a class)

#ifndef LUABIND_ITERATOR_POLICY__071111_HPP
# define LUABIND_ITERATOR_POLICY__071111_HPP

# include <memory>
# include <luabind/config.hpp>
# include <luabind/detail/policy.hpp>
# include <luabind/detail/convert_to_lua.hpp>

namespace luabind { namespace detail {

template <class Iterator, class Container>
struct iterator
{
    static int next(lua_State* L)
    {
        iterator* self = static_cast<iterator*>(
            lua_touserdata(L, lua_upvalueindex(1)));

        if (self->first != self->last)
        {
            convert_to_lua(L, *self->first);
            ++self->first;
        }
        else
        {
            lua_pushnil(L);
        }

        return 1;
    }

    static int destroy(lua_State* L)
    {
        iterator* self = static_cast<iterator*>(lua_touserdata(L, 1));
        self->~iterator();
        return 0;
    }

    iterator(Iterator first, Iterator last, std::shared_ptr<Container> ref)
      : first(first)
      , last(last),
        ref(ref)
    {}

    Iterator first;
    Iterator last;
   std::shared_ptr<Container> ref; // ref to keep shared_ptr alive
};

template <class Iterator, class Container>
int make_range(lua_State* L, Iterator first, Iterator last, std::shared_ptr<Container> c)
{
    void* storage = lua_newuserdata(L, sizeof(iterator<Iterator, Container>));
    lua_newtable(L);
    lua_pushcclosure(L, iterator<Iterator, Container>::destroy, 0);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    lua_pushcclosure(L, iterator<Iterator, Container>::next, 1);
    new (storage) iterator<Iterator, Container>(first, last, c);
    return 1;
}

template <class Container>
  int make_range(lua_State* L, std::shared_ptr<Container> container)
{
    return make_range(L, container->begin(), container->end(), container);
}

struct iterator_converter
{
    typedef iterator_converter type;

    template <class Container>
    void apply(lua_State* L, std::shared_ptr<Container> container)
    {
        make_range(L, container);
    }
};

struct iterator_policy : conversion_policy<0>
{
    static void precall(lua_State*, index_map const&)
    {}

    static void postcall(lua_State*, index_map const&)
    {}

    template <class T, class Direction>
    struct apply
    {
        typedef iterator_converter type;
    };
};

}} // namespace luabind::detail

namespace luabind { namespace {

LUABIND_ANONYMOUS_FIX detail::policy_cons<
    detail::iterator_policy, detail::null_type> return_stl_iterator;

}} // namespace luabind::unnamed

#endif // LUABIND_ITERATOR_POLICY__071111_HPP


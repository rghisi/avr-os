cmake_minimum_required(VERSION 3.27)

project(avr-libstdcpp CXX C)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_NAME avr-libstdcpp)
set(LIBRARY_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(LIBRARY_HEADERS
    include/algorithm
        include/any
        include/array
        include/bit
        include/bitset
        include/cassert
        include/ccomplex
        include/cctype
        include/cerrno
        include/cfenv
        include/cfloat
        include/chrono
        include/cinttypes
        include/ciso646
        include/climits
        include/cmath
        include/compare
        include/complex
        include/concepts
        include/coroutine
        include/csetjmp
        include/csignal
        include/cstdalign
        include/cstdarg
        include/cstdbool
        include/cstddef
        include/cstdint
        include/cstdio
        include/cstdlib
        include/cstring
        include/ctgmath
        include/ctime
        include/cuchar
        include/cwchar
        include/cwctype
        include/deque
        include/forward_list
        include/functional
        include/initializer_list
        include/iterator
        include/limits
        include/list
        include/map
        include/memory
        include/new
        include/numbers
        include/numeric
        include/optional
        include/queue
        include/random
        include/ranges
        include/ratio
        include/scoped_allocator
        include/set
        include/span
        include/stack
        include/string_view
        include/tuple
        include/type_traits
        include/unordered_map
        include/unordered_set
        include/utility
        include/valarray
        include/variant
        include/vector
        include/version
#        include/backward/backward_warning.h
#        include/backward/binders.h
#        include/backward/hash_fun.h
#        include/backward/hash_map
#        include/backward/hash_set
#        include/backward/hashtable.h
#        include/bits/algorithmfwd.h
#        include/bits/alloc_traits.h
#        include/bits/allocated_ptr.h
#        include/bits/allocator.h
#        include/bits/boost_concept_check.h
#        include/bits/c++0x_warning.h
#        include/bits/c++allocator.h
#        include/bits/c++config.h
#        include/bits/char_traits.h
#        include/bits/charconv.h
#        include/bits/concept_check.h
#        include/bits/cpp_type_traits.h
#        include/bits/cxxabi_forced.h
#        include/bits/cxxabi_init_exception.h
#        include/bits/deque.tcc
#        include/bits/enable_special_members.h
#        include/bits/erase_if.h
#        include/bits/exception_defines.h
#        include/bits/forward_list.h
#        include/bits/forward_list.tcc
#        include/bits/functexcept.h
#        include/bits/functional_hash.h
#        include/bits/gslice.h
#        include/bits/gslice_array.h
#        include/bits/hash_bytes.h
#        include/bits/hashtable.h
#        include/bits/hashtable_policy.h
#        include/bits/indirect_array.h
#        include/bits/invoke.h
#        include/bits/iterator_concepts.h
#        include/bits/list.tcc
#        include/bits/mask_array.h
#        include/bits/memoryfwd.h
#        include/bits/move.h
#        include/bits/node_handle.h
#        include/bits/parse_numbers.h
#        include/bits/postypes.h
#        include/bits/predefined_ops.h
#        include/bits/ptr_traits.h
#        include/bits/random.h
#        include/bits/random.tcc
#        include/bits/range_access.h
#        include/bits/range_cmp.h
#        include/bits/ranges_algo.h
#        include/bits/ranges_algobase.h
#        include/bits/ranges_uninitialized.h
#        include/bits/refwrap.h
#        include/bits/slice_array.h
#        include/bits/std_abs.h
#        include/bits/std_function.h
#        include/bits/stl_algo.h
#        include/bits/stl_algobase.h
#        include/bits/stl_bvector.h
#        include/bits/stl_construct.h
#        include/bits/stl_deque.h
#        include/bits/stl_function.h
#        include/bits/stl_heap.h
#        include/bits/stl_iterator.h
#        include/bits/stl_iterator_base_funcs.h
#        include/bits/stl_iterator_base_types.h
#        include/bits/stl_list.h
#        include/bits/stl_map.h
#        include/bits/stl_multimap.h
#        include/bits/stl_multiset.h
#        include/bits/stl_numeric.h
#        include/bits/stl_pair.h
#        include/bits/stl_queue.h
#        include/bits/stl_raw_storage_iter.h
#        include/bits/stl_relops.h
#        include/bits/stl_set.h
#        include/bits/stl_stack.h
#        include/bits/stl_tempbuf.h
#        include/bits/stl_tree.h
#        include/bits/stl_uninitialized.h
#        include/bits/stl_vector.h
#        include/bits/string_view.tcc
#        include/bits/uniform_int_dist.h
#        include/bits/unique_ptr.h
#        include/bits/unordered_map.h
#        include/bits/unordered_set.h
#        include/bits/uses_allocator.h
#        include/bits/valarray_after.h
#        include/bits/valarray_array.h
#        include/bits/valarray_array.tcc
#        include/bits/valarray_before.h
#        include/bits/vector.tcc
#        include/debug/assertions.h
#        include/debug/debug.h
#        include/debug/formatter.h
#        include/debug/functions.h
#        include/debug/helper_functions.h
#        include/debug/macros.h
#        include/decimal/decimal
#        include/decimal/decimal.h
#        include/ext/algorithm
#        include/ext/aligned_buffer.h
#        include/ext/alloc_traits.h
#        include/ext/cmath
#        include/ext/functional
#        include/ext/hash_map
#        include/ext/hash_set
#        include/ext/iterator
#        include/ext/malloc_allocator.h
#        include/ext/memory
#        include/ext/new_allocator.h
#        include/ext/numeric
#        include/ext/numeric_traits.h
#        include/ext/pod_char_traits.h
#        include/ext/rb_tree
#        include/ext/slist
#        include/ext/type_traits.h
#        include/ext/typelist.h
)

set(LIBRARY_SOURCE
#        src/functexcept.cc
#        src/hash_bytes.cc
#        src/hashtable-aux.h
#        src/hashtable_c++0x.cc
#        src/limits.cc
#        src/list.cc
#        src/math.cc
#        src/new_handler.cc
#        src/tree.cc
)

add_library(${LIBRARY_NAME} STATIC
        ${LIBRARY_HEADERS}
        ${LIBRARY_SOURCE}
)

target_include_directories(${LIBRARY_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(${LIBRARY_NAME} PRIVATE
        ${LIBRARY_SOURCE}
)
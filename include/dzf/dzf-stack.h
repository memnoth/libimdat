/*
 * MIT License
 *
 * Copyright (c) 2018-2021 Leesoo Ahn <lsahn@ooseel.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*! @file dzf-stack.h
 *
 * @brief Stack data structure.
 * 
 * Stack is a data structure based on LIFO, also known as Last In First Out.
 * 
 * dzf-stack provides two stack types,
 * - \b Static stack. Once it is built, the length of it never changed.
 * - \b Dynamic stack. It grows up and down anytime if it needs to be resized.
 * 
 * Default: Static stack.  
 * Add \b -DDZF_DYNAMIC_STACK compile flag to switch.
 * 
 * When no space condition is met with \b -DDZF_DYNAMIC_STACK , the capacity 
 * would be multiplied by 2 for every extension as vector.
 * @code
 *   16 // default capacity
 *   32
 *   64
 *   128
 *   256
 * @endcode
 */

#ifndef __DZF_STACK_H__
#define __DZF_STACK_H__

#include "dzf-stack-priv.h"

#define DFLT_STACK_CAP 16

/*!
 * Initialize a stack with required capacity size.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _cap_sze: Capacity.
 * @return None
 */
DZF_PUBLIC
#define dzf_stack_new_with(_stkptr, _cap_sze) \
    _dzf_stack_priv_init(_stkptr, _cap_sze)


/*!
 * Initialize a stack with default capacity (DFLT_STACK_CAP).
 * 
 * This is available with \b DZF_DYNAMIC_STACK flag.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
DZF_PUBLIC
#define dzf_stack_new(_stkptr) \
    dzf_stack_new_with(_stkptr, DFLT_STACK_CAP)


/*!
 * Free allocated memory to the data member.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
DZF_PUBLIC
#define dzf_stack_free(_stkptr) \
    for ( free((_stkptr)->data), \
          (_stkptr)->data = NULL; \
          FALSE; )


/*!
 * Get how many elements it has.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c int
 */
DZF_PUBLIC
#define dzf_stack_size(_stkptr) \
    _dzf_stack_top(_stkptr)+1


/*!
 * Get capacity of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c int
 */
DZF_PUBLIC
#define dzf_stack_cap(_stkptr) \
    ((_stkptr)->capacity)


/*!
 * Check whether it is empty or not.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return TRUE if it is empty, or FALSE.
 */
DZF_PUBLIC
#define dzf_stack_is_empty(_stkptr) \
    ( _dzf_stack_top(_stkptr) == -1 ? TRUE : FALSE )


/*!
 * Check whether it is full or not.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return TRUE if it is full, or FALSE.
 */
DZF_PUBLIC
#define dzf_stack_is_full(_stkptr) \
    ( dzf_stack_size(_stkptr) == dzf_stack_cap(_stkptr) ? TRUE : FALSE )


/*!
 * Push a data at the top of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param value: \c T typed value.
 * @return None
 */
DZF_PUBLIC
#define dzf_stack_push(_stkptr, value) \
    for ( _dzf_stack_priv_extend(_stkptr), \
          ++_dzf_stack_top(_stkptr), \
          (_stkptr)->data[_dzf_stack_top(_stkptr)] = value; \
          FALSE; /* must be false not to loop. */ )


/*!
 * Pop a data at the top of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c T typed value.
 */
DZF_PUBLIC
#define dzf_stack_pop(_stkptr) \
    ( assert(dzf_stack_is_empty(_stkptr) == FALSE), \
      --_dzf_stack_top(_stkptr), \
      (_stkptr)->data[dzf_stack_size(_stkptr)] )


/*!
 * Get a data at the top of the stack.
 * 
 * <i>Note that this does not remove the data as dzf_stack_pop.</i>
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c T typed value.
 */
DZF_PUBLIC
#define dzf_stack_at_top(_stkptr) \
    ( assert(dzf_stack_is_empty(_stkptr) == FALSE), \
      (_stkptr)->data[_dzf_stack_top(_stkptr)] )


/*!
 * Do something with the function through all elements.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _fptr: A pointer to a function that will be called.
 * @param ...: Various arguments to be passed into the function.
 * @return None
 */
DZF_PUBLIC
#define dzf_stack_foreach(_stkptr, _fptr, ...) \
    for ( int i = 0; \
          i < dzf_stack_size(_stkptr); \
          (_fptr)(&((_stkptr)->data[i]), __VA_ARGS__), ++i )
        

#endif

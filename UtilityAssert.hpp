/*!
 *    @file             $Source: common/utility/UtilityAssert.h $
 *    @brief            Header for Utility Asserts
 *
 *    @author           $Author: David Vescovi (dvescovi) $
 *
 *    @version          $Revision: 1.2 $
 *
 *    @date             $Date: 2018/01/31 19:49:10EST $
 *
 *    @par Copyright
 *                      (C) 2020 Medtronic. All rights reserved.
 */

#ifndef UTILITYASSERT_H_
#define UTILITYASSERT_H_

#ifdef __cplusplus
    extern "C" {
#endif

    /// Callback function for when a utility asserts
extern void UtilityOnAssert(char const *file, int line) __attribute__ ((noreturn));

#ifdef __cplusplus
    }
#endif

// TODO: remove this definition and all its uses since it was givin problems when used in headers.
// this will probably never be done, but it doesn't harm. yet.
#define U_DEFINE_THIS_MODULE(name_)

#ifdef UTILITY_NO_ASSERT

#define U_DEFINE_THIS_FILE

#define U_ASSERT(expr)

#else

#define U_DEFINE_THIS_FILE static char const U_THIS_MODULE[] = __FILE__;

#define U_ASSERT(expr) do                                                       \
                     {                                                        \
                         if(!(expr))                                          \
                         {                                                    \
                             UtilityOnAssert(__FILE__, __LINE__);    \
                         }                                                    \
                     }                                                        \
                     while(0)

#endif// UTILITY_NO_ASSERT


#endif /* UTILITYASSERT_H_ */

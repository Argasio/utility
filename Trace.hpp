/*
 * Trace.hpp
 *
 *  Created on: Dec 12, 2021
 *      Author: Argasio
 */
#include <stdarg.h>
#ifndef TRACE_HPP_
#define TRACE_HPP_
#ifdef QSPY
#include "qpcpp.hpp"  // QP/C++ framework API
#endif


#define TRACE(format, ...) InterfaceTrace(format, ##__VA_ARGS__)
#ifdef __cplusplus
extern "C" {
#endif
void InterfaceTrace(const char* string, ...);
#ifdef __cplusplus
}
#endif



#endif /* TRACE_HPP_ */

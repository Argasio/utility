/*
 * Trace.cpp
 *
 *  Created on: Dec 12, 2021
 *      Author: Argasio
 */


#include <string.h>
#include <stdint.h>
#include <Trace.hpp>
//#include <peripheralHandles.h>
#include<stdio.h>
#ifdef QSPY
#include "qpcpp.hpp"  // QP/C++ framework API
#endif
#ifndef TRACE_BUFFER_SIZE
#define TRACE_BUFFER_SIZE 250
#endif
void InterfaceTrace(const char* string, ...)
{
    // Trace if filter allows
    char vsbuf[TRACE_BUFFER_SIZE];

    va_list args;
    va_start(args, string);
    vsnprintf(vsbuf, TRACE_BUFFER_SIZE, string, args);
    va_end(args);
#ifdef QSPY
    // Send String using QSPY User level 0 interface layer message
    QS_BEGIN_ID(QP::QS_USER, 0U)
    QS_STR(vsbuf);
    QS_END()
#endif
}



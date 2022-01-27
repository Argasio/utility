/*!
 *    @file             $Source: common/utility/Fifo.h $
 *    @brief            Header for Fifo Class.
 *
 *    @author           $Author: David Vescovi (dvescovi) $
 *
 *    @version          $Revision: 1.2 $
 *
 *    @date             $Date: 2018/01/31 19:49:02EST $
 *
 *    @par Copyright
 *                      (C) 2020 Medtronic. All rights reserved.
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <cstddef>
#include <cstdint>

namespace Utility
{


template<class T>
class Fifo
{
public:

    /// Create a fifo using the passed buffer for storage
    Fifo(T* buffer, size_t buffSize) :
        buffer(buffer), buffSize(buffSize)
    {
        // Init pointers to start of buffer, when they are equal it means empty
        pPut = &buffer[0];
        pGet = &buffer[0];
    }

    bool IsEmpty()
    {
        return(pPut == pGet);
    }

    void Flush()
    {
        T dummyRead;
        while(Get(&dummyRead))
        {

        }
    }

    /// Put data into the buffer
    bool Put(T data)
    {
        // Where would we put the next one?
        T volatile* nextPut = pPut + 1;

        // Check for wrap
        if(nextPut == &buffer[buffSize])
        {
            // Wrap
            nextPut = &buffer[0];
        }

        // Check for full
        if(nextPut == pGet)
        {
            // Put failed
            return false;
        }
        else
        {
            // Not full, add data
            *pPut = data; // Move data into FIFO
            pPut = nextPut; // Move pointer
            return true;
        }
    }

    /// Check if there is space in the FIFO
    bool HasRoom()
    {
        // Where would we put the next one?
        T volatile* nextPut = pPut + 1;

        // Check for wrap
        if(nextPut == &buffer[buffSize])
        {
            // Wrap
            nextPut = &buffer[0];
        }

        // Check for full
        if(nextPut == pGet)
        {
            // Put failed
            return false;
        }
        else
        {
            return true;
        }
    }

    bool Get(T* data)
    {
        if(pPut == pGet)
        {
            return false; // We are empty
        }
        *data = *(pGet++);  // Copy return data and move read pointer

        // Check for wrap
        if(pGet == &buffer[buffSize])
        {
            pGet = &buffer[0];
        }
        return true;
    }

    uint32_t BuffUsed()
    {
        // Check for wrap
        if(pPut > pGet)
        {
        	return static_cast<uint32_t>(pPut - pGet);
        }
        else
        {
        	return static_cast<uint32_t>((&buffer[buffSize] - pGet) + (pPut - &buffer[0]));
        }
    }

private:
    T*          buffer;
    size_t      buffSize;
    T volatile* pPut;  // Next put pointer
    T volatile* pGet;  // Next get pointer
};

} /* namespace Utility */
#endif /* FIFO_H_ */

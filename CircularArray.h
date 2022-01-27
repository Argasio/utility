/*!
 *    @file             $Source: common/utility/CircularArray.h $
 *    @brief            Header for CircularArray Class.
 *
 *    @author           $Authors: nocim2 - ares2
 *
 *    @version          $Revision: 1.3 $
 *
 *    @date             $Date: 2019/2/12 17:32:12EDT $
 *
 *    @par Description
 *                      Header for CircularArray Class.
 *
 */

#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H
#include <UtilityAssert.hpp>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

namespace Utility
{
    template <class T = uint32_t, unsigned int MAX_SIZE = 10u>
    class CircularArray
    {
    private:
        T circularArray[MAX_SIZE];
        unsigned int idxNextStoreLocation;      //equ to idxHead, stores location where next value to be saved
        unsigned int idxOldestStoreLocation;    //equ to idxTail, stores location where the oldest value is stored
        unsigned int idxLatestStoreLocation;    //stores location where latest value is stored
        unsigned int workingSize;
        unsigned int currentStoredCount;
        bool isArrayFull;
        bool isArrayEmpty;

    public:
        CircularArray()
        {
            U_ASSERT(MAX_SIZE>1u);
            ClearArray();
        }
        void SetArraySize(unsigned int size)
        {
            U_ASSERT((size>1u)&&(size<=MAX_SIZE));
            ClearArray();
            workingSize = size;
        }

        void ClearArray()
        {
            idxNextStoreLocation = idxOldestStoreLocation = idxLatestStoreLocation = currentStoredCount = 0u;
            isArrayFull = false;
            isArrayEmpty = true;
            workingSize = MAX_SIZE;
            for(unsigned int i = 0u; i < workingSize; i++)
            {
                circularArray[i] = static_cast<T>(0);
            }
        }
        void Push(const T value)
        {
            circularArray[idxNextStoreLocation] = value;
            idxLatestStoreLocation = idxNextStoreLocation;
            idxNextStoreLocation = (idxNextStoreLocation + 1u) % workingSize;
            if (isArrayFull == true)
            {
                idxOldestStoreLocation = (idxOldestStoreLocation + 1u) % workingSize;
            }
            else
            {
                currentStoredCount ++;
                isArrayFull = (idxOldestStoreLocation == idxNextStoreLocation);
            }
            isArrayEmpty = false;
        }


        T Pop()
        {
            if(isArrayEmpty){
                currentStoredCount = 0;
                return static_cast<T>(0);
            }else{
                T poppedValue;
                poppedValue = circularArray[idxOldestStoreLocation];
                isArrayFull = false;
                circularArray[idxOldestStoreLocation] = static_cast<T>(0);
                idxOldestStoreLocation = (idxOldestStoreLocation + 1u) % workingSize;
                isArrayEmpty = (idxOldestStoreLocation == idxNextStoreLocation);
                currentStoredCount --;
                return poppedValue;
            }
        }

        T GetSum()
        {
            T sumValues = static_cast<T>(0);
            int sumIndex = idxOldestStoreLocation;
            if( (!isArrayFull) && (idxOldestStoreLocation == idxNextStoreLocation) )
            {
                return static_cast<T>(0);
            }
            do
            {
                sumValues += circularArray[sumIndex];
                sumIndex = (sumIndex + 1) % workingSize;
            }
            while(sumIndex != idxNextStoreLocation);
            return sumValues;
        }

        float GetAverage()
        {
            unsigned int averageIndex = idxOldestStoreLocation;
            unsigned int numberOfValues = 0u;
            T sumValues = static_cast<T>(0);
            if( (!isArrayFull) && (idxOldestStoreLocation == idxNextStoreLocation) )
            {
                return static_cast<T>(0);
            }
            do
            {
                sumValues += circularArray[averageIndex];
                averageIndex = (averageIndex + 1u) % workingSize;
                numberOfValues++;
            }
            while(averageIndex != idxNextStoreLocation);

            return static_cast<float>(sumValues/numberOfValues);
        }

        inline bool IsArrayFull()
        {
            return isArrayFull;
        }

        inline bool IsArrayEmpty()
        {
            return isArrayEmpty;
        }

        inline unsigned int returnCurrentCount()
        {
            return currentStoredCount;
        }

        float GetAbsoluteSlope (float mDiv)
        {
            if(((!isArrayFull) && (idxOldestStoreLocation == idxNextStoreLocation)) || (1u == currentStoredCount))
            {
                return 0.0f;
            }
            return fabsf((static_cast<float>(circularArray[idxLatestStoreLocation]) - static_cast<float>(circularArray[idxOldestStoreLocation])) /
                         (mDiv * static_cast<float>(currentStoredCount-1u)));
        }
    };
}
#endif

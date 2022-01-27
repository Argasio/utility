/*!
 * @file	/TherapyController/utility/ClientList.hpp
 *
 * @brief
 *
 * @par Copyright
 *    		COPYRIGHT (c) 2020 Medtronic Inc. All rights reserved.
 *
 * @author	akkans2
 *
 * @version	1.0
 *
 * @date	Oct 16, 2020 1:34:20 PM
 *
 */
#ifndef FIRMWARE_COMMON_UTILITY_CLIENTLIST_HPP_
#define FIRMWARE_COMMON_UTILITY_CLIENTLIST_HPP_

#include <cstdint>

namespace Utility {
template <class T, int MAX_SIZE>
class ClientList {
 public:
  ClientList() : myIteratorIdx_(0) {
    // Make sure list is nullptr
    for (uint32_t idx = 0; idx < mSIZE_; ++idx) {
      myList_[idx] = nullptr;
    }
  }

  /// Adds a client to the list
  /// @param client pointer to client
  /// @return true if successfully added
  inline bool Add(T* client) {
    bool foundSpot = false;
    for (int idx = 0; idx < mSIZE_; ++idx) {
      if (myList_[idx] == nullptr) {
        myList_[idx] = client;
        foundSpot = true;
        break;
      }
    }
    return foundSpot;
  }

  /// Removes a client from the list
  /// @param client pointer to client to remove
  /// @return true if successfully removed
  inline bool Remove(T* client) {
    bool foundClient = false;

    for (int idx = 0; idx < mSIZE_; ++idx) {
      if (myList_[idx] == client) {
        myList_[idx] = nullptr;
        foundClient = true;
        break;
      }
    }
    return foundClient;
  }

  /// Returns the first client
  /// @return first client or nullptr if empty
  /// @details You must call this first to iterate the list of clients
  inline T* GetFirst() {
    T* firstClient = nullptr;

    // Reset index for GetNext
    myIteratorIdx_ = 0;

    for (int idx = 0; idx < mSIZE_; ++idx) {
      if (myList_[idx] != nullptr) {
        firstClient = myList_[idx];
        myIteratorIdx_ = idx + 1;
        break;
      }
    }
    return firstClient;
  }

  /// Returns the next client
  /// @return next client or nullptr if done
  /// @details You must call GetFirst() before this
  inline T* GetNext() {
    T* nextClient = nullptr;

    for (int idx = myIteratorIdx_; idx < mSIZE_; ++idx) {
      if (myList_[idx] != nullptr) {
        nextClient = myList_[idx];
        myIteratorIdx_ = idx + 1;
        break;
      }
    }
    return nextClient;
  }

 private:
  // Static storage
  static const int mSIZE_ = MAX_SIZE;
  T* myList_[MAX_SIZE];
  int myIteratorIdx_;
};

}  // namespace Utility

#endif  // FIRMWARE_COMMON_UTILITY_CLIENTLIST_HPP_

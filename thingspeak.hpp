/*
 * thingspeak.hpp
 *
 *  Created on: Jan 27, 2022
 *      Author: Argasio
 */

#ifndef THINGSPEAK_HPP_
#define THINGSPEAK_HPP_

namespace THINGSPEAK{
	class ThingspeakChannel{
	public:
		ThingspeakChannel(unsigned int number,  const char* key):key(key),channelNumber(number){}
		bool buildWriteQuery(char* messageBuffer,  int paramNumbers[], float values[], unsigned int numberOfParams);
		bool buildReadQuery(char* messageBuffer, int paramNumber);
		bool parseParam(const char* msg, float& value, int paramNumber);
		bool parseFeed(const char* msg, float* values, int numberOfparams, int* paramNumbers);
		bool buildFeedReadQuery(char* messageBuffer);
	private:
		const char* key;
		unsigned int channelNumber;

	};


}



#endif /* THINGSPEAK_HPP_ */

/*
 * thingspeak.cpp
 *
 *  Created on: Jan 27, 2022
 *      Author: Argasio
 */

#include <thingspeak.hpp>
#include <string.h>
#include <stdio.h>
#include <math.h>
extern const char thingspeakIp[];
namespace THINGSPEAK{


bool ThingspeakChannel:: buildWriteQuery(char* messageBuffer,  int paramNumbers[], float values[], unsigned int numberOfParams){
	memset(messageBuffer,0,strlen(messageBuffer));
	sprintf(messageBuffer,"GET https://api.thingspeak.com/update?api_key=%s", key);
	for(unsigned int i = 0; i< numberOfParams; i++){
		sprintf(messageBuffer+strlen(messageBuffer), "&field%d=%.3f",paramNumbers[i],(float)values[i]);
	}
	sprintf(messageBuffer+strlen(messageBuffer),"=0");
	return true;
}

bool ThingspeakChannel:: buildReadQuery(char* messageBuffer, int paramNumber){
	memset(messageBuffer,0,strlen(messageBuffer));
	sprintf(messageBuffer,"GET https://api.thingspeak.com/channels/%d/fields/%d.json?api_key=%s&results=2", channelNumber,paramNumber, key);
	return true;

}

bool ThingspeakChannel:: buildFeedReadQuery(char* messageBuffer){
	memset(messageBuffer,0,strlen(messageBuffer));
	sprintf(messageBuffer,"GET https://api.thingspeak.com/channels/%d/feeds.json?api_key=%s&results=1", channelNumber, key);
	return true;

}

bool ThingspeakChannel::parseParam(const char* msg, float & value, int paramNumber){

	/*{"channel":{"id":1608001,"name":"innaffiatore","latitude":"0.0","longitude":"0.0","field1":"durata","field2":"pausa","created_at":"2021-12-14T21:30:14Z",
	 * "updated_at":"2021-12-14T21:30:14Z","last_entry_id":26},"feeds":[{"created_at":"2022-02-08T18:31:18Z","entry_id":26,"field2":"31"}]}*/

	//first get last entry ID

	char *lastEntryStrPtr = strstr(msg,"last_entry");
	if(!lastEntryStrPtr){
		return false;
	}
	lastEntryStrPtr = strstr(lastEntryStrPtr,":");
	int lastEntryId = atoi(lastEntryStrPtr+1);
	// then find the last entry
	char lastEntryStringToken[30] = "";
	sprintf(lastEntryStringToken, "entry_id\":%d",lastEntryId );
	char * lastEntryPtr = strstr(lastEntryStrPtr,lastEntryStringToken);
	if(!lastEntryPtr){
		return false;
	}
	char lastEntryStringFieldToken[30] = "";
	// get to the desired field
	sprintf(lastEntryStringFieldToken, "field%d",paramNumber );
	lastEntryPtr = strstr(lastEntryPtr,lastEntryStringFieldToken);

	if(!lastEntryPtr){
		return false;
	}
	// get to the value we desire
	lastEntryPtr = strstr(lastEntryPtr,":");
	//parse value
	value = atof(lastEntryPtr+2);
	return true;

}

bool ThingspeakChannel::parseFeed(const char* msg, float* values, int numberOfparams, int* paramNumbers){

	/*{"channel":{"id":1608001,"name":"innaffiatore","latitude":"0.0","longitude":"0.0","field1":"durata","field2":"pausa",
	 * "created_at":"2021-12-14T21:30:14Z","updated_at":"2021-12-14T21:30:14Z","last_entry_id":25},
	 * "feeds":[{"created_at":"2021-12-18T16:11:55Z","entry_id":24,"field1":"20"},
	 * {"created_at":"2022-01-27T17:07:10Z","entry_id":25,"field1":null}]}*/

	//first get last entry ID

	char *lastEntryStrPtr = strstr(msg,"last_entry");
	if(!lastEntryStrPtr){
		return false;
	}
	lastEntryStrPtr = strstr(lastEntryStrPtr,":");
	int lastEntryId = atoi(lastEntryStrPtr+1);
	// then find the last entry
	char lastEntryStringToken[30] = "";
	sprintf(lastEntryStringToken, "entry_id\":%d",lastEntryId );
	char * lastEntryPtr = strstr(lastEntryStrPtr,lastEntryStringToken);
	if(!lastEntryPtr){
		return false;
	}

	for(int i = 0; i<numberOfparams;i++){
		int currentField = paramNumbers[i];


		char lastEntryStringFieldToken[30] = "";
		char* lastFieldEntryPtr = lastEntryPtr;
		// get to the desired field
		sprintf(lastEntryStringFieldToken, "field%d",currentField );
		lastFieldEntryPtr = strstr(lastEntryPtr,lastEntryStringFieldToken);

		if(!lastFieldEntryPtr){
			return false;
		}
		// get to the value we desire
		lastFieldEntryPtr = strstr(lastFieldEntryPtr,":");
		//parse value
		values[i] = atof(lastFieldEntryPtr+2);
	}
	return true;

}
}// END OF NAMESPACE

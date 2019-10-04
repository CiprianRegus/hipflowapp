/*************************************************************************************************
 *
 * Workfile: cmd_14.h
 * 14Dec18 - stevev
 *
 *************************************************************************************************
 * The content of this file is the
 *     Proprietary and Confidential property of the FieldComm Group
 * Copyright (c) 2018, FieldComm Group, Inc., All Rights Reserved
 *************************************************************************************************
 *
 * Description: This holds one command
 *
 * #include "cmd_14.h"
 */

#ifndef CMD_14_H_
#define CMD_14_H_

#include "command.h"


class cmd_14 : public cmd_base
{

public: // c.dtor
	cmd_14():cmd_base(14) {	};
	~cmd_14(){};

public: // work	
	virtual uint8_t extractData(uint8_t &ByteCnt, uint8_t *pData);
	virtual uint8_t insert_Data(uint8_t &ByteCnt, uint8_t *pData);

};

// extract ByteCnt bytes from data at pData
// return zero on success, response code on error
uint8_t cmd_14::extractData(uint8_t &ByteCnt, uint8_t *pData)
{
	uint8_t ret = 0;

	// nothing to extract here

	return ret;
}


// generate reply
// add bytes from data to pData, filling ByteCnt with the number added (caller adds RC/DS)
// return zero on success, response code (with byte count 0) on error
uint8_t cmd_14::insert_Data(uint8_t &ByteCnt, uint8_t *pData) 
{
	int ret = 0;
	ByteCnt = 0; // just in case
	do // once
	{
		if ( ret = devVar_PV.sensorSerialNumber.insertSelf( &pData, &ByteCnt )  ) break;//0-2	Unsigned-24	Transducer Serial Number 
		if ( ret = devVar_PV.Units             .insertSelf( &pData, &ByteCnt )  ) break;//3	    Enum	Transducer Limits and Minimum Span Units Code (refer to Common Tables Specification)
		if ( ret = convertAndInsert(devVar_PV.upperSensorLimit, devVar_PV, &pData, &ByteCnt )  ) break;//4-7	Float	Upper Transducer Limit
		if ( ret = convertAndInsert(devVar_PV.lowerSensorLimit, devVar_PV, &pData, &ByteCnt )  ) break;//8-11	Float	Lower Transducer Limit
		if ( ret = convertAndInsert(devVar_PV.minSpan         , devVar_PV, &pData, &ByteCnt )  ) break;//12-15	Float	Minimum Span
	}
	while(false);// execute once

	if ( ret )
	{
		printf("Data insertion error in cmd %d. ret = %d.\n", number(), ret);
	}

    return ret;
};

#endif // CMD_14_H_
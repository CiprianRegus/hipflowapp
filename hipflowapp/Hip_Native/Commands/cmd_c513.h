/*************************************************************************************************2019-2021 FieldComm Group, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Description: This holds one command
 *
 * #include "cmd_513.h"
 */

#ifndef CMD_513_H_
#define CMD_513_H_

#include "command.h"


class cmd_513 : public cmd_base
{
	uint16_t newCmd;
	uint8_t  burstMsgNumber;
	bool     isLegacy;

public: // c.dtor
	cmd_513():cmd_base(513) {	};
	~cmd_513(){};

public: // work	
	virtual uint8_t extractData(uint8_t &ByteCnt, uint8_t *pData);
	virtual uint8_t insert_Data(uint8_t &ByteCnt, uint8_t *pData);

};

// extract ByteCnt bytes from data at pData
// return zero on success, response code on error
uint8_t cmd_513::extractData(uint8_t &ByteCnt, uint8_t *pData)
{
	uint8_t ret = RC_SUCCESS;
	uint8_t chngCnt = 0;
	if (ByteCnt < 3)
	{
		ret = RC_TOO_FEW;  // Too few data bytes
	}
	else
	{
		do // once
		{		
			if (ret = countryCode.extractSelf(&pData, &ByteCnt, chngCnt)) break;
			if (ret = siUnitCode.extractSelf(&pData, &ByteCnt, chngCnt)) break;
		} 
		while (false) ;// execute once

		if (!isError(ret) && chngCnt != 0)// something changed in this extraction
		{
			bumpConfigCnt();
		}
	}

	return ret;
}

 
// generate reply
// add bytes from data to pData, filling ByteCnt with the number added (caller adds RC/DS)
// return zero on success, response code (with byte count 0) on error
uint8_t cmd_513::insert_Data(uint8_t &ByteCnt, uint8_t *pData) 
{
	int ret = 0;
	ByteCnt = 0;   // just in case
	do // once
	{		
		if (ret = countryCode.insertSelf(&pData, &ByteCnt)) break;
		if (ret = siUnitCode.insertSelf(&pData, &ByteCnt)) break;
	}
	
	while (false) ;// execute once

	if (ret)
	{
		printf("Data insertion error in cmd %d. ret = %d.\n", number(), ret);
	}

	return ret;
};

#endif // CMD_513_H_
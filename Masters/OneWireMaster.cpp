/******************************************************************//**
* Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
**********************************************************************/

#include "Masters/OneWireMaster.h"
#include "Utilities/crc.h"

using namespace OneWire::crc;

extern "C" void __cxa_pure_virtual() { while (1); }

namespace OneWire
{
    OneWireMaster::CmdResult OneWireMaster::OWWriteBlock(const uint8_t *sendBuf, uint8_t sendLen)
    {
        CmdResult result;

        for (uint8_t idx = 0; idx < sendLen; idx++)
        {
            result = OWWriteByte(sendBuf[idx]);
            if (result != Success)
            {
                break;
            }
        }

        return result;
    }

    OneWireMaster::CmdResult OneWireMaster::OWReadBlock(uint8_t *recvBuf, uint8_t recvLen)
    {
        CmdResult result;

        for (uint8_t idx = 0; idx < recvLen; idx++)
        {
            result = OWReadByte(recvBuf[idx]);
            if (result != Success)
            {
                break;
            }
        }

        return result;
    }

    OneWireMaster::CmdResult OneWireMaster::OWTriplet(SearchDirection & searchDirection, uint8_t & sbr, uint8_t & tsb)
    {
        CmdResult result;
        result = OWReadBit(sbr);
        if (result == Success)
        {
            result = OWReadBit(tsb);
        }
        if (result == Success)
        {
            if (sbr)
            {
                searchDirection = WriteOne;
            }
            else if (tsb)
            {
                searchDirection = WriteZero;
            }
            // else: use search_direction parameter

            result = OWWriteBit((searchDirection == WriteOne) ? 1 : 0);
        }
        return result;
    }
}
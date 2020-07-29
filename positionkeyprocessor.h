#pragma once
#ifndef _POSKEYPROC_H_
#define _POSKEYPROC_H_
#include "defs.h"
#include "bitboard.h"



class positionkeyprocessor
{
public:
	U64 GeneratePosKey(const S_BOARD* pos);
};

#endif


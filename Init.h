#pragma once
#ifndef _INIT_H_
#define _INIT_H_

#include "defs.h"

//This macro fills 64 bits with random numbers.
#define RAND_64 ((U64) rand() | \
(U64) rand() << 15 | \
(U64) rand() << 30 | \
(U64) rand() << 45 | \
((U64)rand() & 0xf) << 60)



class Init
{
public:
	void AllInit();
	void InitBitMasks();
	void InitFilesRanksBrd();

private:
	void InitSq120To64();
	void InitHashKeys();
};

#endif

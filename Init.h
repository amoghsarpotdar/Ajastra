#pragma once

#include "defs.h"
#include "stdlib.h"

#define RAND_64 ((U64) rand() + \
(U64) rand() << 15 + \
(U64) rand() << 30 + \
(U64) rand() << 45 + \
((U64)rand() & 0xf) << 60)

class init
{
public:
	void AllInit();
	void InitBitMasks();

private:
	void InitSq120To64();
	void InitHashKeys();
};


#pragma once
#ifndef _INIT_H_
#define _INIT_H_

#include "defs.h"

#define RAND_64 ((U64) rand() | \
(U64) rand() << 15 | \
(U64) rand() << 30 | \
(U64) rand() << 45 | \
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

#endif

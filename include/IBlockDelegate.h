#ifndef IBLOCK_DELEGATE_H
#define IBLOCK_DELEGATE_H

#include "Block.h"

class IBlockDelegate
{
public:
	virtual void blockDisappearing() = 0;
};

#endif
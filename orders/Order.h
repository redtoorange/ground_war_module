#ifndef ORDER_H
#define ORDER_H
#include "core/object/ref_counted.h"

class Order: public RefCounted{
	GDCLASS(Order, RefCounted);
public:
	virtual void Execute() = 0;
	virtual bool IsComplete() = 0;
};

#endif

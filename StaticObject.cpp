#include "StaticObject.h"
#include "Obj.h"

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}

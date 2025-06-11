#pragma once
#include "../MyType.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	void AddItem();
	void RemoveItem();

private:
	 uint8 m_size;

};
#pragma once

#include <iostream>
#include "TCanvas.h"

#define g() (Singleton::get())

class Singleton
{

private:
	static Singleton *single;
	Singleton();

public:
	static Singleton* get();

	//add here
	TCanvas* c;
};


#include "Singleton.h"

using namespace std;

Singleton::Singleton()
{
	//add here
	c = new TCanvas("c1", "c1", 0, 0, 500, 500);
	c->Divide(2, 1);
}


Singleton* Singleton::get()
{

	if (Singleton::single == NULL)
	{
		single = new Singleton();
	}

	return single;

}
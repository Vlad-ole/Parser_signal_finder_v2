#include <iostream>
#include <set>

using namespace std;

int main()
{
	typedef pair<int, int> pairs; //creating pair as default data type 
	pairs p[5]; //array of pair objects

	//for (int i = 0; i<5; i++){
	//	p[i].first = (i + 1) * 10; //inserting first element of pair
	//	p[i].second = (i + 1); //inserting first element of pair
	//}
	
	p[0].first = 1; p[0].second = 10;
	p[1].first = 1; p[1].second = 20;
	p[2].first = 2; p[2].second = 15;
	p[3].first = 1; p[3].second = 10;
	p[4].first = 1; p[4].second = 11;

	set<pairs> s;   //set to sort pair
	set<pairs> ::iterator it; //iterator to manipulate set

	for (int i = 0; i<5; i++){
		s.insert(p[i]); //inserting pair object in set
	}

	for (it = s.begin(); it != s.end(); it++){
		pairs m = *it; // returns pair to m

		cout << m.first << " " << m.second << endl; //showing pair elements
	}

	system("pause");

	return 0;
}
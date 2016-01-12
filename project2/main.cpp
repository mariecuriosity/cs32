#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
void test()
{
	Sequence s;
	assert(s.insert(0, 10)); //tests insert function
	assert(s.insert(0, 20));
	assert(s.size() == 2); //tests size function/m_len counting correctly
	ItemType x = 999;
	ItemType y = 999;
	assert(s.get(0, x) && x == 20); //tests get function
	assert(s.get(1, x) && x == 10);
	Sequence t = s; //tests copy constructor
	assert(s.size() == t.size()); //checks copy constructor
	assert(s.get(0, x) == t.get(0, x));
	assert(s.get(1, x) == t.get(1, x));
	Sequence r;
	assert(r.insert(0, 55));
	assert(r.insert(0, 77));
	assert(r.insert(0, 99));
	assert(r.insert(0, 111));
	r.swap(s);
	assert(r.size() == t.size());  //checks swap function (size, first and last element)
	assert(r.get(0, x) && t.get(0, y) && x == y);
	assert(r.get(r.size() - 1, x) && t.get(r.size() - 1, y) && x == y);
	assert(r.erase(0) && r.get(0, x) && t.get(1, y) && x == y); //checks erase function
	assert(s.find(111) == 0); //checks find function
	assert(r.find(88) < 0); //checks if can recognize an element not being found
	assert(r.insert(0));
	assert(r.insert(4));
	assert(r.insert(8));
	assert(r.insert(8));
	assert(r.remove(8) > 0 && r.find(8) < 0); //checks remove and find functions
	assert(r.set(2, 4) && r.get(2, x) && x == 4); //checks set function
	assert(!s.empty()); //checks empty function
	Sequence a;
	Sequence b;
	assert(a.insert(0, 32) && a.insert(0, 8) && a.insert(0, 29) && a.insert(0, 17) && a.insert(0, 63));
	assert(b.insert(0, 8) && b.insert(0, 29));
	assert(subsequence(a, b) == 2); //checks subsequence
	Sequence c;
	assert(c.insert(0) && c.insert(1)); //make sure interleave works even if result has something to begin with
	interleave(a, b, c); //following lines check interleave function
	assert(c.size() == (a.size() + b.size()));
	assert(a.get(0, x) && c.get(0, y) && x == y);
	assert(b.get(0, x) && c.get(1, y) && x == y);
	assert(a.get(1, x) && c.get(2, y) && x == y);
	assert(b.get(1, x) && c.get(3, y) && x == y);
	assert(a.get(2, x) && c.get(4, y) && x == y);
	assert(a.get(3, x) && c.get(5, y) && x == y);
	assert(a.get(4, x) && c.get(6, y) && x == y);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}
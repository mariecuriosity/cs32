// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <algorithm>  // for swap
#include <vector>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

const int MAX_BUCKETS = 50000;

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
	//	DictionaryImpl();
	//	~DictionaryImpl();
	void insert(string word);
	void lookup(string letters, void callback(string)) const;
private:
	unsigned int findEmpty(const string& c) const;
	unsigned int findPos(const string& key) const;
	unsigned int hash(const string& key) const;
	void alphabetize(string& word, int start, int end) const;
	string m_words[MAX_BUCKETS];
};

unsigned int DictionaryImpl::hash(const string& key) const
{
	int hash = 0;
	for (size_t i = 0; i < key.length(); ++i)
		hash = hash * 33 + static_cast<int>(key[i]);
	return hash;
}

unsigned int DictionaryImpl::findEmpty(const string& c) const
{
	unsigned int nHash = hash(c) % MAX_BUCKETS;
	for (int i = 0; i < MAX_BUCKETS; ++i)
	{
		nHash = (nHash + i) % MAX_BUCKETS;
		if (m_words[nHash].empty())
			return nHash;
	}
	return -1;
}

unsigned int DictionaryImpl::findPos(const string& c) const
{
	unsigned int nHash = hash(c) % MAX_BUCKETS;
	for (int i = 0; i < MAX_BUCKETS; ++i)
	{
		nHash = (nHash + i) % MAX_BUCKETS;
		if (m_words[nHash] == c)
			return nHash;
	}
	return -1;
}


void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;
	removeNonLetters(letters);
	if (letters.empty())
		return;
	string permutation = letters;
	int pos;
	do
	{
		pos = findPos(permutation);
		if (pos > 0)
			callback(permutation);
		generateNextPermutation(permutation);
	} while (permutation != letters);
}

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	if (!word.empty())
	{
		unsigned int nHash = findEmpty(word);
		if (nHash < 0)
			return;
		m_words[nHash] = word;
	}
}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (string::const_iterator from = s.begin(); from != s.end(); from++)
	{
		if (isalpha(*from))
		{
			*to = tolower(*from);
			to++;
		}
	}
	s.erase(to, s.end());  // chop off everything from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
	string::iterator last = permutation.end() - 1;
	string::iterator p;

	for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
		;
	if (p != permutation.begin())
	{
		string::iterator q;
		for (q = p + 1; q <= last && *q > *(p - 1); q++)
			;
		swap(*(p - 1), *(q - 1));
	}
	for (; p < last; p++, last--)
		swap(*p, *last);
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}

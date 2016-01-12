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
using namespace std;

void removeNonLetters(string& s);

const unsigned long HASH_PRIME = 33;
const unsigned long MAX_BUCKETS = 49999; //prime number!
const unsigned long PRIME_NUMS[26] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
const unsigned long AAA = static_cast<unsigned long>('a');

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
	DictionaryImpl();
	~DictionaryImpl();
	void insert(string word);
	void lookup(string letters, void callback(string)) const;
private:
	unsigned long hash(const string& key) const;
	list<string>* m_words;
};

DictionaryImpl::DictionaryImpl()
{
	m_words = new list<string>[MAX_BUCKETS];
}

DictionaryImpl::~DictionaryImpl()
{
	delete[]m_words;
}

unsigned long DictionaryImpl::hash(const string& key) const
{
	unsigned long hash = 1;
	for (size_t i = 0; i < key.length(); ++i)
		hash = hash * PRIME_NUMS[static_cast<unsigned long>(key[i])-AAA];
	return hash % MAX_BUCKETS;
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;
	removeNonLetters(letters);
	if (letters.empty())
		return;
	unsigned long nHash = hash(letters);
	if (m_words[nHash].empty())
		return;
	sort(letters.begin(), letters.end());
	for (list<string>::iterator it = m_words[nHash].begin(); it != m_words[nHash].end(); ++it)
		if ((*it).length() == letters.length())
		{
			string alpha2 = (*it);
			sort(alpha2.begin(), alpha2.end());
			if (letters == alpha2)
				callback(*it);
		}
}

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	if (!word.empty())
	{
		m_words[hash(word)].push_back(word);
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

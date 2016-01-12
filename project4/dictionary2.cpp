// Dictionary.cpp-

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

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
	DictionaryImpl() {}
	~DictionaryImpl() {}
	void insert(string word);
	void lookup(string letters, void callback(string)) const;
private:
	char unusualLetter(string word) const; //determines letter with lowest frequency
	string m_words;
	void find_frequency(string str, int * count) const;
	//	bool compare_frequencies(const int (&count1)[26], const int (&count2)[26]);
};

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	m_words = word + m_words;
}

char DictionaryImpl::unusualLetter(string word) const
{
	int frequency = 10; //letter groups are separated into levels. determined by oxford study
	char letter = '@'; //current letter with lowest frequency
	for (int i = 0; i < word.length(); ++i)
	{
		switch (word[i])
		{
			//over 8% of letters in English language
		case 'a':
		case 'e':
		case 't':
			if (frequency > 6)
			{
				letter = word[i];
				frequency = 6;
			}
			break;
			//between 6-8% of letters in English language
		case 'h':
		case 'i':
		case 'n':
		case 'o':
		case 'r':
		case 's':
			if (frequency > 3)
			{
				letter = word[i];
				frequency = 3;
			}
			break;
			//between 3-6% of letters in English language
		case 'd':
		case 'l':
			if (frequency > 2)
			{
				letter = word[i];
				frequency = 2;
			}
			break;
			//between 2-3% of letters in English language
		case 'u':
		case 'c':
		case 'f':
		case 'g':
		case 'm':
		case 'w':
		case 'y':
		case 'p':
			if (frequency > 1)
			{
				letter = word[i];
				frequency = 1;
			}
			break;
			//under 2% of letters in English language
		case 'b':
		case 'k':
		case 'v':
		case 'j':
		case 'q':
		case 'x':
		case 'z':
			return word[i];
		}
	}
	return letter;
}

void DictionaryImpl::find_frequency(string str, int * count) const
{
	int temp[26] = { 0 };
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			++temp[str[i] - 'a'];
	}
	count = temp;
}
/*
bool DictionaryImpl::compare_frequencies(const int(&count1)[26], const int(&count2)[26])
{
for (int i = 0; i < 26; ++i)
{
if (count1[i] != count2[i])
return false;
}
return true;
}
*/

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;
	removeNonLetters(letters);
	letters = letters;
	char letterLook = unusualLetter(letters);
	if (letters.empty() || letterLook == '@')
		return;
	for (int i = 0; i < m_words.length(); ++i)
	{
		if (m_words[i] == letterLook)
		{
			//find actual window size around the match location
			int lowerMismatch = -1;
			int upperMismatch = -1;
			int j = 0;
			while (j < letters.length())
			{
				int lowerCount = 0;
				int upperCount = 0;
				for (int k = 0; k < letters.length(); ++k)
				{
					if (upperMismatch < 0 && (i + j) < m_words.length() && m_words[i + j] != letters[k])
						++upperCount;
					if (lowerMismatch < 0 && (i - j) >= 0 && m_words[i - j] != letters[k])
						++lowerCount;
				}
				if (upperCount == letters.length())
					upperMismatch = i + j - 1;
				if (lowerCount == letters.length())
					lowerMismatch = i - j + 1;
				++j;
			}
			if (upperMismatch < 0)
			{
				upperMismatch = i + (letters.length() - 1);
				if (upperMismatch >= m_words.length())
					upperMismatch = m_words.length() - 1;
			}
			if (lowerMismatch < 0)
			{
				lowerMismatch = i - (letters.length() - 1);
				if (lowerMismatch < 0)
					lowerMismatch = 0;
			}
			if (upperMismatch - lowerMismatch < (letters.length() - 1))
				continue;
			int inputCount[26] = { 0 };
			for (int z = 0; z < letters.length(); ++z)
			{
				if (letters[z] >= 'a' && letters[z] <= 'z')
					++inputCount[letters[z] - 'a'];
			}
			//			find_frequency(letters, inputCount);
			for (int h = 0; h <= (upperMismatch - lowerMismatch) - letters.length() && lowerMismatch + h + letters.length() < m_words.length(); ++h)
			{
				int slidingWindowCount[26] = { 0 };
				string slidingWindowStr = m_words.substr(lowerMismatch + h, letters.length());
				for (int z = 0; z < slidingWindowStr.length(); ++z)
				{
					if (slidingWindowStr[z] >= 'a' && slidingWindowStr[z] <= 'z')
						++slidingWindowCount[slidingWindowStr[z] - 'a'];
				}
				//				find_frequency(slidingWindowStr, slidingWindowCount);
				bool allTrue = true;
				for (int g = 0; g < 26; ++g)
				{
					if (inputCount[g] != slidingWindowCount[g])
					{
						allTrue = false;
						break;
					}
				}
				if (allTrue)
				{
					callback(slidingWindowStr);
					break;
				}
			}
		}
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

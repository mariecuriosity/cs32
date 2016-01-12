#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include <string>
typedef std::string ItemType;

class Sequence
{
public:
	Sequence();
	~Sequence();
	Sequence(Sequence& otherPtr);
	Sequence operator =(const Sequence& rhs);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	bool insert(const ItemType& value);
	bool erase(int pos);
//	void print();
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;

	void swap(Sequence& other);
	

private:
	struct Node
	{
		ItemType m_data;
		Node* m_next;
		Node* m_prev;
		Node():m_next(this), m_prev(this){}
	};
	Node *m_head;
	int m_len;
	void insertAtHead(const ItemType& value);
	void insertAtTail(const ItemType& value);
	void insertAtPos(const int pos, const ItemType& value); //pass in stuff to the left of item to add, item to add, and stuff to the right of item.
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif SEQUENCE_INCLUDED
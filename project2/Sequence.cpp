#include "Sequence.h"

Sequence::Sequence(){
	m_head = nullptr;
	m_len = 0;
}

Sequence::~Sequence() //deconstructor
{
	for (Node* p = m_head; m_head != nullptr && size() > 0; p = p->m_next)
	{
		erase(0); //erases everything
	}

}

Sequence::Sequence(Sequence& oldPtr) //copy constructor
{
	int i = 0;
	m_len = 0;
	m_head = nullptr; //set m_head to nullptr just to be safe
	for (Node* p = oldPtr.m_head; i < oldPtr.size(); p = p->m_next) //inserts stuff from oldPtr to the Sequence
	{
		insert(i, p->m_data);
		++i;
	}
}

Sequence Sequence::operator=(const Sequence& rhs) // assignment operator
{
	if (this != &rhs)
	{
		this -> ~Sequence(); //deletes current sequence
		int i = 0;
		for (Node*p = rhs.m_head; size() < rhs.size(); p=p->m_next) //copies everything from the rhs Sequence to this
		{
			insert(i, p->m_data);
			++i;
		}
	}
	return *this;
}

bool Sequence::empty() const
{
	if (m_len == 0)
	{
		return true;
	}
	return false;
}

/*
void Sequence::print()//REMOVE AFTERWARDS!!!
{
//	if (m_head->m_next == m_head)
	if (size() == 0)
	{
		cout << "the sequence has no values" << endl;
	}
	else
	{
//		for (Node*p = m_head->m_next; p != m_head; p = p->m_next)
		Node*p = m_head;
		for (int i = 0; i < m_len; ++i)
		{
			cout << p->m_data << " ";
			p = p->m_next;
		}
		cout << endl;
	}
}
*/

int Sequence::size() const
{
	return m_len;
}

void Sequence::insertAtHead(const ItemType& value) //private function to insert stuff at the head of the sequence
{
	Node* addNode = new Node();
	addNode->m_data = value;
	if (m_head != nullptr)
	{ //exchanges the pointers to connect tail to the new node and make the new node the head
		addNode->m_next = m_head;
		addNode->m_prev = m_head->m_prev;
		m_head->m_prev->m_next = addNode;
		m_head->m_prev = addNode;
	}
	m_head = addNode;
}

void Sequence::insertAtTail(const ItemType& value) //private funtion to insert stuff at the tail of the sequence
{ //exchanges the pointers to connect the old tail and the head to the new node and make the new node the tail
	Node* addPtr = new Node();
	addPtr->m_data = value;
	addPtr->m_prev = m_head->m_prev;
	m_head->m_prev->m_next = addPtr; //current tail's next is the new value
	addPtr->m_next = m_head;
	m_head->m_prev = addPtr;
}

void Sequence::insertAtPos(const int pos, const ItemType& value) //private function to insert stuff at a specific portion of the sequence (not head or tail)
{ //find the nodes directly adjacent to the place you want to insert the value into, and will exchange pointers to connect
	Node* leftPtr = new Node();
	Node* rightPtr = m_head;
	for (int i = 0; i < pos; ++i)
	{
		leftPtr = rightPtr;
		rightPtr = rightPtr->m_next;
	}
	Node * addPtr = new Node();
	addPtr->m_data = value;
	leftPtr->m_next = addPtr;
	addPtr->m_prev = leftPtr;
	addPtr->m_next = rightPtr;
	rightPtr->m_prev = addPtr;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	if (m_head == nullptr || pos == 0)
	{
		insertAtHead(value);
	}

	else if (pos >= m_len) //insert at tail!
	{
		insertAtTail(value);
	}
	else
	{
		insertAtPos(pos, value); //insert at middle
	}
	m_len += 1;
	return true;
}

bool Sequence::insert(const ItemType& value)
{
	if (m_head == nullptr)
	{
		insertAtHead(value);
		m_len += 1;
		return true;
	}
	Node* addNode = new Node();
	addNode->m_data = value;
	int pos = 0;
	for (Node* p = m_head; p->m_data < value && pos < size(); p=p->m_next) //finds first position in which data >= value and inserts into that position
	{
		pos += 1;
	}
	if (pos == 0)
	{
		insertAtHead(value);
	}
	else if (pos == size())
	{
		insertAtTail(value);
	}
	else
	{
		insertAtPos(pos, value);
	}
	m_len += 1;
	return true;
}

bool Sequence::erase(int pos)
{
	if (m_head == nullptr || pos > size() - 1) //won't erase if nothing inside sequence
	{
		return false;
	}
	else if (size() == 1) //don't want to delete nullptr, so will set head to nullpointer
	{
		delete m_head;
		m_head = nullptr;
	}
	else
	{
		int i = 0;
		Node* kill = m_head;
		while (i < pos)
		{
			kill = kill->m_next; //p will point to item we want to "kill"
			++i;
		}
		Node* temp = kill->m_prev;
		temp->m_next = kill->m_next;
		kill->m_next->m_prev = temp;
		if (i == 0)
		{
			m_head = temp->m_next; //if want to delete head, will make the head to the next sequence
		}
		else
		{
			delete kill;
		}
	}
	m_len -= 1;
	return true;
}

int Sequence::remove(const ItemType& value)
{
	int counter = 0; //counts number removed
	int i = size()-1;
	for (Node* p = m_head->m_prev; i >= 0; --i) //starts from the end and removes stuff until reaches item at pos 0
	{
		if (p->m_data == value)
		{
			p = p->m_prev;
			erase(i);
			counter += 1;
		}
		else{
			p = p->m_prev;
		}
	}
	return counter;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < m_len)
	{
		int i = 0;
		Node*p = m_head;
		while (i != pos)
		{
			p = p->m_next;
			++i;
		}
		value = p->m_data; //value of the Node at the pos
		return true;
	}
	return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < m_len)
	{
		int i = 0;
		Node*p = m_head;
		while (i != pos)
		{
			p = p->m_next;
			++i;
		}
		p->m_data = value; //finds node at position and assigs its value
		return true;
	}
	return false;
}

int Sequence::find(const ItemType& value) const
{
	int i = 0;
	Node *p = m_head;
	while (i < size()) //finds first occurrence. will return with the position (i) as soon as finds an equality
	{
		if (p->m_data == value)
		{
			return i;
		}
		p = p->m_next;
		++i;
	}
	return -1;
}

void Sequence::swap(Sequence& other)
{
	if (this != &other)
	{
		Sequence buffer = other; //uses assignment operator to swap!
		other = *this;
		*this = buffer;
	}
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType first;
	seq2.get(0, first); //gets first element of subsequence
	int pos = seq1.find(first);
	if (pos == -1 || seq1.size() < seq2.size()) //if not found in first sequence or if the 1st is smaller than 2nd, then exit function with return -1
	{
		return -1;
	}
	else
	{
		for (int i = pos; i <= seq1.size() - seq2.size(); ++i) //begins at psoition of first occurrence and increments until reaches the differenc in size (otherwise not possible to have complete match)
		{
			ItemType s1_val, s2_val;
			seq1.get(i, s1_val);
			if (first == s1_val) //if find a match for first element, increments through the entire secont sequence
			{
				int counter = 0;
				int j = 0;
				while (j < seq2.size())
				{
					seq1.get(i + j, s1_val);
					seq2.get(j, s2_val);
					if (s1_val == s2_val)
					{
						counter += 1;
					}
					++j;
				}
				if (counter == seq2.size()) //if every value of the 2nd sequence is in first, will return position, otherwise, continues on the loop
				{
					return i;
				}
			}
		}
		return -1;
	}
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence clean; //cleans out result sequence
	result = clean;
	int max_size;
	int s1_size = seq1.size();
	int s2_size = seq2.size();
	if (s1_size > s2_size) //finds maximum length = whichever sequence (1 or 2) are greater
	{
		max_size = s1_size;
	}
	else
	{
		max_size = s2_size;
	}
	int counter = 0;
	for (int i = 0; i < max_size; ++i)
	{
		if (i < s1_size) //adds to result sequence if within size limits
		{
			ItemType s1_val;
			seq1.get(i, s1_val);
			result.insert(counter, s1_val);
			counter += 1;
		}
		if (i < s2_size)
		{
			ItemType s2_val;
			seq2.get(i, s2_val);
			result.insert(counter, s2_val);
			counter += 1;
		}
	}
}
#pragma once

template <class T>
class SimpleNodeList;
template<class T>
class SimpleNode;
template<class T>
class SimpleNodeListIterator
{
public:
	SimpleNode<T> * m_node;
	SimpleNodeList<T>* m_list;

	SimpleNodeListIterator(SimpleNodeList<T> * p_list = nullptr,
		SimpleNode<T>* p_node = nullptr){
		m_list = p_list;
		m_node = p_node;
	}

	void Start()
	{
		if (m_list != nullptr)
			m_node = m_list->m_head;
	}

	void End()
	{
		if (m_list != nullptr)
			m_node = m_list->m_tail;
	}

	void Forth()
	{
		if (m_node != nullptr)
			m_node = m_node->m_nextNode;
	}

	T& Item()
	{
		return m_node->m_data;
	}

	bool Valid()
	{
		return (m_node != nullptr);
	}
};

template<class T>
class SimpleNode{
public:
	T m_data;
	SimpleNode<T>* m_nextNode;

	SimpleNode(){
		m_nextNode = nullptr;
	}

	void InsertAfter(T p_data){
		SimpleNode<T>* newNode = new SimpleNode<T>;
		newNode->m_data = p_data;
		newNode->m_nextNode = this->m_nextNode;
		this->m_nextNode = newNode;
	}
};

template<class T>
class SimpleNodeList{
public:
	SimpleNode<T>* m_head;
	SimpleNode<T>* m_tail;
	int m_count = 0;

	SimpleNodeList(){
		m_head = m_tail = nullptr;
		m_count = 0;
	}

	~SimpleNodeList(){
		SimpleNode<T>* itr = m_head;
		SimpleNode<T>* next;
		while (itr != nullptr){
			next = itr->m_nextNode;
			delete itr;
			itr = next;
		}
	}

	void Append(T p_data){
		if (m_head == nullptr){
			m_head = m_tail = new SimpleNode<T>;
			m_head->m_data = p_data;
		}
		else{
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_nextNode;
		}
		m_count++;
	}

	void RemoveHead(){
		if (m_head != nullptr){
			SimpleNode<T>* newHead = m_head->m_nextNode;
			delete m_head;
			m_head = newHead;
			m_count--;
		}
	}

	void DeleteHead(){
		if (m_head != nullptr){
			SimpleNode<T>* newHead = m_head->m_nextNode;
			delete m_head->m_data;
			delete m_head;
			m_head = newHead;
			m_count--;
		}
	}

	T* ToArray(){
		T* newArray = new T[m_count];
		SimpleNode<T>* itr = m_head;
		int i = 0;;
		while (itr != 0){
			newArray[i] = itr->m_data;
			itr = itr->m_nextNode;
			i++;
		}
		return newArray;
	}

	SimpleNodeListIterator<T> GetIterator()
	{
		SimpleNodeListIterator<T> sli(this, m_head);
		return sli;
	}
};

template<class T>
class DoubleNode {
public:
	T m_data;
	DoubleNode<T>* m_nextNode;
	DoubleNode<T>* m_previousNode;

	DoubleNode() {
		m_nextNode = nullptr;
		m_previousNode = nullptr;
	}

	void InsertAfter(T p_data) {
		DoubleNode<T>* newNode = new DoubleNode<T>;
		newNode->m_data = p_data;
		newNode->m_nextNode = this->m_nextNode;
		newNode->m_previousNode = this;
		this->m_nextNode = newNode;
	}
};

template<class T>
class DoubleNodeList {
public:
	DoubleNode<T>* m_head;
	DoubleNode<T>* m_tail;
	int m_count = 0;

	DoubleNodeList() {
		m_head = m_tail = 0;
		m_count = 0;
	}

	~DoubleNodeList() {
		DoubleNode<T>* itr = m_head;
		DoubleNode<T>* next;
		while (itr != 0) {
			next = itr->m_nextNode;
			delete itr;
			itr = next;
		}
	}

	void Append(T p_data) {
		if (m_head == 0) {
			m_head = m_tail = new DoubleNode<T>;
			m_head->m_data = p_data;
		}
		else {
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_nextNode;
		}
		m_count++;
	}

	void Remove(DoubleNode<T>* node) {
		if (node != 0 && node != nullptr) {
			if (node == m_head) {
				m_head = node->m_nextNode;
			}
			if (node == m_tail) {
				m_tail = node->m_previousNode;
			}
			if(node->m_previousNode != nullptr && node->m_previousNode != 0)
				node->m_previousNode->m_nextNode = node->m_nextNode;
			if (node->m_nextNode != nullptr && node->m_nextNode != 0)
				node->m_nextNode->m_previousNode = node->m_previousNode;
		}
		m_count--;
	}

	void Insert(DoubleNode<T>* node) {
		if (m_count > 0) {
			DoubleNode<T>* oldTail = m_tail;
			oldTail->m_nextNode = node;
			m_tail = node;
			m_tail->m_nextNode = 0;
			m_tail->m_previousNode = oldTail;
		}
		else {
			m_head = m_tail = node;
		}
		m_count++;
	}

	void RemoveHead() {
		if (m_head != 0) {
			DoubleNode<T>* newHead = m_head->m_nextNode;
			delete m_head;
			m_head = newHead;
			m_count--;
		}
	}

	void DeleteHead() {
		if (m_head != 0) {
			DoubleNode<T>* newHead = m_head->m_nextNode;
			delete m_head->m_data;
			delete m_head;
			m_head = newHead;
			m_count--;
		}
	}
};
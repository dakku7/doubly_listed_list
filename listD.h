#include <iostream>
template <typename T>

class DoublLinkedList {

	class Node {
	public:

		Node* pNext;
		Node* pPrev;
		T data;
			Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
				this->data = data;
				this->pNext = pNext;
				this->pPrev = pPrev;
			}

			~Node() {
				pNext = nullptr;
				pPrev = nullptr;
			}
	};
	Node* head;
	Node* tail;
	int size;

	bool out_of_range_insert(int index) {
		if (index < 0 || index > size) {
			return true;
		}

		return false;
	}

	Node* getNode(int index) {
		if (out_of_range(index)) {
			throw std::out_of_range("error: out of range index");
		}
		Node* tmp;

		if (index < size / 2) {
			tmp = head;
			for (int i = 0; i < index; ++i) {
				tmp = tmp->pNext;
			}
		}
		else {
			tmp = tail;
			for (int i = size - 1; i > index; --i) {
				tmp = tmp->pPrev;
			}
		}
		return tmp;
	}
public:
		
	DoublLinkedList() {
		this->head = this->tail = nullptr;
		size = 0;
	}

	

	void push_back(T data) {
		Node* tmp = new Node(data);

		if (size == 0) {
			head = tmp;
			tail = tmp; 
		}
		else {
			tmp->pPrev = tail;
			tail->pNext = tmp;
			tail = tmp;
		}

		++size;
	}
	void push_front(T data) {
		Node* tmp = new Node(data);

		if (size == 0) {
			head = tmp;
			tail = tmp;
		}
		else {
			tmp->pNext = head;
			head->pPrev = tmp;
			head = tmp;
		}

		++size;
	}
	void pop_back() {
		if (isEmpty()) {
			std::cout << "\nempty\n";
			return;
		}
		Node* tmp = tail;
		tail = tmp->pPrev;

		// if tail != nullptr
		if(tail) {
			tail->pNext = nullptr;
		}
		else {
			head = nullptr;
		}
	
		delete tmp;
		--size;
	}
	void pop_front() {
		if (isEmpty()) {
			std::cout << "\nempty\n";
			return;
		}

		Node* tmp = head;
		head = tmp->pNext;

		if (head) {
			head->pPrev = nullptr;
		}
		else {
			tail = nullptr;
		}

		delete tmp;
		--size;
	}
	void clear() {
		while (size)
		{
			pop_front();

		}
	}
	void Print() {
		Node* tmp = head;
		while (tmp != nullptr)
		{
			std::cout << tmp->data << " " ;
			tmp = tmp->pNext;
		}
		std::cout << std::endl;
	}
	void rPrint() {
		Node* tmp = tail;
		while (tmp != nullptr)
		{
			std::cout << tmp->data << '\n';
			tmp = tmp->pPrev;
		}
	}
	int getSize() const {
		return size;
	}
	bool isEmpty() {
		if (tail == nullptr) return true;
		return false;
	}
	bool out_of_range(int index) {
		if (index < 0 || index > size - 1) {
			return true;
		}

		return false;
	}
	T& operator[](const int index) {
		Node* tmp;

		if (index < size / 2) {
			tmp = head;
			for (int i = 0; i < index; ++i) {
				tmp = tmp->pNext;
			}
		}
		else {
			tmp = tail;
			for (int i = size - 1; i > index; --i) {
				tmp = tmp->pPrev;
			}
		}
		return tmp->data;
	}	
	T& at(const int index)  {
		if (out_of_range(index)) {
			throw std::out_of_range("error: out of range index");
		}
		return(*this)[index];
	}
	void insert(T value, int index) {
		if (out_of_range_insert(index)) {
			throw std::out_of_range("error: out of range index");
		}
		if (index == 0) {
			push_front(value);
			return;
		}

		if (index == size) {
			push_back(value);
			return;
		}
		Node* tmp = new Node(value);

		Node* current = getNode(index);

		tmp->pPrev = current->pPrev;
		tmp->pNext = current;

		current->pPrev = tmp;
		tmp->pPrev->pNext = tmp;
	
		++size;
	}
	void remove(int index) {
		if (out_of_range(index)) {
			throw std::out_of_range("error: out of range index");
		}
		if (index == 0) {
			pop_front();
			return;
		}

		if (index == size - 1) {
			pop_back();
			return;
		}

		Node* tmp = getNode(index);
		tmp->pPrev->pNext = tmp->pNext;
		tmp->pNext->pPrev = tmp->pPrev;

		--size;
		delete tmp;
	}
	void reverse() {
		if (head == nullptr || tail == nullptr) {
			return;
		}

		Node* current = head;
		Node* temp = nullptr;

		while (current != nullptr)
		{
			temp = current->pNext; // например работаем так temp = 3, так как current pNext = 3, от 1
			std::swap(current->pNext, current->pPrev); // потом я делаю так что pNext который указывает на 3, теперь указывает на null ptr(данный внутри это 1)
			// то есть вышло так что data = 1, имеет pPrev= nullptr, pNext = 3
			current->pPrev = temp; // потом я делаю так что nullptr становится 3
			current = temp; // переход по циклу ко второму индексу,ну то есть 3 

		}

		std::swap(head, tail);
	}
	T back() {
		return tail->data;
	}
	void fill(int value, int size) {
		clear();
		for (int i = 0; i < size; ++i) {
			push_back(value);
		}
	}
	

	class iterator {
	private:
		Node* current;

	public:
		iterator(Node* current = nullptr) {
			this->current = current;
		}

		//prefix
		iterator& operator++() {
			if (current == nullptr) {
				return *this;
			}
			current = current->pNext;
			return *this;
		}
		//postfix
		iterator& operator++(int)  {
			if (current == nullptr) {
				return *this;
			}
			iterator _tmp = *this;
			current = current->pNext;
			return _tmp;
		}
		bool operator!=(const iterator& right) const {
			return current != right.current;
		}
		 T& operator*() const {
			 return current->data;
		}
		 iterator& operator+=(int value) {
			 for (int i = 0; i < value; i++)
			 {
				 ++*this;
			 }
			 return *this;
		 }
		 iterator& operator=(const iterator& right) {
			 if (*this != right) {
				 current = right.current;
			 }
			 return *this;
		 }
		 iterator& operator-=(int value) {
				 for (int i = 0; i < value; i++)
				 {
					 --*this;
				 }
				return *this;		 
		 }
		 iterator operator+(int n) const {
			 iterator temp = *this;
			 for (int i = 0; i < n; i++)
			 {
				 ++temp;
			 }
			 return temp;
		 }
		 iterator operator-(int n) {
			 iterator temp = *this;
			 for (int i = 0; i < n; i++) {
				 --temp;
			 }
			 return temp;
		 }
		 //prefix
		 iterator& operator--() {
			 if (current == nullptr) {
				 return *this;
			 }
			 current = current->pPrev;
			 return *this;
		 }
		 //postfix
		 iterator& operator--(int) {
			 if (current == nullptr) {
				 return *this;
			 }
			 iterator _tmp = *this;
			 current = current->pPrev;
			 return _tmp;
		 }
	};

	iterator begin() {
		return iterator(head);
	}

	iterator cbegin() const {
		return iterator(tail);
	}

	iterator end()  {
		return iterator(nullptr);
	}

	iterator cend() const{
		return iterator(nullptr);
	}

	
	
	~DoublLinkedList() {
		clear();
	}
};
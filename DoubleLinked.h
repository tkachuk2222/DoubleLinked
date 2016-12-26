#pragma once
using namespace std;
template<typename T>
class DoubleLinked
{
public:
	DoubleLinked();
	DoubleLinked(T num, T val = 0);
	DoubleLinked(const DoubleLinked& ob);		//?

	~DoubleLinked();
	void addToBegin(T);
	void addToEnd(T);
	void add(T,T);
	void show();
	void delFirst();
	void delEnd();
	bool del(T);
	unsigned long size();
	void clear();
	bool isEmpty();
	void swap(DoubleLinked<T>ob);
private:
	class Item
	{
	public:
		friend class DoubleLinked;
		Item(int data = 0) :data_(data), pnext_(nullptr), pprev_(nullptr) {};
		//~Item();

	private:
		T data_;
		Item*pnext_;
		Item*pprev_;
	}; //*listBegin, *listEnd;
//abo:
	Item*listBegin;
	Item*listEnd;
};

template<typename T>
DoubleLinked<T>::DoubleLinked()
{
	listBegin = nullptr;
	listEnd = nullptr;
}
template<typename T>
inline DoubleLinked<T>::DoubleLinked(T num, T val)
{
	cout << "constructor T num, T val\n";
	Item *it = new Item(val);
	listBegin = it;
	Item*tmp = listBegin;
	listBegin->pprev_ = nullptr;
	for (int i = 0; i < num - 1; i++)
	{
		tmp->pnext_ = new Item;
		tmp->pprev_ = tmp;
		tmp->pprev_ = new Item;
		tmp = tmp->pnext_;
		
		tmp->data_ = val;
		
		tmp->pnext_ = nullptr;
		listEnd = tmp;
	}
	cout << "Constructor\n";
}
template<typename T>
inline DoubleLinked<T>::DoubleLinked(const DoubleLinked & ob)
{
	cout << "constructor copy\n";
	Item*tmp = nullptr;
	Item*tmpOb = ob.listBegin;
	
	while (tmpOb) {
		if (tmp != nullptr) {
			tmp->pnext_ = new Item;
			tmp->pnext_->pprev_ = tmp;
			tmp = tmp->pnext_;
			tmp->data_ = tmpOb->data_;
			tmpOb = tmpOb->pnext_;
			listEnd = tmp;
		}
		else {
			tmp = new Item;
			tmp->data_ = tmpOb->data;
			tmp->pprev_ = nullptr;
			listBegin = tmp;
			tmpOb = tmpOb->pnext;
		}
	}
	cout << "constructor copy\n";

}
template<typename T>
DoubleLinked<T>::~DoubleLinked()
{
	cout << "destructor\n";
}
template<typename T>
void DoubleLinked<T>::addToBegin(T n) {
	Item*it = new Item(n);
	if (listBegin == nullptr) {
		listBegin = it;
		listEnd = it;
	}
	else {
		it->pnext_ = listBegin;
		listBegin->pprev_ = it;
		listBegin = it;
	}
}
template<typename T>
void DoubleLinked<T>::show() {
	if (!listBegin)
		cout << "list is empty\n";
	Item*tmp = listBegin;
	while (tmp) {
		cout << tmp->data_ << "\t";
		tmp = tmp->pnext_;
	}
	cout << endl;
}
template<typename T>
inline void DoubleLinked<T>::delFirst()
{
	if (listBegin == nullptr) {
		return;
	}
	else {
		Item*it = listBegin;
		it->pnext_->pprev_ = nullptr;
		listBegin = listBegin->pnext_;
		delete it;
	}
}
template<typename T>
inline void DoubleLinked<T>::delEnd(){
	if (!listBegin)
		return;
	else {
		Item*tmp = listBegin;
		while (tmp->pnext_) {
			if (tmp->pnext_->pnext_ == nullptr) {
				Item*del = tmp->pnext_;
				tmp->pnext_ = nullptr;
				listEnd = tmp;
				delete del;
				return;
			}
			tmp = tmp->pnext_;
		}
	}
}
template<typename T>
inline bool DoubleLinked<T>::del(T val)
{
	if(!listBegin)
		return false;
	else {
		Item*tmp = listBegin;
		Item*tmp2 = tmp;
		int count = 0;
		val -= 1;
			while (tmp) {
					if (count - val  == 0) {
					    if (tmp->pnext_ == nullptr) {
							delEnd();
							return true;

						}
						else if (tmp->pprev_ == nullptr) {
							delFirst();
							return true;
						}
						
						else {
							tmp->pprev_->pnext_ = tmp->pnext_;
							tmp->pnext_->pprev_ = tmp->pprev_;
							delete tmp;
							return true;
						}
					
					}
				tmp2 = tmp;
				tmp = tmp->pnext_;
				count++;

			}
		}
	return false;
}
template<typename T>
inline unsigned long DoubleLinked<T>::size()
{
	if(!listBegin)
		return 0;
	Item*tmp = listBegin;
	int count = 0;
	while (tmp->pnext_) {
		count++;
		tmp = tmp->pnext_;
	}
	return count;
}
template<typename T>
inline void DoubleLinked<T>::clear()
{
	int num = 1;
	while (listBegin) {
		del(num);
		num++;
		listBegin=listBegin->pnext_;
	}
}
template<typename T>
inline bool DoubleLinked<T>::isEmpty()
{
	if (listBegin)
		return true;
	return false;
}
template<typename T>
inline void DoubleLinked<T>::swap(DoubleLinked<T>ob)
{
	Item*tmpBeg = listBegin;
	Item*tmpEnd = listEnd;
	listBegin = ob.listBegin;
	listEnd = ob.listEnd;
	ob.listBegin = tmpBeg;
	ob.listEnd = tmpEnd;
}
template<typename T>
void DoubleLinked<T>::addToEnd(T n) {
	Item*it = new Item(n);
	if (listBegin == nullptr) {
		listBegin = it;
		listEnd = it;
	}
	else {
		Item*tmp = listBegin;
		while (tmp->pnext_) {
			tmp = tmp->pnext_;
		}
		tmp->pnext_ = it;
		listEnd = it;
	}
}
template<typename T>
void DoubleLinked<T>::add(T num, T val) {
	Item *it = new Item(val);
	if (listBegin == nullptr) {
		listBegin = it;
		listEnd = it;
	}
	else {
		Item*tmp = listBegin;
		if (listBegin->pnext_ == nullptr)
			addToEnd(val);
		else if (listEnd->pprev_ == nullptr)
			addToBegin(val);
		else
			while (tmp->pnext_) {
				if (tmp->data_ == num) {
					it->pnext_ = tmp->pnext_;
					tmp->pnext_->pprev_ = it;
					it->pprev_ = tmp;
					tmp->pnext_ = it;
				}
				tmp = tmp->pnext_;
			}
	}
}

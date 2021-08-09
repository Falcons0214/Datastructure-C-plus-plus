#include<iostream>

template <class T>
class node
{
private:
    T data;
    node *next;
    node *prev;

public:
    node() {
        next = prev = nullptr;
    }
    node(T d) {
        node();
        this->data = d;
    }
    node(T d, node<T> *n, node<T> *p) {
        data = d;
        next = n;
        prev = p;
    }
    T getData() {
        return data;
    }
    node *getPrev() {
        return prev;
    }
    node *getNext() {
        return next;
    }
    void setData(T data) {
        this->data = data;
    }
    void setNext(node<T> *addr) {
        next = addr;
    }
    void setPrev(node<T> *addr) {
        prev = addr;
    }
    void deleteNode(node<T> *node) {
        delete node;
    }
    void printData() {
        std::cout<<data<<" ";
    }
};

template <class T>
class LinkList
{
private:
    node<T> *head, *tail;
    int count;

public:
    LinkList() {
        count = 0;
        head = tail = nullptr;
    }

    LinkList(node<T> arr[], int num) {
        count = num;
        node<T> *cur = &arr[0];
        head = cur;
        cur->setPrev(nullptr);
        for(int i=1; i<num; i++)
        {
            cur->setNext(arr[i]);
            (cur->getNext())->setPrev(arr[i-1]);
            cur = cur->getNext();
        }
        cur->setNext(nullptr);
        tail = cur;
    }

    bool isEmpty() {
        if( head == nullptr && tail == nullptr )
            return true;
        return false;
    }

    void insertFromHead(node<T> *node) {
        // std::cout<<node->getData()<<" ";
        node->setNext(head);
        if(isEmpty()) {
            head = tail = node;
        }else{
            head->setPrev(node);
            head = node;
        }
        count++;
    }

    void insertFromTail(node<T> *node) {
        // std::cout<<node->getData()<<" ";
        node->setPrev(tail);
        if(isEmpty()) {
            head = tail = node;
        }else{
            tail->setNext(node);
            tail = node;
        }
        count++;
    }

    void insertToIndex(node<T> *node, int index) {
        if(isEmpty()) {
            std::cout << "Empty!"<<'\n';
            return; 
        }
        node<T> *cur = head;
        for(int i=0; i<index; i++) {
            cur = cur->getNext();
        }
        node->setNext(cur->getNext());
        node->setPrev(cur);
        (node->getNext())->setPrev(node);
    }

    node<T> *removeFromHead() {
        if(isEmpty()) {
            std::cout<<"empty"<<'\n';
            return nullptr;
        }
        node<T> *cur = head;
        count--;
        head = cur->getNext();
        head->setPrev(nullptr);
        return cur;
    }

    node<T> *removeFromTail() {
        if(isEmpty()) {
            std::cout<<"empty"<<'\n';
            return nullptr;
        }
        node<T> *cur = tail;
        count--;
        tail = cur->getPrev();
        tail->setNext(nullptr);
        return cur;
    }

    node<T> *removeFromIndex(node<T> *node, int index) {
        if(isEmpty()) {
            std::cout<<"Empty!"<<'\n';
            return; 
        }
        node<T> *cur = head;
        for(int i=0; i<index; i++) {
            cur = cur->getNext();
        }
        // lazy
        // (cur->getPrev())->setNext() 
    }

    node<T> *searchNode(int index) {
        node<T> *cur = head;
        for(int i=0; i<index; i++) {
            cur = cur->getNext();
        }
        return cur;
    }
    
    void printList() {
        node<T> *cur = head;
        while(cur != nullptr) {
            cur->printData();
            cur = cur->getNext();
        }
    }
};

int main()
{
    node<int> n[10];
    LinkList<int> LL;

    for(int i=1; i<=10; i++){
        n[i-1].setData(i);
    }

    for(int i=0; i<5; i++)
    {
        LL.insertFromHead(&n[i]);
    }

    for(int i=5; i<10; i++)
    {
        LL.insertFromTail(&n[i]);
    }

    LL.printList();

    std::cout<<'\n';

    LL.removeFromHead();
    LL.printList();

    std::cout<<'\n';

    LL.removeFromTail();
    LL.printList();

    return 0;
}
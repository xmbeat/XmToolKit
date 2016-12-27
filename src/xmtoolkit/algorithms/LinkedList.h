#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Iterable.h"

template <class T>
class LinkedList : public Iterable<T> {
private:

    struct Node {
        T data;
        Node *next;

        Node(T d) {
            data = d;
            next = 0;
        }
    };

    class LinkedListIterator : public Iterator<T> {
    public:
        Node *mNode;
        Node *mCurrent;

        virtual bool hasNext() {
            return mNode != NULL;
        }

        virtual T next() {
            T aux = mNode->data;
            mNode = mNode->next;
            return aux;
        }

        LinkedListIterator(): mNode(NULL), mCurrent(NULL) {
        }
    };
    Node *mHead;
    Node *mTail;
    int mSize;
    LinkedListIterator *mIterator;
public:

    LinkedList() : mHead(0), mTail(0), mSize(0) {
        mIterator = new LinkedListIterator();
    }
    virtual ~LinkedList() {
        clear();
        delete mIterator;
    }

    virtual void clear() {
        while (mHead) {
            Node*aux = mHead;
            mHead = mHead->next;
            delete aux;
        }
        mSize = 0;
        mHead = mTail = 0;
    }

    virtual bool size() {
        return mSize;
    }

    virtual void add(T data) {
        Node *nuevo = new Node(data);
        if (mTail) {
            mTail->next = nuevo;
            mTail = nuevo;
        } else {
            mTail = mHead = nuevo;
        }
        mSize++;
    }

    virtual Iterator<T> *iterator() {
        mIterator->mNode = mHead;
        return mIterator;
    }

    virtual bool remove(T data) {
        Node *ant = 0;
        Node *aux = mHead;
        while (aux) {
            //Coinciden los datos
            if (aux->data == data) {
                //Solo habia un elemento
                if (mHead == mTail) {
                    mTail = mHead = 0;
                }//La cabeza se quita
                else if (aux == mHead) {
                    mHead = mHead->next;
                }//Se quita algun otro elemento
                else {
                    ant->next = aux->next;
                }
                mSize--;
                delete aux;
                return true;
            }
            ant = aux;
            aux = aux->next;
        }
        return false;
    }


};
#endif // LINKEDLIST_H

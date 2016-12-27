#ifndef ITERABLE_H
#define ITERABLE_H
template<class T>
class Iterator{
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator(){}
};
template <class T>
class Iterable
{
public:
    virtual Iterator<T> *iterator() = 0;
    virtual ~Iterable() {}
protected:
private:
};

#endif // ITERABLE_H

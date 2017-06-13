#include "corn.h"

CobLayer::CobLayer(size_t cobRingSize) :
    _cobRingSize(cobRingSize),
    above(nullptr),
    below(nullptr),
    _currentCobRingPosition(0)
{
    _kernels = new Kernel*[cobRingSize]();
}

Kernel* CobLayer::insert(int data)
{
    if (isFull())
    {
        return 0;
    }
    
    Kernel* newKernel = new Kernel(data);
    _kernels[_currentCobRingPosition] = newKernel;
    ++_currentCobRingPosition;
    return newKernel;
}

int CobLayer::pop()
{
    // TODO guard against negatives
    Kernel *popped = _kernels[_currentCobRingPosition];
    int data = popped->data;
    delete popped;
    --_currentCobRingPosition;
    return data;
}

int CobLayer::peek(size_t at) const
{
    return _kernels[at]->data;
}

bool CobLayer::isFull() const
{
    return _currentCobRingPosition == _cobRingSize;
}

size_t CobLayer::size() const
{
    return _cobRingSize;
}

size_t CobLayer::count() const
{
    return _currentCobRingPosition;
}

CobLayer::~CobLayer()
{
    if (_kernels)
    {
        for (int i = 0; i < _currentCobRingPosition; ++i)
        {
            if (_kernels[i])
            {
                delete _kernels[i];
            }
        }
        delete[] _kernels;
    }
}

Cob::Cob(size_t cobRingSize) : _cobRingSize(cobRingSize), top(nullptr), bottom(nullptr)
{
}

Kernel* Cob::insert(int data)
{
    Kernel *insertedKernel = nullptr;
    
    if (top && !top->isFull())
    {
        insertedKernel = top->insert(data);
    }
    else
    {
        // CobLayer is full, add new node and add data there
        CobLayer* newNode = new CobLayer(_cobRingSize);
        if (!bottom)
        {
            bottom = newNode;
            bottom->above = nullptr;
            bottom->below = nullptr;
            top = bottom;
        }
        else
        {
            newNode->below = top;
            newNode->below->above = newNode;
            top = newNode;
            top->above = nullptr;
        }
        insertedKernel = top->insert(data);
    }
    return insertedKernel;
}

size_t Cob::size() const
{
    return _cobRingSize;
}

Cob::~Cob()
{
    CobLayer* it = bottom;
    while (it)
    {
        CobLayer* above = it->above;
        delete it;
        it = above;
    }
}
/*
int Iterator::operator*()
{
    return _collectionType->peek();
}

Iterator Iterator::operator++()
{
    _collectionType = _collectionType->above;
    return Iterator(_collectionType);
}

Iterator Iterator::operator++(int)
{
    _collectionType = _collectionType->above;
    return Iterator(_collectionType);
}

Iterator Iterator::operator--()
{
    _collectionType = _collectionType->below;
    return Iterator(_collectionType);
}

Iterator Iterator::operator--(int)
{
    _collectionType = _collectionType->below;
    return Iterator(_collectionType);
}
*/
Corn::Corn(size_t cobRingSize) : _cob(cobRingSize)
{

}

Corn::Corn(const Corn& other) : _cob(other._cobRingSize)
{

}

Corn& Corn::operator=(const Corn& other)
{
    return *this;
}

Corn::~Corn()
{

}
/*
Iterator Corn::createIterator()
{
    return Iterator(this->_cob.bottom);
}
*/
Kernel* Corn::insert(int data)
{
    return _cob.insert(data);
}

size_t Corn::cobSize() const
{
    return _cob.size();
}

size_t Corn::kernelCount() const
{
    size_t count = 0;
    CobLayer* it = _cob.top;
    while (it != _cob.bottom)
    {
        count += it->count();
    }
    return count;
}


#include <string>
#include <array>
#include <memory>

template<typename CollectionType>
class KernelIterator
{
 public:    
    KernelIterator(CollectionType collectionType) :
        _collectionType(collectionType),
        _currentPosition(0)
    {}

    int operator*()
    {
        return _collectionType->peek(_currentPosition);
    }
    KernelIterator& operator++()
    {
        ++_currentPosition;
        if (_currentPosition >= _collectionType->count())
        {
            _collectionType = nullptr;
        }
        return *this;
    }

    bool hasNext() const
    {
        return _collectionType != nullptr;
    }

 private:
    CollectionType _collectionType;
    size_t _currentPosition;
};

class Kernel
{
 public:
 Kernel(int dat) : data(dat) {}
    int operator*() { return data; }  
    int data;
};

class CobLayer
{
 public:
    friend class Cob;
    
    template<typename CollectionType>
    friend class KernelIterator;
    typedef KernelIterator<CobLayer*> Iterator;

    CobLayer(size_t cobRingSize);
    ~CobLayer();
    Kernel* insert(int data);
    int pop();
    int peek(size_t at) const;
    bool isFull() const;
    size_t size() const;
    size_t count() const;

    Iterator createIterator()
    {
        return Iterator(this);
    }

 public:
    CobLayer* above;
    CobLayer* below;
    
 private:
    Kernel** _kernels;
    size_t _cobRingSize;
    size_t _kernelCount;
    size_t _currentCobRingPosition;
};

class Cob
{
 public:
    Cob(size_t cobRingSize);
    ~Cob();
    Kernel* insert(int data);
    size_t size() const;
    CobLayer* top;
    CobLayer* bottom;
    
 private:        
    size_t _cobRingSize;
    size_t _size;
};

template<typename CollectionType>
class CobIterator
{
 public:    
    CobIterator(CollectionType collectionType) : _collectionType(collectionType)
    {}

    CollectionType operator*()
    {
        return _collectionType;
    }
    CobIterator& operator++()
    {
        if (_collectionType)
        {
            _collectionType = _collectionType->below;
        }
        return *this;
    }

    bool hasNext() const
    {
        return _collectionType != nullptr;
    }
 private:
    CollectionType _collectionType;
};

class Corn
{
 public:
    template<typename CollectionType>
    friend class CobIterator;
    typedef CobIterator<CobLayer*> Iterator;
    
    Corn(size_t cobRingSize);
    Corn(const Corn& other);
    Corn& operator=(const Corn& other);
    ~Corn();

    Iterator createIterator()
    {
        return Iterator(this->_cob.top);
    }
    
    Kernel* insert(int data);
    size_t cobSize() const;
    size_t kernelCount() const;

 private:
    size_t _cobRingSize;
    Cob _cob;
};

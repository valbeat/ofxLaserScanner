#ifndef observer_h
#define observer_h

#include <studio.h>

// observerパターンのtemplete
template <class T>
class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}
    // notifyされた時に呼ばれる関数
    virtual void update(T *subject)= 0;
};

#endif /* observer_h */

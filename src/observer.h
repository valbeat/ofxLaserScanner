//
//  observer.h
//  LaserScanner
//
//  Created by kajikawa on 2/2/16.
//
//

#ifndef observer_h
#define observer_h

#include <studio.h>

template <class T>
class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void update(T *subject)= 0;
};

#endif /* observer_h */

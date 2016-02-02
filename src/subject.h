//
//  subject.h
//  LaserScanner
//
//  Created by kajikawa on 2/2/16.
//
//

#ifndef subject_h
#define subject_h

#include <studio.h>

template <class T>
class Subject {
public:
    Subject() {}
    virtual ~Subject(){}
    void attach(Observer<T> &observer){
        m_observers.push_back(&observers);
    }
    void notify() {
        vector<Observer<T> *>::iterator it;
        for (it=m_observers.begin();it!=m_observers.end();it++)
            (*it)->update(static_cast<T *>(this));
        }
    }
private:
    vector<Observer<T> *> m_observers;
};


#endif /* subject_h */

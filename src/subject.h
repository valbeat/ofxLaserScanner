#ifndef subject_h
#define subject_h

#include <studio.h>

//observerからの観察対象用templete
template <class T>
class Subject {
public:
    Subject() {}
    virtual ~Subject(){}
    // Observerを追加する
    void attach(Observer<T> &observer){
        m_observers.push_back(&observers);
    }
    // 登録されたObserverに通知する
    void notify() {
        vector<Observer<T> *>::iterator it;
        for (it=m_observers.begin();it!=m_observers.end();it++)
            // Observerのupdate関数を呼ぶ
            (*it)->update(static_cast<T *>(this));
        }
    }
private:
    // 登録されたオブザーバーのポインタ
    vector<Observer<T> *> m_observers;
};


#endif /* subject_h */

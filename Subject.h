#ifndef NOTE_SUBJECT_H
#define NOTE_SUBJECT_H

#include "Observer.h"

class Subject{
public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void unregisterObserver(Observer* o) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

#endif //NOTE_SUBJECT_H

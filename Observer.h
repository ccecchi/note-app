#ifndef NOTE_OBSERVER_H
#define NOTE_OBSERVER_H

class Observer{
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

#endif //NOTE_OBSERVER_H

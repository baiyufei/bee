#include <iostream>
#include <string>
#include <memory>

class WeekendStrategy {
public:
    void virtual spend() = 0;
};

class PlayStrategy: public WeekendStrategy {
public:
    void spend() { std::cout << " plays computer in weekend\n"; }
};

class ExerciseStrategy : public WeekendStrategy {
public:
    void spend() { std::cout << " excercises in weekend\n"; }
};

class StudyStrategy : public WeekendStrategy {
public:
    void spend() { std::cout << " studies in weekend\n"; }
};

class Student {
public:
    Student(std::string name,std::shared_ptr<WeekendStrategy> ws) : _name(name), _ws(ws) {};
    void spendWeekend() {
        std::cout << _name;
        _ws->spend();
    }
private:
    std::string _name;
    std::shared_ptr<WeekendStrategy> _ws;
};

int main() {
    std::shared_ptr<WeekendStrategy> p = std::make_shared<ExerciseStrategy>();
    Student a("xiao ming", p);
    a.spendWeekend();
    p = std::make_shared<PlayStrategy>();
    Student b("xiao bai", p);
    b.spendWeekend();
    p = std::make_shared<StudyStrategy>();
    Student c("xiao hong", p);
    c.spendWeekend();

    return 0;
}

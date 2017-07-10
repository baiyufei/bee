#include <iostream>
#include <string>
#include <memory>
#include <set>

using namespace std;

class News;

class Observer {
public:
    virtual void update(News*) = 0;
};

// subject
class News {
public:
    void addObserver(shared_ptr<Observer> ob) {
        _obs.insert(ob);
    }
    void removeObserver(shared_ptr<Observer> ob) {
        _obs.erase(ob);
    }

    void notifyObserver() {
        for (auto ob = _obs.begin(); ob != _obs.end(); ob++) {
            (*ob)->update(this);
        }
    }

    void setMessage(string s) {
        message = s;
        notifyObserver();
    }

    string getMessage() {
        return message;
    }

private:
    set<shared_ptr<Observer>> _obs;
    string message;
};

class Notice : public Observer {
public:
    void update(News *n) {
        content = n->getMessage();
    };
    void show() { cout << content << endl; }
private:
    string content;
};

int main() {
    News news;
    shared_ptr<Notice> n1 = make_shared<Notice>();
    shared_ptr<Notice> n2 = make_shared<Notice>();
    news.addObserver(n1);
    news.addObserver(n2);
    news.setMessage("first new");
    n1->show();
    n2->show();
    news.removeObserver(n2);
    news.setMessage("second new");
    n1->show();
    n2->show();

    return 0;
}

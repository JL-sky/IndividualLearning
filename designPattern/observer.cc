#include<iostream>
#include<list>

#if 0
class Monitor {
 public:
    void printPrice(int price) {
        std::cout << "monitor price >>> " << price << std::endl;
    }
};

class BillBoard {
 public:
    void displayPrice(int price) {
        std::cout << "BillBoard price >>> " << price << std::endl;
    }
};

class Stock {
 public:
    void set_price(int price) {
        price_ = price;
        monitor_->printPrice(price);
        billboard_->displayPrice(price);
    }

 private:
    int price_;
    std::unique_ptr<Monitor> monitor_;
    std::unique_ptr<BillBoard> billboard_;
};

void test() {
    Stock stock;
    stock.set_price(20);
}

#endif

#if 0

class Observer {
 public:
    virtual void update(int) = 0;

 private:
};

class Monitor : public Observer {
 public:
    void printPrice(int price) {
        std::cout << "monitor >>> " << price << std::endl;
    }
    void update(int price) override { printPrice(price); }
};

class BillBoard : public Observer {
 public:
    void displayPrice(int price) {
        std::cout << "billoard >>> " << price << std::endl;
    }

    void update(int price) override { displayPrice(price); }
};

class Stock {
 public:
    void attach(Observer *obj) { observerlist_.emplace_back(obj); }

    void deattach(Observer *obj) { observerlist_.remove(obj); }

    void notify(int price) {
        for (auto &obj : observerlist_) {
            obj->update(price);
        }
    }
    void set_price(int price) {
        price_ = price;
        notify(price);
    }

 private:
    int price_;
    std::list<Observer *> observerlist_;
};

void test() {
    Monitor monitor;
    BillBoard billBoard;

    Stock stock;
    stock.attach(&monitor);
    stock.attach(&billBoard);

    stock.set_price(100);
    stock.set_price(10000);
}

#endif

#if 1
class Stock;
class Observer {
 public:
    explicit Observer(Stock *stock);
    virtual ~Observer();
    virtual void update(int) = 0;

 protected:
    Stock *stock_;
};

class Monitor : public Observer {
 public:
    explicit Monitor(Stock *stock) : Observer(stock) {}
    void printPrice(int price) {
        std::cout << "monitor >>> " << price << std::endl;
    }
    void update(int price) override { printPrice(price); }
};

class BillBoard : public Observer {
 public:
    explicit BillBoard(Stock *stock) : Observer(stock) {}
    void displayPrice(int price) {
        std::cout << "billoard >>> " << price << std::endl;
    }

    void update(int price) override { displayPrice(price); }
};

class Stock {
 public:
    void attach(Observer *obj) { observerlist_.emplace_back(obj); }

    void deattach(Observer *obj) { observerlist_.remove(obj); }

    void notify(int price) {
        for (auto &obj : observerlist_) {
            obj->update(price);
        }
    }
    void set_price(int price) {
        price_ = price;
        notify(price);
    }

 private:
    int price_;
    std::list<Observer *> observerlist_;
};

Observer::Observer(Stock *stock) : stock_(stock) { stock_->attach(this); }
Observer::~Observer() { stock_->deattach(this); }

void test() {
    Stock stock;
    Monitor monitor(&stock);
    BillBoard billBoard(&stock);

    stock.set_price(1);
    stock.set_price(10);
    stock.set_price(1000);
}

#endif

int main() {
    test();
    return 0;
}

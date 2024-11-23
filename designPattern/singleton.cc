#include<mutex>
#include<iostream>

#if 1

class Singleton{
  public:
    static Singleton& GetInstance(){
      return instance_;
    }

    void print(){std::cout<<"sington mode ---- "<<std::endl;}
  private:
    static Singleton instance_;
    Singleton(){}
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
};

Singleton Singleton::instance_;

#endif


#if 0
class Singleton {
 public:
    static Singleton *GetInstance() {
        if (!instance_) {
            std::lock_guard<std::mutex> lock(mtx_);
            if (!instance_)
                instance_ = new Singleton();
        }
        return instance_;
    }

    void print(){std::cout<<"sington mode ---- "<<std::endl;}

 private:
    static Singleton *instance_;
    static std::mutex mtx_;

    Singleton() {};
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};


// 静态成员变量定义：初始化为 nullptr
Singleton* Singleton::instance_ = nullptr;

// 静态成员变量初始化：mutex
std::mutex Singleton::mtx_;
#endif

int main(){
  Singleton::GetInstance().print();
  //Singleton::GetInstance()->print();
  return 0;
}

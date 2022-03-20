#include<iostream>

// template base
template<class>
struct my_package_task;

// template specialization
template<class R, class ArgType>
struct my_package_task<R(ArgType)>{ // R(ArgType) is reference type function  
  R (&f)(ArgType); // f is reference type function of R(ArgType)
  template<class F> my_package_task(F&& f_):f(f_){};
  R get_value(){
    return R{0};
  }
};

int func(int a){
  return a*a;
};

int main(int argc, char *argv[])
{
  my_package_task<int(int)> task(func);
  std::cout<<task.get_value()<<std::endl;
  return 0;
}

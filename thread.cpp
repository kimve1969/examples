#include<iostream>
#include<thread>
#include<atomic>

// clang thread.cpp -o thread -lstdc++ -pthread -fsanitize=thread -fPIC
//int gint = 0; // concurrent is bad
std::atomic<int> gint(0); // concurrent is ok 

void incr(){
  for(int i=0; i<1'000'000; ++i) ++gint;
} 

int main(int argc, char *argv[])
{
  std::thread th[2]{std::thread(incr), std::thread(incr)};

  
  th[0].join();
  th[1].join();

  std::cout<<"gint = "<<gint<<"\n";
  
  return 0;
}


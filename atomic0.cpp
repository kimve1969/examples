#include<atomic>

static int v1=0;
std::atomic<int> v2{0};

int f1(){
  return ++v1;
}

int f2(){
  return v2.fetch_add(1, std::memory_order_relaxed);
}

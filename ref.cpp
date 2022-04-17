#include<iostream>

struct X{
  int m_a;
  X(int x=0):m_a(x){ std::cout<<"X(int)\n"; }
  X(const X& x):m_a(x.m_a){ std::cout<<"X(const X&)\n"; }
  X(X&& x){ std::cout<<"X(X&&)\n"; }
  X& operator=(const X& x){
    std::cout<<"X::operator(const X&)\n";
    m_a = x.m_a;
    return (*this);
  }
};

std::ostream& operator<<(std::ostream& out, const X& x){ return out<<x.m_a; }

X fval(){ return 0; }
X glbx(10);
X& flval(){ return glbx; }
const X& fclval(){ return glbx; }
X&& frval(){ return std::move(glbx); }

void g_by_val(X x){}
void g_by_clval(const X& x){}
void g_by_rval(X&& x){}

int main(){
  // --------------------- variants type X
  X x{0}; // by value
  X& lrefx = x; // by lvalue
  const X& clrefx = 5; // by const lvalue
  X&& rrefx = 6; // by rvalue

  std::cout<<"x = "<<x<<", lrefx = "<<lrefx<<", clrefx = "<<clrefx<<", rrefx = "<<rrefx<<std::endl;

  // ------- TEST to pass parameters to function ------
  std::cout<<"\nTEST g_by_val()\n";
  
  g_by_val(x); 
  g_by_val(lrefx);
  g_by_val(clrefx);
  g_by_val(rrefx);

  g_by_val( fval() );
  g_by_val( flval() );
  g_by_val( fclval() );
  g_by_val( frval() );
  
  std::cout<<"\nTEST g_by_clval()\n";

  g_by_clval(x); 
  g_by_clval(lrefx);
  g_by_clval(clrefx);
  g_by_clval(rrefx);

  g_by_clval( fval() );
  g_by_clval( flval() );
  g_by_clval( fclval() );
  g_by_clval( frval() );

  std::cout<<"\nTEST g_by_rval()\n";

  //g_by_rval(x); // cannot bind rvalue X&& to lvalue X
  //g_by_rval(lrefx); // cannot bind rvalue X&& to lvalue X
  //g_by_rval(clrefx); // cannot bind rvalue X&& to const lvalue X
  //g_by_rval(rrefx); // cannot bind rvalue X&& to const lvalue X

  g_by_rval( fval() );
  //g_by_rval( flval() ); // cannot bind rvalue X&& to const lvalue X
  //g_by_rval( fclval() ); // cannot bind rvalue X&& to const lvalue X
  g_by_rval( frval() );
  
  return 0;
}

#include <iostream>

void simple_print(const char *s) {
  std::cout << "[simple_print]" << s << std::endl;
}

struct S {
  int A;
};

template <int I, class T>
[[jit]]
void test(double f) {
  std::cout << "Test JIT Function: " << S{5}.A << "   " << f << std::endl;
}

/*
void test(int I, std::string __type_T)
{
  //
  ORCJITV2::emitCXXcode(IR(test<I, get_type(__type_T)));
  call(test<I, T>();
}
*/

template <int J>
[[jit]]
int test2() {
  switch (J) {
  case 1:
    return 42;
  case 2:
    return 53;
  default:
    return -1;
  }
}

[[jit]]
int test3(int a) {
  switch (a) {
  case 1:
    return 42;
  case 2:
    return 53;
  default:
    return -1;
  }
}

template <unsigned I> unsigned test4(unsigned a) { return a * I; }

unsigned bbb(unsigned a) { return a >> 1; }

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "Calling JIT function test" << std::endl;
  test<42, S>(3.14);
  std::cout << "Called JIT function test" << std::endl;

  std::cout << test2<2>() << std::endl;

  [[jit]] auto ret = test4<80>(90);
  std::cout << ret << std::endl;

  [[jit]] auto ret2 = bbb(test4<40>(12));
  std::cout << ret2 << std::endl;

  /* not supported yet
  auto ret3 = 0u;
  [[jit]] ret3 = test4<40>(12);
  std::cout << ret3 << std::endl;
  */

  [[jit]] int ttt;

  ttt = 42;

  return ttt + 42;
}

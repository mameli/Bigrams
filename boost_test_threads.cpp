#include <iostream>
#include <thread>
#include <chrono>
void wait(int seconds)
{
   std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void fun()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << i << '\n';
  }
}

int main()
{

  std::thread t{fun};
  t.join();
}

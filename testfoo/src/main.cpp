#include <foo/foo.h>
#include <iostream>

int main()
{
    auto result = foo::mysqrt(2);
    std::cout << result << "\n";
    return 0;
}

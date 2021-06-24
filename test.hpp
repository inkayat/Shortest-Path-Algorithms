#include <assert.h>
#include <string>
#include <string.h>


void ASSERT(int n, std::string test)
{
    if(test == std::string("test1.txt")) assert(n=140);
    if(test == std::string("test2.txt")) assert(n=163);
    if(test == std::string("test3.txt")) assert(n=150);
    if(test == std::string("test4.txt")) assert(n=131);
    if(test == std::string("test5.txt")) assert(n=-1);
}




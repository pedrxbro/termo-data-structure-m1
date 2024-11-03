#include <iostream>
#include <locale.h>
#include "func.hpp"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    menu();  
    return 0;
}

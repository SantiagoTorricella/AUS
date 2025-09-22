#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>

    const T& maximo (const T& a , const T& b)
    {
        return (a >= b) ? a : b;
    }
template<class T>
    const T& menor (const T& a ,  const T& b)
    {
        return (a <= b) ? a : b;
    }

int main () 
{
    cout << "Int mayor: " << maximo(4,6) << endl;
    cout << "Int Menor: " << menor(8,15) << endl;
    cout << "Char Menor: " << menor('c','x') << endl;
    cout << "Char Mayor: " << maximo ('z','y') << endl;
}



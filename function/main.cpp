#include <iostream>
#include <functional>

using namespace std; 


int isEven(int num) {
    return num % 2 == 0;
}

int main() {
    function<int(int)> f1(isEven);
    function<int(int)> f2 = &isEven;
    cout << f1(2) << f2(2) << endl;
}
#include <iostream>
#include <exception>

using namespace std;

int main() {
    try {
        throw invalid_argument("bad argument xxx");
    } catch (exception& e) {
        cout << "Got exception: " << e.what() << endl;
    }
    return 0;
}
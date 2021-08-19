#include <iostream>
#include "MultiSet.h"

using std::cout;
using std::endl;

int main(){
    cout << endl;
    cout << " ----- MULTISET" << endl; 
    MultiSet<char> m = MultiSet<char>(); 
    m.add('a');
    m.add('a');
    m.add('b');
    cout << "a: " << m.get('a') << endl; // a: 2 cout << "b: " << m.get('b') << endl; // b: 1 cout << "c: " << m.get('c') << endl; // c: 0 cout << "size: " << m.size() << endl; // 3
    cout << m.as_string() << endl;
    m.removen('a', 2);
    cout << m.as_string() << endl;
    // b: 1     // note no a:0 should be present
    m.removen('a',0);
    cout << m.as_string() << endl; // b: 1
    m.removen('b', 1);
    cout << m.as_string() << endl;
    m.removen('c',0); // no problem cout << m.as_string() << endl;
    m.add('c');
    m.add('c');
    m.add('c');
    cout << m.as_string() << endl; // c: 3
    try {
        m.removen('c',5); // too many
        // empty
        // empty
    } catch (std::out_of_range& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };
    cout << m.as_string() << endl; // c: 3
    return 0;
}
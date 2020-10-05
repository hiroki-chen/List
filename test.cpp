#include "MyList.hpp"
#include "ErrorLog.hpp"

/*
 * Notice: Index of the list starts at 0.
 */ 

int main() {
    std::vector<int> arr;
    int a[10] = {1, 2, 3, 4, 5, 6, 6, 6, 6, 7};
    char b[5] = {'a', 'b', 'c', 'd', 'e'};

    std::random_device e;
    std::uniform_int_distribution<int> rndList(0, 999);

    for (int i = 0; i < 10; i ++) {
        arr.push_back(rndList(e));
    }

    List<int> test(arr);
    List<int> test2(a, 10);
    
    test2.merge(test);
    test2.print();
    List<int>::iterator it = test.begin();
    it += 2;// Okay. test it passed
    test2.erase(it);
    test2.print();

    return 0;
}
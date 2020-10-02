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
    List<int> test3(test);
    List<char> test4(b, 5);
    List<int> test5(a, 10);
    
    test2.sort();
    test2.insertHandler(test2.begin(), 3);
    test2.updateHandler(test2.begin(), 4);
    test2.push_front(333);
    int i = 1;
    for (List<int>::iterator it = test2.begin(); it != test2.end(); ++it) {
        std::cout << *it << std::endl;
        //if (i ++ == 3) { test2.erase(it);}
    }
    List<int>::iterator it = test2.begin();
    it.advance(1);
    std::cout << *it << std::endl;
    //test.clear();
    std::cout << test2.listSize() << std::endl;
    test2.print();

    return 0;
}
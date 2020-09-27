#include "MyList.hpp"

int main() {
    std::vector<int> arr;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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
    test.print();
    test2.print();
    test3.print();
    test4.print();

    test.sort(true);
    test.print();

    std::cout << "test.listSize(): " << test.listSize() << std::endl;
    std::cout << "test.front(): " << test.front() << std::endl;

    std::cout << "doing merge" << std::endl;
  
    test2.merge(test);
    test2.pop_back();
    test2.print();
    test.clear();
    test.print();

    return 0;
}
#include "MyList.hpp"
#include "ErrorLog.hpp"

template<typename T>
List<T> meld(List<T>& lhs, List<T>& rhs) {
    auto i1 = lhs.begin(), i2 = rhs.begin();
    List<T> ans;
    while (i1!= lhs.end() && i2 != rhs.end()) {
        ans.push_back(*i1);
        lhs.erase(i1++);
        ans.push_back(*i2);
        rhs.erase(i2++);
    }

    while (i1 != lhs.end()) {
        ans.push_back(*i1);
        lhs.erase(i1++);
    }

    while (i2 != rhs.end()) {
        ans.push_back(*i2);
        rhs.erase(i2++);
    }

    return ans;
}

template<typename T>
void split(List<T> c, List<T>& a, List<T>& b) {
    auto it = c.begin();
    int i = 0;

    while (it++ != c.end()) {
        if (i++ % 2 == 0) { b.push_back(*it); }
        else { a.push_back(*it); }
    }
}

/*
 * Notice: Index of the list starts at 0.
 */ 

int main() {
    std::vector<int> arr;
    int a[6] = {1, 2, 3, 4, 5, 6};
    char b[5] = {'a', 'b', 'c', 'd', 'e'};

    std::random_device e;
    std::uniform_int_distribution<int> rndList(0, 999);

    for (int i = 0; i < 10; i ++) {
        arr.push_back(rndList(e));
    }

    List<int> test(arr);
    List<int> test2(a, 6);
    
    test.print();
    test2.print();

    List<int> test3 = meld(test, test2);

    test3.print();
    test3.makeCircle();                                                                                                                                                                                                                                                                                                                                                                                                                         
    List<int> na, nb;
    test3.split(na, nb);
    na.print();
    nb.print();

    return 0;
}
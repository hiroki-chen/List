# List
This is a basic datastructure for **list**.
## How to use this?
1. You can exert some operations on this structure by using `iterator` defined as follows:
```cpp
    class iterator {
        ListNode<T>* field;
        iterator* begin;
        iterator* end;

    public:
        //There would be a constructor that does nothing.
        iterator();
        iterator(const iterator& i);
        iterator(ListNode<T>* node);
            
        bool operator ==(const iterator& rhs);
        bool operator !=(const iterator& rhs);
        void operator ++();
        void operator --();
        T& operator *();
    };
```
2. Or you can simply using interface functions provided by me:
```cpp
    void insertHandler(T value, int position);
    void deleteHandler(T value);
    void updateHandler(T value, T newValue);
    void searchHandler(T value);

    /*
     * Some implementations used to alter the list itself.
     */ 

    void print(void);
    void reverse(void);
    void sort(bool bigger = false);
    void merge(List<T>& list);
    void clear(void);
    void unique(void);

    friend ListNode<T>* doMerge(ListNode<T>* left, ListNode<T>* right);
    friend ListNode<T>* doSort(ListNode<T>* head);
    friend ListNode<T>* doReverse(ListNode<T>* head);

    T front(void);
    void push_back(T value);
    void pop_back(void);
    void push_front(T value);
    void pop_front(void);
    int listSize(void);
    bool empty(void);

    bool operator == (List<T> list);
    bool operator != (List<T> list);
    void operator += (T value);
    void operator += (List<T>& list) = delete; // You cannot use this because this is a forward list.
```

## NOTICE
Current version is yet not stable and may contain numerous bugs that can be deadly to your programming as well. Also it may be low in effiency. 
If you want to depoly any applications on your devices, please read the source code rather carefully, while I am still working hard on enhancing the performance of 
the data structure.

You can define a `List` through many different ways as below:
```cpp
List<int> test(arr);
List<int> test2(a, 10);
List<int> test3(test);
List<char> test4(b, 5);
List<int> test5(a, 10);
```
**stringify is about to be supported :)*


## Update Log
### 2020-9-26
1. Added orginal version.

### 2020-9-27
1. Fixed bugs of `insertHandler(T, int)`, so it will not collide with `deleteHandler`;
2. Fixed bugs of `deleteHandler(T)`. Now you can delete more than one elements.
3. Added `iterator` structure, but yet to be fully drived.

### 2020-9-28 1
1. Fixed bugs of `deleteHandler(T)`. Now it can delete successive values. Overloaded version will be soon supported;
2. Added new features about `ErrorLog` which is able to print error informations on the screen without using `std::cout`.

### 2020-9-28 2
1. Deleted `ErrorLog`, and updated to `exception` class;
2. Added basic support for `List<T>::iterator` for `List`, and with error checking.
3. Abandoned some old ideas.

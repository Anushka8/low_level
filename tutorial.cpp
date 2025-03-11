#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std; // to avoid std::cout everytime
/*******************************************************************************************************************
HELLO WORLD
*******************************************************************************************************************/
void hello_world()
{
    int x;
    cout << "Hello, world!" << endl;
    cin >> x;
    cout << x + 86 << endl;
}

/*******************************************************************************************************************
POINTERS
*******************************************************************************************************************/
void pointers()
{
    int num = 10;
    int *ptr = &num; // ptr is a pointer to an int and stores the address of num

    cout << "Value of num: " << num << endl;
    cout << "Value stored in pointer: " << ptr << endl;
    cout << "Address of num: " << &num << endl;
    // *ptr means deferencing, allowing actual value stored at the address
    std::cout << "Value at address stored in pointer: " << *ptr << endl;

    *ptr = 20;
    cout << "Updated num: " << num << endl;
}

/*******************************************************************************************************************
OPERATOR OVERLOAD
*******************************************************************************************************************/

class Test
{
    int x, y;

public:
    Test() { cout << "Constructor is called\n"; }
    ~Test() { cout << "Destructor is called\n"; }

    void *operator new(size_t size)
    {
        cout << "Allocating " << size << " bytes\n";
        return malloc(size);
    }

    void operator delete(void *ptr) noexcept
    {
        cout << "Freeing memory\n";
        free(ptr);
    }
};

/*******************************************************************************************************************
DYNAMIC ARRAY
*******************************************************************************************************************/
class DynamicArray
{
private:
    int *arr;
    size_t capacity;
    size_t size;

public:
    // constructor with capacity as a parameter, followed for initializer (no significant effect)
    DynamicArray(size_t cap = 2) : capacity(cap), size(0)
    {
        arr = new int[capacity];
    }

    // if size increases, dynamically increase array size, reassign values to bigger array
    void push_back(int val)
    {
        if (capacity == size)
        {
            capacity *= 2;
            int *newArr = new int[capacity];
            for (size_t i = 0; i < size; i++)
            {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = val;
    }

    int operator[](size_t index) const
    {
        return arr[index];
    }

    ~DynamicArray()
    {
        delete[] arr;
    }
};

/*******************************************************************************************************************
MEMORY POOL ALLOCATOR
*******************************************************************************************************************/
class MemoryPool
{
private:
    vector<void *> pool;

public:
    MemoryPool(size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            pool.push_back(malloc(32));
        }
    }

    void *allocate()
    {
        if (pool.empty())
            return malloc(32);
        void *block = pool.back();
        pool.pop_back();
        return block;
    }

    void deallocate(void *block)
    {
        pool.push_back(block);
    }

    ~MemoryPool()
    {
        for (void *block : pool)
            free(block);
    }
};

int main()
{
    // hello_world();

    // pointers();

    // Test *obj = new Test();
    // delete obj;

    // DynamicArray arr;
    // arr.push_back(4);
    // arr.push_back(5);
    // arr.push_back(6);
    // for (size_t i = 0; i < 3; i++)
    // {
    //     cout << "Element " << i << " is " << arr[i] << endl;
    // }

    MemoryPool pool(1);
    int *a = (int *)pool.allocate();
    *a = 42;
    cout << "Value: " << *a << endl;
    pool.deallocate(a);

    return 0;
}
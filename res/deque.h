#ifndef VECTOR_H
#define VECTOR_H

#endif // VECTOR_H
using namespace std;
template<typename T>
class deque
{
    private:
        T* array;
        int capacity;
        int currentSize;

    public:
        deque() {
            capacity = 10000;
            array = new T[10000];
            currentSize = 0;
        }

        deque(int size) {
            capacity = size;
            array = new T[size];
            currentSize = 0;
        }


    int size(){
        return capacity;
    }

    void push_back(T val){
        if(currentSize < capacity){
            array[currentSize++] = val;
        }else{
            capacity *= 1.5;
            array2 = new T[capacity];
            memcpy(array2, array, sizeof(array));
            delete array;
            array = &array2;
            push_back(val);
        }
        currentSize++;
    }

    void push_front(T val){
        if(currentSize < capacity){
            int i=0;
            for(i=currentSize;i>=0;i--)
                array[i+1] = array[i];
            array[0] = val;
        }else{
            capacity *= 1.5;
            T* array2 = new T[capacity];
            memcpy(array2, array, currentSize * sizeof(T));
            delete array;
            array = &array2;
            push_front(val);
        }
        currentSize++;
    }

    void pop_back(){
        if(currentSize > 0)
             currentSize--;

    }

    T back(){
        if(currentSize > 0)
            return array[currentSize];

    }

    void clear(){
        delete array;
        array = new T[capacity];
    }
};

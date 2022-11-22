#include <vector>
#include <iostream>

template <typename T>
class maxHeap {

private:
    std::vector<T> a;
    
    int parent(int i) {
        //function to return index of parent
        return i / 2;
    }

    int lson(int i) {
        //function to return index of left child
        return 2 * i + 1;
    }

    int rson(int i) {
        //function to return index of right child
        return 2 * i + 2;
    }

    void heapify(int i) {
        int ls = lson(i);
        int rs = rson(i);
        int max_index;
        max_index = ls < a.size() && a[ls] > a[i] ? ls : i;
        max_index = rs < a.size() && a[rs] > a[max_index] ? rs : max_index;

        if (max_index != i) {
            int temp = a[i];
            a[i] = a[max_index];
            a[max_index] = temp;
            heapify(max_index);
        }
    }
public:
    void heapPush(T& x) {
        //function to add a element to the heap
        a.push_back(x);
        int i = a.size() - 1;
        int p_i = parent(i);
        while(i!=0 && a[i] > a[p_i]) {
            int temp = a[i];
            a[i] = a[p_i];
            a[p_i] = temp;
            i = p_i;
            p_i = parent(i);
        }
    }

    T heapPop(int i = 0) {
        //function to remove a element from the heap, will remove the top element if index value not specified
        auto value = a[i];
        a[i] = a[a.size() - 1];
        a.pop_back();
        heapify(i);
        return value;
    }

    void heapPrint() {
        //function to print the heap
        std::cout<<"\n================================heapPrint Results================================\n";
        for (auto x:a){
            std::cout<<x<<",";
        }
        std::cout<<std::endl;
    }

};

int main() {
    //test function
    maxHeap<int> heap_test;
    int test1=4, test2=432, test3=7, test4=46, test5=1, test6=33, test7=3, test8=0;
    heap_test.heapPush(test1);
	heap_test.heapPrint();
	heap_test.heapPush(test2);
	heap_test.heapPush(test3);
	heap_test.heapPush(test4);
	heap_test.heapPush(test5);
	heap_test.heapPrint();
	heap_test.heapPop();
	heap_test.heapPrint();
	heap_test.heapPop();
	heap_test.heapPrint();
	heap_test.heapPop(2);
	heap_test.heapPrint();
    heap_test.heapPush(test7);
    heap_test.heapPush(test8);
	heap_test.heapPop(1);
	heap_test.heapPrint();

    return 0;
}
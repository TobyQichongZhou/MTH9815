//Qichong Zhou
//22th Nov 2022
#include <vector>
#include <iostream>

template <typename T>
class quickSort{
private:
    void swap(std::vector<T>& a, int i1, int i2) {
        //function to swap two elements
        auto temp = a[i1];
        a[i1] = a[i2];
        a[i2] = temp;
    }

    int seperate(std::vector<T>& a, int l, int r) {
        // function to seperate the list needed to sort into list smaller than pivot and list bigger than pivot, return the location of povit
        auto pivot_value = a[r];
        int low_zone_end = l;
        for (int i = l; i < r; i++) {
            if (a[i] <= pivot_value) {
                swap(a, i, low_zone_end);
                low_zone_end++;
            }
        }
        swap(a, low_zone_end, r);
        return low_zone_end;
    }

    void sorted_(std::vector<T>& a, int l, int r) {
        //recursion function to run quicksort
        if (r - l > 0) {
            auto pivot_value = a[r];
            auto pivot = seperate(a, l, r);
            sorted_(a, l, pivot - 1);
            sorted_(a, pivot + 1, r);
        }
        
    }

public:

    void sorted(std::vector<T>& a) {
        //exposed interface of quicksort for user
        int l = 0, r = a.size() - 1;
        sorted_(a, l, r);
    }

};

template <typename T>
void print_sorted_array(std::vector<T>& a) {
    std::cout<<"\n================================Sorted Array================================\n";
    for (auto x:a) {
        std::cout<<x<<",";
    }
    std::cout<<std::endl;
}

int main(){
    //test case
    std::vector<int> test1 = {};
    std::vector<int> test2 = {0};
    std::vector<int> test3 = {1,0};
    std::vector<int> test4 = {0,2,1};
    std::vector<int> test5 = {1,2,3,4,5,6,6,7};
    std::vector<int> test6 = {42,5,54,5,435,36,3,76,46,534,5,56,432,5654,8,7,8,54,1,3,576,78,62,3,437,6,96,756};
    quickSort<int> qs_test;
    qs_test.sorted(test1);
    qs_test.sorted(test2);
    qs_test.sorted(test3);
    qs_test.sorted(test4);
    qs_test.sorted(test5);
    qs_test.sorted(test6);
    print_sorted_array(test1);
    print_sorted_array(test2);
    print_sorted_array(test3);
    print_sorted_array(test4);
    print_sorted_array(test5);
    print_sorted_array(test6);
       
    return 0;

}
#include <iostream>
#include <cstring>

class MinStack {
public:
    MinStack(): top_(0), capacity_(4), data_(new int[4]), min_(new int[4]) {}
    
    void push(int val) {
        if (top_ == capacity_){
            capacity_ *= 2;
            int* tmp_data = new int[capacity_];
            std::memcpy(tmp_data, data_, top_ * sizeof(int));
            // std::copy(data_, &data_[top_], tmp_data);
            
            std::swap(tmp_data, data_);
            delete[] tmp_data;

            int* tmp_min = new int[capacity_];
            std::memcpy(tmp_min, min_, top_ * sizeof(int));
            // std::copy(min_, &min_[top_], tmp_min);

            std::swap(tmp_min, min_);
            delete[] tmp_min;
        }
        if(top_ > 0){min_[top_] = std::min(min_[top_-1], val);}
        else{min_[0] = val;}
        data_[top_++] = val;
    }
    
    void pop() {
        --top_;
    }
    
    int top() {
        return data_[top_-1];
    }
    
    int getMin() {
        return min_[top_-1];
    }
    ~MinStack(){
        delete[] min_;
        delete[] data_;
    }
private:
    size_t top_;
    size_t capacity_;
    int* data_;
    int* min_;
};

int main(){
    MinStack ms = MinStack();
    for(int i = 0; i < 10; ++i){
        ms.push(-10 + i*i);
        ms.push(-10 + i*i);
        ms.pop();
        std::cout << "first = " << ms.top() << " min = " << ms.getMin() << '\n';

    }

}
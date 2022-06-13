#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
/*
 * VarArr: Template Class for Custom Vector to resolve init values
 * Copyright (C) 2022 Everett Gaius S. Vergara, evergara@shinra.com.ph
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


template<typename T>
class VarArr
{
public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer begin) : data_ptr_(begin) {};
        auto operator*() const -> reference { return *data_ptr_; }
        auto operator->() -> pointer { return data_ptr_; }
        auto operator++() -> Iterator& { ++data_ptr_; return *this; }
        auto operator++(int) -> Iterator { Iterator t = *this; ++data_ptr_; return t; }
        friend auto operator==(const Iterator& lhs, const Iterator& rhs) -> bool { return lhs.data_ptr_ == rhs.data_ptr_; }
        friend auto operator!=(const Iterator& lhs, const Iterator& rhs) -> bool { return lhs.data_ptr_ != rhs.data_ptr_; }
    
    private:
        pointer data_ptr_;
    };

    struct ConstantIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        ConstantIterator(pointer begin) : data_ptr_(begin) { };
        auto operator*() const -> reference { return *data_ptr_; }
        auto operator->() -> pointer { return data_ptr_; }
        auto operator++() -> ConstantIterator& { ++data_ptr_; return *this; }
        auto operator++(int) -> ConstantIterator { ConstantIterator t = *this; ++data_ptr_; return t; }
        friend auto operator==(const ConstantIterator& lhs, const ConstantIterator& rhs) -> bool { return lhs.data_ptr_ == rhs.data_ptr_; }
        friend auto operator!=(const ConstantIterator& lhs, const ConstantIterator& rhs) -> bool { return lhs.data_ptr_ != rhs.data_ptr_; }
    
    private:
        pointer data_ptr_;
    };

    auto begin() const -> Iterator { return Iterator(data_); }
    auto end() const -> Iterator { return Iterator(data_ + size_); }
    auto cbegin() const -> ConstantIterator { return ConstnatIterator(data_); }
    auto cend() const -> ConstantIterator { return ConstantIterator(data_ + size_); }    

public:
    VarArr () : data_(new T[1]), size_(1), push_ix_(0) {};
    VarArr (size_t size) : data_(new T[size]), size_(size), push_ix_(0) {}

    // Copy Constructor
    VarArr(const VarArr& rhs) : data_(new T[rhs.size_]), size_(rhs.size_) { 
        std::copy(rhs.data_, rhs.data_ + size_, data_); 
        push_ix_ = rhs.push_ix_;
    }

    // Move Constructor
    VarArr(VarArr&& rhs) : data_(rhs.data_), size_(rhs.size_), push_ix_(rhs.push_ix_) { 
        rhs.size_ = 0; 
        rhs.data_ = nullptr; 
        rhs.push_ix_ = 0;
    }

    // Copy Assignment
    VarArr& operator=(const VarArr& rhs) {

        if (&rhs != this) {
            delete[] data_;
            data_ = new T[size_];
            std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
            size_ = rhs.size_;
            push_ix_ = rhs.push_ix_;
        }

        return *this;
    }

    VarArr& operator=(VarArr&& rhs) {

        if (&rhs != this) {

            delete[] data_;
            data_ = rhs.data_;
            size_ = rhs.size_;
            push_ix_ = rhs.push_ix_;

            rhs.size_ = 0;
            rhs.data_ = nullptr;
            rhs.push_ix_ = 0;
        }

        return *this;
    }

    T& operator[](int i) const {

        return data_[i];
    }

    ~VarArr() {

        delete[] data_;
    }

    const size_t size() const {  

        return size_; 
    }

    void push(T t) {

        if (push_ix_ == size_) {
            T *new_data {new T[2 * size_]};
            if (data_ != nullptr) {
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                size_ <<= 1;
            }
            data_ = new_data;
            std::cout << "resize to: " << size_ << "\n"; 
        }

        *(data_ + push_ix_) = t;
        ++push_ix_;
    }

    T* data() {

        return data_;
    }
    
    // void reserve(size_t size) {

    //     if (size > size_) {
    //         T *t {new T[size]};

    //         push_ix_ = t + (push_ptr_ - data_);

    //         if (data_ != nullptr) {
    //             std::copy(data_, data_ + size, t);
    //             delete[] data_;
    //         }
            
    //         data_ = t;
    //         size_ = size;
    //     }
    // }

private:
    T *data_ {nullptr};
    size_t size_ {0};
    size_t push_ix_ {0};
};

auto main(int argc, char* argv[]) -> int
{

    VarArr<int> int_arr(10);

    for (int i = 0; i < 11; ++i)
    int_arr.push(i);



    // // const int *p = 10;
    // //const char *str = "afdadf";

    // // Regular Constructor
    // VarArr<int> var_arr_int_a(10);

    // // Copy Constructor
    // VarArr<int> var_arr_int_b(20);


    // int *a, b;
    // int &x = b, y;
    

    return 0;
}
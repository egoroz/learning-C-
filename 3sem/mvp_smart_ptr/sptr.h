#pragma once

#include <iostream>

template <class T>
class UniquePtr {
public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(const UniquePtr& o) = delete;
    UniquePtr& operator=(const UniquePtr& o) = delete;

    UniquePtr(UniquePtr&& o) {
        ptr = o.ptr;
        o.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        delete ptr;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
        return *this;
    }

    UniquePtr(T* p) : ptr(p) {}

    T* operator->() { return ptr; }

    T& operator*() { return *ptr; }

    ~UniquePtr() { delete ptr; }

private:
    T* ptr;
};


// ================================================


struct RefCntBlock {
    size_t strong, weak;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    friend class WeakPtr<T>;
public:
    SharedPtr(): s_ptr(nullptr), cnt(nullptr) {}
    SharedPtr(const SharedPtr& o): s_ptr(o.s_ptr), cnt(o.cnt) { if (cnt) ++cnt->strong; }
    SharedPtr& operator=(const SharedPtr& o) {
        if (this != &o) {
            (*this).~SharedPtr();
            s_ptr = o.s_ptr;
            cnt = o.cnt;
            if (cnt) ++cnt->strong;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& rhs): s_ptr(rhs.s_ptr), cnt(rhs.cnt) {
        rhs.s_ptr = nullptr;
        rhs.cnt = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& rhs) {
        if (this != &rhs) {
            //std::cerr << "strong: " << cnt->strong << "\n";
            (*this).~SharedPtr();
            s_ptr = rhs.s_ptr;
            cnt = rhs.cnt;
            rhs.s_ptr = nullptr;
            rhs.cnt = nullptr;
        }
        return *this;
    }

    SharedPtr(T* p): s_ptr(p), cnt(new RefCntBlock{1, 0}) {}

    SharedPtr(const WeakPtr<T>& o) : s_ptr(o.w_ptr), cnt(o.cnt) {
        if (cnt) ++cnt->strong;
    }

    void Reset() {
        (*this).~SharedPtr();
        s_ptr = nullptr;
        cnt = nullptr;
    }

    T* operator->() { return s_ptr; }

    T& operator*() { return *s_ptr; }

    ~SharedPtr () {
        if (!cnt) {return;}
        //std::cerr << "strong: " << cnt->strong << ""weak: << cnt->weak << "\n";
        if (--cnt->strong == 0) {
            delete s_ptr;
            if (cnt->weak == 0) {
                delete cnt;
            }    
        }
    }


private:
    T* s_ptr;
    RefCntBlock* cnt;
};

template <class T>
class WeakPtr {
    friend class SharedPtr<T>;
public:
    WeakPtr(): w_ptr(nullptr), cnt(nullptr) {}
    WeakPtr(const WeakPtr& o): w_ptr(o.w_ptr), cnt(o.cnt) { if (cnt) ++cnt->weak; }
    WeakPtr& operator=(const WeakPtr& o) {
        if (this != &o) {
            (*this).~WeakPtr();
            w_ptr = o.w_ptr;
            cnt = o.cnt;
            if (cnt) {++cnt->weak;}
        }
        return *this;
    }

    WeakPtr(WeakPtr&& rhs): w_ptr(rhs.w_ptr), cnt(rhs.cnt) {
        rhs.w_ptr = nullptr;
        rhs.cnt = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& rhs) {
        if (this != &rhs) {
            (*this).~WeakPtr();
            w_ptr = rhs.w_ptr;
            cnt = rhs.cnt;
            rhs.w_ptr = nullptr;
            rhs.cnt = nullptr;
        }
        return *this;
    }

    WeakPtr(const SharedPtr<T>& o): w_ptr(o.s_ptr), cnt(o.cnt) { if (cnt) ++cnt->weak; }

    WeakPtr& operator=(const SharedPtr<T>& o) {
        (*this).~WeakPtr();
        w_ptr = o.s_ptr;
        cnt = o.cnt;
        //std::cerr << "weak: " << cnt->weak << "\n";
        if (cnt) {++cnt->weak;}
        //std::cerr << "weak: " << cnt->weak << "\n";
        return *this;
    }

    void Reset() {
        (*this).~WeakPtr();
        w_ptr = nullptr;
        cnt = nullptr;
    }

    bool Expired() const { 
        if (!cnt || cnt->strong == 0) {
            // std::cerr << "HERE1\n";
            return true;
        } else {
            // std::cerr << "HERE2\n";
            return false;
        }
    }

    SharedPtr<T> Lock() { 
        if (Expired()) {
            return SharedPtr<T>();
        } else {
            return SharedPtr<T>(*this);
        }
    }

    ~WeakPtr () {
        if (!cnt){return;}
        //std::cerr << "strong: " << cnt->strong << ""weak: << cnt->weak << "\n";
        if (--cnt->weak == 0 && cnt->strong == 0) {
            delete cnt;
        }
    }

private:
    T* w_ptr;
    RefCntBlock* cnt;
};

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

    UniquePtr& operator=(UniquePtr&& o) {
        if (&o == this) {
            return *this;
        }
        delete ptr;
        ptr = o.ptr;
        o.ptr = nullptr;
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
    SharedPtr() : s_ptr(nullptr), cnt(nullptr) {}
    SharedPtr(const SharedPtr& o) : s_ptr(o.s_ptr), cnt(o.cnt) { if (cnt) ++cnt->strong; }
    SharedPtr& operator=(const SharedPtr& o) {
        if (this != &o) {
            this->~SharedPtr();
            s_ptr = o.s_ptr;
            cnt = o.cnt;
            if (cnt) ++cnt->strong;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& o) : s_ptr(o.s_ptr), cnt(o.cnt) {
        o.s_ptr = nullptr;
        o.cnt = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& o) {
        if (this != &o) {
            this->~SharedPtr();
            s_ptr = o.s_ptr;
            cnt = o.cnt;
            o.s_ptr = nullptr;
            o.cnt = nullptr;
        }
        return *this;
    }

    SharedPtr(T* p) : s_ptr(p), cnt(new RefCntBlock{1, 0}) {}

    // Implementation below
    SharedPtr(const WeakPtr<T>& o) : s_ptr(o.w_ptr), cnt(o.cnt) {
        if (cnt) ++cnt->strong;
    }

    // Replaces pointer with nullptr
    void Reset() {
        this->~SharedPtr();
        s_ptr = nullptr;
        cnt = nullptr;
    }

    T* operator->() { return s_ptr; }

    T& operator*() { return *s_ptr; }

    ~SharedPtr () {
        if (cnt) {
            if (--cnt->strong == 0) {
                delete s_ptr;
                if (cnt->weak == 0) {
                    delete cnt;
                }
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
    WeakPtr() : w_ptr(nullptr), cnt(nullptr) {}
    WeakPtr(const WeakPtr& o) : w_ptr(o.w_ptr), cnt(o.cnt) { if (cnt) ++cnt->weak; }
    WeakPtr& operator=(const WeakPtr& o) {
        if (this != &o) {
            this->~WeakPtr();
            w_ptr = o.w_ptr;
            cnt = o.cnt;
            if (cnt) ++cnt->weak;
        }
        return *this;
    }

    WeakPtr(WeakPtr&& o) : w_ptr(o.w_ptr), cnt(o.cnt) {
        o.w_ptr = nullptr;
        o.cnt = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& o) {
        if (this != &o) {
            this->~WeakPtr();
            w_ptr = o.w_ptr;
            cnt = o.cnt;
            o.w_ptr = nullptr;
            o.cnt = nullptr;
        }
        return *this;
    }

    WeakPtr(const SharedPtr<T>& o) : w_ptr(o.s_ptr), cnt(o.cnt) { if (cnt) ++cnt->weak; }

    WeakPtr& operator=(const SharedPtr<T>& o) {
        this->~WeakPtr();
        w_ptr = o.s_ptr;
        cnt = o.cnt;
        if (cnt) ++cnt->weak;
        return *this;
    }

    // Replaces pointer with nullptr
    void Reset() {
        this->~WeakPtr();
        w_ptr = nullptr;
        cnt = nullptr;
    }

    bool Expired() const { 
        if (!cnt || cnt->strong == 0) {
            return true;
        } else {
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
        if (cnt && --cnt->weak == 0 && cnt->strong == 0) {
            delete cnt;
        }
    }

private:
    T* w_ptr;
    RefCntBlock* cnt;
};
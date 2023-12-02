#include <iostream>
#include <vector>
#include <cstdint>

using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using sll = signed long long;
using i64 = __int64_t;

class BigInt{
public:
    std::vector<u16> nums;
    i16 sign;
    const u16 u16_max = static_cast<u16>(-1); 

    BigInt();
    ~BigInt() = default;
    BigInt(const std::string& s);
    BigInt(const BigInt&) = default;
    BigInt(BigInt&&) = default;
    BigInt& operator=(const BigInt&) = default;
    BigInt& operator=(BigInt&&) = default;

    BigInt& operator=(const u16&);


    // BigInt& operator+(const BigInt&) = delete;
    // BigInt& operator-(const BigInt&) = delete;
    // BigInt& operator*(const BigInt&) = delete;
    BigInt& operator%(const BigInt&) = delete;
    BigInt& operator/(const BigInt&) = delete;

    BigInt& operator++();                       //prefix
    BigInt& operator--();
    BigInt operator++(int);                    //postfix
    BigInt operator--(int);
    
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);

    bool operator==(const BigInt&);
    bool operator<(const BigInt&);
    bool operator<=(const BigInt&);
    bool operator>(const BigInt&);
    bool operator>=(const BigInt&);

    void DeleteLeadingZeros();
    void SetSize(size_t);
    void BinaryWrite();
};

BigInt& BigInt::operator++(){
    BigInt t("1");
    *this += t;
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt old(*this);
    BigInt t("1");
    *this += t;
    return old;
}

BigInt& BigInt::operator--(){
    BigInt t("1");
    *this -= t;
    return *this;
}

BigInt BigInt::operator--(int){
    BigInt old(*this);
    BigInt t("1");
    *this -= t;
    return old;
}

BigInt operator+(const BigInt& a, const BigInt& b){
    BigInt total = a;
    total += b;
    return total;
}

BigInt operator-(const BigInt& a, const BigInt& b){
    BigInt total = a;
    total -= b;
    return total;
}

BigInt operator*(const BigInt& a, const BigInt& b){
    BigInt total = a;
    total *= b;
    return total;
}

BigInt Abs(const BigInt& a){
    BigInt t = a;
    if (a.sign == -1){t.sign = 1;}
    return t;
}

BigInt::BigInt(){
    sign = 0;
    for (size_t i = 0; i < 4; ++i){
        nums.push_back(0);
    }
}



BigInt::BigInt(const std::string& s) {
    size_t start = 0;

        if (s[0] == '-'){sign = -1; start = 1;}
        else if(s.length() == 1 && s == "0"){sign = 0; for (size_t i = 0; i < 2; ++i){nums.push_back(0);}; return;}
        else {sign = 1;}

        for (size_t i = start; i < s.length(); ++i) {
            u16 carry = s[i] - '0';
            for (auto& num : nums) {
                u32 tmp = static_cast<u32>(num) * 10 + carry;
                num = tmp & 0xFFFF;
                carry = tmp >> 16;
            }
            if (carry > 0) nums.push_back(carry);
        }
        for (size_t i = 0; i < 2; ++i){
        nums.push_back(0);
    }
}

BigInt& BigInt::operator=(const u16& u){
    for (size_t i = 1; i < nums.size(); ++i){ nums[i] = 0;};
    if(u == 0){sign = 0;}
    nums[0] = u;
    return *this;
}

BigInt& BigInt::operator+=(const BigInt& rhs){
    size_t i_max = std::max(nums.size(), rhs.nums.size());
    BigInt t = rhs;
    while (nums.size() < i_max + 1){nums.push_back(0);}
    while (t.nums.size() < i_max + 1){t.nums.push_back(0);}
    if (sign == 1 && rhs.sign == 1){
        for (size_t i = 0; i < i_max; ++i){
            if(nums[i] > u16_max - rhs.nums[i]){nums[i+1]++;}
            nums[i] += rhs.nums[i];
        }
    }

    else if (sign == -1 && rhs.sign == -1){
        for (size_t i = 0; i < i_max; ++i){
            if(nums[i] > u16_max - rhs.nums[i]){nums[i+1]++;}
            nums[i] += rhs.nums[i];
        }
    }
    else if (Abs(*this) >= Abs(rhs)){
        
        if (sign == 1 && rhs.sign == -1){
            for(size_t i = 0; i < i_max; ++i){
                if(nums[i] < rhs.nums[i]){nums[i+1]--; nums[i] = (u16_max + 1) - rhs.nums[i] + nums[i];}
                else{nums[i] -= rhs.nums[i];}
            }
        }
        else if (sign == -1 && rhs.sign == 1){
        for(size_t i = 0; i < i_max; ++i){
            if(nums[i] < rhs.nums[i]){nums[i+1]--; nums[i] = (u16_max + 1) - rhs.nums[i] + nums[i];}
            else{nums[i] -= rhs.nums[i];}
            }
            // std::cout << "HERE"<<'\n';
        }
        if (sign != rhs.sign){
            bool flag = true;
            for(size_t i = 0; i < nums.size(); ++i){
                if(nums[i] != 0){flag = false; break;}
            }
            if (flag){sign = 0;}
        }
    }
    
    else if(Abs(*this) < Abs(rhs)){
        if (sign == 1 && rhs.sign == -1){
            for (size_t i = 0 ; i < i_max; ++i){
                if (nums[i] > rhs.nums[i]){nums[i+1]++; nums[i] = (u16_max + 1) - nums[i] + rhs.nums[i];}
                else{nums[i] = rhs.nums[i] - nums[i];}
            }
            sign = -1;
            }

        else if (sign == -1 && rhs.sign == 1){
            for (size_t i = 0 ; i < i_max; ++i){
                if (nums[i] > rhs.nums[i]){nums[i+1]++; nums[i] = (u16_max + 1) - nums[i] + rhs.nums[i];}
                else{nums[i] = rhs.nums[i] - nums[i];}
            }
            sign = 1;
        }

        else if (sign == 0 && rhs.sign == 1){nums = rhs.nums; sign = 1;}

        else if (sign == 0 && rhs.sign == -1){nums = rhs.nums; sign = -1;}
    }
    DeleteLeadingZeros();
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& rhs){
    if(sign == 0){*this += rhs;}
    else if(sign == 1){sign = -1; *this += rhs;}
    else if(sign == -1){sign = 1; *this += rhs;}

    if (sign == 1){sign = -1;} 
    else if (sign == -1){sign = 1;}
    DeleteLeadingZeros();
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& rhs){
    if(sign * rhs.sign == -1){sign = -1;}
    else if(sign* rhs.sign == 1){sign = 1;}
    else if(sign == 0){DeleteLeadingZeros(); return *this;}
    else if(rhs.sign == 0){*this = 0; return *this;}

    BigInt prod;
    prod.SetSize(nums.size() * rhs.nums.size() + 1);
    BigInt t;
    t.SetSize(nums.size() * rhs.nums.size() + 1);

    for(size_t i = 0; i < nums.size(); ++i){
        t = 0;
        u32 t1 = 0;
        for(size_t j = 0; j < rhs.nums.size() + 1; ++j){
            // t1 = (u32)nums[i] * (u32)rhs.nums[j];
            t1 = nums[i] * rhs.nums[j];
            if (t.nums[j+i] > u16_max - t1){ t.nums[i+j+1]++; } 
            t.nums[i+j] += static_cast<u16>(t1);
                    // t.BinaryWrite();


            // std::cout<<t1<<' ';
            t1 >>= 16;
                        // std::cout<<t1<<std::endl;

            if (t.nums[j+i+1] > u16_max - t1){ t.nums[j+i+2]++; } 
            t.nums[j+i+1] += static_cast<u16>(t1);
                    // t.BinaryWrite();

        }
        for (size_t i = 0; i < t.nums.size(); ++i){if (nums[i] != 0){t.sign = 1; break;}}
                            // t.BinaryWrite();
        prod += t;
                            // prod.BinaryWrite();

    }
    // prod.BinaryWrite();
    prod.DeleteLeadingZeros();
    // prod.BinaryWrite();
    nums = prod.nums;
    return *this;
}

bool BigInt::operator<(const BigInt& rhs){
    // std::cout << '\n' << "this = " << sign << " rhs = "<< rhs.sign << '\n';
    if (sign > rhs.sign){return false;}
    if (sign < rhs.sign){return true;}
    BigInt t = rhs;
    if (sign == 1 && rhs.sign == 1){
        if (nums.size() > t.nums.size()){
            for (size_t i = t.nums.size() - 1; i >= 0; --i){
                if (nums[i] > t.nums[i]){return false;}
                if (nums[i] < t.nums[i]){return true;}
            }
        }

        else{
            for (size_t i = nums.size() - 1; i >= 0; --i){
                if (nums[i] > t.nums[i]){return false;}
                if (nums[i] < t.nums[i]){return true;}
            }
        }
    }
    else if (sign == -1 && rhs.sign == -1){
        if (nums.size() > t.nums.size()){
            for (size_t i = t.nums.size() - 1; i >= 0; --i){
                if (nums[i] > t.nums[i]){return true;}
                if (nums[i] < t.nums[i]){return false;}
            }
        }

        else{
            for (size_t i = nums.size() - 1; i >= 0; --i){
                if (nums[i] > t.nums[i]){std::cout << i <<' ';return true;}
                if (nums[i] < t.nums[i]){return false;}
            }
        }
    }
    // std::cout<<"HERE";
    return false;
}

bool BigInt::operator>=(const BigInt& rhs){
    return !(*this < rhs);
}

bool BigInt::operator==(const BigInt& rhs){
    if(sign != rhs.sign){return false;}
    if(rhs.nums.size() > nums.size()){
        for(size_t i = 0; i < nums.size(); ++i){
            if (nums[i] != rhs.nums[i]){return false;}
        }
        for(size_t i = nums.size(); i < rhs.nums.size(); ++i){
            if (rhs.nums[i] != 0){return false;}
        }
    }
    else if(rhs.nums.size() < nums.size()){
        for(size_t i = 0; i < rhs.nums.size(); ++i){
            if (nums[i] != rhs.nums[i]){return false;}
        }
        for(size_t i = rhs.nums.size(); i < nums.size(); ++i){
            if (nums[i] != 0){return false;}
        }
    }
    return true;
}

bool BigInt::operator<=(const BigInt& rhs){
    return (*this < rhs || *this == rhs);
}

bool BigInt::operator>(const BigInt& rhs){
    return !(*this <= rhs);
}

void BigInt::DeleteLeadingZeros(){
    size_t need = 0;
    for(size_t i = nums.size() - 1; 1 < i; --i){
        if(nums[i] == 0){++need;}
        else{break;}
    }
    for(size_t i = 0; i < need; ++i){
        nums.pop_back();
    }
}

void BigInt::SetSize(size_t size){
    auto n = size - nums.size();
    if (size < n){return;}
    for (size_t i = 0; i < n; ++i){nums.push_back(0);};
}

std::ostream& operator<<(std::ostream& os, const std::vector<u16> &input){
    for (auto const &i: input){
        os << i << ' ';
    }
    return os;
}

void BigInt::BinaryWrite(){
        std::cout << " [" << "SIGN: " << sign << " | ";
        std::cout << nums << "]\n";
}
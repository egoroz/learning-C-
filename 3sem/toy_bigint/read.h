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
    BigInt operator++(int);                     //postfix
    BigInt operator--(int);
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);

    bool operator==(const BigInt&);
    bool operator<(const BigInt&);
    bool operator<=(const BigInt&);
    bool operator>(const BigInt&);
    bool operator>=(const BigInt&);

    void Delete_Leading_Zeros();
    void Set_Size(size_t);
    void Write_In_65536_Binary_System();
};

BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
BigInt Abs(const BigInt& a);
std::ostream& operator<<(std::ostream& os, const std::vector<u16> &input);
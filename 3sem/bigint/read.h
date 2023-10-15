#include <iostream>
#include <string>
#include <cstdint>

using u16 = uint16_t;
using u32 = uint32_t;

class Big{
public:
  bool sign;
  u16 a, b;
  const u16 u16_max = static_cast<u16>(-1);

  Big() : a(0), b(0), sign(0){}
  Big(u16 a, u16 b, bool sign) : a(a), b(b), sign(sign){}
  Big(const Big& big) = default;
  Big(Big&& big) = default;
  ~Big() = default;

  Big& operator+=(const Big& rhs);
  Big& operator-=(const Big& rhs);

  Big MultiplyBy2(size_t n);
  Big HelperForOperatorMult(const Big& big1, const Big& big2);
  
  Big& operator=(const Big& rhs);
  Big& operator*=(const Big& rhs);

  bool operator>(const Big& rhs);
  bool operator>=(const Big& rhs);
  bool operator<(const Big& rhs);
  bool operator<=(const Big& rhs);
  bool operator==(const Big& rhs);

};

Big operator+(const Big& big1, const Big& big2);
Big operator-(const Big& big1, const Big& big2);
Big operator*(const Big& big1, const Big& big2);

Big Abs(const Big& big);
Big Negative(const Big& big);

void Print(const Big& n);
Big ReadBigNumber(const char * text);
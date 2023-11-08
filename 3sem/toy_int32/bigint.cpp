#include <iostream>
#include <string>
#include <cstdint>

using u16 = uint16_t;
using u32 = uint32_t;

class Big;
Big Abs(const Big& big);
Big Negative(const Big& big);

class Big {
public:
  bool sign;
  u16 a, b;
  const u16 u16_max = static_cast<u16>(-1);

  Big() : a(0), b(0), sign(0){}

  Big(u16 a, u16 b, bool sign) : a(a), b(b), sign(sign){}

  Big(const Big&) = default;

  Big(Big&& big) = default;
  
  ~Big() = default;

  Big& operator=(const Big& rhs){
    a = rhs.a;
    b = rhs.b;
    sign = rhs.sign;
    return(*this);
  }

  Big& operator=(Big&& rhs){
    a = rhs.a;
    b = rhs.b;
    sign = rhs.sign;
    return(*this);
  }

  Big& operator+=(const Big& rhs){
    if (sign == 0 && rhs.sign == 0){
      if (b > u16_max - rhs.b){
          ++a;
      }
      b += rhs.b;
      a += rhs.a;
      }
    else if(sign == 0 && rhs.sign == 1){
      *this -= Abs(rhs);
    }
    else if(sign == 1 && rhs.sign == 0){
      bool flag = Abs(*this) > Abs(rhs);
        sign = 0;
        *this -= rhs;
        sign = flag;
    }
    else{
      sign = 0;
      *this += Abs(rhs);
      sign = 1;
    }

    return (*this);
}

  Big& operator-=(const Big& rhs){
    if (*this > rhs){
      if(sign == 0 && rhs.sign == 0){
        if(rhs.b > b){a--;}
        a -= rhs.a;
        b -= rhs.b;
      }
      else if(sign == 1 && rhs.sign == 1){
        Big t_rhs = rhs;
        if(rhs.b < b){t_rhs.a--;}
        t_rhs.a -= a;
        t_rhs.b -= b;

        a = t_rhs.a;
        b = t_rhs.b;
        sign = 0;
      }
      else if(sign == 0 && rhs.sign == 1){
        if(b > u16_max - rhs.b){a++;}
        a += rhs.a;
        b += rhs.b;
        }
    }
    else{
      if(sign == 0 && rhs.sign == 0){
        Big t_rhs = rhs;
        if(rhs.b < b){t_rhs.a--;}
        t_rhs.a -= a;
        t_rhs.b -= b;
        t_rhs.sign = 1;
        
        a = t_rhs.a;
        b = t_rhs.b;
        sign = t_rhs.sign;
      }
      else if(sign == 1 && rhs.sign == 1){
        Big t_rhs = rhs;
        if(rhs.b < b){t_rhs.a--;}
        t_rhs.a -= a;
        t_rhs.b -= b;
        t_rhs.sign = 0;

        a = t_rhs.a;
        b = t_rhs.b;
        sign = t_rhs.sign;
      }
      else if(sign == 1 && rhs.sign == 0){
        Big t_rhs = rhs;
        if (t_rhs.b > u16_max - b){t_rhs.a++;}
        t_rhs.a += a;
        t_rhs.b += b;
        a = t_rhs.a;
        b = t_rhs.b;
      }
    }
  return (*this);
  } 

  Big MultiplyBy2InN(size_t n){
    a <<= n;
    u16 t = b;
    t >>= (16-n);
    a += t;
    b <<= n;
    return (*this);
  }

  Big& HelperForOperatorMult(const Big& big1, const Big& big2){
      Big prod;

      for (size_t i = 0; i < 16; i++){
        u16 t1, t2;
        t1 = big2.b; 
        t1 <<= (15 - i);
        t1 >>= 15;         // t - 0 or 1
        
        t1 = t1 * big1.b;
        t2 = t1;

        t1 <<= i;
        if (prod.b > u16_max - t1){++prod.a;}
        prod.b += t1;

        t2 >>= (16 - i);
        prod.a += t2;
      }

      prod.a += big1.b * big2.a;
      a = prod.a;
      b = prod.b;
      return (*this);
    }

  Big& operator*=(const Big& rhs){
    Big prod;
    
    if (sign == rhs.sign){sign = 0;}
    else{sign = 1;}

    if (Abs(*this) > Abs(rhs)){*this = HelperForOperatorMult(rhs, *this);}
    else{*this = HelperForOperatorMult(*this, rhs);}

    return(*this);
  }


// (c++20 operator <=> vozvrashaet 0, 1 ili 2)
  bool operator<(const Big& rhs){
    if (sign == 0 && rhs.sign != 0){return false;}
    if (sign != 0 && rhs.sign == 0){return true;}
    if (sign == 0 && rhs.sign == 0){return (a < rhs.a || (a == rhs.a && b < rhs.b));}
    return !(a < rhs.a || (a == rhs.a && b < rhs.b));
  }
  bool operator==(const Big& rhs){
    return (sign == rhs.sign && a == rhs.a && b == rhs.b);
  }
  bool operator<=(const Big& rhs){
    return (*this < rhs  || *this == rhs);
  }
  bool operator>(const Big& rhs){
    return !(*this <= rhs);
  }
  bool operator>=(const Big& rhs){
    return !(*this < rhs);
  }

};

Big operator+(const Big& big1, const Big& big2){
  Big t = big1;
  t += big2;
  return t;
  }

Big operator-(const Big& big1, const Big& big2){
  Big t = big1;
  t -= big2;
  return t;
  }

Big operator*(const Big& big1, const Big& big2){
  Big t = big1;
  t *= big2;
  return t;
}

Big Abs(const Big& big){
  Big t = big;
  t.sign = 0;
  return t;
}

Big Negative(const Big& big){
  Big t = big;
  t.sign = 1;
  return t;
}

void Print(const Big& n) { 
    u32 t = n.a;
    t <<= 16;
    t += n.b;
    if (n.sign == 1 && !(n.a == 0 && n.b == 0)){
    std::cout << "Big number = " << "-" << t << '\n';
    return;
    }
    std::cout << "Big number = " << t << '\n';
  }


Big ReadBigNumber(const char* text) {
  Big big;

  const u16 u16_max = static_cast<u16>(-1);
  std::string s = text;

  size_t i = 0;

  if (s[0] == '-'){
    big.sign = true;
    i++;
  }

  for (; i < s.length(); ++i) {
    u16 tmp_a = 0, tmp_b = 0;
    tmp_a = big.b >> 14;
    tmp_b = big.b << 2;

    if (big.b > u16_max - tmp_b) {tmp_a += 1;}

    big.b = big.b + tmp_b;
    tmp_a <<= 1;
    tmp_a += (big.b >> 15);
    big.b <<= 1;
    big.a = big.a * 10 + tmp_a;
    
    u16 cur_digit = s[i] - '0';
    if (big.b > u16_max - cur_digit) {++big.a;}
    big.b += cur_digit;
  }

  return big;
  }

// int main(){
//   Big a = ReadBigNumber("-1");
//   Big b = ReadBigNumber("-100");
//   Big c = ReadBigNumber("-100000");
//   Big d = ReadBigNumber("-100001");
//   a *= b;
//   Print(a);
//   a = b * c;
//   Print(a);
//   Print(c);
//   Print(d);
//   std::cout << std::boolalpha
//             << (a < b) << '\n'
//             << (a < c) << '\n'
//             << (c < d) << '\n'
//             << (d < c) << '\n';
// }

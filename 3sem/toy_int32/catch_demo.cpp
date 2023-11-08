#include "catch.hpp"
#include "read.h"
#include <cmath>

#define CHECK_READ_TEST(v) do {CheckIsReadOk(#v, v); } while(false)
#define CHECK_MULTIPLICATION(v1, v2) do {CheckMult(#v1, v1, #v2, v2); } while(false)
#define CHECK_SUM(v1, v2) do {CheckSum(#v1, v1, #v2, v2); } while(false)
#define CHECK_DIF(v1, v2) do {CheckDif(#v1, v1, #v2, v2); } while(false)


u32 CreateTempBasedOnBigInt(Big big){
  int t = big.a;
  t <<= 16;
  t += big.b;
  return t;
}

void CheckIsReadOk(const char* text, int value) {
  Big b = ReadBigNumber(text);
  u32 t = CreateTempBasedOnBigInt(b);
  if (b.sign){t = -t;}
  REQUIRE(t == value);
}

void CheckMult(const char* text_a, int a, const char* text_b, int b){
  Big big1 = ReadBigNumber(text_a);
  Big big2 = ReadBigNumber(text_b);

  Big total_big = big1 * big2;
  u32 t2 = CreateTempBasedOnBigInt(total_big);

  big1 *= big2;
  u32 t1 = CreateTempBasedOnBigInt(big1);

  if (total_big.sign == 1){t2 = -t2;}
  if (big1.sign == 1){t1 = -t1;}

  bool bool1 = (t1 == t2);
  bool1 *= (t1 == (a * b));
  REQUIRE(bool1);
}

void CheckSum(const char* text_a, int a, const char* text_b, int b){
  Big big1 = ReadBigNumber(text_a);
  Big big2 = ReadBigNumber(text_b);

  Big total_big = big1 + big2;
  u32 t1 = CreateTempBasedOnBigInt(total_big);

  big1 += big2;
  u32 t2 = CreateTempBasedOnBigInt(big1);

  if (total_big.sign == 1){t1 = -t1;}
  if (big1.sign == 1){t2 = -t2;}

  bool bool1 = (t1 == t2);
  bool1 *= (t1 == (a + b));
  REQUIRE(bool1);
}

void CheckDif(const char* text_a, int a, const char* text_b, int b){
  Big big1 = ReadBigNumber(text_a);
  Big big2 = ReadBigNumber(text_b);

  Big total_big = big1 - big2;
  u32 t1 = CreateTempBasedOnBigInt(total_big);
  
  big1 -= big2;
  u32 t2 = CreateTempBasedOnBigInt(big1);

  if (total_big.sign == 1){t1 = -t1;}
  if (big1.sign == 1){t2 = -t2;}

  bool bool1 = (t1 == t2);
  bool1 *= (t1 == (a - b));
  REQUIRE(bool1);
}

TEST_CASE("Read_test") {
   // Numbers greater then (2^32 - 1) or less then 0 - not considered
    CHECK_READ_TEST(0);
    CHECK_READ_TEST(234);
    CHECK_READ_TEST(999);
    CHECK_READ_TEST(-1);
    CHECK_READ_TEST(3267);
    CHECK_READ_TEST(-193574);
    CHECK_READ_TEST(1098324);
    CHECK_READ_TEST(1450255);
    CHECK_READ_TEST(-334789611);
    CHECK_READ_TEST(375294491);
    CHECK_READ_TEST(-1473255435);
    CHECK_READ_TEST(4294967295);
    CHECK_READ_TEST(-2094967293);

}

TEST_CASE("Operations_test") {
    // total product must not be greater then the max_u32
    CHECK_MULTIPLICATION(1, 1222);
    CHECK_MULTIPLICATION(123, 6767);
    CHECK_MULTIPLICATION(12, 244);
    CHECK_MULTIPLICATION(976, 334);
    CHECK_MULTIPLICATION(33333, 10);
    CHECK_MULTIPLICATION(456756, 12);
    CHECK_MULTIPLICATION(9, 2737374);
    CHECK_MULTIPLICATION(32737, 33);
    CHECK_MULTIPLICATION(0, 0);
    CHECK_MULTIPLICATION(1, 1);
    CHECK_MULTIPLICATION(10000, 10000);

    CHECK_MULTIPLICATION(1, -1222);
    CHECK_MULTIPLICATION(123, -6767);
    CHECK_MULTIPLICATION(-12, 244);
    CHECK_MULTIPLICATION(-976, 334);
    CHECK_MULTIPLICATION(33333, -10);
    CHECK_MULTIPLICATION(-456756, 12);
    CHECK_MULTIPLICATION(9, -2737374);
    CHECK_MULTIPLICATION(-32737, -33);
    CHECK_MULTIPLICATION(-0, -0);
    CHECK_MULTIPLICATION(-0, 0);
    CHECK_MULTIPLICATION(0, -0);
    CHECK_MULTIPLICATION(-1, -1);
    CHECK_MULTIPLICATION(-10000, 10000);


    // Sum test
    CHECK_SUM(1248124, 4356);
    CHECK_SUM(0, 234234);
    CHECK_SUM(1234134234,3);
    CHECK_SUM(4235656,5454444);
    CHECK_SUM(324545, 546456);
    CHECK_SUM(234234, 324232);
    CHECK_SUM(2342, 3434);
    CHECK_SUM(325234324, 35425545);
    CHECK_SUM(0, 0);

    CHECK_SUM(-1248124, 4356);
    CHECK_SUM(0, -234234);
    CHECK_SUM(-0, -234234);
    CHECK_SUM(-0, 234234);
    CHECK_SUM(-1234134234,-3);
    CHECK_SUM(4235656,-5454444);
    CHECK_SUM(-324545, -546456);
    CHECK_SUM(-234234, 324232);
    CHECK_SUM(-2342, -3434);
    CHECK_SUM(-325234324, 35425545);
    CHECK_SUM(10, -10);
    CHECK_SUM(-10, 10);

    CHECK_DIF(0, 0);
    CHECK_DIF(-2, -10);
    CHECK_DIF(-10000, 1000222);
    CHECK_DIF(213124, -1222229);
    CHECK_DIF(10000, 1);
    CHECK_DIF(1, 10000);
    CHECK_DIF(2134214, 1243421);
    CHECK_DIF(-2234234, -234234);
    CHECK_DIF(-2, -2);
    CHECK_DIF(2, 2);
    CHECK_DIF(2, -2);

}
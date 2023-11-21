#include "catch.hpp"
#include "bigint.h"
#include <cmath>
#include <iostream>

#define CHECK_READ_TEST(v) do {CheckIsReadOk(#v, v); } while(false)
#define CHECK_MULT(v1, v2) do {CheckMult(#v1, v1, #v2, v2); } while(false)
#define CHECK_SUM(v1, v2) do {CheckSum(#v1, v1, #v2, v2); } while(false)
#define CHECK_DIF(v1, v2) do {CheckDif(#v1, v1, #v2, v2); } while(false)

#define CHECK_INC_AND_DEC(v) do {CheckIncDec(#v, v); } while(false)




i64 CreateTempBasedOnBigInt(BigInt big){
  i64 t = big.nums[1];
  t <<= 16;
  t += big.nums[0];
  return t;
}

void CheckIsReadOk(const std::string& text, i64 value) {
  BigInt b(text);
  b.Write_In_65536_Binary_System();
  i64 t = CreateTempBasedOnBigInt(b);
  if (b.sign == -1){t = -t;}

  REQUIRE(t == value);
}

void CheckMult(const char* text_a, i64 a, const char* text_b, i64 b){
  BigInt big1(text_a);
  BigInt big2(text_b);

  big1.Write_In_65536_Binary_System();
  big2.Write_In_65536_Binary_System();

  BigInt total_big = big1 * big2;
  i64 t2 = CreateTempBasedOnBigInt(total_big);

  std::cerr << "Произведение: * \n";
  total_big.Write_In_65536_Binary_System();

  big1 *= big2;
  i64 t1 = CreateTempBasedOnBigInt(big1);

  std::cerr << "Произведение: *= \n";
  big1.Write_In_65536_Binary_System();

  if (total_big.sign == -1){t2 = -t2;}
  if (big1.sign == -1){t1 = -t1;}

  bool bool1 = (t1 == t2);
  bool1 = (bool1 && (t1 == (a * b)));
  REQUIRE(bool1);
}


void CheckSum(const char* text_a, i64 a, const char* text_b, i64 b){
  BigInt big1(text_a);
  BigInt big2(text_b);

  big1.Write_In_65536_Binary_System();
  big2.Write_In_65536_Binary_System();

  BigInt total_big = big1 + big2;
  i64 t1 = CreateTempBasedOnBigInt(total_big);

  std::cerr << "Сумма + :\n";
  total_big.Write_In_65536_Binary_System();
  
  big1 += big2;
  i64 t2 = CreateTempBasedOnBigInt(big1);

  std::cerr << "Сумма +=:\n";
  (big1).Write_In_65536_Binary_System();

  if (total_big.sign == -1){t1 = -t1;}
  if (big1.sign == -1){t2 = -t2;}
  // std::cout << "t1=t2 == " << t1 << " = "<< t2 << '\n';

  bool bool1 = (t1 == t2);
  bool1 = (bool1 && (t1 == (a + b)));
  REQUIRE(bool1);
}

void CheckDif(const char* text_a, i64 a, const char* text_b, i64 b){
  BigInt big1(text_a);
  BigInt big2(text_b);

  big1.Write_In_65536_Binary_System();
  big2.Write_In_65536_Binary_System();

  BigInt total_big = big1 - big2;
  i64 t1 = CreateTempBasedOnBigInt(total_big);
  
  std::cerr << "Разность: - \n";
  total_big.Write_In_65536_Binary_System();


  big1 -= big2;
  i64 t2 = CreateTempBasedOnBigInt(big1);

  std::cerr << "Разность: -= \n";
  big1.Write_In_65536_Binary_System();

  if (total_big.sign == -1){t1 = -t1;}
  if (big1.sign == -1){t2 = -t2;}

  bool bool1 = (t1 == t2);
  bool1 = (bool1 && (t1 == (a - b)));
  REQUIRE(bool1);
}

void CheckIncDec(const char* text, i64 a){
  BigInt big(text);
  bool flag;

  ++big;
  i64 t = CreateTempBasedOnBigInt(big);
  if(big.sign == -1){t = -t;}
  flag = (t == (++a));

  // big.Write_In_65536_Binary_System();
  // std::cout << t << ' ' << flag << '\n';

  

  --big;
  t = CreateTempBasedOnBigInt(big);
  if(big.sign == -1){t = -t;}
  flag = (flag && (t == --a));
  

  // big.Write_In_65536_Binary_System();
  // std::cout << t << '\n';
  // std::cout << t << ' ' << flag << '\n';

  big++;
  t = CreateTempBasedOnBigInt(big);
  if(big.sign == -1){t = -t;}
  flag = (flag && (t == ++a));

  // big.Write_In_65536_Binary_System();
  // std::cout << t << '\n';
  // std::cout << t << ' ' << flag << '\n';

  big--;
  t = CreateTempBasedOnBigInt(big);
  if(big.sign == -1){t = -t;}
  flag = (flag && (t == --a));

  // big.Write_In_65536_Binary_System();
  // std::cout << t << '\n';
  // std::cout << t << ' ' << flag << '\n';

  REQUIRE(flag);
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
    CHECK_MULT(1, 1222);
    CHECK_MULT(123, 6767);
    CHECK_MULT(12, 244);
    CHECK_MULT(976, 334);
    CHECK_MULT(33333, 10);
    CHECK_MULT(456756, 12);
    CHECK_MULT(9, 2737374);
    CHECK_MULT(32737, 33);
    CHECK_MULT(0, 0);
    CHECK_MULT(1, 1);
    CHECK_MULT(10000, 10000);

    CHECK_MULT(1, -1222);
    CHECK_MULT(123, -6767);
    CHECK_MULT(-12, 244);
    CHECK_MULT(-976, 334);
    CHECK_MULT(33333, -10);
    CHECK_MULT(-456756, 12);
    CHECK_MULT(9, -2737374);
    CHECK_MULT(-32737, -33);
    CHECK_MULT(-0, -0);
    CHECK_MULT(-0, 0);
    CHECK_MULT(0, -0);
    CHECK_MULT(-1, -1);
    CHECK_MULT(-10000, 10000);


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
    CHECK_DIF(0, 1000222);
    CHECK_DIF(10000, 0);
    CHECK_DIF(0, -1000222);
    CHECK_DIF(-10000, 0);
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

TEST_CASE("Operators_test") {
  CHECK_INC_AND_DEC(0);
  CHECK_INC_AND_DEC(1);
  CHECK_INC_AND_DEC(1000);
  CHECK_INC_AND_DEC(-10000);
  CHECK_INC_AND_DEC(1111111);
  CHECK_INC_AND_DEC(11111111);
  CHECK_INC_AND_DEC(-23142345);
  CHECK_INC_AND_DEC(-435345445);
  CHECK_INC_AND_DEC(-3233);
  CHECK_INC_AND_DEC(-1);
  CHECK_INC_AND_DEC(65335);
  CHECK_INC_AND_DEC(-65335);

}
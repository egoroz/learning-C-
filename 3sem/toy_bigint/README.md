# BigInteger



>Реализация класса BigInt (длинной арифметики) на c++ с тестами, которые покрывают большинство случаев.\
Корректная работа не на Linux не гарантируется\
Полное описание полей и методов класса BigInt должно быть в "read.h"

**Компиляция**

>Проверить работоспособность:
>>g++ big.o catch_demo.o catch_main.o\
./a.out

>Полная компиляция (ждать порядка минуты):
>>g++ -c big.cpp catch_demo.cpp catch_main.cpp\
g++ big.o catch_demo.o catch_main.o\
./a.out

>Править класс BigInt и тесты:
>>g++ -c big.cpp catch_demo.cpp\
g++ big.o catch_demo.o catch_main.o\
./a.out
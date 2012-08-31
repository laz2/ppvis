#include "stdafx.h"
#include "UnitTest++.h" // Главный заголовочный файл библиотеки UnitTest++

#include <iostream>

#include "Money.h"

struct ConstructorFixture
{
   ConstructorFixture() : _currencyFF( "FF" ),
      _floatNumber123( 12345678.90123f )
   {
   };
   const std::string _currencyFF;
   const float _floatNumber123;
};

TEST_FIXTURE( ConstructorFixture, TestConstructorNumber )
{
   Money money( _floatNumber123, _currencyFF );
   CHECK_CLOSE( _floatNumber123,
                money.getAmount(),
                0.01f );
}

TEST_FIXTURE( ConstructorFixture, TestConstructorCurrency )
{
   Money money( _floatNumber123, _currencyFF );
   CHECK( money.getCurrency() == _currencyFF );
}

struct OperatorFixture
{
   OperatorFixture() : _currencyFF( "FF" ),
                       _currencyUSD( "USD" ),
                       _floatNumber12( 12.0f ),
                       _floatNumber123( 123.0f )
   {};

   const std::string _currencyFF;
   const std::string _currencyUSD;
   const float _floatNumber12;
   const float _floatNumber123;
};

TEST_FIXTURE( OperatorFixture, TestEqual )
{
   Money money12FF( _floatNumber12, _currencyFF );
   Money money123USD( _floatNumber123, _currencyUSD );

   CHECK( money12FF == money12FF );
   CHECK( money123USD == money123USD );
}

TEST_FIXTURE( OperatorFixture, TestNotEqual )
{
   Money money12FF( _floatNumber12, _currencyFF );
   Money money123FF( _floatNumber123, _currencyFF );
   Money money12USD( _floatNumber12, _currencyUSD );
   Money money123USD( _floatNumber123, _currencyUSD );

   CHECK( money12FF != money123FF );
   CHECK( money12FF != money12USD );
   CHECK( money12USD != money123USD );
}

TEST( TestAdd )
{
   // setup
   Money money12FF( 12, "FF" );
   Money expectedMoney( 135, "FF" );

   // process
   Money money( 123, "FF" );
   money += money12FF;

   // check
   CHECK_EQUAL( expectedMoney.getAmount(), money.getAmount() );
   CHECK( money.getAmount() == expectedMoney.getAmount() );  // less information
}

TEST( TestIncompatibleMoneyError )
{
   // Просто проверим, как отлавливаются исключения
   CHECK_THROW( throw IncompatibleMoneyError(), IncompatibleMoneyError );
}

TEST_FIXTURE( OperatorFixture, TestAddThrow )
{
   Money money123FF( _floatNumber123, _currencyFF );
   Money money123USD( _floatNumber123, _currencyUSD );

   CHECK_THROW( money123FF += money123USD, IncompatibleMoneyError );
}

int menu()
{
    std::cout << "Program menu: \n\t1.First\n\t2.Second\n\t3.Third" << std::endl; 
    return 0;
}

int main( int argc, char const *argv[] )
{
    // Если передан аргумент командной строки "-menu",
    // то выведем программное меню, иначе запустим тесты.
    //
    if (argc == 2) 
        if (!strcmp(argv[1], "-menu"))
            return menu();
        else
        {
            std::cerr << "Usage: MoneyTestApp [-menu]" << std::endl;
            return 1;
        }
    else
        return UnitTest::RunAllTests();
}

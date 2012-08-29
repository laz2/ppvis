#pragma once

#include <string>
#include <stdexcept>

class IncompatibleMoneyError : public std::runtime_error
{
public:
   IncompatibleMoneyError() : runtime_error( "Incompatible moneys" )
   {
   }
};

class Money
{
private:
    float m_amount; // Величина денежной суммы
    std::string m_currency; // Наименование валюты

public:
   Money( float amount, std::string currency /* Наименование валюты */ )
      : m_amount( amount ), m_currency( currency )
   {
   }

   float getAmount() const
   {
      return m_amount;
   }

   std::string getCurrency() const
   {
      return m_currency;
   }

   bool operator ==( const Money &other ) const
   {
      return m_amount == other.m_amount  &&
        m_currency == other.m_currency;
   }

   bool operator !=( const Money &other ) const
   {
      return !(*this == other);
   }

   Money &operator +=( const Money &other )
   {
      if ( m_currency != other.m_currency )
      {
         throw IncompatibleMoneyError();
      }

      m_amount += other.m_amount;
      return *this;
   }
};

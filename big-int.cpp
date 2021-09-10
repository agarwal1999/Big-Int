
#ifndef BIG_INT
#define BIG_INT

#include <iostream>

class BigInt
{
  std::string value;
  char sign;

public:
  // Constructors:
  BigInt();
  BigInt(const BigInt &);
  BigInt(const long long &);
  BigInt(const std::string &);

  // Assignment operators:
  BigInt &operator=(const BigInt &);
  BigInt &operator=(const long long &);
  BigInt &operator=(const std::string &);

  // Unary arithmetic operators:
  BigInt operator+() const; // unary +
  BigInt operator-() const; // unary -

  // Binary arithmetic operators:
  BigInt operator+(const BigInt &) const;
  BigInt operator-(const BigInt &) const;
  BigInt operator*(const BigInt &) const;
  BigInt operator/(const BigInt &) const;
  BigInt operator%(const BigInt &) const;
  BigInt operator+(const long long &) const;
  BigInt operator-(const long long &) const;
  BigInt operator*(const long long &) const;
  BigInt operator/(const long long &) const;
  BigInt operator%(const long long &) const;
  BigInt operator+(const std::string &) const;
  BigInt operator-(const std::string &) const;
  BigInt operator*(const std::string &) const;
  BigInt operator/(const std::string &) const;
  BigInt operator%(const std::string &) const;

  // Arithmetic-assignment operators:
  BigInt &operator+=(const BigInt &);
  BigInt &operator-=(const BigInt &);
  BigInt &operator*=(const BigInt &);
  BigInt &operator/=(const BigInt &);
  BigInt &operator%=(const BigInt &);
  BigInt &operator+=(const long long &);
  BigInt &operator-=(const long long &);
  BigInt &operator*=(const long long &);
  BigInt &operator/=(const long long &);
  BigInt &operator%=(const long long &);
  BigInt &operator+=(const std::string &);
  BigInt &operator-=(const std::string &);
  BigInt &operator*=(const std::string &);
  BigInt &operator/=(const std::string &);
  BigInt &operator%=(const std::string &);

  // Increment and decrement operators:
  BigInt &operator++();   // pre-increment
  BigInt &operator--();   // pre-decrement
  BigInt operator++(int); // post-increment
  BigInt operator--(int); // post-decrement

  // Relational operators:
  bool operator<(const BigInt &) const;
  bool operator>(const BigInt &) const;
  bool operator<=(const BigInt &) const;
  bool operator>=(const BigInt &) const;
  bool operator==(const BigInt &) const;
  bool operator!=(const BigInt &) const;
  bool operator<(const long long &) const;
  bool operator>(const long long &) const;
  bool operator<=(const long long &) const;
  bool operator>=(const long long &) const;
  bool operator==(const long long &) const;
  bool operator!=(const long long &) const;
  bool operator<(const std::string &) const;
  bool operator>(const std::string &) const;
  bool operator<=(const std::string &) const;
  bool operator>=(const std::string &) const;
  bool operator==(const std::string &) const;
  bool operator!=(const std::string &) const;

  // I/O stream operators:
  friend std::istream &operator>>(std::istream &, BigInt &);
  friend std::ostream &operator<<(std::ostream &, const BigInt &);

  // Conversion functions:
  std::string to_string() const;
  int to_int() const;
  long to_long() const;
  long long to_long_long() const;
};

#endif

#ifndef BIG_INT_UTILITY_FUNCTIONS
#define BIG_INT_UTILITY_FUNCTIONS

#include <tuple>

bool is_valid_number(const std::string &num)
{
  for (char digit : num)
    if (digit < '0' or digit > '9')
      return false;

  return true;
}

void strip_leading_zeroes(std::string &num)
{
  size_t i;
  for (i = 0; i < num.size(); i++)
    if (num[i] != '0')
      break;

  if (i == num.size())
    num = "0";
  else
    num = num.substr(i);
}

void add_leading_zeroes(std::string &num, size_t num_zeroes)
{
  num = std::string(num_zeroes, '0') + num;
}

void add_trailing_zeroes(std::string &num, size_t num_zeroes)
{
  num += std::string(num_zeroes, '0');
}

std::tuple<std::string, std::string> get_larger_and_smaller(const std::string &num1, const std::string &num2)
{
  std::string larger, smaller;
  if (num1.size() > num2.size() or
      (num1.size() == num2.size() and num1 > num2))
  {
    larger = num1;
    smaller = num2;
  }
  else
  {
    larger = num2;
    smaller = num1;
  }

  // pad the smaller number with zeroes
  add_leading_zeroes(smaller, larger.size() - smaller.size());

  return std::make_tuple(larger, smaller);
}

#endif

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

BigInt::BigInt()
{
  value = "0";
  sign = '+';
}

BigInt::BigInt(const BigInt &num)
{
  value = num.value;
  sign = num.sign;
}

BigInt::BigInt(const long long &num)
{
  value = std::to_string(num);
  if (num < 0)
  {
    sign = '-';
    value = value.substr(1);
  }
  else
    sign = '+';
}

BigInt::BigInt(const std::string &num)
{
  if (num[0] == '+' or num[0] == '-')
  {
    std::string magnitude = num.substr(1);
    if (is_valid_number(magnitude))
    {
      value = magnitude;
      sign = num[0];
    }
    else
    {
      throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
    }
  }
  else
  {
    if (is_valid_number(num))
    {
      value = num;
      sign = '+';
    }
    else
    {
      throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
    }
  }
  strip_leading_zeroes(value);
}

#endif

#ifndef BIG_INT_CONVERSION_FUNCTIONS_HPP
#define BIG_INT_CONVERSION_FUNCTIONS_HPP

std::string BigInt::to_string() const
{

  return this->sign == '-' ? "-" + this->value : this->value;
}

int BigInt::to_int() const
{
  return std::stoi(this->to_string());
}

long BigInt::to_long() const
{
  return std::stol(this->to_string());
}

long long BigInt::to_long_long() const
{
  return std::stoll(this->to_string());
}

#endif

#ifndef BIG_INT_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ASSIGNMENT_OPERATORS_HPP

BigInt &BigInt::operator=(const BigInt &num)
{
  value = num.value;
  sign = num.sign;

  return *this;
}

BigInt &BigInt::operator=(const long long &num)
{
  BigInt temp(num);
  value = temp.value;
  sign = temp.sign;

  return *this;
}

BigInt &BigInt::operator=(const std::string &num)
{
  BigInt temp(num);
  value = temp.value;
  sign = temp.sign;

  return *this;
}

#endif

#ifndef BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP

BigInt BigInt::operator+() const
{
  return *this;
}

BigInt BigInt::operator-() const
{
  BigInt temp;

  temp.value = value;
  if (value != "0")
  {
    if (sign == '+')
      temp.sign = '-';
    else
      temp.sign = '+';
  }

  return temp;
}

#endif

#ifndef BIG_INT_RELATIONAL_OPERATORS_HPP
#define BIG_INT_RELATIONAL_OPERATORS_HPP

bool BigInt::operator==(const BigInt &num) const
{
  return (sign == num.sign) and (value == num.value);
}

bool BigInt::operator!=(const BigInt &num) const
{
  return !(*this == num);
}

bool BigInt::operator<(const BigInt &num) const
{
  if (sign == num.sign)
  {
    if (sign == '+')
    {
      if (value.length() == num.value.length())
        return value < num.value;
      else
        return value.length() < num.value.length();
    }
    else
      return -(*this) > -num;
  }
  else
    return sign == '-';
}

bool BigInt::operator>(const BigInt &num) const
{
  return !((*this < num) or (*this == num));
}

bool BigInt::operator<=(const BigInt &num) const
{
  return (*this < num) or (*this == num);
}

bool BigInt::operator>=(const BigInt &num) const
{
  return !(*this < num);
}

bool BigInt::operator==(const long long &num) const
{
  return *this == BigInt(num);
}

bool operator==(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) == rhs;
}

bool BigInt::operator!=(const long long &num) const
{
  return !(*this == BigInt(num));
}

bool operator!=(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) != rhs;
}

bool BigInt::operator<(const long long &num) const
{
  return *this < BigInt(num);
}

bool operator<(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) < rhs;
}

bool BigInt::operator>(const long long &num) const
{
  return *this > BigInt(num);
}

bool operator>(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) > rhs;
}

bool BigInt::operator<=(const long long &num) const
{
  return !(*this > BigInt(num));
}

bool operator<=(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) <= rhs;
}

bool BigInt::operator>=(const long long &num) const
{
  return !(*this < BigInt(num));
}

bool operator>=(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) >= rhs;
}

bool BigInt::operator==(const std::string &num) const
{
  return *this == BigInt(num);
}

bool operator==(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) == rhs;
}

bool BigInt::operator!=(const std::string &num) const
{
  return !(*this == BigInt(num));
}

bool operator!=(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) != rhs;
}

bool BigInt::operator<(const std::string &num) const
{
  return *this < BigInt(num);
}

bool operator<(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) < rhs;
}

bool BigInt::operator>(const std::string &num) const
{
  return *this > BigInt(num);
}

bool operator>(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) > rhs;
}

bool BigInt::operator<=(const std::string &num) const
{
  return !(*this > BigInt(num));
}

bool operator<=(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) <= rhs;
}

bool BigInt::operator>=(const std::string &num) const
{
  return !(*this < BigInt(num));
}

bool operator>=(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) >= rhs;
}

#endif

#ifndef BIG_INT_MATH_FUNCTIONS
#define BIG_INT_MATH_FUNCTIONS

#include <string>

BigInt abs(const BigInt &num)
{
  return num < 0 ? -num : num;
}

BigInt big_pow10(size_t exp)
{
  return BigInt("1" + std::string(exp, '0'));
}

BigInt pow(const BigInt &base, int exp)
{
  if (exp < 0)
  {
    if (base == 0)
      throw std::logic_error("Cannot divide by zero");
    return abs(base) == 1 ? base : 0;
  }
  if (exp == 0)
  {
    if (base == 0)
      throw std::logic_error("Zero cannot be raised to zero");
    return 1;
  }

  BigInt result = base, result_odd = 1;
  while (exp > 1)
  {
    if (exp % 2)
      result_odd *= result;
    result *= result;
    exp /= 2;
  }

  return result * result_odd;
}

BigInt pow(const long long &base, int exp)
{
  return pow(BigInt(base), exp);
}

BigInt pow(const std::string &base, int exp)
{
  return pow(BigInt(base), exp);
}

BigInt sqrt(const BigInt &num)
{
  if (num < 0)
    throw std::invalid_argument("Cannot compute square root of a negative integer");

  if (num == 0)
    return 0;
  else if (num < 4)
    return 1;
  else if (num < 9)
    return 2;
  else if (num < 16)
    return 3;

  BigInt sqrt_prev = 0;

  BigInt sqrt_current = big_pow10(num.to_string().size() / 2 - 1);

  while (abs(sqrt_current - sqrt_prev) > 1)
  {
    sqrt_prev = sqrt_current;
    sqrt_current = (num / sqrt_prev + sqrt_prev) / 2;
  }

  return sqrt_current;
}

#endif

#ifndef BIG_INT_BINARY_ARITHMETIC_OPERATORS
#define BIG_INT_BINARY_ARITHMETIC_OPERATORS

#include <climits>
#include <cmath>
#include <string>

const long long FLOOR_SQRT_LLONG_MAX = 3037000499;

BigInt BigInt::operator+(const BigInt &num) const
{
  // if the operands are of opposite signs, perform subtraction
  if (this->sign == '+' and num.sign == '-')
  {
    BigInt rhs = num;
    rhs.sign = '+';
    return *this - rhs;
  }
  else if (this->sign == '-' and num.sign == '+')
  {
    BigInt lhs = *this;
    lhs.sign = '+';
    return -(lhs - num);
  }

  // identify the numbers as `larger` and `smaller`
  std::string larger, smaller;
  std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

  BigInt result;     // the resultant sum
  result.value = ""; // the value is cleared as the digits will be appended
  short carry = 0, sum;
  // add the two values
  for (long i = larger.size() - 1; i >= 0; i--)
  {
    sum = larger[i] - '0' + smaller[i] - '0' + carry;
    result.value = std::to_string(sum % 10) + result.value;
    carry = sum / (short)10;
  }
  if (carry)
    result.value = std::to_string(carry) + result.value;

  // if the operands are negative, the result is negative
  if (this->sign == '-' and result.value != "0")
    result.sign = '-';

  return result;
}

/*
    BigInt - BigInt
    ---------------
    The operand on the RHS of the subtraction is `num`.
*/

BigInt BigInt::operator-(const BigInt &num) const
{
  // if the operands are of opposite signs, perform addition
  if (this->sign == '+' and num.sign == '-')
  {
    BigInt rhs = num;
    rhs.sign = '+';
    return *this + rhs;
  }
  else if (this->sign == '-' and num.sign == '+')
  {
    BigInt lhs = *this;
    lhs.sign = '+';
    return -(lhs + num);
  }

  BigInt result; // the resultant difference
  // identify the numbers as larger and smaller
  std::string larger, smaller;
  if (abs(*this) > abs(num))
  {
    larger = this->value;
    smaller = num.value;

    if (this->sign == '-') // -larger - -smaller = -result
      result.sign = '-';
  }
  else
  {
    larger = num.value;
    smaller = this->value;

    if (num.sign == '+') // smaller - larger = -result
      result.sign = '-';
  }
  // pad the smaller number with zeroes
  add_leading_zeroes(smaller, larger.size() - smaller.size());

  result.value = ""; // the value is cleared as the digits will be appended
  short difference;
  long i, j;
  // subtract the two values
  for (i = larger.size() - 1; i >= 0; i--)
  {
    difference = larger[i] - smaller[i];
    if (difference < 0)
    {
      for (j = i - 1; j >= 0; j--)
      {
        if (larger[j] != '0')
        {
          larger[j]--; // borrow from the j-th digit
          break;
        }
      }
      j++;
      while (j != i)
      {
        larger[j] = '9'; // add the borrow and take away 1
        j++;
      }
      difference += 10; // add the borrow
    }
    result.value = std::to_string(difference) + result.value;
  }
  strip_leading_zeroes(result.value);

  // if the result is 0, set its sign as +
  if (result.value == "0")
    result.sign = '+';

  return result;
}

BigInt BigInt::operator*(const BigInt &num) const
{
  if (*this == 0 or num == 0)
    return BigInt(0);
  if (*this == 1)
    return num;
  if (num == 1)
    return *this;

  BigInt product;
  if (abs(*this) <= FLOOR_SQRT_LLONG_MAX and abs(num) <= FLOOR_SQRT_LLONG_MAX)
    product = std::stoll(this->value) * std::stoll(num.value);
  else
  {
    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

    size_t half_length = larger.size() / 2;
    auto half_length_ceil = (size_t)ceil(larger.size() / 2.0);

    BigInt num1_high, num1_low;
    num1_high = larger.substr(0, half_length);
    num1_low = larger.substr(half_length);

    BigInt num2_high, num2_low;
    num2_high = smaller.substr(0, half_length);
    num2_low = smaller.substr(half_length);

    strip_leading_zeroes(num1_high.value);
    strip_leading_zeroes(num1_low.value);
    strip_leading_zeroes(num2_high.value);
    strip_leading_zeroes(num2_low.value);

    BigInt prod_high, prod_mid, prod_low;
    prod_high = num1_high * num2_high;
    prod_low = num1_low * num2_low;
    prod_mid = (num1_high + num1_low) * (num2_high + num2_low) - prod_high - prod_low;

    add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
    add_trailing_zeroes(prod_mid.value, half_length_ceil);

    strip_leading_zeroes(prod_high.value);
    strip_leading_zeroes(prod_mid.value);
    strip_leading_zeroes(prod_low.value);

    product = prod_high + prod_mid + prod_low;
  }
  strip_leading_zeroes(product.value);

  if (this->sign == num.sign)
    product.sign = '+';
  else
    product.sign = '-';

  return product;
}

std::tuple<BigInt, BigInt> divide(const BigInt &dividend, const BigInt &divisor)
{
  BigInt quotient, remainder, temp;

  temp = divisor;
  quotient = 1;
  while (temp < dividend)
  {
    quotient++;
    temp += divisor;
  }
  if (temp > dividend)
  {
    quotient--;
    remainder = dividend - (temp - divisor);
  }

  return std::make_tuple(quotient, remainder);
}

BigInt BigInt::operator/(const BigInt &num) const
{
  BigInt abs_dividend = abs(*this);
  BigInt abs_divisor = abs(num);

  if (num == 0)
    throw std::logic_error("Attempted division by zero");
  if (abs_dividend < abs_divisor)
    return BigInt(0);
  if (num == 1)
    return *this;
  if (num == -1)
    return -(*this);

  BigInt quotient;
  if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
    quotient = std::stoll(abs_dividend.value) / std::stoll(abs_divisor.value);
  else if (abs_dividend == abs_divisor)
    quotient = 1;
  else
  {
    quotient.value = ""; // the value is cleared as digits will be appended
    BigInt chunk, chunk_quotient, chunk_remainder;
    size_t chunk_index = 0;
    chunk_remainder.value = abs_dividend.value.substr(chunk_index, abs_divisor.value.size() - 1);
    chunk_index = abs_divisor.value.size() - 1;
    while (chunk_index < abs_dividend.value.size())
    {
      chunk.value = chunk_remainder.value.append(1, abs_dividend.value[chunk_index]);
      chunk_index++;
      while (chunk < abs_divisor)
      {
        quotient.value += "0";
        if (chunk_index < abs_dividend.value.size())
        {
          chunk.value.append(1, abs_dividend.value[chunk_index]);
          chunk_index++;
        }
        else
          break;
      }
      if (chunk == abs_divisor)
      {
        quotient.value += "1";
        chunk_remainder = 0;
      }
      else if (chunk > abs_divisor)
      {
        strip_leading_zeroes(chunk.value);
        std::tie(chunk_quotient, chunk_remainder) = divide(chunk, abs_divisor);
        quotient.value += chunk_quotient.value;
      }
    }
  }
  strip_leading_zeroes(quotient.value);

  if (this->sign == num.sign)
    quotient.sign = '+';
  else
    quotient.sign = '-';

  return quotient;
}

BigInt BigInt::operator%(const BigInt &num) const
{
  BigInt abs_dividend = abs(*this);
  BigInt abs_divisor = abs(num);

  if (abs_divisor == 0)
    throw std::logic_error("Attempted division by zero");
  if (abs_divisor == 1 or abs_divisor == abs_dividend)
    return BigInt(0);

  BigInt remainder;
  if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
    remainder = std::stoll(abs_dividend.value) % std::stoll(abs_divisor.value);
  else if (abs_dividend < abs_divisor)
    remainder = abs_dividend;
  else
  {
    BigInt quotient = abs_dividend / abs_divisor;
    remainder = abs_dividend - quotient * abs_divisor;
  }
  strip_leading_zeroes(remainder.value);

  // remainder has the same sign as that of the dividend
  remainder.sign = this->sign;
  if (remainder.value == "0") // except if its zero
    remainder.sign = '+';

  return remainder;
}

BigInt BigInt::operator+(const long long &num) const
{
  return *this + BigInt(num);
}

BigInt operator+(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) + rhs;
}

BigInt BigInt::operator-(const long long &num) const
{
  return *this - BigInt(num);
}

BigInt operator-(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) - rhs;
}

BigInt BigInt::operator*(const long long &num) const
{
  return *this * BigInt(num);
}

BigInt operator*(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) * rhs;
}

BigInt BigInt::operator/(const long long &num) const
{
  return *this / BigInt(num);
}

BigInt operator/(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) / rhs;
}

BigInt BigInt::operator%(const long long &num) const
{
  return *this % BigInt(num);
}

BigInt operator%(const long long &lhs, const BigInt &rhs)
{
  return BigInt(lhs) % rhs;
}

BigInt BigInt::operator+(const std::string &num) const
{
  return *this + BigInt(num);
}

BigInt operator+(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) + rhs;
}

BigInt BigInt::operator-(const std::string &num) const
{
  return *this - BigInt(num);
}

BigInt operator-(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) - rhs;
}

BigInt BigInt::operator*(const std::string &num) const
{
  return *this * BigInt(num);
}

BigInt operator*(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) * rhs;
}

BigInt BigInt::operator/(const std::string &num) const
{
  return *this / BigInt(num);
}

BigInt operator/(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) / rhs;
}

BigInt BigInt::operator%(const std::string &num) const
{
  return *this % BigInt(num);
}

BigInt operator%(const std::string &lhs, const BigInt &rhs)
{
  return BigInt(lhs) % rhs;
}

#endif

#ifndef BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS
#define BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS

BigInt &BigInt::operator+=(const BigInt &num)
{
  *this = *this + num;

  return *this;
}

BigInt &BigInt::operator-=(const BigInt &num)
{
  *this = *this - num;

  return *this;
}

BigInt &BigInt::operator*=(const BigInt &num)
{
  *this = *this * num;

  return *this;
}

BigInt &BigInt::operator/=(const BigInt &num)
{
  *this = *this / num;

  return *this;
}

BigInt &BigInt::operator%=(const BigInt &num)
{
  *this = *this % num;

  return *this;
}

BigInt &BigInt::operator+=(const long long &num)
{
  *this = *this + BigInt(num);

  return *this;
}

BigInt &BigInt::operator-=(const long long &num)
{
  *this = *this - BigInt(num);

  return *this;
}

BigInt &BigInt::operator*=(const long long &num)
{
  *this = *this * BigInt(num);

  return *this;
}

BigInt &BigInt::operator/=(const long long &num)
{
  *this = *this / BigInt(num);

  return *this;
}

BigInt &BigInt::operator%=(const long long &num)
{
  *this = *this % BigInt(num);

  return *this;
}

BigInt &BigInt::operator+=(const std::string &num)
{
  *this = *this + BigInt(num);

  return *this;
}

BigInt &BigInt::operator-=(const std::string &num)
{
  *this = *this - BigInt(num);

  return *this;
}

BigInt &BigInt::operator*=(const std::string &num)
{
  *this = *this * BigInt(num);

  return *this;
}

BigInt &BigInt::operator/=(const std::string &num)
{
  *this = *this / BigInt(num);

  return *this;
}

BigInt &BigInt::operator%=(const std::string &num)
{
  *this = *this % BigInt(num);

  return *this;
}

#endif

#ifndef BIG_INT_INCREMENT_DECREMENT_OPERATORS_HPP
#define BIG_INT_INCREMENT_DECREMENT_OPERATORS_HPP

BigInt &BigInt::operator++()
{
  *this += 1;

  return *this;
}

BigInt &BigInt::operator--()
{
  *this -= 1;

  return *this;
}

BigInt BigInt::operator++(int)
{
  BigInt temp = *this;
  *this += 1;

  return temp;
}

BigInt BigInt::operator--(int)
{
  BigInt temp = *this;
  *this -= 1;

  return temp;
}

#endif

#ifndef BIG_INT_IO_STREAM_OPERATORS_HPP
#define BIG_INT_IO_STREAM_OPERATORS_HPP

std::istream &operator>>(std::istream &in, BigInt &num)
{
  std::string input;
  in >> input;
  num = BigInt(input); // remove sign from value and set sign, if exists

  return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &num)
{
  if (num.sign == '-')
    out << num.sign;
  out << num.value;

  return out;
}

#endif

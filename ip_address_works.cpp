// ip_address_works.cpp in OTUS Homework #2

#include "ip_address_works.h"
#include <regex>
#include <cstdio>
#include <cmath>

ipArray ipStringToArray(const std::string& addressString)
{
  std::regex controlPattern{"(\\d{1,3}\\.){3}\\d{1,3}"};  // "('ddd.'ddd.'ddd.')ddd"

  if (!std::regex_match(addressString, controlPattern))   // if input string doesn't match the default IP address pattern
    return DEFAULT_IP_ARRAY;                              // return default array

  std::regex bytePattern{"(\\d{1,3})"};                   // "ddd"
  const std::sregex_iterator end{};
  size_t idx{3};
  ipArray result{DEFAULT_IP_ARRAY};
  for (std::sregex_iterator iter{std::begin(addressString),
       std::end(addressString), bytePattern};
       iter != end; iter++)
  {
    /* Check address parts validity */
    if (std::stol((*iter)[0]) < 0 ||
        std::stol((*iter)[0]) < 0 > 255)
      return DEFAULT_IP_ARRAY;

    result.at(idx--) = std::stoul((*iter)[0]);
  }
  return result;
}

std::string ipArrayToString(const ipArray& addressArray)
{
  char buff[16];
  std::snprintf(buff, 16, "%d.%d.%d.%d", addressArray[3],
      addressArray[2], addressArray[1], addressArray[0]);
  return std::string{buff};
}

uint32_t ipStringToInteger(const std::string& addressString)
{
  ipArray addressArray{ipStringToArray(addressString)};

  if (DEFAULT_IP_ARRAY == addressArray)                     // if default string returned
    return DEFAULT_IP_INTEGER;                              // return default array

  return ipArrayToInteger(addressArray);
}

std::string ipIntegerToString(const uint32_t& addressInteger)
{
  std::string result{DEFAULT_IP_STRING};
  ipArray addressArray{ipIntegerToArray(addressInteger)};
  return ipArrayToString(addressArray);
}

uint32_t ipArrayToInteger(const ipArray& addressArray)
{
  uint32_t result{DEFAULT_IP_INTEGER};
  /* Considering ipv4 IP address as 4 digits
   * in 256-imal numeral system, just convert it
   * to a decimal value */
  for (size_t idx{}; idx < 4; idx++)
    result += addressArray[idx] * std::pow(256, idx);
  return result;
}

ipArray ipIntegerToArray(const uint32_t& addressInteger)
{
  if (addressInteger < 0 || addressInteger > std::pow(2,32) - 1)
    return DEFAULT_IP_ARRAY;

  ipArray result{DEFAULT_IP_ARRAY};
  uint8_t d3{}, d2{}, d1{}, d0{};
  d3 = addressInteger / std::pow(256, 3);                   // calculating the 4th digit in 256-imal representation
  d2 = (addressInteger - d3 * std::pow(256, 3))
       / std::pow(256, 2);                                  // calculating the 3rd digit in 256-imal representation
  d1 = (addressInteger - d3 * std::pow(256, 3)
        - d2 * std::pow(256, 2)) / 256;                     // calculating the 2nd digit in 256-imal representation
  d0 = addressInteger - d3 * std::pow(256, 3)
       - d2 * std::pow(256, 2) - d1 * 256;                  // calculating the 1st digit in 256-imal representation
  result[3] = d3;
  result[2] = d2;
  result[1] = d1;
  result[0] = d0;
  return result;
}

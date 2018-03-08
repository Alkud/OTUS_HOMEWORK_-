// otus_hw_2_test.cpp in Otus Homework #2

#define BOOST_TEST_MODULE OTUS_HW_2_TEST

#include <boost/test/unit_test.hpp>
#include "ip_address_works.h"
#include <cmath>


BOOST_AUTO_TEST_SUITE(homework_2_test)

BOOST_AUTO_TEST_CASE(check_string_to_integer)
{
  /* Test wrong input */
  std::string addressString{"a.0.zz.p"};
  BOOST_CHECK(ipStringToInteger(addressString) == 0 );

  /* Test 0 */
  addressString = std::string{"0.0.0.0"};
  BOOST_CHECK(ipStringToInteger(addressString) == 0 );

  /* Test 1 */
  addressString = std::string{"0.0.0.1"};
  BOOST_CHECK(ipStringToInteger(addressString) == 1 * std::pow(256, 0) );

  /* Test 256 */
  addressString = std::string{"0.0.1.0"};
  BOOST_CHECK(ipStringToInteger(addressString) == 1 * std::pow(256, 1) );

  /* Test 65536 = 256^2 */
  addressString = std::string{"0.1.0.0"};
  BOOST_CHECK(ipStringToInteger(addressString) == 1 * std::pow(256, 2) );

  /* Test 16777216 = 256^3 */
  addressString = std::string{"1.0.0.0"};
  BOOST_CHECK(ipStringToInteger(addressString) == 1 * std::pow(256, 3) );

  /* Test 4294967295  = 2^32-1 */
  addressString = std::string{"255.255.255.255"};
  BOOST_CHECK(ipStringToInteger(addressString) == UINT32_MAX);
}

BOOST_AUTO_TEST_CASE(check_integer_to_string)
{
  /* Test 0.0.0.0 */
  uint32_t addressInteger{};
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"0.0.0.0"} );

  /* Test 0.0.0.1 */
  addressInteger = 1 * std::pow(256, 0);
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"0.0.0.1"} );

  /* Test 0.0.1.0 */
  addressInteger = 1 * std::pow(256, 1);
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"0.0.1.0"} );

  /* Test 0.1.0.0 */
  addressInteger = 1 * std::pow(256, 2);
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"0.1.0.0"} );

  /* Test 1.0.0.0 */
  addressInteger = 1 * std::pow(256, 3);
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"1.0.0.0"} );

  /* Test 255.255.255.255 */
  addressInteger = UINT32_MAX;
  BOOST_CHECK(ipIntegerToString(addressInteger) == std::string{"255.255.255.255"} );
}


BOOST_AUTO_TEST_SUITE_END()

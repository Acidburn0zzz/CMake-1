/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#include <cmConfigure.h> // IWYU pragma: keep

#include "cm_string_view.hxx"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cmStringAlgorithms.h"

int testStringAlgorithms(int /*unused*/, char* /*unused*/ [])
{
  int failed = 0;

  auto assert_ok = [&failed](bool test, cm::string_view title) {
    if (test) {
      std::cout << "Passed: " << title << "\n";
    } else {
      std::cout << "Failed: " << title << "\n";
      ++failed;
    }
  };

  auto assert_string = [&failed](cm::string_view generated,
                                 cm::string_view expected,
                                 cm::string_view title) {
    if (generated == expected) {
      std::cout << "Passed: " << title << "\n";
    } else {
      std::cout << "Failed: " << title << "\n";
      std::cout << "Expected: " << expected << "\n";
      std::cout << "Got: " << generated << "\n";
      ++failed;
    }
  };

  // ----------------------------------------------------------------------
  // Test cmJoin
  {
    typedef std::string ST;
    typedef std::vector<std::string> VT;
    assert_string(cmJoin(ST("abc"), ";"), "a;b;c", "cmJoin std::string");
    assert_string(cmJoin(VT{}, ";"), "", "cmJoin std::vector empty");
    assert_string(cmJoin(VT{ "a" }, ";"), "a", "cmJoin std::vector single");
    assert_string(cmJoin(VT{ "a", "b", "c" }, ";"), "a;b;c",
                  "cmJoin std::vector multiple");
    assert_string(cmJoin(VT{ "a", "b", "c" }, "<=>"), "a<=>b<=>c",
                  "cmJoin std::vector long sep");
  }

  // ----------------------------------------------------------------------
  // Test cmStrCat
  {
    int ni = -1100;
    unsigned int nui = 1100u;
    long int nli = -12000l;
    unsigned long int nuli = 12000ul;
    long long int nlli = -130000ll;
    unsigned long long int nulli = 130000ull;
    std::string val =
      cmStrCat("<test>", ni, ',', nui, ',', nli, ",", nuli, ", ", nlli,
               std::string(", "), nulli, cm::string_view("</test>"));
    std::string expect =
      "<test>-1100,1100,-12000,12000, -130000, 130000</test>";
    assert_string(val, expect, "cmStrCat strings and integers");
  }
  {
    float const val = 1.5f;
    float const div = 0.00001f;
    float f = 0.0f;
    std::istringstream(cmStrCat("", val)) >> f;
    f -= val;
    assert_ok((f < div) && (f > -div), "cmStrCat float");
  }
  {
    double const val = 1.5;
    double const div = 0.00001;
    double d = 0.0;
    std::istringstream(cmStrCat("", val)) >> d;
    d -= val;
    assert_ok((d < div) && (d > -div), "cmStrCat double");
  }

  // ----------------------------------------------------------------------
  // Test cmWrap
  {
    typedef std::vector<std::string> VT;
    assert_string(cmWrap("<", VT{}, ">", "; "), //
                  "",                           //
                  "cmWrap empty, string prefix and suffix");
    assert_string(cmWrap("<", VT{ "abc" }, ">", "; "), //
                  "<abc>",                             //
                  "cmWrap single, string prefix and suffix");
    assert_string(cmWrap("<", VT{ "a1", "a2", "a3" }, ">", "; "), //
                  "<a1>; <a2>; <a3>",                             //
                  "cmWrap multiple, string prefix and suffix");

    assert_string(cmWrap('<', VT{}, '>', "; "), //
                  "",                           //
                  "cmWrap empty, char prefix and suffix");
    assert_string(cmWrap('<', VT{ "abc" }, '>', "; "), //
                  "<abc>",                             //
                  "cmWrap single, char prefix and suffix");
    assert_string(cmWrap('<', VT{ "a1", "a2", "a3" }, '>', "; "), //
                  "<a1>; <a2>; <a3>",                             //
                  "cmWrap multiple, char prefix and suffix");
  }

  // ----------------------------------------------------------------------
  // Test cmHas(Literal)Prefix and cmHas(Literal)Suffix
  {
    std::string str("abc");
    assert_ok(cmHasPrefix(str, 'a'), "cmHasPrefix char");
    assert_ok(!cmHasPrefix(str, 'c'), "cmHasPrefix char not");
    assert_ok(cmHasPrefix(str, "ab"), "cmHasPrefix string");
    assert_ok(!cmHasPrefix(str, "bc"), "cmHasPrefix string not");
    assert_ok(cmHasPrefix(str, str), "cmHasPrefix complete string");
    assert_ok(cmHasLiteralPrefix(str, "ab"), "cmHasLiteralPrefix string");
    assert_ok(!cmHasLiteralPrefix(str, "bc"), "cmHasLiteralPrefix string not");

    assert_ok(cmHasSuffix(str, 'c'), "cmHasSuffix char");
    assert_ok(!cmHasSuffix(str, 'a'), "cmHasSuffix char not");
    assert_ok(cmHasSuffix(str, "bc"), "cmHasSuffix string");
    assert_ok(!cmHasSuffix(str, "ab"), "cmHasSuffix string not");
    assert_ok(cmHasSuffix(str, str), "cmHasSuffix complete string");
    assert_ok(cmHasLiteralSuffix(str, "bc"), "cmHasLiteralSuffix string");
    assert_ok(!cmHasLiteralSuffix(str, "ab"), "cmHasLiteralPrefix string not");
  }

  return failed;
}

#include "recipe/linear_algebra/vector.h"
#include <gtest/gtest.h>
#include <sstream>
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include <limits>

namespace recipe {
namespace linear_algebra {

//
// Vector class
//
TEST(VectorTest, CopyConstructor) {
  Vector expect(3);
  Vector actual(expect);

  EXPECT_VECTOR_ELEMENT_NEAR(expect, actual, std::numeric_limits<double>::epsilon());
}

TEST(VectorTest, ConstructorInitializer) {
  Vector actual = Vector({1, 2, 3});

  EXPECT_EQ(1, actual(0));
  EXPECT_EQ(2, actual(1));
  EXPECT_EQ(3, actual(2));
}

TEST(VectorTest, ConstructorData) {
  const int size = 3;
  std::unique_ptr<double[]> data = TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> expect(new double[size]);
  std::copy(data.get(), data.get() + size, expect.get());

  Vector actual(size, std::move(data));
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(expect[i], actual(i));
  }
}

TEST(VectorTest, Size) {
  Vector actual(4);
  EXPECT_EQ(4, actual.Size());
}

TEST(VectorTest, OperatorPlus) {
  const Vector other = MakeVector({1, 2, 3, 4});
  Vector actual = MakeVector({4, 3, 2, 1});

  actual += other;
  Vector expect = MakeVector({5, 5, 5, 5});
  EXPECT_EQ(expect, actual);
}

TEST(VectorTest, OperatorParenthesis) {
  Vector actual(3);
  actual(1) = 1.0;

  EXPECT_EQ(1.0, actual(1));
}

TEST(VectorTest, OperatorAsignment) {
  Vector expect(3);
  expect(0) = 1.0;

  Vector actual = expect;
  EXPECT_EQ(expect, actual);
}

#ifndef NDEBUG
TEST(VectorTest, AssertIndexOutOfRange) {
  Vector v(3);
  EXPECT_DEATH(v(-1), "Assertion *");
  EXPECT_DEATH(v(3), "Assertion *");
}
#endif

//
// Free functions
//

TEST(VectorTest, MakeUnitVector) {
  Vector actual = MakeUnitVector(3, 1);
  Vector expect({0.0, 1.0, 0.0});

  EXPECT_EQ(expect, actual);
}

TEST(VectorTest, VectorOutputStreamOperator1) {
  Vector data({1.0, 2.0, 3.0});

  std::ostringstream actual;
  actual << data;
  std::string expect = "1, 2, 3, ";
  EXPECT_STREQ(expect.c_str(), actual.str().c_str());
}

TEST(VectorTest, VectorOutputStreamOperator2) {
  Vector data({1.5, 2.5, 3.5});

  std::ostringstream actual;
  actual << data;
  std::string expect = "1.5, 2.5, 3.5, ";
  EXPECT_STREQ(expect.c_str(), actual.str().c_str());
}

}  // namespace linear_algebra
}  // namespace recipe

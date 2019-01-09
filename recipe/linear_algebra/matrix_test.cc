#include "recipe/linear_algebra/matrix.h"
#include <gtest/gtest.h>
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace linear_algebra {

TEST(MatrixTest, CopyConstructor) {
  Matrix m(2, 3);
  Matrix mm(m);
  EXPECT_EQ(m, mm);
}

TEST(MatrixTest, Shape) {
  Matrix m(2, 3);
  EXPECT_EQ(2, m.NumRow());
  EXPECT_EQ(3, m.NumCol());
}

TEST(MatrixTest, AssignmentOperator) {
  Matrix m(2, 3);
  m(0, 0) = 1.0;
  EXPECT_EQ(1.0, m(0, 0));
  Matrix mm = m;
  EXPECT_EQ(m, mm);
}

//
// Matrix::Slice
//
TEST(MatrixTest, SliceExample) {
  Matrix data = MakeMatrix({
      // clang-format off
      {1, 2, 3,},
      {4, 5, 6,},
      {7, 8, 9,},
      // clang-format on
  });
  const Matrix actual = data.Slice(1, 2, 1, 2);
  Matrix expect = MakeMatrix({
      // clang-format off
      {5, 6,},
      {8, 9,},
      // clang-format on
  });
  EXPECT_EQ(expect, actual);
}

//
// Free functions
//
TEST(AssignMatrixTest, SimpleExample) {
  Matrix assignee = MakeMatrix(
      // clang-format off
    {
    {1, 2, 3,},
    {4, 5, 6,},
    {7, 8, 9,},
          // clang-format on
      });
  const Matrix assigner = MakeMatrix({
      // clang-format off
    {11, 12,},
    {14, 15,},
      // clang-format on
  });
  const Matrix expect = MakeMatrix(
      // clang-format off
    {
    {1, 2, 3,},
    {4, 11, 12,},
    {7, 14, 15,},
          // clang-format on
      });
  AssignMatrix(&assignee, assigner, 1, 1);
  EXPECT_EQ(expect, assignee);
}

#ifndef NDEBUG
TEST(AssignMatrixTest, AssertCase) {
  Matrix assignee = MakeMatrix(
      // clang-format off
    {
    {1, 2, 3,},
    {4, 5, 6,},
    {7, 8, 9,},
          // clang-format on
      });
  const Matrix assigner = MakeMatrix({
      // clang-format off
    {11, 12,},
    {14, 15,},
      // clang-format on
  });
  EXPECT_ASSERT_FAIL(AssignMatrix(&assignee, assigner, -1, 1));
  EXPECT_ASSERT_FAIL(AssignMatrix(&assignee, assigner, 1, -1));
  EXPECT_ASSERT_FAIL(AssignMatrix(&assignee, assigner, 2, 1));
  EXPECT_ASSERT_FAIL(AssignMatrix(&assignee, assigner, 1, 2));
}
#endif

TEST(MakeMatrixTest, SquaredMatrixExample) {
  Matrix actual = MakeMatrix({
      // clang-format off
    {1, 2, 3,},
    {4, 5, 6,},
    {7, 8, 9,},
      // clang-format on
  });
  Matrix expect(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expect(row, col) = row * 3 + col + 1;
    }
  }
  EXPECT_EQ(expect, actual);
}

TEST(MakeMatrixTest, NonSquaredMatrixExample0) {
  Matrix actual = MakeMatrix({
      // clang-format off
    {1, 2, 3,},
    {4, 5, 6,},
    {7, 8, 9,},
    {10, 11, 12},
      // clang-format on
  });
  Matrix expect(4, 3);
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 3; ++col) {
      expect(row, col) = row * 3 + col + 1;
    }
  }
  EXPECT_EQ(expect, actual);
}

TEST(MakeMatrixTest, NonSquaredMatrixExample1) {
  Matrix actual = MakeMatrix({
      // clang-format off
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
      // clang-format on
  });
  Matrix expect(3, 4);
  for (int row = 0; row < expect.NumRow(); ++row) {
    for (int col = 0; col < expect.NumCol(); ++col) {
      expect(row, col) = row * expect.NumCol() + col + 1;
    }
  }
  EXPECT_EQ(expect, actual);
}

TEST(MatrixTest, MakeIdentityMatrixTest) {
  Matrix expect = MakeMatrix(
      // clang-format off
      {
      {1.0, 0.0, 0.0,},
      {0.0, 1.0, 0.0,},
      {0.0, 0.0, 1.0,},
          // clang-format on
      });
  Matrix actual = MakeIdentityMatrix(3);
  EXPECT_EQ(expect, actual);
}

#ifndef NDEBUG
TEST(MatrixTest, AssertIndexOutOfRange) {
  Matrix m(2, 3);
  EXPECT_DEATH(m(-1, 0), "Assertion *");
  EXPECT_DEATH(m(0, 3), "Assertion *");
}
#endif

//
// GetColumnVector
//
class GetColumnVectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    data0_ = MakeMatrix({
        // clang-format off
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
        // clang-format on
    });
  }
  void TearDown() override {}
  Matrix data0_;
};

TEST_F(GetColumnVectorTest, Example0) {
  Vector vec(2);
  const int col_index = 0;
  const int row_offset = 1;
  const int vec_size = vec.Size();
  GetColumnVector(data0_.Get(), vec.Get(), col_index, row_offset, vec_size,
                  data0_.NumRow(), data0_.NumCol());
  const Vector expect = MakeVector({4, 7});
  EXPECT_EQ(expect, vec);
}

TEST_F(GetColumnVectorTest, Example1) {
  Vector vec(3);
  const int col_index = 2;
  const int row_offset = 0;
  const int vec_size = vec.Size();
  GetColumnVector(data0_.Get(), vec.Get(), col_index, row_offset, vec_size,
                  data0_.NumRow(), data0_.NumCol());
  const Vector expect = MakeVector({3, 6, 9});
  EXPECT_EQ(expect, vec);
}

#ifndef NDEBUG
TEST_F(GetColumnVectorTest, ColIndexIsLargerThanMatrixSize) {
  Vector vec(3);
  const int col_index = 3;
  const int row_offset = 0;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetColumnVector(data0_.Get(), vec.Get(), col_index,
                                     row_offset, vec_size, data0_.NumRow(),
                                     data0_.NumCol()));
}

TEST_F(GetColumnVectorTest, RowOffsetIsLargerThanMatrixSize) {
  Vector vec(3);
  const int col_index = 2;
  const int row_offset = 3;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetColumnVector(data0_.Get(), vec.Get(), col_index,
                                     row_offset, vec_size, data0_.NumRow(),
                                     data0_.NumCol()));
}

TEST_F(GetColumnVectorTest, VecSizeIsLargerThanMatrixSize) {
  Vector vec(4);
  const int col_index = 2;
  const int row_offset = 0;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetColumnVector(data0_.Get(), vec.Get(), col_index,
                                     row_offset, vec_size, data0_.NumRow(),
                                     data0_.NumCol()));
}
#endif  // #ifndef NDEBUG

//
// GetRowVector
//

class GetRowVectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    data0_ = MakeMatrix({
        // clang-format off
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
        // clang-format on
    });
  }
  void TearDown() override {}
  Matrix data0_;
};

TEST_F(GetRowVectorTest, Example0) {
  Vector vec(2);
  const int row_index = 0;
  const int col_offset = 1;
  const int vec_size = vec.Size();
  GetRowVector(data0_.Get(), vec.Get(), row_index, col_offset, vec_size,
               data0_.NumRow(), data0_.NumCol());
  const Vector expect = MakeVector({2, 3});
  EXPECT_EQ(expect, vec);
}

TEST_F(GetRowVectorTest, Example1) {
  Vector vec(3);
  const int row_index = 2;
  const int col_offset = 0;
  const int vec_size = vec.Size();
  GetRowVector(data0_.Get(), vec.Get(), row_index, col_offset, vec_size,
               data0_.NumRow(), data0_.NumCol());
  const Vector expect = MakeVector({7, 8, 9});
  EXPECT_EQ(expect, vec);
}

#ifndef NDEBUG
TEST_F(GetRowVectorTest, RowIndexIsLargerThanMatrixSize) {
  Vector vec(3);
  const int row_index = 3;
  const int col_offset = 0;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetRowVector(data0_.Get(), vec.Get(), row_index,
                                  col_offset, vec_size, data0_.NumRow(),
                                  data0_.NumCol()));
}

TEST_F(GetRowVectorTest, ColOffsetIsLargerThanMatrixSize) {
  Vector vec(3);
  const int row_index = 2;
  const int col_offset = 3;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetRowVector(data0_.Get(), vec.Get(), row_index,
                                  col_offset, vec_size, data0_.NumRow(),
                                  data0_.NumCol()));
}

TEST_F(GetRowVectorTest, VecSizeIsLargerThanMatrixSize) {
  Vector vec(4);
  const int row_index = 2;
  const int col_offset = 0;
  const int vec_size = vec.Size();

  EXPECT_ASSERT_FAIL(GetRowVector(data0_.Get(), vec.Get(), row_index,
                                  col_offset, vec_size, data0_.NumRow(),
                                  data0_.NumCol()));
}
#endif  // #ifndef NDEBUG

}  // namespace linear_algebra
}  // namespace recipe

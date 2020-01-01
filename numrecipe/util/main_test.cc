#include <glog/logging.h>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  FLAGS_log_dir = "/tmp";
  return RUN_ALL_TESTS();
}

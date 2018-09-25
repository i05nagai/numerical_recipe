#include "recipe/util/sample.h"
#include <glog/logging.h>

namespace recipe {
namespace util {
int hoge() {
  LOG(INFO) << "file";
  return 1;
}
}  // namespace util
}  // namespace recipe

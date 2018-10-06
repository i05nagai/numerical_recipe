#include "recipe/util/sample.h"
#include <glog/logging.h>

namespace recipe {
namespace util {
int Bar() {
  DLOG(INFO) << "file";
  return 1;
}
}  // namespace util
}  // namespace recipe

#include "numrecipe/util/sample.h"
#include <glog/logging.h>

namespace numrecipe {
namespace util {
int Bar() {
  DLOG(INFO) << "file";
  return 1;
}
}  // namespace util
}  // namespace numrecipe

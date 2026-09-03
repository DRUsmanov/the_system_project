#pragma once

#include <cstdint>
#include <string>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct AdminCategoryIdTag {};
}  // namespace detail

using AdminCategoryId = utils::Tagged<uint64_t, detail::AdminCategoryIdTag>;
using AdminCategoryIdHasher = utils::TaggedHasher<AdminCategoryId>;

}  // namespace domain

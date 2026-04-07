#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <string>

namespace domain {

namespace detail {
    struct AdminCategoryIdTag{};
} // namespace detail

using AdminCategoryId = utils::Tagged<int, detail::AdminCategoryIdTag>;
using AdminCategoryIdHasher = utils::TaggedHasher<AdminCategoryId>;

struct AdminCategory {
    int admin_category_id;
};
    
} // namespace domain

#pragma once

#include <optional>

#include "domain/value_data/types.h"
#include "utils/tagged.h"

namespace domain {

namespace detail {
struct Profession {};
}  // namespace detail

using ProfessionId = utils::Tagged<int, detail::Profession>;
using ProfessionIdHasher = utils::TaggedHasher<ProfessionId>;

struct Profession {
    ProfessionId profession_id;
    std::string name;
};

}  // namespace domain

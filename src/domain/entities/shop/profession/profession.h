#pragma once

#include <cstdint>
#include <optional>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct Profession {};
}  // namespace detail

using ProfessionId = utils::Tagged<uint64_t, detail::Profession>;
using ProfessionIdHasher = utils::TaggedHasher<ProfessionId>;

struct Profession {
    ProfessionId profession_id;
    std::string name;
};

}  // namespace domain

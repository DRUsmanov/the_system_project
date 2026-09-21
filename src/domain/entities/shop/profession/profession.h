#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct Profession {};
}  // namespace detail

using ProfessionId = utils::Tagged<uint64_t, detail::Profession>;
using ProfessionIdHasher = utils::TaggedHasher<ProfessionId>;

struct Profession {
    std::string name;
};

using Professions = std::unordered_map<ProfessionId, Profession, ProfessionIdHasher>;

}  // namespace domain

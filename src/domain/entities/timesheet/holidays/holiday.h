#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <string>

namespace domain {

namespace detail {
    struct Holiday{};
    struct ExtraHolidayDay{};
    struct PreHolidayDay{};
} // namespace detail

using HolidayId = utils::Tagged<int, detail::Holiday>;
using HolidayIdHasher = utils::TaggedHasher<HolidayId>;

    
} // namespace domain

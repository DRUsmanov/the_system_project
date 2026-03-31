#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <string>

namespace domain {

namespace detail {
    struct HolidayIdtag{};
    struct ExtraHolidayDayIdTag{};
    struct PreHolidayDayIdTag{};
} // namespace detail

using HolidayId = utils::Tagged<int, detail::HolidayIdtag>;
using HolidayIdHasher = utils::TaggedHasher<HolidayId>;

    
} // namespace domain

#pragma once

#include <cstdint>
#include <string>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct HolidayIdtag {};
struct ExtraHolidayDayIdTag {};
struct PreHolidayDayIdTag {};
}  // namespace detail

using HolidayId = utils::Tagged<uint64_t, detail::HolidayIdtag>;
using HolidayIdHasher = utils::TaggedHasher<HolidayId>;

using Holidays = std::unordered_set<Date, DateHasher>;
using ExtraHolidays = std::unordered_set<Date, DateHasher>;
using PreHolidays = std::unordered_set<Date, DateHasher>;

}  // namespace domain
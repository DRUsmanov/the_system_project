#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

namespace domain {

namespace detail {
    struct Vacation{};
} // namespace detail

using VacationId = utils::Tagged<int, detail::Vacation>;
using VacationIdHasher = utils::TaggedHasher<VacationId>;

struct Vacation{
    Date start;
    Date end;

    bool IsVacationDay(const Date& date) {
        return !(date < start || date > end);
    }
};
    
} // namespace domain

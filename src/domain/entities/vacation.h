#pragma once

#include "../../utils/tagged.h"
#include "../value_data/timesheet_data.h"

namespace domain {

namespace detail {
    struct Vacation{};
} // namespace detail

using VacationId = utils::Tagged<int, detail::Vacation>;
using VacationIdHasher = utils::TaggedHasher<VacationId>;

struct VacationData{
    Date start;
    Date end;

    bool IsVacationDay(const Date& date) {
        return !(date < start || date > end);
    }
};
    
} // namespace domain

#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

namespace domain {

namespace detail {
    struct VacationIdTag{};
} // namespace detail

using VacationId = utils::Tagged<int, detail::VacationIdTag>;
using VacationIdHasher = utils::TaggedHasher<VacationId>;

struct Vacation{
    Date start;
    Date end;

    bool IsVacationDay(const Date& date) const {
        return !(date < start || date > end);
    }
};

struct VacationHasher {
    size_t operator()(const Vacation& vacation) const {
        return DateHasher{}(vacation.start) + 37 * DateHasher{}(vacation.end);
    }
};

bool operator==(const Vacation& vacation1, const Vacation& vacation2) {
    return vacation1.start == vacation2.start && vacation1.end == vacation2.end;
}
    
} // namespace domain

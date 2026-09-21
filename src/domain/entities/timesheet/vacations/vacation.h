#pragma once

#include <cstdint>
#include <unordered_map>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct VacationIdTag {};
}  // namespace detail

using VacationId = utils::Tagged<uint64_t, detail::VacationIdTag>;
using VacationIdHasher = utils::TaggedHasher<VacationId>;

struct Vacation {
    Date start;
    Date end;

    bool isVacationDay(const Date& date) const {
        return !(date < start || date > end);
    }
};

struct VacationHasher {
    size_t operator()(const Vacation& vacation) const {
        return DateHasher{}(vacation.start) + 37 * DateHasher{}(vacation.end);
    }
};

inline bool operator==(const Vacation& vacation1, const Vacation& vacation2) {
    return vacation1.start == vacation2.start && vacation1.end == vacation2.end;
}

using Vacations = std::unordered_map<VacationId, Vacation, VacationIdHasher>;

}  // namespace domain

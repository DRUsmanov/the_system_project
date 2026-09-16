#pragma once

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

enum class LeaveType : uint64_t {
    VACATION = 0,                    // Отпуск
    STUDY_LEAVE = 1,                 // Ученический отпуск
    STATE_DUTIES = 2,                // Гос. обязанности
    MOBILIZATION = 3,                // Мобилизация
    SICK_LEAVE = 4,                  // Больничный
    MEDICAL_CHECKUP = 5,             // Медосмотр
    DONOR_DAY = 6,                   // Донорский день
    SICK_LEAVE_DURING_VACATION = 7,  // Больничный во время отпуска
    MEDICAL_EXAMINATION = 8,         // Диспансеризация
    LEAVE_WITHOUT_PAY = 9,           // Отпуск без сохранения з/п
    ADDITIONAL_DAY_OFF = 10,         // Дополнительный день отдыха
    COLLECTIVE_AGREEMENT = 11,       // Коллективный договор
    TRAINING = 12                    // Обучение
};

}  // namespace domain

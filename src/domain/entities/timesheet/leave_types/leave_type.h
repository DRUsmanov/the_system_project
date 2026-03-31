#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

namespace domain {

enum class LeaveType {
    STUDY_LEAVE, // Ученический отпуск
    STATE_DUTIES, // Гос. обязанности
    MOBILIZATION, // Мобилизация
    SICK_LEAVE, // Больничный
    MEDICAL_CHECKUP, // Медосмотр
    DONOR_DAY, // Донорский день
    SICK_LEAVE_DURING_VACATION, // Больничный во время отпуска
    MEDICAL_EXAMINATION, // Диспансеризация
    LEAVE_WITHOUT_PAY, // Отпуск без сохранения з/п
    ADDITIONAL_DAY_OFF, // Дополнительный день отдыха
    COLLECTIVE_AGREEMENT, // Коллективный договор
    TRAINING // Обучение
};
    
} // namespace domain

#pragma once

#include <string_view>
#include <unordered_map>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

enum class LeaveType : uint64_t {
    VACATION = 1,                // Отпуск
    STUDY_LEAVE,                 // Ученический отпуск
    STATE_DUTIES,                // Гос. обязанности
    MOBILIZATION,                // Мобилизация
    SICK_LEAVE,                  // Больничный
    MEDICAL_CHECKUP,             // Медосмотр
    DONOR_DAY,                   // Донорский день
    SICK_LEAVE_DURING_VACATION,  // Больничный во время отпуска
    MEDICAL_EXAMINATION,         // Диспансеризация
    LEAVE_WITHOUT_PAY,           // Отпуск без сохранения з/п
    ADDITIONAL_DAY_OFF,          // Дополнительный день отдыха
    COLLECTIVE_AGREEMENT,        // Коллективный договор
    TRAINING,                    // Обучение
    WEEKEND,                     // Выходной
    HOLIDAY,                     // Праздник
    EXTRA_HOLIDAY                // Дополнительный праздничный выходной
};

constexpr std::string_view VACATION = "Отпуск";
constexpr std::string_view STUDY_LEAVE = "Ученический отпуск";
constexpr std::string_view STATE_DUTIES = "Гос. обязанности";
constexpr std::string_view MOBILIZATION = "Мобилизация";
constexpr std::string_view SICK_LEAVE = "Больничный";
constexpr std::string_view MEDICAL_CHECKUP = "Медосмотр";
constexpr std::string_view DONOR_DAY = "Донорский день";
constexpr std::string_view SICK_LEAVE_DURING_VACATION = "Больничный во время отпуска";
constexpr std::string_view MEDICAL_EXAMINATION = "Диспансеризация";
constexpr std::string_view LEAVE_WITHOUT_PAY = "Отпуск без сохранения з/п";
constexpr std::string_view ADDITIONAL_DAY_OFF = "Дополнительный день отдыха";
constexpr std::string_view COLLECTIVE_AGREEMENT = "Коллективный договор";
constexpr std::string_view TRAINING = "Обучение";
constexpr std::string_view WEEKEND = "Выходной";
constexpr std::string_view HOLIDAY = "Праздник";
constexpr std::string_view EXTRTA_HOLIDAY = "Дополнительный праздничный выходной";

using LeaveTypeDescriptions = std::unordered_map<LeaveType, std::string_view>;

inline const LeaveTypeDescriptions kLeaveTypeDescriptions{
    {LeaveType::VACATION, VACATION},
    {LeaveType::STUDY_LEAVE, STUDY_LEAVE},
    {LeaveType::STATE_DUTIES, STATE_DUTIES},
    {LeaveType::MOBILIZATION, MOBILIZATION},
    {LeaveType::SICK_LEAVE, SICK_LEAVE},
    {LeaveType::MEDICAL_CHECKUP, MEDICAL_CHECKUP},
    {LeaveType::DONOR_DAY, DONOR_DAY},
    {LeaveType::SICK_LEAVE_DURING_VACATION, SICK_LEAVE_DURING_VACATION},
    {LeaveType::MEDICAL_EXAMINATION, MEDICAL_EXAMINATION},
    {LeaveType::LEAVE_WITHOUT_PAY, LEAVE_WITHOUT_PAY},
    {LeaveType::ADDITIONAL_DAY_OFF, ADDITIONAL_DAY_OFF},
    {LeaveType::COLLECTIVE_AGREEMENT, COLLECTIVE_AGREEMENT},
    {LeaveType::TRAINING, TRAINING},
    {LeaveType::WEEKEND, WEEKEND},
    {LeaveType::HOLIDAY, HOLIDAY},
    {LeaveType::EXTRA_HOLIDAY, EXTRTA_HOLIDAY}};

}  // namespace domain

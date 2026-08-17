#include "shop_service.h"

using namespace application;

domain::Shop ShopService::getShop() const {
    return shop_repository_->downloadShop();
}

bool application::ShopService::addEmployee(const domain::Employee& employee,
                                           domain::DepartmentId department_id,
                                           domain::StaffPositionId staff_position_id,
                                           domain::WorkScheduleId work_schedule_id) {
    return shop_repository_->uploadEmployee(employee, department_id, staff_position_id, work_schedule_id);
}

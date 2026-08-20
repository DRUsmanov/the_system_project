#include "shop_service.h"

using namespace application;

domain::Shop ShopService::getShop() const {
    return shop_repository_->downloadShop();
}

bool application::ShopService::addEmployee(domain::Shop::EmployeeAssignment employee_assignment,
                                           const domain::Employee& employee) {
    return shop_repository_->uploadEmployee(employee,
                                            employee_assignment.department_id,
                                            employee_assignment.staff_position_id,
                                            employee_assignment.work_schedule_id);
}

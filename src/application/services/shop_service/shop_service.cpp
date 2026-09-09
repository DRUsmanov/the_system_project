#include "services/shop_service/shop_service.h"

#include "logger.h"

using namespace application;

domain::Shop ShopService::getShop() const {
    return shop_repository_->downloadShop();
}

std::optional<domain::EmployeeId> application::ShopService::addNewEmployee(
    domain::Shop::EmployeeAssignment employee_assignment,
    const domain::Employee& employee) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return shop_repository_->uploadEmployee(employee,
                                            employee_assignment.department_id,
                                            employee_assignment.staff_position_id,
                                            employee_assignment.work_schedule_id);
}

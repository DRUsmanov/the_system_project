set(ENTITIES_DIR
    ${SRC_ROOT}/domain/entities
)
set(REPOSITORIES_DIR
    ${SRC_ROOT}/domain/repositories
)
set(VALUE_DATA_DIR
    ${SRC_ROOT}/domain/value_data
)

set(ENTITIES_SOURCE
    ${ENTITIES_DIR}/permission/permission.h
    ${ENTITIES_DIR}/shop/department/department.h
    ${ENTITIES_DIR}/shop/employee/employee.h
    ${ENTITIES_DIR}/shop/profession/profession.h
    ${ENTITIES_DIR}/shop/staff_position/staff_position.h
    ${ENTITIES_DIR}/shop/shop.h
    ${ENTITIES_DIR}/shop/shop.cpp
    ${ENTITIES_DIR}/timesheet/admin_categorys/admin_category.h
    ${ENTITIES_DIR}/timesheet/holidays/holiday.h
    ${ENTITIES_DIR}/timesheet/leave_types/leave_type.h
    ${ENTITIES_DIR}/timesheet/vacations/vacation.h
    ${ENTITIES_DIR}/timesheet/work_schedules/work_schedule.h
    ${ENTITIES_DIR}/timesheet/work_schedules/work_schedule.cpp
    ${ENTITIES_DIR}/timesheet/timesheet.h
    ${ENTITIES_DIR}/timesheet/timesheet.cpp
    ${ENTITIES_DIR}/user/user.h
)

set(REPOSITORIES_SOURCE
    ${REPOSITORIES_DIR}/exams_repository.h
    ${REPOSITORIES_DIR}/permission_repository_interface.h
    ${REPOSITORIES_DIR}/shop_repository_interface.h
    ${REPOSITORIES_DIR}/timesheet_repository_interface.h
    ${REPOSITORIES_DIR}/users_repository_interface.h
)

set(VALUE_DATA_SOURCE
    ${VALUE_DATA_DIR}/types.h
)

set(DOMAIN_SOURCE
    ${ENTITIES_SOURCE}
    ${REPOSITORIES_SOURCE}
    ${VALUE_DATA_SOURCE}
)

add_library(domain STATIC ${DOMAIN_SOURCE})

target_include_directories(domain PUBLIC ${SRC_ROOT})

target_link_libraries(domain PUBLIC UTILS)

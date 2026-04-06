# Проект в разработке!

# Описание
Проект по разработке системы управления производственными цехами для нефтеперерабатывающей компании.

# Модули
+ [__База данных__](#база-данных)
  * [__Пользователи__](#пользователи)
  * [__Производственный цех__](#производственный-цех)
  * [__Табель рабочего времени__](#табель-рабочего-времени)
  * [__Табель сверхурочной работы__](#табель-сверхурочной-работы)
  * [__Табель работ в выходной день__](#табель-работ-в-выходной-день)
  * [__Отсутствия__](#отсутствия)
+ [__Аутентификация__](#аутентификация)
+ [__Модуль управления подразделением__](#модуль-управления-подразделением)
+ [__Модуль табеля учета рабочего времени__](#модуль-табеля-учета-рабочего-времени)
+ [__Модуль обучения__](#модуль-обучения)
+ [__Модуль инструктажей__](#модуль-инструктажей )
+ [__Модуль оборудования__](#модуль-оборудования)
+ [__Модуль плановых производственных работ__](#модуль-плановых-производственных-работ)

## База данных
На диаграммах прямоугольниками представлены таблицы, которые определены в прочих разделах базы данных.

### Пользователи
```mermaid
erDiagram
users{
serial id PK
int employee_id FK
varchar(100) login
varchar(100) password
bigint permissions
int admin_category_id FK
}

admin_categorys{
serial id PK
varchar(100) type
}

employees ||--|| users : "один пользователь -> один сотрудник"
admin_categorys ||--o| users : "один пользователя -> ноль или одна категория одминистраторов"
```
### Производственный цех
```mermaid
erDiagram
departments{
serial id PK
varchar(100) department
}

staff_positions{
serial id PK
varchar(100) staff_position
}

work_schedules{
serial id PK
JSONB work_schedule
varchar(100) description
}

employees{
serial id PK
varchar(100) last_name
varchar(100) first_name
varchar(100) patronymic
date birth_date
date employment_date
int employee_number
}

staffing_assignments{
serial id PK
int employee_id FK
int department_id FK
int staff_position_id FK
int work_schedule_id FK
}

employees ||--|| staffing_assignments : "один сотрудник -> одно назначение"
departments ||--o{ staffing_assignments : "один участок -> работает ноль или много сотрудников"
work_schedules ||--o{ staffing_assignments : "один график -> работает ноль или много сотрудников"
staff_positions ||--o{ staffing_assignments : "одна позиция -> занимает ноль или много сотрудников"

professions{
serial id PK
varchar(100) profession
}

roles{
serial id PK
varchar(100) role
}

employees_professions{
serial id PK
int employee_id FK
int profession_id FK
}

employees_roles{
serial id PK
int employee_id FK
int role_id FK
}

employees ||--|{ employees_professions : "сотрудник -> одна или несколько профессий"
employees ||--o{ employees_roles : "сотрудник -> ноль или несколько ролей"
professions ||--o{ employees_professions : "профессия -> занимает ноль или несколько сотрудников"
roles ||--o{ employees_roles : "роль -> занимает ноль или несколько сотрудников"
```

### Табель рабочего времени
```mermaid
erDiagram
timesheet{
serial id PK
int employee_id FK
int department_id FK
int staff_position_id FK
int profession_id FK
int work_schedule_id FK
date date
time_without_time_zone work_start
time_without_time_zone work_end
time_without_time_zone work_time
time_without_time_zone night_work_start
time_without_time_zone night_work_end
time_without_time_zone nigth_work_time
time_without_time_zone rest_start
time_without_time_zone rest_end
int leave_type
int admin_category_id FK
int admin_employee_id FK
varchar(100) comment
}

employees ||--o{ timesheet : "один сотрудник -> много ссылок в табеле"
departments ||--o{ timesheet : "один участок -> много ссылок в табеле"
staff_positions ||--o{ timesheet : "одна позиция -> много ссылок в табеле"
professions ||--o{ timesheet : "одна профессия -> много ссылок в табеле"
work_schedules ||--o{ timesheet : "один график -> много ссылок в табеле"
admin_categorys ||--|{ timesheet : "одна категория -> много ссылок в табеле"
```
### Табель сверхурочной работы
```mermaid
erDiagram
overtime_work{
serial id PK
int employee_id FK
int department_id FK
int staff_position_id FK
int profession_id FK
date date
time_without_time_zone work_start
time_without_time_zone work_end
time_without_time_zone work_time
int admin_category_id FK
int admin_employee_id FK
varchar(100) reason
bool add_compensatory_time
varchar(100) comment
}

employees ||--o{ overtime_work : "один сотрудник -> много ссылок в табеле сверхурочной работы"
departments ||--o{ overtime_work : "один участок -> много ссылок в табеле сверхурочной работы"
staff_positions ||--o{ overtime_work : "одна позиция -> много ссылок в табеле сверхурочной работы"
professions ||--o{ overtime_work : "одна профессия -> много ссылок в табеле сверхурочной работы"
admin_categorys ||--|{ overtime_work : "одна категория -> много ссылок в табеле сверхурочной работы"
```

### Табель работ в выходной день
```mermaid
erDiagram
weekend_work{
serial id PK
int employee_id FK
int department_id FK
int staff_position_id FK
int profession_id FK
date date
time_without_time_zone work_start
time_without_time_zone work_end
time_without_time_zone work_time
time_without_time_zone rest_start
time_without_time_zone rest_end
int admin_category_id FK
int admin_employee_id FK
varchar(100) reason
bool add_compensatory_time
varchar(100) comment
}

employees ||--o{ weekend_work : "один сотрудник -> много ссылок в табеле работ в выходной день"
departments ||--o{ weekend_work : "один участок -> много ссылок в табеле работ в выходной день"
staff_positions ||--o{ weekend_work : "одна позиция -> много ссылок в табеле работ в выходной день"
professions ||--o{ weekend_work : "одна профессия -> много ссылок в табеле работ в выходной день"
admin_categorys ||--|{ weekend_work : "одна категория -> много ссылок в табеле работ в выходной день"
```

### Отсутствия
```mermaid
erDiagram
pre_holidays_days{
serial id PK
date date
}

holidays{
serial id PK
date date
}

extra_holidays_days{
serial id PK
date date
}
```
```mermaid
erDiagram
study_vacations{
serial id PK
int employee_id FK
date start_date
date end_date
}

civic_duties{
serial id PK
int employee_id FK
date start_date
date end_date
}

dispensary_checkups{
serial id PK
int employee_id FK
date start_date
date end_date
}

donor_days{
serial id PK
int employee_id FK
date start_date
date end_date
}

vacations{
serial id PK
int employee_id FK
date start_date
date end_date
}

employees ||--o{ study_vacations : "один сотрудник -> ноль или много ученических отпусков"
employees ||--o{ civic_duties : "один сотрудник -> ноль или много исполнений гособязанностей"
employees ||--o{ dispensary_checkups : "один сотрудник -> ноль или много диспансеризаций"
employees ||--o{ donor_days : "один сотрудник -> ноль или много донорских дней"
employees ||--o{ vacations : "один сотрудник -> ноль или много отпусков"
```
```mermaid
erDiagram
mobilizations{
serial id PK
int employee_id FK
date start_date
date end_date
}

sick_leaves{
serial id PK
int employee_id FK
date start_date
date end_date
}

medical_checkups{
serial id PK
int employee_id FK
date start_date
date end_date
}

study{
serial id PK
int employee_id FK
date date
int profession_id FK
int study_program_id FK
}

employees ||--o{ mobilizations : "один сотрудник -> ноль или много мобилизаций"
employees ||--o{ sick_leaves : "один сотрудник -> ноль или много больничных"
employees ||--o{ medical_checkups : "один сотрудник -> ноль или много медосмотров"
employees ||--o{ study : "один сотрудник -> ноль или много обучений"
```
```mermaid
erDiagram
unpaid_leaves{
serial id PK
int employee_id FK
date start_date
date end_date
}

compensatory_days_leaves{
serial id PK
int employee_id FK
date start_date
date end_date
}

compensatory_times_leaves{
serial id PK
int employee_id FK
date date
time_without_time_zone start_time
time_without_time_zone end_time
}

collective_agreement_leaves{
serial id PK
int employee_id FK
date start_date
date end_date
}

employees ||--o{ unpaid_leaves : "один сотрудник -> ноль или много отпусков без сохр. ЗП"
employees ||--o{ compensatory_days_leaves : "один сотрудник -> ноль или много доп. дней отдыха"
employees ||--o{ compensatory_times_leaves : "один сотрудник -> ноль или много доп. времени отдыха"
employees ||--o{ collective_agreement_leaves : "один сотрудник -> ноль или много отсутствий по КД"
```

### Обучение, проверки знаний
```mermaid
erDiagram
study_programs{
serial id PK
varchar(100) program
int period
}

electrical_permits{
serial id PK
varchar(100) electrical_permit
int period
}

height_groups{
serial id PK
varchar(100) height_group
int period
}

work_instructions_exams_periods{
serial id PK
int profession_id FK
int period
}

professions ||--|| work_instructions_exams_periods : "одна профессия -> одна периодичность"
```
```mermaid
erDiagram
instructions_types{
serial id PK
varchar(100) type
int period
}

electrical_permits_exams{
serial id PK
int employee_id FK
int electrical_permit_id FK
date date
}

work_at_height_exams{
serial id PK
int employee_id FK
int height_group_id FK
date date
}

work_instructions_exams{
serial id PK
int employee_id FK
int profession_id FK
date date
}

instructions{
serial id PK
int employee_id FK
int instruction_type_id FK
date date
}

employees ||--o{  instructions : "один работник -> ноль или много инструктажей"
instructions_types ||--o{  instructions : "один вид инструктажа -> ноль или много инструктажей по нему"
employees ||--o{  electrical_permits_exams : "один работник -> ноль или много проверок знаний на группу по электробезопасности"
electrical_permits ||--o{  electrical_permits_exams : "одна группа по электробезопасности -> ноль или много проверок знаний по ней"
employees ||--o{  work_at_height_exams : "один работник -> ноль или много проверок знаний на группу по высоте"
height_groups ||--o{  work_at_height_exams : "одна группа по высоте -> ноль или много проверок знаний по ней"
employees ||--o{  work_instructions_exams : "один работник -> ноль или много проверок знаний по профессии"
professions ||--o{  work_instructions_exams : "одна профессия -> ноль или много проверок знаний по ней"
```
## Аутентификация
```mermaid
sequenceDiagram

actor user

box rgb(138, 136, 252) Infrastructure
participant RequestHandler
participant LoginRequestHandler
participant TokenGenerator
end

box rgb(243, 252, 136) Application
participant ApplicationManagerInterface
participant LoginServiceInterface
end

box rgb(136, 252, 210) Domain
participant UserRepositoryInterface
end

actor DB@{"type" : "database"}

autonumber
user ->> RequestHandler: login_request
activate RequestHandler
RequestHandler ->> LoginRequestHandler: login_request
deactivate RequestHandler
activate LoginRequestHandler
LoginRequestHandler ->> ApplicationManagerInterface: InputLoginDtO
activate ApplicationManagerInterface
ApplicationManagerInterface ->> LoginServiceInterface: LoginData
activate LoginServiceInterface
LoginServiceInterface ->> UserRepositoryInterface: LoginData
activate UserRepositoryInterface
UserRepositoryInterface ->> DB: sql_login_request

activate DB

alt Успешная аутентификация
DB -->> UserRepositoryInterface: success
UserRepositoryInterface -->> LoginServiceInterface: User
LoginServiceInterface -->> ApplicationManagerInterface: User
ApplicationManagerInterface -->> LoginRequestHandler: OutputLoginDto
LoginRequestHandler ->> TokenGenerator: payload
activate TokenGenerator
TokenGenerator -->> LoginRequestHandler: token
deactivate TokenGenerator
LoginRequestHandler -->> user: 200 + system.html + token

else Неуспешная аутентификация
autonumber 7
DB -->> UserRepositoryInterface: unsuccess
deactivate DB
UserRepositoryInterface -->> LoginServiceInterface: nullopt
deactivate UserRepositoryInterface
LoginServiceInterface -->> ApplicationManagerInterface: nullopt
deactivate LoginServiceInterface
ApplicationManagerInterface -->> LoginRequestHandler: nullopt
deactivate ApplicationManagerInterface
LoginRequestHandler -->> user: 401
deactivate LoginRequestHandler
end
```
## Модуль управления подразделением
Модуль предназначен для управления структурой подразделения.
### Инструменты:
+ Добавление участка
+ Удаление участка
+ Добавление штатной единицы
+ Удаление штатной единицы
+ Добавление работника
+ Удаление работника
+ Перевод работника на другой участок
+ Перевод работника на другую штатную единицу

## Модуль табеля учета рабочего времени
Модуль предназначен для фиксации фактически отработанного времени и отсутствий работников.
Модуль предусматривает версионирование табеля рабочего времени между администраторами табеля для поддержания истинности данных при конфликтах разных версий.
+ Системная версия - базовая версия табеля сгенерированная автоматически на год для всего подразделения.
+ Версия техника - измененная техником базовая версия табеля.
+ Версия участка - изменная персоналом участка (начальником участка/мастером) базовая версия табеля.
### Инструменты:
+ Генерация базового табеля.
+ Вывод данных по участку.
+ Изменение данных работника в табеле.
## Модуль обучения
Отслеживает сроки обучения работников, сопостовляет их с табелем учета рабочего времени, составляет график обучения на год.

## Модуль инструктажей 
Отслеживает сроки проведения инструктажей работников.

## Модуль оборудования
Структурирует оборудование производственного цеха.

## Модуль плановых производственных работ
Формирует графики плановых производственных работ. Ведет учет выполненных работ.

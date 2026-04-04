# Проект в разработке!

# Описание
Проект по разработке системы управления производственными цехами для Газпром нефтехим Салават.

# Модули
+ [__База данных__](#база-данных)
+ [__Аутентификация, авторизация__](#аутентификация-авторизация)
+ [__Модуль управления подразделением__](#модуль-управления-подразделением)
+ [__Модуль табеля учета рабочего времени__](#модуль-табеля-учета-рабочего-времени)
+ [__Модуль обучения__](#модуль-обучения)
+ [__Модуль инструктажей__](#модуль-инструктажей )
+ [__Модуль оборудования__](#модуль-оборудования)
+ [__Модуль плановых производственных работ__](#модуль-плановых-производственных-работ)

## База данных
На диаграммах прямоугольниками представлены таблицы, которые определены в прочих разделах базы данных.
## Пользователи
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

employees ||--|| users : "один пользователь -> один сотрудник"
admin_category ||--o| users : "один пользователя -> ноль или одна категория одминистраторов"
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
## Табель сверхурочной работы
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

## Табель работ в выходной день
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
## Аутентификация, авторизация
Доступ к системе осуществляется по логину и пароль. Данные хранятся в БД в таблице __users__. Таблица __users__ также хранить __employee_id__ и права доступа __permissions__.

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

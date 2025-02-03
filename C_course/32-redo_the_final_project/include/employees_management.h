#ifndef EMPLOYEES_MANAGEMENT_H
#define EMPLOYEES_MANAGEMENT_H

#include <string.h>
#include "database_file_management.h"
#include "common.h"
#include "employees.h"  

int add_new_employee_to_database_file(struct database_header *db_header , struct employees *db_employees , char *newemploye);

#endif 
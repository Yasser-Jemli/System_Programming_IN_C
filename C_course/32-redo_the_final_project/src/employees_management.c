#include "employees_management.h"


int add_new_employee_to_database_file(struct database_header *db_header , struct employees *db_employees , char *newemploye){
    char *saveptr; 

    char *firstname = strtok_r(newemploye , "," , &saveptr);
    char *lastname = strtok_r(NULL , "," , &saveptr);
    char *id = strtok_r(NULL , "," , &saveptr);
    char *required_hours = strtok_r(NULL , "," , &saveptr);
    char *job_title = strtok_r(NULL , "," , &saveptr);

    // printf("The New Employee to be added is : %s %s with ID : %d , the required hours : %d , the job title : %s", firstname ,lastname , id , required_hours , job_title);

    strncpy(db_employees[db_header->employee_count-1].firstname, firstname, sizeof(db_employees[db_header->employee_count-1].firstname));
    strncpy(db_employees[db_header->employee_count-1].lastname, lastname, sizeof(db_employees[db_header->employee_count-1].lastname));
    db_employees[db_header->employee_count-1].id = atoi(id) ;
    db_employees[db_header->employee_count-1].required_hours = atoi(required_hours);
    strncpy(db_employees[db_header->employee_count-1].job_title, job_title, sizeof(db_employees[db_header->employee_count-1].job_title));

    printf("Employees Firstname is : %s \n" , db_employees->firstname);
    printf("Employees Lastname is : %s \n" , db_employees->lastname);
    printf("Employees id is : %d \n" , db_employees->id);
    printf("Employees required hours is : %d \n" , db_employees->required_hours);
    printf("Employees job title is : %s \n" , db_employees->job_title);
    return STATUS_SUCCESS ;


}

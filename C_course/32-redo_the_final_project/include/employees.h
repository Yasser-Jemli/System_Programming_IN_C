#ifndef EMPLOYEES_H
#define EMPLOYEES_H

struct employees {
    char firstname[256];
    char lastname[256];
    unsigned int id;
    unsigned int required_hours;
    char job_title[256];
};

#endif // EMPLOYEES_H
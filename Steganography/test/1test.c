#include <stdio.h>

typedef struct 
{
    int id;
    char name[20];
    float salary;
}Employee;




int main()
{
    Employee emp = {1, "Alice", 5000.0};
    FILE *file;
    file = fopen("employee.txt", "wb");
    if(file == NULL)
    {
        perror("Erro opening file\n");
        return 1;
    }
    fwrite(&emp, sizeof(emp), 1,file );
    fclose(file);
    Employee emp_read;
    file = fopen("employee.txt", "rb");
    if(file == NULL)
    {
        perror("Failed to open file\n");
        return 1;
    }
    fread(&emp_read, sizeof(emp), 1, file);
    fclose(file);
    printf("ID: %d, Name: %s, Salary %0.2f\n", emp_read.id, emp_read.name, emp_read.salary);
    return 0;
}
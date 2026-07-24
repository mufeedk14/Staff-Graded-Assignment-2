#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct{
    int id;
    char name[50];
    float salary;
} Employee;

int main(){
    {
        /* open() is the system call needed to open a file to perform operations, the command is responsible for assigning a file descriptor
        it returns a file descriptor which is assigned to variable fd. Open converts file path into file descriptor and assigns permissions*/

        int fd = open("employee.txt",O_RDWR | O_CREAT | O_TRUNC, 0644);

        if (fd == -1)
        {
            perror("Failed to open/create file");
            exit(1);
        }
        Employee e1 = {1, "Joestar", 1000};
        Employee e2 = {2, "Dio", 2000};
        Employee e3 = {3, "Light", 3000};


        /* write() was used to write information stored in a buffer of memory which was records e1,e2 and e3 here*/

        //writing initial records
        write(fd, &e1, sizeof(Employee));
        write(fd, &e2, sizeof(Employee));
        write(fd, &e3, sizeof(Employee));

        //Changing second employee details
        Employee new_details = {2, "Diego",5000};
        lseek(fd, 1 * sizeof(Employee), SEEK_SET);
        write(fd, &new_details, sizeof(Employee));

        /*the lseek() system call is used to reposition the read/write pointer within the file*/

        //getting details of third employee
        Employee buffer;
        lseek(fd, 2 * sizeof(Employee), SEEK_SET);
        read(fd, &buffer, sizeof(Employee));
        printf("Record 3: %d %s %.2f\n", buffer.id, buffer.name, buffer.salary);

        /*the read() system call was used to read bytes from the file, starting from the pointer location until size of Employee struct, ensuring it reads the entire record and puts it in buffer*/

        /* close(), closes the file according to given file descriptor and releases resources*/
        close(fd);
        return 0;

    }

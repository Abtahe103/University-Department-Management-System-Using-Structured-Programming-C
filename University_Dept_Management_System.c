#include<stdio.h>
#include<string.h>

char admin_id[50];
char teacher_id[50];
char student_id[50];

typedef struct admin
{
    char id[50];
    char pass[50];

}admin;

typedef struct teacher
{
    char id[50];
    char pass[50];
    char course[500];
}teacher;

typedef struct student
{
    char id[50];
    char pass[50];
    char student_name[50];
    char course_name[50];
    char course_mark[50];
}student;

int admin_login()
{
    admin a;
    printf("Admin user id : ");
    scanf("%s",a.id);

    printf("Admin password : ");
    scanf("%s",a.pass);

    FILE *fp;

    admin a1;

    fp = fopen("admin_password.txt","r");

    if(fp == NULL)
    {
        fp = fopen("admin_password.txt","w");
        fwrite(&a,sizeof(admin),1,fp);
        fclose(fp);
        fp = fopen("admin_password.txt","r");

    }
    int check = 0;
    fread(&a1,sizeof(admin),1,fp);
    if(strcmp(a1.id,a.id)==0 && strcmp(a1.pass,a.pass)==0)
    {
        strcpy(admin_id, a.id);
        check = 1;
    }
    fclose(fp);
    return check;
}

int teacher_login()
{
    char filename[50];

    teacher t;
    printf("teacher's user id : ");
    scanf("%s",t.id);

    printf("teacher's password : ");
    scanf("%s",t.pass);

    strcpy(filename,t.id);

    FILE *fp;

    teacher t1;

    fp = fopen(filename,"r");

    int check = 0;
    fread(&t1,sizeof(teacher),1,fp);
    if(strcmp(t1.id,t.id)==0 && strcmp(t1.pass,t.pass)==0)
    {
        strcpy(teacher_id, t.id);
        check = 1;
    }
    fclose(fp);
    return check;
}

int student_login()
{
    char filename[50];
    student s;
    printf("student's Roll : ");
    scanf("%s",s.id);

    printf("student's password : ");
    scanf("%s",s.pass);


    strcpy(filename,s.id);

    FILE *fp;

    student s1;

    fp = fopen(filename,"r");

    int check = 0;
    fread(&s1,sizeof(student),1,fp);
    if(strcmp(s1.id,s.id)==0 && strcmp(s1.pass,s.pass)==0)
    {
        strcpy(student_id, s.id);
        check = 1;
    }
    fclose(fp);
    return check;
}

void add_teacher()
{
	teacher t;
	char filename[50];

	printf("Enter teacher's user id : \n");
	scanf("%s",t.id);
	printf("Enter teacher's password : \n");
	scanf("%s",t.pass);
	strcpy(filename,t.id);

	FILE *fp=fopen(filename,"r");
	if(fp != NULL){
        printf("\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("Teacher with this user id already exists\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        return;
	}

	fp=fopen(filename,"w");
	fwrite(&t,sizeof(teacher),1,fp);
	fclose(fp);
    FILE *list_fp = fopen("teachers_list.txt", "a");
    if (list_fp != NULL) {
        fprintf(list_fp, "%s\n", t.id);
        fclose(list_fp);
    }
    printf("\n");
    printf("****************************\n");
    printf("SUCCESSFULLY ADDED A TEACHER\n");
    printf("****************************\n");
    return ;
}

void add_student()
{
	student s;
	char filename[50];

	printf("Enter student's Roll : \n");
	scanf("%s",s.id);
	printf("Enter student's password : \n");
	scanf("%s",s.pass);
	printf("Student's Full Name: ");
    getchar(); // Consume the newline character left in the input buffer
    fgets(s.student_name, sizeof(s.student_name), stdin);

    // Remove the newline character from the student name if it exists
    size_t len = strlen(s.student_name);
    if (len > 0 && s.student_name[len - 1] == '\n') {
        s.student_name[len - 1] = '\0';
    }


	strcpy(filename,s.id);
	FILE *fp=fopen(filename,"r");
	if(fp != NULL){

        printf("\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("Student with this user id/Roll already exists\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");

        return;
	}

	fp=fopen(filename,"w");
	fwrite(&s,sizeof(student),1,fp);
	fclose(fp);

	FILE *list_fp = fopen("students_list.txt", "a");
    if (list_fp != NULL) {
        fprintf(list_fp, "%s\n", s.id);
        fclose(list_fp);
    }

    printf("\n");
    printf("****************************\n");
    printf("SUCCESSFULLY ADDED A STUDENT\n");
    printf("****************************\n");
    return ;
}

void course_assign() {
    teacher t;
    char filename[50];
    printf("Enter teacher's user id : \n");
    scanf("%s", t.id);
    fflush(stdin);
    // printf("Enter teacher's password : \n");
    // scanf("%s", t.pass);
    fflush(stdin);

    strcpy(filename, t.id);

    teacher t1;
    FILE *fp = fopen(filename, "r");

    fread(&t1, sizeof(teacher), 1, fp);
    fclose(fp);

    if (strcmp(t1.id, t.id) == 0) {
        int x, i;
        char course_name[50];
        strcat(filename, "_courses.txt");
        fp = fopen(filename, "a");
        printf("The number of courses to assign for the teacher: \n");
        scanf("%d", &x);

        getchar();

        for (i = 1; i <= x; i++) {
            printf("Enter name of course #%d: ", i);
            fgets(course_name, sizeof(course_name), stdin);

            size_t len = strlen(course_name);
            if (len > 0 && course_name[len - 1] == '\n') {
                course_name[len - 1] = '\0';
            }

            fprintf(fp, "%s\n", course_name);
        }

        fclose(fp);
        printf("Courses assigned successfully to teacher %s.\n", t.id);
    } else {
        printf("TEACHER NOT FOUND\n");
    }
}


void show_teacher_list() {
    FILE *list_fp = fopen("teachers_list.txt", "r");

    if (list_fp == NULL) {
        printf("Teachers list file not found or empty.\n");
        return;
    }

    printf("List of Teachers:\n");

    char teacher_id[50];
    while (fscanf(list_fp, "%s", teacher_id) != EOF) {
        printf("%s\n", teacher_id);
    }

    fclose(list_fp);
}

void show_student_list() {
    FILE *list_fp = fopen("students_list.txt", "r");

    if (list_fp == NULL) {
        printf("Students list file not found or empty.\n");
        return;
    }

    printf("List of Students:\n");

    char student_id[50];
    while (fscanf(list_fp, "%s", student_id) != EOF) {
        printf("%s\n", student_id);
    }

    fclose(list_fp);
}


void delete_teacher_account() {
    char teacher_id[50];
    printf("Enter the Teacher's User ID to delete: ");
    scanf("%s", teacher_id);

    char filename[50];
    sprintf(filename, "%s", teacher_id);
    if (remove(filename) == 0) {
        printf("Teacher account deleted successfully.\n");
    } else {
        printf("Teacher account not found.\n");
    }

    char course_filename[50];
    sprintf(course_filename, "%s_courses.txt", teacher_id);
    remove(course_filename);

    FILE *list_fp = fopen("teachers_list.txt", "r");
    if (list_fp == NULL) {
        printf("Teachers list file not found or empty.\n");
        return;
    }

    FILE *temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {

        fclose(list_fp);
        return;
    }

    char teacher_line[100];
    while (fgets(teacher_line, sizeof(teacher_line), list_fp)) {
        char current_teacher_id[50];
        sscanf(teacher_line, "%s", current_teacher_id);

        if (strcmp(current_teacher_id, teacher_id) != 0) {
            fprintf(temp_fp, "%s", teacher_line);
        }
    }

    fclose(list_fp);
    fclose(temp_fp);

    remove("teachers_list.txt");
    rename("temp.txt", "teachers_list.txt");

}

void delete_student_account() {
    char student_id[50];
    printf("Enter the Student's User ID to delete: ");
    scanf("%s", student_id);

    char filename[50];
    sprintf(filename, "%s", student_id);
    if (remove(filename) == 0) {
        printf("Student account deleted successfully.\n");
    } else {
        printf("Student account not found.\n");
    }

    FILE *list_fp = fopen("students_list.txt", "r");
    if (list_fp == NULL) {
        printf("Students list file not found or empty.\n");
        return;
    }

    FILE *temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {

        fclose(list_fp);
        return;
    }

    char student_line[100];
    while (fgets(student_line, sizeof(student_line), list_fp)) {
        char current_student_id[50];
        sscanf(student_line, "%s", current_student_id);

        if (strcmp(current_student_id, student_id) != 0) {
            fprintf(temp_fp, "%s", student_line);
        }
    }

    fclose(list_fp);
    fclose(temp_fp);

    remove("students_list.txt");
    rename("temp.txt", "students_list.txt");

}

void provide_marks() {
    char teacher_filename[50];
    sprintf(teacher_filename, "%s", teacher_id);

    FILE *teacher_file = fopen(teacher_filename, "r");

    if (teacher_file == NULL) {
        printf("Teacher with user id %s not found.\n", teacher_id);
        return;
    }

    fclose(teacher_file);

    char course_filename[50];
    sprintf(course_filename, "%s_courses.txt", teacher_id);
    FILE *course_file = fopen(course_filename, "r");

    if (course_file == NULL) {
        printf("No courses assigned to teacher %s.\n", teacher_id);
        return;
    }

    printf("List of Courses Assigned to Teacher %s:\n", teacher_id);
    char course_name[50][50];
    int num_courses = 0;

    while (fgets(course_name[num_courses], sizeof(course_name[num_courses]), course_file) != NULL) {
        printf("%s", course_name[num_courses]);
        num_courses++;
    }

    fclose(course_file);

    char student_roll[50];
    printf("\nEnter student's user id to assign marks: ");
    scanf("%s", student_roll);

    char student_filename[50];
    sprintf(student_filename, "%s", student_roll);
    FILE *student_file = fopen(student_filename, "r");

    if (student_file == NULL) {
        printf("Student with id %s not found.\n", student_roll);
        return;
    }

    fclose(student_file);

    printf("Enter the course for which you want to assign marks : ");
    char selected_course[100];
    scanf(" %[^\n]s", selected_course); // Read the entire line including spaces

    char course_marks_filename[50];
    sprintf(course_marks_filename, "%s_%s_marks.txt", selected_course, student_roll);
    FILE *marks_file = fopen(course_marks_filename, "w");

    if (marks_file == NULL) {
        printf("Error opening marks file.\n");
        return;
    }



    float marks;
    printf("Enter marks for %s in %s: ", student_roll, selected_course);
    scanf("%f", &marks);
    fprintf(marks_file, "%s %f\n", student_roll, marks);
    fclose(marks_file);

    char course_marks_filename2[50];
    sprintf(course_marks_filename2, "%s_marks.txt", selected_course);
    FILE *marks_file2 = fopen(course_marks_filename2, "a");

    if (marks_file2 == NULL) {
        printf("Error opening marks file.\n");
        return;
    }
    fprintf(marks_file2, "%s %f\n", student_roll, marks);
    fclose(marks_file2);
    printf("Marks assigned successfully for %s in %s.\n", student_roll, selected_course);
}

void all_student_marks() {
    char teacher_filename[50];
    sprintf(teacher_filename, "%s", teacher_id);

    FILE *teacher_file = fopen(teacher_filename, "r");

    if (teacher_file == NULL) {
        printf("Teacher with user id %s not found.\n", teacher_id);
        return;
    }

    fclose(teacher_file);

    char course_filename[50];
    sprintf(course_filename, "%s_courses.txt", teacher_id);
    FILE *course_file = fopen(course_filename, "r");

    if (course_file == NULL) {
        printf("No courses assigned to teacher %s.\n", teacher_id);
        return;
    }

    printf("List of Courses Assigned to Teacher %s:\n", teacher_id);
    char course_name[50][50];
    int num_courses = 0;

    while (fgets(course_name[num_courses], sizeof(course_name[num_courses]), course_file) != NULL) {
        printf("%s", course_name[num_courses]);
        num_courses++;
    }

    fclose(course_file);

    char selected_course[100];
    printf("\nEnter the course for which you want to see all student marks: ");
    scanf(" %[^\n]s", selected_course);

    char course_marks_filename[50];
    sprintf(course_marks_filename, "%s_marks.txt", selected_course);
    FILE *marks_file = fopen(course_marks_filename, "r");

    if (marks_file == NULL) {
        printf("No marks found for course %s.\n", selected_course);
        return;
    }

    printf("Student Marks for %s:\n", selected_course);
    char student_roll[50];
    float marks;

    while (fscanf(marks_file, "%s %f", student_roll, &marks) != EOF) {
        printf("Student ID: %s, Marks: %.2f\n", student_roll, marks);
    }

    fclose(marks_file);
}





void check_marks() {

    char student_filename[50];
    sprintf(student_filename, "%s", student_id);
    FILE *student_file = fopen(student_filename, "r");

    if (student_file == NULL) {
        printf("Student with id %s not found.\n", student_id);
        return;
    }

    fclose(student_file);

    printf("Enter the course for which you want to check marks : ");
    char selected_course[100];
    scanf(" %[^\n]s", selected_course);

    char course_marks_filename[50];
    sprintf(course_marks_filename, "%s_%s_marks.txt", selected_course, student_id);
    FILE *marks_file = fopen(course_marks_filename, "r");

    if (marks_file == NULL) {
        printf("Marks for %s in %s not found.\n", student_id, selected_course);
        return;
    }

    printf("Marks for %s in %s:\n", student_id, selected_course);

    char course[50];
    float marks;

    while (fscanf(marks_file, "%s %f", course, &marks) != EOF) {
        printf("%s: %.2f\n", course, marks);
    }

    fclose(marks_file);
}



void find_student() {
    char student_id[50];
    printf("Enter the Student's User ID to find: ");
    scanf("%s", student_id);

    char student_filename[50];
    sprintf(student_filename, "%s", student_id);
    FILE *student_file = fopen(student_filename, "r");

    if (student_file == NULL) {
        printf("Student with User ID %s not found.\n", student_id);
        return;
    }

    student s;
    fread(&s, sizeof(student), 1, student_file);
    fclose(student_file);

    printf("Student Name: %s\n", s.student_name);
    printf("Student Roll: %s\n", s.id);
}





void admin_panel()
{

    if(admin_login())
    {
        printf("\n\n");
        printf("                    **********************\n");
        printf("        ||||||||    WELCOME TO ADMIN PANEL   ||||||||\n");
        printf("                    **********************\n");
    }
    else
    {
        printf("\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("WRONG USER ID OR PASSWORD\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        return ;
    }
    while(1)
    {
        int x;
        printf("\n\n");
        printf("TO ADD A TEACHER PLEASE ENTER (1)\n");
        printf("TO ADD A STUDENT PLEASE ENTER (2)\n");
        printf("TO ASSIGN COURSES TO A TEACHER PLEASE ENTER (3)\n");
        printf("TO SEE TEACHER'S LIST ENTER (4)\n");
        printf("TO DELETE TEACHER'S ACCOUNT ENTER (5)\n");
        printf("TO SEE STUDENT'S LIST ENTER (6)\n");
        printf("TO DELETE STUDENT'S ACCOUNT ENTER (7)\n");

        printf("TO EXIT ADMIN PANEL PLEASE ENTER(0)\n");

        scanf("%d",&x);
        if(x == 1)
            add_teacher();
        else if(x == 2)
            add_student();
        else if(x == 3)
            course_assign();
        else if(x == 4)
            show_teacher_list();
        else if(x == 5)
            delete_teacher_account();
        else if(x == 6)
            show_student_list();
        else if(x == 7)
            delete_student_account();
        else
        {
            printf("EXITING ADMIN PANEL\n");
            return;
        }
    }

}

void teacher_panel()
{
    if(teacher_login())
    {
        printf("\n\n");
        printf("                    ************************\n");
        printf("       ||||||||     WELCOME TO TEACHER PANEL     ||||||||\n");
        printf("                    ************************\n");
    }
    else
    {
        printf("\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("WRONG USER ID OR PASSWORD\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        return ;
    }
    while(1)
    {
        int x;
        printf("\n\n");
        printf("TO PROVIDE CLASS TEST MARKS PLEASE ENTER (1)\n");
        printf("TO FIND A STUDENT PLEASE ENTER (2)\n");
        printf("TO SEE THE MARKS OF ALL THE STUDENTS FOR A COURSE ENTER (3)\n");
        printf("TO EXIT TEACHER PANEL PLEASE ENTER (0)\n");
        scanf("%d",&x);
        if(x == 1)
            provide_marks();
        else if(x == 2)
            find_student();
        else if(x == 3)
            all_student_marks();
        else
        {
            printf("EXITING TEACHER PANEL\n");
            return;
        }
    }
}

void student_panel()
{
    if(student_login())
    {
        printf("\n\n");
        printf("                    ************************\n");
        printf("                    WELCOME TO STUDENT PANEL\n");
        printf("                    ************************\n");
    }
    else
    {
        printf("\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("WRONG USER ID OR PASSWORD\n");
        printf("xxxxxxxxxxxxxxxxxxxxxxxxx\n");
        return ;
    }
    while(1)
    {
        int x;
        printf("\n\n");
        printf("TO CHECK YOUR CLASS TEST MARKS PLEASE ENTER (1)\n");
        printf("TO EXIT STUDENT PANEL PRESS PLEASE ENTER (0)\n");
        scanf("%d",&x);
        fflush(stdin);
        if(x == 1)
            check_marks();
        else{
            printf("EXITING STUDENT PANEL\n");
            return;

        }

    }

}

int main()
{
	int x;
	while(1)
	{
	    printf("\n\n");
	    printf("   _____________________********************_____________________*********************_________________________\n");
        printf("                        ********************                     *********************\n");
        printf("\n\n");
		printf("\TO LOGIN AS AN ADMIN PLEASE ENTER (1) \nTO LOGIN AS A TEACHER PLEASE ENTER (2)\nTO LOGIN AS A STUDENT PLEASE ENTER (3)\nOr enter 0 to exit:\n");
        scanf("%d",&x);
        if(x==1) admin_panel();
        else if(x == 2) teacher_panel();
        else if(x == 3) student_panel();

	}
	return 0;
}


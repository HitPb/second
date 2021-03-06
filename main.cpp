#include "pch.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <Windows.h>
//1
#define MAX_SIZE 20

struct user
{
	char* fio;
	char* birthdate;
	char* worktime;
	int id;
	char* sex;
	char* pos;
};

enum field
{
	fio, birthdate, worktime, sex, pos
};

char* amountoftimes();
char* checkField();
int checkoutB();
void swap(user* &s1, user* &s2);
void sort(user* users, int field, int size, FILE* file);
struct user* delete_struct(user* users, int size, FILE* file);
void joinuser(user* user);
int structSize(int check);
int readStruct(user* users, int check, int size);
void printToFile(FILE* file, user* users, int size);
void clearuserdata(user** users, int size);
int printMenu();



int main()
{
	FILE* file = fopen("data.txt", "w");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	user *users = NULL;
	int size = 0;
	int inData = 0;
	int check = 0;
	int menuObj = 0;
	char ch = '\0';
	bool f = false;

	do
	{
		menuObj = printMenu();
		switch (menuObj)
		{
		case 1:
		{
			check = checkoutB();
			size = structSize(check);

			size = size <= MAX_SIZE ? size : MAX_SIZE;
			users = (user*)malloc(size * sizeof(user));

			readStruct(users, check, size);
			inData = 1;
		}
		break;
		case 2:
		{
			if (inData == 0)
			{
				printf("Error 404\n");
				continue;
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					joinuser(&users[i]);
				}
			}
			break;
		}
		case 3:
		{
			if (inData == 0)
			{
				printf("Error 404\n");
				continue;
			}
			else
			{
				char* whatField = checkField();
				if (strcmp(whatField, "fio") == 0)
				{
					sort(users, fio, size, file);
				}
				else if (strcmp(whatField, "birthdate") == 0)
				{
					sort(users, birthdate, size, file);
				}
				else if (strcmp(whatField, "worktime") == 0)
				{
					sort(users, worktime, size, file);
				}
				else if (strcmp(whatField, "sex") == 0)
				{
					sort(users, sex, size, file);
				}
				else if (strcmp(whatField, "pos") == 0)
				{
					sort(users, pos, size, file);
				}
			}
			break;
		}
		case 4:
		{
			if (inData == 0)
			{
				printf("Error 404\n");
				continue;
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					joinuser(&users[i]);
				}
			}

			delete_struct(users, size, file);
		}
		break;
		case 5:
		{
			if (inData == 0)
			{
				printf("Error 404\n");
				continue;
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					printToFile(file, &users[i], size);
				}
			}
			break;
		}
			clearuserdata(&users, size);
			_getch();
		}
	} while (menuObj != 6);
	return 0;
}

void swap(user* &s1, user* &s2)
{
	user* tmpUser = s1;
	s1 = s2;
	s2 = tmpUser;
}

void sort(user* users, int field, int size, FILE* file)
{
	user** sort_str = NULL;
	sort_str = new user*[size];
	for (int i = 0; i < size; i++)
	{
		sort_str[i] = &users[i];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = size - 2; j >= i; j--)
		{
			if (field == fio)
			{
				if ((strcmp(sort_str[j]->fio, sort_str[j + 1]->fio)) > 0)
				{
					swap(sort_str[j], sort_str[j + 1]);
				}
			}
			if (field == sex)
			{
				if ((strcmp(sort_str[j]->sex, sort_str[j + 1]->sex)) > 0)
				{
					swap(sort_str[j], sort_str[j + 1]);
				}
			}
			if (field == pos)
			{
				if ((strcmp(sort_str[j]->pos, sort_str[j + 1]->pos)) > 0)
				{
					swap(sort_str[j], sort_str[j + 1]);
				}
			}
			if (field == birthdate)
			{
				if ((atoi(sort_str[j]->birthdate)) > (atoi(sort_str[j + 1]->birthdate)))
				{
					swap(sort_str[j], sort_str[j + 1]);
				}
			}
			if (field == worktime)
			{
				if ((atoi(sort_str[j]->worktime)) > (atoi(sort_str[j + 1]->worktime)))
				{
					swap(sort_str[j], sort_str[j + 1]);
				}
			}
		}
	}

	if (field == fio)
	{
		fprintf(file, "Отсортировано по полю fio(фамилии)\n");
	}
	if (field == sex)
	{
		fprintf(file, "Отсортировано по полю sex(полу)\n");
	}
	if (field == pos)
	{
		fprintf(file, "Отсортировано по полю pos(статусу пенсии)\n");
	}
	if (field == birthdate)
	{
		fprintf(file, "Отсортировано по полю birthdate(году рождения)\n");
	}
	if (field == worktime)
	{
		fprintf(file, "Отсортировано по полю worktime(стажу работы)\n");
	}

	for (int i = 0; i < size; i++)
	{
		printf("{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
			sort_str[i]->id, sort_str[i]->fio, sort_str[i]->birthdate, sort_str[i]->worktime, sort_str[i]->sex, sort_str[i]->pos);
		fprintf(file, "{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
			sort_str[i]->id, sort_str[i]->fio, sort_str[i]->birthdate, sort_str[i]->worktime, sort_str[i]->sex, sort_str[i]->pos);
	}
}

struct user* delete_struct(user* users, int size, FILE* file)
{
	char c = '\n';
	int checkout = 0;
	int del = 0;
	int leap = 0;

	user *del_str = NULL;
	del_str = new user[size];

	for (int i = 0; i < size; i++)
	{
		del_str[i] = users[i];
	}

	printf("Введите ID структуры, которую необходимо удалить: ");
	do
	{
		while (scanf_s("%d%c", &del, &c) != 2 || c != '\n')
		{
			printf("Введите корректый ID, подлежащий удалению: ");
			while (getchar() != '\n');
		}
		if (del < 0 || del > size - 1)
		{
			printf("Введите корректый ID, подлежащий удалению: ");
		}
		else
		{
			checkout = 1;
		}
	} while (checkout != 1);

	for (int i = 0; i < size; i++)
	{
		if (i == del)
			leap += 1;
		if (leap == 1)
		{
			del_str[i] = users[i + 1];
		}
		else
		{
			del_str[i] = users[i];
		}
	}

	fprintf(file, "Удален %d ID\n", del);

	for (int i = 0; i < size - 1; i++)
	{
		printf("{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
			del_str[i].id, del_str[i].fio, del_str[i].birthdate, del_str[i].worktime, del_str[i].sex, del_str[i].pos);
		fprintf(file, "{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
			del_str[i].id, del_str[i].fio, del_str[i].birthdate, del_str[i].worktime, del_str[i].sex, del_str[i].pos);
	}
	return del_str;
}

void joinuser(user *user)
{
	printf("{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
		user->id, user->fio, user->birthdate, user->worktime, user->sex, user->pos);
}

int structSize(int check)
{
	int size = 0;
	if (check == 1)
	{
		char c = '\n';
		int checkout = 0;
		printf("Введите количество сотрудников: ");
		do
		{
			while (scanf_s("%d%c", &size, &c) != 2 || c != '\n')
			{
				printf("Введите корректное значение кол-ва сотрудников: ");
				while (getchar() != '\n');
			}
			if (size > 0)
			{
				checkout = 1;
			}
			else
			{
				printf("Введите корректное значение кол-ва сотрудников: ");
			}
		} while (checkout != 1);
	}
	else
	{
		FILE *in;
		in = fopen("workers.txt", "r");
		fscanf(in, "%d", &size);
	}
	return size;
}

char* amountoftimes()
{
	char c[2];
	bool flag = false;
	printf("Повторить?(Y/N): ");
	do
	{
		scanf("%s", c);
		if ((strcmp(c, "Y") == 0) || (strcmp(c, "N") == 0))
		{
			flag = true;
		}
		else
		{
			printf("Вы не дали ответ. Попробуйте ещё: ");
		}

	} while (flag == false);
	return c;
}

int readStruct(user* users, int check, int size)
{
	int checkout = 0;
	char c = '\n';
	char buffer[128];
	if (check == 1)
	{
		for (int i = 0; i < size; i++)
		{
			printf("Cотрудник #%d\nФИО: ", i + 1);
			scanf("%s", buffer);
			users[i].id = i;
			users[i].fio = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].fio, buffer);
			int bday = 0;
			printf("Год рождения: ");
			do
			{
				scanf("%s", buffer);
				bday = atoi(buffer);
				if (bday == 0 || bday > 2017 || bday < 1910)
				{
					printf("Невереный год! Введите снова: ");
				}
			} while (bday == 0 || bday > 2017 || bday < 1910);
			users[i].birthdate = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].birthdate, buffer);
			int yearsofwork = 0;
			printf("Стаж работы: ");
			do
			{
				scanf("%s", buffer);
				yearsofwork = atoi(buffer);
				if (yearsofwork > (2018 - bday))
				{
					printf("Вы ввели стаж, превышающий жизнь человека. Попробуйте снова: ");
				}
				else if (yearsofwork == 0 || yearsofwork < 1)
				{
					printf("Неверный стаж работы! Введите снова: ");
				}
			} while (yearsofwork == 0 || yearsofwork < 1 || yearsofwork >(2018 - bday));
			users[i].worktime = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].worktime, buffer);
			bool flag = false;
			printf("Пол сотрудника(м/ж): ");
			do
			{
				scanf("%s", buffer);
				if ((buffer[0] == 'м') || (buffer[0] == 'ж'))
				{
					users[i].sex = (char*)malloc(strlen(buffer) + 1);
					strcpy(users[i].sex, buffer);
					flag = true;
				}
				else
				{
					printf("Введите корректный пол работника: ");
				}
			} while (flag != true);
			if (users[i].sex[0] == 'м')
			{
				if ((2018 - atoi(users[i].birthdate)) >= 65)
				{
					users[i].pos = _strdup("Да");
				}
				else
				{
					users[i].pos = _strdup("Нет");
				}
			}
			if (users[i].sex[0] == 'ж')
			{
				if ((2018 - atoi(users[i].birthdate)) >= 60)
				{
					users[i].pos = _strdup("Да");
				}
				else
				{
					users[i].pos = _strdup("Нет");
				}
			}
		}
	}
	else if (check == 2)
	{
		FILE *in;
		in = fopen("workers.txt", "r");
		fseek(in, 4, SEEK_SET);
		for (int i = 0; i < size; i++)
		{
			fscanf(in, "%s", &buffer);
			users[i].id = i;
			users[i].fio = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].fio, buffer);
			fscanf(in, "%s", &buffer);
			users[i].birthdate = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].birthdate, buffer);
			fscanf(in, "%s", &buffer);
			users[i].worktime = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].worktime, buffer);
			fscanf(in, "%s", &buffer);
			users[i].sex = (char*)malloc(strlen(buffer) + 1);
			strcpy(users[i].sex, buffer);
			if (users[i].sex[0] == 'м')
			{
				if ((2018 - atoi(users[i].birthdate)) >= 65)
				{
					users[i].pos = _strdup("Да");
				}
				else
				{
					users[i].pos = _strdup("Нет");
				}
			}
			if (users[i].sex[0] == 'ж')
			{
				if ((2018 - atoi(users[i].birthdate)) >= 60)
				{
					users[i].pos = _strdup("Да");
				}
				else
				{
					users[i].pos = _strdup("Нет");
				}
			}
		}
		fclose(in);
	}
	return size;
}

char* checkField()
{
	char check[10];
	bool flag = false;
	printf("Наименования полей - fio(ФИО лица), birthdate(год рождения), worktime(стаж работы), sex(пол), pos(по статусу пенсии)\n");
	printf("Введите поле, по которому нужно отсортировать: ");
	do
	{
		scanf("%s", check);
		if ((strcmp(check, "fio") == 0) || (strcmp(check, "birthdate") == 0) || (strcmp(check, "worktime") == 0) || (strcmp(check, "sex") == 0) || (strcmp(check, "pos") == 0))
		{
			flag = true;
		}
		else
		{
			printf("Введите корректное поле: ");
		}
	} while (flag == false);
	return check;
}

void printToFile(FILE* file, user* users, int size)
{
	fprintf(file, "{id: %d, ФИО: \"%s\", Год рождения: \"%s\", Стаж работы: \"%s\", Пол: \"%s\", Пенсия по возрасту: \"%s\"}\n",
		users->id, users->fio, users->birthdate, users->worktime, users->sex, users->pos);
}

void clearuserdata(user** users, int size)
{
	for (int i = 0; i < size; i++)
	{
		free((*users)[i].fio);
		free((*users)[i].birthdate);
		free((*users)[i].pos);
		free((*users)[i].worktime);
		free((*users)[i].sex);
	}
	free(*users);
}

int checkoutB()
{
	printf("Выберите способ заполнения структуры (1 - с клавиатуры, 2 - с файла): ");
	int checkout = 0;
	int type = 0;
	char c = '\n';
	do
	{
		while (scanf_s("%d%c", &type, &c) != 2 || c != '\n')
		{
			printf("Введите корректное решение о заполнении: ");
			while (getchar() != '\n');
		}
		if (type > 0 && type < 3)
		{
			checkout = 1;
		}
		else
		{
			printf("Введите корректное решение о заполнении: ");
		}
	} while (checkout != 1);
	return type;
}

int printMenu()
{
	char c = '\n';
	int checkout = 0;
	int menuObj = 0;
	printf("[1] - Ввод данных\n");
	printf("[2] - Вывод данных\n");
	printf("[3] - Сортировка данных\n");
	printf("[4] - Удаление данных\n");
	printf("[5] - Запись данных в файл\n");
	printf("[6] - Завершение работы\n");
	printf("К чему нужно приступить? - ");
	do
	{
		while (scanf_s("%d%c", &menuObj, &c) != 2 || c != '\n')
		{
			printf("Выберите из предложенного: ");
			while (getchar() != '\n');
		}
		if (menuObj > 0 || menuObj < 7)
		{
			checkout = 1;
		}
		else
		{
			printf("Выберите из предложенного: ");
		}
	} while (checkout != 1);
	return menuObj;
}

/*Данная программа проверяет
базовые знания пользователя по
языку Си.
Основные функции:
	- решение задач;
	- просмотр статистики;
	- удаление статистики

Цель пользователя - сформировать статистику
Чтобы сформировать статистику нужно пройти
все вопросы

Благодаря шифрованию файла статистики(базы данных)
ее затруднительно подделать

Статистика также имеет ключ подтверждения
имеея данные пользователя можно проверить
подлинность его статистики через
спец. программу
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#include "tasks.h"
#include "stats.h"


int main(void)
{
	//для русских букв
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
	
	srand(time(NULL));
	
	
	// Главное меню
	int count;//!
	int menu_choice = 0;
	bool flag_update = false;
	
	
	/*переменные, хранящие
	данные пользователя в программе*/
	int q_all = get_q_all();
	int all_balls = q_all * 5;
	char nick_name[10];
	int count_true = 0;
	int count_balls = 0;
	int q_pos = 0;
	int r1, r2;
	while (menu_choice != 4) {		
		//создание статистики(если не создана)
		if (stats_was_created() == false) {
			r1 = (rand() % 20) + 1; //[1; 20]
			r2 = (rand() % 50) + 1; //[1; 50]
			hello(nick_name);
			flag_update = true;
		}
		
		//шифрование, обновление статистики
		if (flag_update == true) {
			encryption_data(&count_true, &count_balls, &q_pos,
							r1, r2);
			if (update_stats(nick_name, count_true, count_balls,
							q_pos, r1, r2) == 1)
				return 1;
		}
		
		//чтение и расшифровка данных из базы
		if (read_data_for_stats(nick_name, &count_true,
			&count_balls, &q_pos, &r1, &r2) == 1)
				return 1;
		decryption_data(&count_true, &count_balls, &q_pos,
							r1, r2);
		
		
		//Выбор действий
		printf("Введите пункт меню:\
		\n(1) Решать задачи по программированию\
		\n(2) Посмотреть статистику\
		\n(3) Удалить статистику\
		\n(4) Выйти\
		\n: ");
		if (scanf("%d", &menu_choice) != 1) {
			puts("Ошибка ввода");
			return 1;
		}
		if (menu_choice <= 0 || menu_choice > 4) {
			puts("Недействительный пункт меню");
			return 0;
		}
		
		
		// (1) Решать задачи по программированию
		if (menu_choice == 1) {
			if (q_pos >= q_all) {
				puts("Вы достигли конца.\
				\nВаша статистика полностью сформирована\n");
				continue;
			}
				
			//решение задач
			if (start_work(&count_true, &count_balls, &q_pos) == 1)
				return 1;
			flag_update = true;
		}
		
		
		// (2) Посмотреть статистику
		else if (menu_choice == 2) {
			printf("\
			\nНикнейм: %s\
			\nДата: %s\
			\nВремя: %s\
			\nПройдеНо вопросов: %d из %d\
			\nПравильных ответов: %d из %d\
			\nБаллы: %d из %d\
			\nКлюч подтверждения статистики: %d\
			\n\n",
			nick_name, "none", "none",
			q_pos, q_all,
			count_true, q_all,
			count_balls, all_balls,
			r1);
		}
		
		// (3) Удалить статистику
		else if (menu_choice == 3) {
			if (delete_stats() == 1)
				return 1;
			flag_update = false;
			count_true = 0;
			count_balls = 0;
			q_pos = 0;
			clean_buffer();
		}
		
	}
	
	return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


enum {max_len_nickname = 10};

const char *answers[] = {"5", "12", "10",
	"90", "105", "1000",
	"aaaa", "robin", "good"};
const char *insert_terms[] = {"3", "10", "8",
	"92", "107", "1002",
	"okey", "value", "win"};


int create_pos_file(void)
{
	FILE *create_file = fopen("position_base.txt", "w");
	if (create_file == NULL)
		return 1;
		
	fprintf(create_file, "%d", -2025);//-2025 = 0 - шифров.значения
	fclose(create_file);
	
	return 0;
}


bool pos_base_was_created(void)
{
	FILE *read_file = fopen("position_base.txt", "r");
	
	if (read_file == NULL)
		return false;
	
	fclose(read_file);
	return true;
}


int get_pos(void)
{
	FILE *read_file = fopen("position_base.txt", "r");
	if (read_file == NULL) {
		printf("Error in get_pos\n");
		return 1;
	}
	
	int pos;
	if (fscanf(read_file, "%d", &pos) != 1)
		return 1;
	fclose(read_file);
	
	return pos;
}


int plus_pos_to_base(void)
{
	int pos = get_pos();
	if (pos == 1)
		return 1;
	
	FILE *write_file = fopen("position_base.txt", "w");
	if (write_file == NULL)
		return 1;
	
	fprintf(write_file, "%d", pos+1);
	fclose(write_file);
	
	return 0;
}


int get_q_all(void)
{
	return sizeof(answers) / sizeof(*answers);
}


void clean_buffer(void)
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) ;
}


void hello(char *nick_name)
{
	int correct_input = 0;
	while (correct_input == 0) {
		printf("Введите свой никнейм\n: ");	
		fgets(nick_name, max_len_nickname, stdin);
		correct_input = 1;
		int len_nickname = strlen(nick_name);
		if (len_nickname <= 3) {
			printf("Никнейм должен быть длинее 2 символов\n");
			correct_input = 0;
			continue;
		}
		if (nick_name[len_nickname-1] == '\n') //short input
			nick_name[--len_nickname] = '\0';
		else //long input
			clean_buffer();
		
		//проверка на латинские символы никнейма
		for (int i = 0; i < len_nickname; i++) {
			char c = nick_name[i];
			if (c >= 'A' && c <= 'Z') {
				puts("Нельзя использовать заглавные символы\
				\nПопробуйте еще раз\n");
				correct_input = 0;
				break;
			}
			if (c < 'a' || c > 'z') {
				puts("Можно использовать только латинские символы (a-z)\
				\nПопробуйте еще раз\n");
				correct_input = 0;
				break;
			}
		}
	}
	printf("Вы зарегистрировали статистику\
 с никнеймом %s\n\n", nick_name);
}


void gen_question(char *question, int *true_answer, int *balls, int q_pos)
{
	(*balls) = 5;
	
	
	//формирование вопроса
	sprintf(question, "Сколько будет 2 + %s\n", insert_terms[q_pos]);
	//формирование вариантов
	int id_list_variant_answers[8];
	int count_append_id_list = 0;
	int number_variant_answers = (rand() % 7) + 2; //[2; 8]
	(*true_answer) = rand() % number_variant_answers; //[0; n_var_ans)
	for (int i = 0; i < number_variant_answers; i++) {
		//формирование правильного варианта
		if (i == *true_answer) {
			char variant_answer_text[15];
			sprintf(variant_answer_text, "(%d) %s\n",
			i+1, answers[q_pos]);
			strcat(question, variant_answer_text);
			count_append_id_list++;
			continue;
		}
		int rand_id = rand() %
		 (sizeof(answers) / sizeof(*answers)); //[0; sizeof(answers))
		bool variant_was_reapeted = false;
		for (int j = 0; j < count_append_id_list; j++) {
			if (rand_id == id_list_variant_answers[j]) {
				variant_was_reapeted = true;
				break;
			}
		}
		if (rand_id == q_pos || variant_was_reapeted == true) {
			i--;
			continue;
		}
		
		char variant_answer_text[15];
		sprintf(variant_answer_text, "(%d) %s\n", i+1, answers[rand_id]);
		strcat(question, variant_answer_text);
		id_list_variant_answers[i] = rand_id;
		count_append_id_list++;
	}
	strcat(question, ": ");
}


int start_work(int *count_true, int *count_balls)
{	
	bool truth_answer_text = false;
	bool go_to_task_menu = false;
	while (1) {
		if (go_to_task_menu) {
			int tasks_menu_choice;
			printf("Ваш ответ %s\n\nВыберите следующее действие\
			\n(1) Перейти на следующий вопрос\
			\n(2) Сохранить прогресс. и выйти в главное меню\
			\n: ",
			(truth_answer_text) ? "верный" : "пока неправильный");
			if (scanf("%d", &tasks_menu_choice) != 1) {
				puts("Ошибка ввода");
				return 1;
			}
			if (tasks_menu_choice <= 0 || tasks_menu_choice > 2) {
				puts("Недействительный пункт меню\n");
				break;
			}
			
			if (tasks_menu_choice == 2)
				break;
		}
		
		
		
		//Основная логика
		int my_answer;
		
		//генерация вопроса
		char question[300];
		int true_answer;
		int balls;
		
		//получение позиции
		int q_pos = get_pos();
		
		//генерация вопроса
		gen_question(question, &true_answer, &balls,
		q_pos+2025);//q_pos-2025  - расшифровка
		printf("%s", question);
		//ввод ответа
		scanf("%d", &my_answer);
		
		//обработка ответа
		truth_answer_text = 0;
		if (my_answer == true_answer+1) {
			(*count_true)++;
			(*count_balls) += balls;
			truth_answer_text = true;
		}
		else {
			truth_answer_text = false;			
		}
		go_to_task_menu = true;
		
		//создание базы позиции вопроса(если не создана)
		if (pos_base_was_created() == false)
			if (create_pos_file() == 1)
				return 1;
		
		//сдвиг позиции
		if (plus_pos_to_base() == 1)
			return 1;
	}
	
	return 0;
}
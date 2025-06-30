#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void encryption_data(int *count_true, int *count_balls, int *q_pos,
int r1, int r2)
{
	*count_true = *count_true - (r1+r2);
	*count_balls = *count_balls - r2*5 + r1 + 10;
	*q_pos = *q_pos - r1*r2 + 70;
}


void decryption_data(int *count_true, int *count_balls, int *q_pos,
int r1, int r2)
{
		*count_true = *count_true + (r1+r2);
		*count_balls = *count_balls + r2*5 - r1 - 10;
		*q_pos = *q_pos + r1*r2 - 70;
}


int read_data_for_stats(const char *nick_name, int *count_true, int *count_balls,
int *q_pos, int *r1, int *r2)
{
	FILE *file_read = fopen("stats_base.txt", "r");
	if (file_read == NULL) {
		if (file_read == NULL)
			return 1;
	}
	
	if (fscanf(file_read, "%s %d %d %d %d %d",
				nick_name, count_true, count_balls, q_pos, r1, r2) != 6)
		return 1;
		
	
	fclose(file_read);
	return 0;
}


bool stats_was_created(void)
{
	FILE *fp = fopen("stats_base.txt", "r");
	
	if (fp == NULL)
		return false;

	fclose(fp);
	return true;	
}


int update_stats(const char *nick_name, int count_true, int count_balls,
int q_pos, int r1, int r2)
{
	FILE *file_write = fopen("stats_base.txt", "w");
	if (file_write == NULL)
		return 1;
	
	fprintf(file_write, "%s %d %d %d %d %d",
	nick_name,
	count_true, count_balls,
	q_pos, r1, r2);
	
	fclose(file_write);
	return 0;
}


int delete_stats(void)
{
	if (stats_was_created() == false) {
		puts("Ошибка удаления. Статистики не существуют.\n");
		return 0;
	}
	
	int del_choice;
	printf("Вы действительно хотите удалить свою статистику?\
	\n(1) Да\
	\n(2) Нет\
	\n: ");
	if (scanf("%d", &del_choice) != 1)
		return 1;
	
	if (del_choice == 1) {
		if (remove("stats_base.txt") != 0) {
			puts("Не удалось удалить");
			return 1;
		}
		
		puts("Вы успешно удалили статистику\n");
	}
	else
		printf("\n");
	
	return 0;
}
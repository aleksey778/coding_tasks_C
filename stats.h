#ifndef HEADER_STATS
#define HEADER_STATS




void encryption_data(int *count_true, int *count_balls, int *q_pos,
int r1, int r2);

void decryption_data(int *count_true, int *count_balls, int *q_pos,
int r1, int r2);

int read_data_for_stats(const char *nick_name, int *count_true, int *count_balls,
int *q_pos, int *r1, int *r2);

int update_stats(const char *nick_name, int count_true, int count_balls,
int q_pos, int r1, int r2);

bool stats_was_created(void);

int delete_stats(void);




#endif
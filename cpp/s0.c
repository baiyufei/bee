/**
 * 四个线程，分别输出ABCD，通过条件变量使他们轮流工作
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int work_id = 0;

struct Job {
  int id;
  pthread_t tid;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
  int time;
  char c;
  struct Job* next;
};

void do_job(struct Job* jp) {
  printf("%c", jp->c);
  jp->time--;
  work_id++;
  if (work_id == 4)
    work_id = 0;
  pthread_mutex_unlock(&jp->mutex);
  pthread_cond_signal(&jp->next->cond);
}


void* job_thread(void *arg) {
  struct Job *jp = (struct Job *) arg;

  while(jp->time > 0) {
    // 达到条件，执行任务，没达到条件，等待达到条件，执行任务
    pthread_mutex_lock(&jp->mutex);
    if (work_id == jp->id) {
      do_job(jp);
    }
    else {
      pthread_cond_wait(&jp->cond, &jp->mutex);
      do_job(jp);
    }
  }

}

int main() {
  struct Job job[4];
  char s[] = "ABCD";

  for (int i = 0; i < 4; i++) {
    job[i].id = i;
    pthread_mutex_init(&(job[i].mutex), NULL);
    pthread_cond_init(&(job[i].cond),NULL);
    job[i].c = s[i];
    job[i].time = 10;
    if (i != 3) {
      job[i].next = &job[i+1];
    }
    else {
      job[i].next = &job[0];
    }
  }
  for (int i = 0; i < 4; i++) {
    pthread_create(&(job[i].tid), NULL, job_thread, &(job[i]));
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(job[i].tid, NULL);
  }

  return 0;
}

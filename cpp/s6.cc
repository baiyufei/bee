#include <pthread.h>
#include <stdio.h>

class Singleton {
  static Singleton* instance;
  static pthread_once_t once_control;

 public:
  static Singleton* getInstance() {
    pthread_once(&once_control, init);
    return instance;
  }

  static void init() {
    instance = new Singleton;
    printf("only run once\n");
  }
};

pthread_once_t Singleton::once_control = PTHREAD_ONCE_INIT;
Singleton* Singleton::instance = NULL;

void* func(void* arg) {
  Singleton::getInstance();
  printf("%ld\n", (long)pthread_self());
  return NULL;
}

int main() {
  pthread_t tid[32];
  for (int i = 0; i < 32; i++) {
    int err;
    err = pthread_create(tid + i, NULL, func, NULL);
    if (err != 0) {
      return 1;
    }
  }
  for (int i = 0; i < 32; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}

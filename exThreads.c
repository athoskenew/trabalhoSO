void *thread_func(void *arg) {
 ptr_thread_arg targ = (ptr_thread_arg) arg;
 int i;

 for(i = targ->idx ; i< (targ->idx + targ->length) ; i++ ) {
  printf("Thread %ld – value %d\n", pthread_self(), i);
 }
}

int main(){
 pthread_t threads[2]; 
 thread_arg arguments[2];

 int i;
 int threadCriada;

 for(i=0; i<2; i++) {
  arguments[i].idx = i * 10;
  arguments[i].length = 10;

  printf("arguments[%d] idx: %d - length: %d \n",i, arguments[i].idx, arguments[i].length);

  threadCriada = pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));

  if(threadCriada){
   perror("Erro ao criar o thread");
            return 1;
  }
 }

 for(i=0; i<2; i++) {
  pthread_join(threads[i], NULL);
 }

}


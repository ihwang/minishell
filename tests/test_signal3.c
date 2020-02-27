// 아래 예제에서는 while() 문을 이용하여 계속 문자열을 출력하면서
// Ctrl-C 로 SIGINT가 발생하면 바로 종료하는 것이 아니라
// 프로그램에서 작성된 함수를 실행한 후에
// 다시 Ctrl-C 키가 눌리면 기존의 방법에 따라
// 프로세스가 종료되는 것을 보여 줍니다.


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void (*old_fun)( int);

void sigint_handler(int signo)
{
	int a;
	a = signo;
   printf( "Ctrl-C 키를 눌루셨죠!!\n");
   printf( "또 누르시면 종료됩니다.\n");
   signal( SIGINT, sigint_handler);   // 또는 signal( SIGINT, SIG_DFL);
}

int main( void)
{
   old_fun = signal( SIGINT, sigint_handler);
   while(1 )
   {
      printf( "forum.falinux.com\n");
      sleep( 1);
   }
}

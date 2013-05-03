#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig)
{
	printf("got sig %d\n", sig);
}

const struct sigaction sigio = {
	.__sigaction_u = {
		.__sa_handler = handler,
	},
};
	

int main(int argc, char *argv[])
{
	printf("hello world\n");
  
	sigaction(SIGIO, &sigio, 0);

	sleep(20);

}

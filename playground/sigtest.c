#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig, struct __siginfo *siginfo, void *sigptr)
{
	printf("got sig %d from %d\n", sig, siginfo->si_pid);
}

const struct sigaction sigio = {
	.__sigaction_u = {
		.__sa_sigaction = handler,
	},
	.sa_flags = SA_SIGINFO,
};
	

int main(int argc, char *argv[])
{
	printf("hello world\n");
  
	sigaction(SIGIO, &sigio, 0);

	sleep(20);

}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <errno.h>

int main (int argc, char *argv[])
{
	struct passwd *p;

	if (argc < 2) {
		fprintf(stderr, "setuser: usage: setuser user prog [args]\n");
		exit(1);
	}

	p = getpwnam(argv[1]);
	if (p == NULL) {
		fprintf(stderr, "setuser: user `%s' not found.\n", argv[1]);
		exit(1);
	}

	if (initgroups(argv[1], p->pw_gid) < 0) {
		fprintf(stderr, "setuser: initgroups() failed: %s\n",
		  strerror(errno));
		exit(1);
	}
	if (setregid(p->pw_gid, p->pw_gid) < 0) {
		fprintf(stderr, "setuser: setregid() failed: %s\n",
		  strerror(errno));
		exit(1);
	}
	if (setreuid(p->pw_uid, p->pw_uid) < 0) {
		fprintf(stderr, "setuser: setreuid() failed: %s\n",
		  strerror(errno));
		exit(1);
	}

	argv += 2;
	execvp(argv[0], argv);
	fprintf(stderr, "setuser: execvp() failed: %s\n",
	  strerror(errno));
	exit(1);
}

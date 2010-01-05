/* vi: set sw=4 ts=4:
 *
 * setsid.c - Run program in a new session ID.
 *
 * Copyright 2006 Rob Landley <rob@landley.net>
 *
 * Not in SUSv3.
 * See http://www.opengroup.org/onlinepubs/009695399/utilities/

USE_SETSID(NEWTOY(setsid, "^<1t", TOYFLAG_USR|TOYFLAG_BIN))

config SETSID
	bool "setsid"
	default y
	help
	  usage: setsid [-t] command [args...]

	  Run process in a new session.

	  -t	Grab tty (become foreground process, receiving keyboard signals)
*/

#include "toys.h"

void setsid_main(void)
{
	while (setsid()<0)
		if (vfork()) _exit(0);
	if (toys.optflags) {
		setpgid(0,0);
		tcsetpgrp(0, getpid());
	}
	xexec(toys.optargs);
}

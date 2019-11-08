/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


#include "os.h"
#include "gateSystem.h"

#ifdef LINUX
/* Termination handler */
void signal_handler(int signum, siginfo_t *sigInfo, void *context) {
  syslog(LOG_INFO, "Shut down signal is %d", signum);
  syslog(LOG_INFO, "Shutting down gate engine service...");
  // clean the system.
  tprintf("gateService ", 255,"shut down signal is %d, sender PID:%d", signum, sigInfo->si_pid);
  gateCleanUpSystem();
  // close the syslog
  syslog(LOG_INFO, "Shut down gate engine service successfully");
  tprintf("gateService ", 255,"gate engine is shut down!");
  closelog();
  exit(EXIT_SUCCESS);
}
#else
void signal_handler(){
}
#endif

int main(int argc, char *argv[]) {

  /* Set termination handler. */
/*
  struct sigaction act;
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = signal_handler;
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGHUP, &act, NULL);
  sigaction(SIGINT, &act, NULL);
*/

  // sigaction(SIGABRT, &act, NULL);

  // Open /var/log/syslog file to record information.
/*  openlog("gate engine:", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1);
  syslog(LOG_INFO, "Starting gate engine service...");*/

  // Initialize the system
  if (gateInitSystem() < 0) {
    /*syslog(LOG_ERR, "Error initialize gate engine system");
    closelog();*/

    gateCleanUpSystem();
    exit(-1);
  }

  gateStartSystem();


}

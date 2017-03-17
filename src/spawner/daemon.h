/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_DAEMON_H_
#define _DAEMON_SPAWNER_DAEMON_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "../exception/permission_denied.h"
#include "spawner.h"

namespace Daemon::Spawner {
    class Daemon : public Spawner
    {
        public:
            Daemon(Executable *e, unsigned int n, char const *name);
            ~Daemon();

            static void terminateFork(int signal);

        protected:
            pid_t divide();
            void runFork();

        private:
            void initDescriptors();
            char const* changeWd();
            static int openLfp();
            void bindSignals();
            static void pushPid(int fd, pid_t pid);

            char const *name;
            char const *cwd;
            static char const *pidFilename;
            char const *wdBase = "/run";
            int lfp;
    };
}

#endif

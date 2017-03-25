/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _SPAWNER_DAEMONSPAWNER_H_
#define _SPAWNER_DAEMONSPAWNER_H_

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "exception/permissionDenied.h"
#include "spawner.h"

namespace Spawner {
    class DaemonSpawner : public Spawner
    {
        public:
            DaemonSpawner(Executable *e, unsigned int n, char const *name);
            ~DaemonSpawner();

        protected:
            pid_t divide();
            void runFork();

        private:
            void initDescriptors();
            char const* changeWd();
            static int openLfp();
            void bindSignals();
            static void pushPid(int fd, pid_t pid);
            static void terminateFork(int signal);

            char const *name;
            char const *cwd;
            static char const *pidFilename;
            char const *wdBase = "/run";
            int lfp;
    };
}

#endif

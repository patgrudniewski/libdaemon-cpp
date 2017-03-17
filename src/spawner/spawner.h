/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_SPAWNER_H_
#define _DAEMON_SPAWNER_SPAWNER_H_

#include <csignal>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <sys/wait.h>
#include <unistd.h>

#include "executable.h"

namespace Daemon::Spawner {
    class Spawner
    {
        public:
            ~Spawner();
        protected:
            Spawner(Executable* e);
            void spawn(unsigned int n);
            void destroy(unsigned int n);
            virtual pid_t divide();
            virtual void runFork();

        private:
            void destroy();
            void reset();

            Executable *executable;
            std::set<pid_t> *pid;
    };
}

#endif

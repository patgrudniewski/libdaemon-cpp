/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_SPAWNER_H_
#define _DAEMON_SPAWNER_SPAWNER_H_

#include <csignal>
#include <cstdlib>
#include <stdexcept>
#include <unistd.h>

#include "executable.h"

namespace Daemon::Spawner {
    class Spawner
    {
        public:
            Spawner(Executable* e);
            void spawn(int n);

        private:
            pid_t divide();

            Executable *executable;
    };
}

#endif

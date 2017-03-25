/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_SPAWNER_H_
#define _DAEMON_SPAWNER_SPAWNER_H_

#include <stdexcept>
#include <unistd.h>

#include "executable.h"

namespace Daemon::Spawner {
    class Spawner
    {
        public:
            virtual ~Spawner();

        protected:
            Spawner(Executable* e);
            void spawn(unsigned int n);
            virtual pid_t divide();
            virtual void runFork();

        private:
            Executable *executable;
    };
}

#endif

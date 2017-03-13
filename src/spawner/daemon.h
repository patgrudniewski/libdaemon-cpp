/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_DAEMON_H_
#define _DAEMON_SPAWNER_DAEMON_H_

#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include "spawner.h"

namespace Daemon::Spawner {
    class Daemon : public Spawner
    {
        public:
            Daemon(Executable *e, unsigned int n);

        protected:
            void initFork();

        private:
            void initDescriptors();
    };
}

#endif

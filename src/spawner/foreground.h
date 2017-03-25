/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_FOREGROUND_H_
#define _DAEMON_SPAWNER_FOREGROUND_H_

#include <csignal>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <sys/wait.h>
#include <unistd.h>

#include "executable.h"
#include "spawner.h"

namespace Daemon::Spawner {
    class Foreground : public Spawner
    {
        public:
            Foreground(Executable* e, unsigned int n);
            ~Foreground();

            void destroy(unsigned int n);

        protected:
            pid_t divide();

        private:
            static std::set<pid_t> pid;

            static void handleChildSignal(int signal);
            void destroy();
            void bindSignals();
            void idle();
    };
}

#endif

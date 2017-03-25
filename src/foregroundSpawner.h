/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _SPAWNER_FOREGROUNDSPAWNER_H_
#define _SPAWNER_FOREGROUNDSPAWNER_H_

#include <csignal>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <sys/wait.h>
#include <unistd.h>

#include "executable.h"
#include "spawner.h"

namespace Spawner {
    class ForegroundSpawner : public Spawner
    {
        public:
            ForegroundSpawner(Executable* e, unsigned int n);
            ~ForegroundSpawner();

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

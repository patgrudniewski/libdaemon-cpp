/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "spawner.h"

using namespace std;

namespace Daemon::Spawner {
    Spawner::Spawner(Executable* e)
        :executable(e)
    {  }

    Spawner::~Spawner()
    {  }

    void Spawner::spawn(unsigned int n)
    {
        for (int i = 0; i < n; i++) {
            this->divide();
        }
    }

    pid_t Spawner::divide()
    {
        pid_t pid;

        pid = fork();
        if (pid < 0) {
            throw runtime_error("Error when forking");
        } else if (pid == 0) {
            this->runFork();

            exit(EXIT_SUCCESS);
        }

        return pid;
    }

    void Spawner::runFork()
    {
        this->executable->run();
    }
}

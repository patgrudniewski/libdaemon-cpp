/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "spawner.h"

using namespace std;

namespace Daemon::Spawner {
    Spawner::Spawner(Executable* e)
        :executable(e)
    {
        this->reset();
    }

    Spawner::~Spawner()
    {
        delete this->pid;
    }

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

        this->pid->insert(pid);

        return pid;
    }

    void Spawner::runFork()
    {
        this->reset();
        this->executable->run();
    }

    void Spawner::destroy(unsigned int n)
    {
        for (int i = 0; i < n; i++) {
            this->destroy();
        }
    }

    void Spawner::destroy()
    {
        pid_t pid;
        set<pid_t>::iterator iterator;

        if (0 == this->pid->size()) {
            throw runtime_error("Forks not found");
        }

        iterator = --(this->pid->end());
        pid = *iterator;

        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);

        this->pid->erase(iterator);
    }

    void Spawner::reset()
    {
        this->pid = new set<pid_t>();
    }
}

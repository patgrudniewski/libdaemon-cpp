/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "foregroundSpawner.h"

using namespace std;

namespace Spawner {
    ForegroundSpawner::ForegroundSpawner(Executable* e, unsigned int n)
        :Spawner(e)
    {
        this->bindSignals();
        this->spawn(n);
        this->idle();
    }

    ForegroundSpawner::~ForegroundSpawner()
    {
        this->destroy(ForegroundSpawner::pid.size());
    }

    pid_t ForegroundSpawner::divide()
    {
        pid_t pid;

        pid = Spawner::divide();
        ForegroundSpawner::pid.insert(pid);

        return pid;
    }

    void ForegroundSpawner::destroy(unsigned int n)
    {
        for (int i = 0; i < n; i++) {
            this->destroy();
        }
    }

    void ForegroundSpawner::destroy()
    {
        pid_t pid;
        set<pid_t>::iterator iterator;

        if (0 == ForegroundSpawner::pid.size()) {
            throw runtime_error("Forks not found");
        }

        iterator = --(ForegroundSpawner::pid.end());
        pid = *iterator;

        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);

        ForegroundSpawner::pid.erase(iterator);
    }

    void ForegroundSpawner::bindSignals()
    {
        signal(SIGCHLD, ForegroundSpawner::handleChildSignal);
    }

    void ForegroundSpawner::idle()
    {
        while (ForegroundSpawner::pid.size()) {
            sleep(1);
        }
    }

    void ForegroundSpawner::handleChildSignal(int signal)
    {
        pid_t pid;
        set<pid_t>::iterator iterator;

        pid = wait(NULL);
        iterator = ForegroundSpawner::pid.find(pid);
        ForegroundSpawner::pid.erase(iterator);
    }

    std::set<pid_t> ForegroundSpawner::pid;
}

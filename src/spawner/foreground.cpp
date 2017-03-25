/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "foreground.h"

using namespace std;

namespace Daemon::Spawner {
    Foreground::Foreground(Executable* e, unsigned int n)
        :Spawner(e)
    {
        this->bindSignals();
        this->spawn(n);
        this->idle();
    }

    Foreground::~Foreground()
    {
        this->destroy(Foreground::pid.size());
    }

    pid_t Foreground::divide()
    {
        pid_t pid;

        pid = Spawner::divide();
        Foreground::pid.insert(pid);

        return pid;
    }

    void Foreground::destroy(unsigned int n)
    {
        for (int i = 0; i < n; i++) {
            this->destroy();
        }
    }

    void Foreground::destroy()
    {
        pid_t pid;
        set<pid_t>::iterator iterator;

        if (0 == Foreground::pid.size()) {
            throw runtime_error("Forks not found");
        }

        iterator = --(Foreground::pid.end());
        pid = *iterator;

        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0);

        Foreground::pid.erase(iterator);
    }

    void Foreground::bindSignals()
    {
        signal(SIGCHLD, Foreground::handleChildSignal);
    }

    void Foreground::idle()
    {
        while (Foreground::pid.size()) {
            sleep(1);
        }
    }

    void Foreground::handleChildSignal(int signal)
    {
        pid_t pid;
        set<pid_t>::iterator iterator;

        pid = wait(NULL);
        iterator = Foreground::pid.find(pid);
        Foreground::pid.erase(iterator);
    }

    std::set<pid_t> Foreground::pid;
}

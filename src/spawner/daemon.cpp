/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "daemon.h"

namespace Daemon::Spawner {
    Daemon::Daemon(Executable *e, unsigned int n)
        :Spawner(e)
    {
        this->spawn(n);

        exit(EXIT_SUCCESS);
    }

    void Daemon::initFork()
    {
        Spawner::initFork();

        this->initDescriptors();
    }

    void Daemon::initDescriptors()
    {
        int fd;

        for (fd = getdtablesize(); fd >= 0; --fd) {
            close(fd);
        }
        fd = open("/dev/null", O_RDWR);
        dup(fd);
        dup(fd);
    }
}

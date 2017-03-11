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
}

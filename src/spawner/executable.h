/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _DAEMON_SPAWNER_EXECUTABLE_H_
#define _DAEMON_SPAWNER_EXECUTABLE_H_

namespace Daemon::Spawner {
    class Executable
    {
        public:
            virtual void run() = 0;
    };
}

#endif

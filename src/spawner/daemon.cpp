/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "daemon.h"

using namespace std;

using namespace Daemon::Exception;

namespace Daemon::Spawner {
    char const* Daemon::pidFilename = "daemon.pid";

    Daemon::Daemon(Executable *e, unsigned int n, char const *name)
        :Spawner(e), name(name)
    {
        if (getuid()) {
            throw PermissionDenied("Daemon can be run only as a root");
        }

        umask(027);
        this->cwd = this->changeWd();
        this->lfp = Daemon::openLfp();

        this->spawn(n);

        exit(EXIT_SUCCESS);
    }

    Daemon::~Daemon()
    {
        close(this->lfp);
    }

    char const* Daemon::changeWd()
    {
        string dirname(this->wdBase);
        struct stat sb;

        dirname
            .append("/")
            .append(this->name)
            .append("/")
            ;

        if (stat(dirname.c_str(), &sb) && !S_ISDIR(sb.st_mode) && -1 == mkdir(dirname.c_str(), 750)) {
            throw runtime_error("Unable to create daemon run directory");
        }

        chdir(dirname.c_str());
        return dirname.c_str();
    }

    int Daemon::openLfp()
    {
        int lfp;

        lfp = open(Daemon::pidFilename, O_RDWR|O_CREAT, 0640);
        if (-1 == lfp) {
            throw runtime_error("Unable to open PID file");
        };

        if (lockf(lfp, F_TLOCK, 0) < 0) {
            throw runtime_error("Unable to lock PID file");
        }

        return lfp;
    }

    pid_t Daemon::divide()
    {
        pid_t pid;

        pid = Spawner::divide();
        Daemon::pushPid(this->lfp, pid);

        return pid;
    }

    void Daemon::runFork()
    {
        this->initDescriptors();
        this->bindSignals();

        Spawner::runFork();
    }

    void Daemon::pushPid(int fd, pid_t pid)
    {
        char buf[10];

        sprintf(buf, "%d\n", pid);
        write(fd, buf, strlen(buf));
    }

    void Daemon::bindSignals()
    {
        signal(SIGTERM, Daemon::terminateFork);
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

    void Daemon::terminateFork(int signal)
    {
        pid_t pid, iBuf;
        vector<pid_t> forks;
        int lfp;
        char cBuf;
        string sBuf;

        lfp = Daemon::openLfp();
        pid = getpid();
        while (read(lfp, &cBuf, 1) > 0) {
            if (0x0A == cBuf) {
                iBuf = atoi(sBuf.c_str());
                if (iBuf > 0 && iBuf != pid) {
                    forks.push_back(iBuf);
                }

                sBuf.clear();
                continue;
            }
            sBuf.append(1, cBuf);
        }

        ftruncate(lfp, 0);
        for (int i = 0; i < forks.size(); ++i) {
            Daemon::pushPid(lfp, forks[i]);
        }

        exit(EXIT_SUCCESS);
    }
}

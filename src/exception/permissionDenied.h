/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#ifndef _SPAWNER_EXCEPTION_PERMISSIONDENIED_H_
#define _SPAWNER_EXCEPTION_PERMISSIONDENIED_H_

#include <stdexcept>
#include <string>

namespace Spawner::Exception {
    class PermissionDenied : private std::runtime_error
    {
        public:
            PermissionDenied(const std::string &what_arg);
            PermissionDenied(const char *what_arg);
    };
}

#endif

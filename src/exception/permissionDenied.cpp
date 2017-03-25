/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "permissionDenied.h"

using namespace std;

namespace Spawner::Exception {
    PermissionDenied::PermissionDenied(const string &what_arg)
        :runtime_error(what_arg)
    {  }

    PermissionDenied::PermissionDenied(const char *what_arg)
        :runtime_error(what_arg)
    {  }
}

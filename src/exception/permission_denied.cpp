/**
 * @author Patryk Grudniewski <patgrudniewski@gmail.com>
 */

#include "permission_denied.h"

using namespace std;

namespace Daemon::Exception {
    PermissionDenied::PermissionDenied(const string &what_arg)
        :runtime_error(what_arg)
    {  }

    PermissionDenied::PermissionDenied(const char *what_arg)
        :runtime_error(what_arg)
    {  }
}

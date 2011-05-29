// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
#ifndef $guard$
#define $guard$

$headers:include(); separator="\n"$
#include "hessian/Connection.h"

namespace $namespace$ {

class $class$: public $interface$
{
protected:
    hessian::Connection& connection_;
    
public:
    $class$ (hessian::Connection& connection):
        connection_(connection)
    { }
    
    $function: declareFunction(); separator="\n"$
};

}//namespace $namespace$
#endif

// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
#ifndef $guard$
#define $guard$

$headers:include(); separator="\n"$
#include "hessian/HessianInputStream.h"
#include "hessian/HessianOutputStream.h"

namespace $namespace$ {

struct $class$
{
    $dataMember: defineDataMember(); separator="\n"$
};

hessian::HessianInputStream& operator>>(hessian::HessianInputStream& in, $class$& object);
hessian::HessianOutputStream& operator<<(hessian::HessianOutputStream& out, const $class$& object);

}//namespace $namespace$
#endif

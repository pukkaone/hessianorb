// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
#ifndef $guard$
#define $guard$

#include "hessian/HessianInputStream.h"
#include "hessian/HessianOutputStream.h"

namespace $namespace$ {

struct $class$
{
    enum Enum
    {
	$enumerator; separator=",\n"$
    };
};

hessian::HessianInputStream& operator>>(hessian::HessianInputStream& in, $class$::Enum& value);
hessian::HessianOutputStream& operator<<(hessian::HessianOutputStream& out, $class$::Enum value);

}//namespace $namespace$
#endif

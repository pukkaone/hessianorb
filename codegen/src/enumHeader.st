// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
#ifndef $guard$
#define $guard$

#include "hessian/HessianInputStream.h"
#include "hessian/HessianOutputStream.h"

namespace $namespace$ {

enum $enum$
{
    $enumerator; separator=",\n"$
};

hessian::HessianInputStream& operator>>(hessian::HessianInputStream& in, $enum$& value);
hessian::HessianOutputStream& operator<<(hessian::HessianOutputStream& out, $enum$ value);

}//namespace $namespace$
#endif

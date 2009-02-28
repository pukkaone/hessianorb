// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
#ifndef $guard$
#define $guard$

$headers:include(); separator="\n"$
#include "hessian/HessianInputStream.h"
#include "hessian/HessianOutputStream.h"

namespace hessian {

inline hessian::HessianInputStream&
operator>> (hessian::HessianInputStream& in, $containerType$& container)
{
    in.beginList();
    container.clear();
    while (in.peek() != 'z') {
        $elementType$ element;
        in >> element;
        container.push_back(element);
    }
    in.endList();
    return in;
}

inline hessian::HessianOutputStream&
operator<< (hessian::HessianOutputStream& out, const $containerType$& container)
{
    out.beginList();
    for ($containerType$::const_iterator p = container.begin(); p != container.end(); ++p) {
        out << *p;
    }
    out.endList();
    return out;
}

}//namespace hessian
#endif

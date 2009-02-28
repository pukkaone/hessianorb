// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
$headers:include(); separator="\n"$

namespace $namespace$ {

$dataMember: defineDataMemberKey(); separator="\n"$

hessian::HessianInputStream&
operator>> (hessian::HessianInputStream& in, $class$& object)
{
    in.beginObject();
    while (in.peek() != 'z') {
        std::string key;
        in >> key;
        
        $dataMember: readDataMember(); separator=" else "$ else {
            in.throwUnknownPropertyException(key);
        }
    }
    in.endObject();
    return in;
}

hessian::HessianOutputStream&
operator<< (hessian::HessianOutputStream& out, const $class$& object)
{
    static char TYPE_NAME[] = "$javaClass$";
    out.beginObject(TYPE_NAME, sizeof(TYPE_NAME) - 1);
    $dataMember: writeDataMember(); separator="\n"$
    out.endObject();
    return out;
}

}//namespace $namespace$

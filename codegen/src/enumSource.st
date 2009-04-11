// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
$headers:include(); separator="\n"$
#include <map>
#include <string>

namespace {

const std::string KEY_NAME("name");

class EnumToNameMap: public std::map<$namespace$::$enum$, std::string>
{
public:
    EnumToNameMap ()
    {
        $enumerator: insertEnumToNameMap(); separator="\n"$
    }
};

EnumToNameMap &
enumToNameMap ()
{
    static EnumToNameMap map;
    return map;
}

class NameToEnumMap: public std::map<std::string, $namespace$::$enum$>
{
public:
    NameToEnumMap ()
    {
        $enumerator: insertNameToEnumMap(); separator="\n"$
    }
};

NameToEnumMap &
nameToEnumMap ()
{
    static NameToEnumMap map;
    return map;
}

}//namespace

namespace $namespace$ {

hessian::HessianInputStream&
operator>> (hessian::HessianInputStream& in, $enum$& value)
{
    in.beginObject();
    while (in.peek() != 'z') {
        std::string key;
        in >> key;

        if (key == KEY_NAME) {
            std::string name;
            in >> name;
            
            value = nameToEnumMap()[name];        
        } else {
            in.throwUnknownPropertyException(key);
        }
    }
    in.endObject();
    return in;
}

hessian::HessianOutputStream&
operator<< (hessian::HessianOutputStream& out, $enum$ value)
{
    static char TYPE_NAME[] = "$javaClass$";
    out.beginObject(TYPE_NAME, sizeof(TYPE_NAME) - 1);
    out << KEY_NAME << enumToNameMap()[value];
    out.endObject();
    return out;
}

}//namespace $namespace$

// THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
$headers:include(); separator="\n"$
#include <map>
#include <string>
#include <vector>

namespace {

const std::string KEY_NAME("name");

class EnumToNameMap: public std::vector<std::string>
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

class NameToEnumMap: public std::map<std::string, $namespace$::$class$::Enum>
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
operator>> (hessian::HessianInputStream& in, $class$::Enum& value)
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
operator<< (hessian::HessianOutputStream& out, $class$::Enum value)
{
    static char TYPE_NAME[] = "$javaClass$";
    out.beginObject(TYPE_NAME, sizeof(TYPE_NAME) - 1);
    out << KEY_NAME << enumToNameMap()[value];
    out.endObject();
    return out;
}

}//namespace $namespace$

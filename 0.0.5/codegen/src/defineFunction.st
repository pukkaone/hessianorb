$it.returnType$
$class$::$it.name$ ($it.parameters; separator=", "$)
{
    static char METHOD_NAME[] = "$it.name$";
    hessian::Call<$it.returnType$ > call(METHOD_NAME, sizeof(METHOD_NAME) - 1);
    $it.parameters: writeParameter(); separator="\n"$
    return call.invoke(connection_);
}

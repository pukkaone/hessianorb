# Java To C++ Mapping #


## Synopsis ##

| **Java Type**    | **Hessian Type** | **C++ Type** |
|:-----------------|:-----------------|:-------------|
|`byte[]`        |binary          |`std::vector<char>`|
|`boolean`       |boolean         |`bool`|
|`char`          |string          |`std::string` containing UTF-8 encoded character|
|`java.util.Date`|date            |`hessian::Date`|
|`double`        |double          |`double`|
|`enum`          |map             |`enum`|
|`int`           |int             |`hessian::Int`|
|`List<`_E_`>`   |list            |`std::vector<`_E_`>`|
|`long`          |long            |`hessian::Long`|
|`Serializable`  |map             |`struct`|
|`String`        |string          |`std::string` containing UTF-8 encoded characters|


## List ##

A Java parameterized list such as `List<`_E_`>` is mapped to a C++ `std::vector<`_E_`>` with the element type mapped from Java to C++.


## Serializable ##

A Java `Serializable` class is mapped to a C++ `struct`.  Each non-transient, non-static field of the `Serializable` class is mapped to a `struct` data member with the same name.


## Enum ##

A Java `enum` is mapped to a C++ `enum` defined inside a class scope.  For example, the Java `enum`
```
enum Season {
    WINTER, SPRING, SUMMER, FALL
}
```
is mapped to the C++ `enum`
```
struct Season {
    enum Enum {
        WINTER, SPRING, SUMMER, FALL
    };
};
```


## Exceptions ##

A remote procedure call may throw these exceptions.

`hessian::ConnectionException`
> An error occurred trying to transfer data across the network.

`hessian::ProtocolException`
> Indicates an error in the received data.  For example, if the status code returned from an HTTP POST indicates an error.

`hessian::MarshallException`
> An error occurred trying to process Hessian formatted data. This is a subclass of `ProtocolException`.

`hessian::Fault`
> The reply from a Hessian service is a fault instead of a normal return value.

All of these exceptions are a subclass of `std::runtime_error`, so you may
catch this exception if you don't what to catch one of the above specific
exceptions.
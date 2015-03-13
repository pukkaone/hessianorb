# Getting Started #

This tutorial shows by example how to build a distributed application with
a Java server and C++ client.


## Define Service Interface ##

Create a Java interface defining the methods your server will implement.
```
package com.example.echo;

public interface EchoService {
    String echoString(String value);
}
```
Use the Java compiler to compile this Java source code.


## Generate Client-Side Proxy ##

Generate C++ code for a client-side proxy.  The proxy implements the service
interface methods by forwarding them to the server.

The command:

> `hessianc -classpath` _path-to-compiled-Java-code_ `echo com.example.echo.EchoService`

specifies
  * the location of the compiled Java code for the service interface,
  * the C++ namespace for the generated C++ code, and
  * one or more Java interfaces.

By default, the command writes the generated C++ files to the current
directory.  Use the options

`-header-dest` _directory_
> to specify the directory where C++ header files are generated.
`-source-dest` _directory_
> to specify the directory where C++ source files are generated.


## Implement Client ##

To connect to the server using HTTP, include the header:
```
#include "hessian/HttpConnection.h"
```

The proxy class is named by appending `Proxy` to the service interface name.
You need to include the header for the generated proxy class:
```
#include "echo/EchoServiceProxy.h"
```

Create a connection to the server:
```
hessian::HttpConnection connection("http://localhost:8888/echo/remoting/EchoService");
```

To perform a remote procedure call to the server, create a proxy instance and call
a member function on the proxy:
```
echo::EchoServiceProxy echoService(connection);

std::string result = echoService.echoString("hello");
```
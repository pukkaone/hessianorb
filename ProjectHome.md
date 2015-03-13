This is a framework to implement a [Hessian](http://hessian.caucho.com/) client in C++.  A code generator
examines type information from a Java interface to generate C++ code which can
call the methods of the interface.  In effect, Java is the interface definition
language for specifying the methods callable by clients.

The steps for building a distributed application with a Java server and C++
client are:

  1. Create a Java interface defining methods to be called by clients.
  1. Write a Java server which implements the Java interface and exposes it to clients using Hessian.
  1. Generate C++ code for a client-side proxy. The proxy implements the interface methods by performing remote procedure calls to the server.
  1. Write a C++ client application which calls methods on the proxy.


## Development Status ##

**Alpha** -- Application programming interface may change.
CallbckPubManager
================

A library for attaching callback to Event publishers for the Dwenguino/Arduino platform.

Introduction
------------
It is quite comon to associate a function call to an event. 
For example, if pin **X** of the board goes **UP** one would like to turn a **LED** on.
To do this we need an object (the Manager) that knows that function `ledOn` should be called
when X goes up. Something like:

```
manager.bind (ledOn, X_up)
```

Here `manager` is the object that knows the relation betwen the *callback*[1](#callback) `ledOn` 
and the *event publisher* `X_up`.

<a name="callback">[1]</a>: Callback is a fancy name for functions that are called 
when something happens


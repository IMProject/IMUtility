#ifndef UTILITY_MISRA_C_2012_DOC_H_
#define UTILITY_MISRA_C_2012_DOC_H_

/*

Documentation for MISRA C:2012 Dir 4.1: overflow
------------------------------------------------
In all cases where overflow can happen, extra checks are implemented in production
code which will not allow overflow to happen.

Documentation for MISRA C:2012 Dir 4.1: unexpected wrapping
-----------------------------------------------------------
There is not unexpected wrapping in the code.

Documentation for MISRA C:2012 Dir 4.1: invalid shift
-----------------------------------------------------
In all cases where invalid shift can happen, extra checks are implemented in
production code which will not allow invalid shift to happen.

Documentation for MISRA C:2012 Dir 4.1: division/remainder by zero
------------------------------------------------------------------
In all cases where division/remainder operations are used, check is implemented
in production code which will prevent division/remainder operations by zero.

Documentation for MISRA C:2012 Dir 4.1: unsequenced side effects
----------------------------------------------------------------
Unsequenced side error cannot happen because no function in this code is meant
to be executed from interrupt handlers, or in multi-threading environments.

Documentation for MISRA C:2012 Dir 4.1: read from uninitialized automatic object
--------------------------------------------------------------------------------
Automatic objects are always initialized before their usage. ECLAIR is used for
MISRA rules verification, and there is no violations nor cautions regarding 9.1
rule.

Documentation for MISRA C:2012 Dir 4.1: read from uninitialized allocated object
--------------------------------------------------------------------------------
Allocated objects are not used in the code. ECLAIR is used for MISRA rules
verification, and there is no violations nor cautions regarding 21.3 rule.

Documentation for MISRA C:2012 Dir 4.1: write to string literal or const object
-------------------------------------------------------------------------------
String literal and const object are placed inside read-only section of memory.
Therefore, all write requests that are attempted on such section of memory are
correctly handled.

Documentation for MISRA C:2012 Dir 4.1: non-volatile access to volatile object
------------------------------------------------------------------------------
Non-volatile access to volatile object is not used in the project.

Documentation for MISRA C:2012 Dir 4.1: access to dead allocated object
-----------------------------------------------------------------------
Allocated objects are not used in the code. ECLAIR is used for MISRA rules
verification, and there is no violations nor cautions regarding 21.3 rule.

Documentation for MISRA C:2012 Dir 4.1: access to dead automatic object
-----------------------------------------------------------------------
Pointers to automatic variables are never returned, nor stored in wider-scoped objects.

Documentation for MISRA C:2012 Dir 4.1: access to dead thread object
--------------------------------------------------------------------
Per thread objects are not used in the code.

Documentation for MISRA C:2012 Dir 4.1: access using null pointer
-----------------------------------------------------------------
Guards are implemented and used in production code to avoid possible null
pointer/invalid pointer access.

Documentation for MISRA C:2012 Dir 4.1: access using invalid pointer
--------------------------------------------------------------------
Guards are implemented and used in production code to avoid possible null
pointer/invalid pointer access.

Documentation for MISRA C:2012 Dir 4.1: access using out-of-bounds pointer
--------------------------------------------------------------------------
Guards are implemented and used in production code to avoid possible
out-of-bounds pointer access.

Documentation for MISRA C:2012 Dir 4.1: access using unaligned pointer
----------------------------------------------------------------------
Only pointer conversion that is used in the code is pointer conversion to:
char, unsigned char, const char, const unsigned char.

Documentation for MISRA C:2012 Dir 4.1: mistyped access to object
-----------------------------------------------------------------
Only pointer conversion that is used in the code is pointer conversion to:
char, unsigned char, const char, const unsigned char.

Documentation for MISRA C:2012 Dir 4.1: mistyped access to function
-------------------------------------------------------------------
In all cases where function pointers are used, guards are implemented in
production code.

Documentation for MISRA C:2012 Dir 4.1: invalid pointer arithmetic
------------------------------------------------------------------
In all cases where pointer arithmetic is used, guards are implemented in
production code.

Documentation for MISRA C:2012 Dir 4.1: invalid pointer comparison
------------------------------------------------------------------
Guard are implemented in production code to avoid invalid pointer comparison.

Documentation for MISRA C:2012 Dir 4.1: overlapping copy
--------------------------------------------------------
In all cases where overlap can happen, extra checks are implemented in production
code which will not allow overlap to happen.

Documentation for MISRA C:2012 Dir 4.1: invalid arguments to function
---------------------------------------------------------------------
All arguments passed to functions are validated.

Documentation for MISRA C:2012 Dir 4.1: returned function error
---------------------------------------------------------------
Return value of all functions are checked at each call site, and all functions
that may produce an error will return a suitable status.

Documentation for MISRA C:2012 Dir 4.1: tainted input
-----------------------------------------------------
All parameters of all functions are checked before being used.

Documentation for MISRA C:2012 Dir 4.1: data race
-------------------------------------------------
No function in this code is meant to be executed from interrupt handlers,
or in a multi-threading environment.

Documentation for MISRA C:2012 Dir 4.1: invariant violation
-----------------------------------------------------------
In all cases where invariant violation can happen, extra checks are implemented
in production code which will not allow invariant violation to happen.

Documentation for MISRA C:2012 Dir 4.1: communication error
-----------------------------------------------------------
External communication is not involved in the code.

*/

#endif /* UTILITY_MISRA_C_2012_DOC_H_ */

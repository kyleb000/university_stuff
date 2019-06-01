These functions 'format' and 'format_with_placeholder' are used for string interpolation for C++.
This means you can have a string such as "Hello, {0}", and these functions will go and replace them with the
given arguments you pass. You can pass any number of arguments to the functions, of any type, and the types
of each arguments can differ. In fact, you can even pass your own types, so long as they support the << operator
with an std::ostream& type as the lvalue.

For example:
    std::string hello_string = format("Hello, {0}! You are {0} years old.", "Alice", 23);
will produce a string of "Hello, Alice! You are 23 years old."

Also:
    std::string hello_string = format_with_placeholder("Hello, %?! You are %? years old.", "%?", "Alice", 23);
will also yield "Hello, Alice! You are 23 years old."

So, here is the usage of these functions:
    format: returns a string
    Arguments: the first argument must be a string or a const char* type object. You can pass any number of
    following arguments of any type with mixed types
    Exceptions: Will throw a std::runtime_error if you do not pass enough placeholders for the number of 
    arguments you pass to the function
    
    format_with_placeholder: returns a string
    Arguments: the first argument must be a string or a const char* type object. The second argument must also be 
    a string or const char*. This argument is the placeholder you want the function to use instead of the 
    default {0}. You can pass any number of following arguments of any type with mixed types
    Exceptions: Will throw a std::runtime_error if you do not pass enough placeholders for the number of 
    arguments you pass to the function

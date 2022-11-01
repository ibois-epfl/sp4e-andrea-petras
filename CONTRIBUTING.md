
## Guide for contributors
Here's you can find some documentations and guidelines to contribute to homework2.

### GitHub commit convetion
All commits need to be labeled with a tag among these:
```
git commit -m "ADD:<description>"         <--- for adding new elements
git commit -m "FIX:<description>"         <--- for fixing (errors, typos)
git commit -m "MILESTONE:<description>"   <--- for capping moment in development
git commit -m "UPDATE:<description>"      <--- for moddification to the same file
git commit -m "MISC:<description>"        <--- for any other reasons to be described
```

### Naming/C++ convention
Here's the naming convention for this project:
- `localVariable`: lowerCamelCase.
- `type PrivateVariable`: public member of a class
- `type m_PrivateVariable`: Hungarian notation with UpperCamelCase for private class members.
- `static type s_StaticVariable`: Hungarian notation with UpperCamelCase for static members of class.
- `APP_SPEC`: Constants with SNAKE_UPPER_CASE.
- All the other naming uses UpperCamelCase.

Here's an example:
```c++
// next line graph style
void Foo()
{
    /* content */
}

// structure name uses UpperCamelCase
struct AnExampleStruct
{
    // structure attribute uses UpperCamelCase
    const char* Name;
};

// class name uses UpperCamelCase
class AnExampleClass
{
public:
    AnExampleClass(const int& init);
    virtual ~AnExampleClass();

    // member functions use UpperCamelCase
    void PublicMemberFunction()
    {
        // local variable uses lowerCamelCase
        int localVariable = 0;
    }

// A field indicator to separate the functions and attributes
public:
    int PublicVariable;


// Private member function block
private:
    // member functions use UpperCamelCase
    void PrivateMemberFunction(); 

// Also a field indicator to separate the functions and attributes
private:
    // private variables uses Hungarian notation with UpperCamelCase
    int m_PrivateVariable; // m_VariableName for normal variable
    static int s_Instance; // s_VariableName for static variable
};

// Filenames should start with small letters and written in snake case
src
└── source_example.cc
└── header_example.hh

// Start headers with 
#pragma once
```
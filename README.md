# f1d

Generate structs from field tuples with convenient metadata

## Test results
Branch          | Build         | Tests coverage
----------------|-------------- | --------------
master          | [![Build Status](https://travis-ci.org/Caian/f1d.svg?branch=master)](https://travis-ci.org/Caian/f1d) | [![codecov.io](https://codecov.io/github/Caian/f1d/coverage.svg?branch=master)](https://codecov.io/github/Caian/f1d)

## Introduction

This project allows the creation of structs from tuples, where each name and type in the tuple expand to an individual field in the struct.

Additional methods allow quick access to the field count, original field names, field types (as typed in the source code), field sizes (though sizeof), and allow searching for the index of the field by its name.

There is also a factory class generated for each struct that can be used to ensure all fields have been properly set during initialization of the structs.

## Requirements

This project requires [boost](https://www.boost.org/) for the preprocessor capabilites and as a dependency for the [ex3](https://github.com/Caian/ex3) project, used as the base for the exceptions thrown by the factory class. It also requires libdl, as a dependency of boost stacktrace.

## Usage

The macro `F1D_STRUCT_MAKE` is used to generate the struct, the factory, a nested namespace `types` containing one type per field, and a nested namespace `traits` with a metafunction used to query the type of a given field index.

For instance, the following call:

```c++
F1D_STRUCT_MAKE(my_struct_3,
    3, (
        (field1, float),
        (field2, int  ),
        (field3, char )
    )
) // my_struct_3
```

will be expanded to the following:

```c++
namespace types {
    typedef float field1_t;
    typedef int   field2_t;
    typedef char  field3_t;
}

struct my_struct_3
{
    types::field1_t field1;
    types::field2_t field2;
    types::field3_t field3;

    static const unsigned int num_fields = 3;
    static unsigned int get_num_fields() { ... }
    static const char** get_field_names() { ... }
    static const char* get_field_name(unsigned int index) { ... }
    static const char** get_type_names() { ... }
    static const char* get_type_name(unsigned int index) { ... }
    static unsigned int get_field_index(const std::string& name) { ... }
    static const size_t* get_type_sizes() { ... }
    static size_t get_type_size(unsigned int index) { ... }
};

class my_struct_3_factory
{
    // definition of factory

public:

    void begin() { ... }
    void end() { ... }

    const my_struct_3& get() const { ... }

    void set_field1(const types::field1_t& value) { ... }
    void set_field2(const types::field2_t& value) { ... }
    void set_field3(const types::field3_t& value) { ... }

    const types::field1_t& get_field1() const { ... }
    const types::field3_t& get_field3() const { ... }
    const types::field2_t& get_field2() const { ... }
};

namespace types {
    template <class T, unsigned int N>
    struct value_type
    {
        typedef void type;
    };

    template <>
    struct value_type<my_struct_3, 0>
    {
        typedef types::field1_t type;
    };

    template <>
    struct value_type<my_struct_3, 1>
    {
        typedef types::field2_t type;
    };

    template <>
    struct value_type<my_struct_3, 2>
    {
        typedef types::field3_t type;
    };
}
```

## Multiple structs per namespace

By default, calling `F1D_STRUCT_MAKE` will generate a `traits` namespace with template declarations that are incompatible with multiple structs. To solve this problem, it is possible to create the `traits` namespace first using the `F1D_TRAITS_MAKE()` macro and then use multiple calls to `F1D_STRUCT_MAKE_NT` (NT stands for no-traits) to create the structs:

```c++
F1D_TRAITS_MAKE()

F1D_STRUCT_MAKE_NT(first_struct,
    3, (
        (a, int),
        (b, int),
        (c, int)
    )
) // first_struct

F1D_STRUCT_MAKE_NT(second_struct,
    2, (
        (d, int),
        (e, int)
    )
) // second_struct
```

Although this solves the problem with the `traits` namespace, it is still possible for typedef collisions to occur inside the `types` namespace. Unfortunately at the moment there is still no solution for this particular case.

## Struct factory

The factory class can be used to ensure that each field of the struct is set once and only once when the struct is being initialized. To use it, you must:

- Instance a factory object;
- Call `begin()`;
- Set every field through its setter exactly once;
- Call `end()` to finish the initialization;
- Call `get()` to obtain a constant reference to the initialized struct;

The *begin-set-end-get* cycle can be repeated as many times as necessary, always following this exact order. The `get()` method can be called multiple times, but always after `end()`.

Additionally, the factory contains getters for each field in the struct, these getters can only be called after the field has been initialized, including after calling `end()`.

## Field wrappers

Field wrappers are automatically-generated structs to assist in extracting specific fields via template metaprogramming instead of relying on C++ pointer to members.

Each field generated by f1d has also a companion field struct generated under `types` namespace with the same name as the field itself plus the `_f` suffix.

Field wrappers can be initialized and assigned from the original type value, other field object from the same type and also from the f1d-generated struct:

```c++
const float v1 = 1.4f;

test::my_struct ms;

test::types::field1_f field1_1;
test::types::field1_f field1_2;
test::types::field1_f field1_3;
test::types::field1_f field1_4;

field1_1 = v1;
field1_2 = field1_1;
field1_3 = ms;
```

They have a `get` method to return either a constant reference to the field value, or a mutable reference for changing its value:

```c++
const float v1 = 1.4f;

test::types::field1_f field1_1;

field1_1.get() = v1;

const float vf1 = field1_1.get();
```

They can be used as functors to apply their field value to either a reference to the same underlying type, or even a f1d-generated struct, making them handy when applying transforms:

```c++
test::types::field1_f field1(1.3);

float vf1;
test::my_struct ms;

field1(vf1);
field1(ms);
```

They also have a special `set_member` method that allows fields to set their values to any kind of struct, as long as the name of the member matches the original f1d-generated struct one:

```c++
struct some_struct
{
    int real_field1;
    char some_field2;
    double field1; // not really! ;)
};

test::types::field1_f field1(1.3);

test::my_struct ms;
some_struct ss;

field1(ms);
field1(ss);
```

Field wrappers have their own `field_type` and `field_index` traits to access information about their source fields:

```c++
typedef test::types::field1_f Field;

typedef test::traits::field_type<Field>::type ValueType; // float

unsigned int Index = test::traits::field_index<Field>::value; // 0
```

It's also possible to get the field wrapper type directly from the field index using the `field_wrapper_type` trait:

```c++
typedef test::traits::field_wrapper_type<test::my_struct, 0>::type Field1;
Field1 field1(1.3);
```

Finally, field wrappers are also compatible with boost tuples:

```c++
#include <boost/tuple/tuple.hpp>

test::my_struct ms;

typedef boost::tuple<
    test::types::field1_f,
    test::types::field3_f
    > my_field_tuple;

typedef boost::tuple<
    test::traits::field_type<test::types::field1_f>::type,
    test::traits::field_type<test::types::field3_f>::type
    > my_value_tuple;

// Create a field tuple from the struct
my_field_tuple ftuple(ms, ms);

// Cast a field tuple to a value tuple
my_value_tuple vtuple(ftuple);

// One can also access elements from the field tuple as their final type
const float vt1 = boost::get<0>(ftuple);
const int   vt2 = boost::get<1>(ftuple);
```

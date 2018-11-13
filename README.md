# f1d
Generate structs from field tuples with convenient metadata

## Introduction

This project allows the creation of structs from tuples, where each name and type in the tuple expand to an individual field in the struct.

Additional methods allow quick access to the field count, original field names, field types (as typed in the source code), field sizes (though sizeof), and allow searching for the index of the field by its name.

There is also a factory class generated for each struct that can be used to ensure all fields have been properly set during initialization of the structs.

## Requirements

This project requires [boost](https://www.boost.org/) for the preprocessor capabilites and as a dependency for the [ex3](https://github.com/Caian/ex3) project, used as the base for the exceptions thrown by the factory class.

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
    static const char* get_field_name(unsigned int index) { ... }
    static const char* get_type_name(unsigned int index) { ... }
    static unsigned int get_field_index(const std::string& name) { ... }
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

Currently, the template `value_type` **does not** allow multiple `F1D_STRUCT_MAKE` declarations in a single namespace because there will be multiple definitions of the base template trait inside the `traits` namespace. This may change in the future if I can find a solution that does not sacrifice simplicity.

## Struct factory

The factory class can be used to ensure that each field of the struct is set once and only once when the struct is being initialized. To use it, you must:

- Instance a factory object;
- Call begin();
- Set every field through its setter exactly once;
- Call end() to finish the initialization;
- Call get() to obtain a constant reference to the initialized struct;

The *begin-set-end-get* cycle can be repeated as many times as necessary, always following this exact order. The `get()` method can be called multiple times, but always after `end()`.

Additionally, the factory contains getters for each field in the struct, these getters can only be called after the field has been initialized, including after calling `end()`.

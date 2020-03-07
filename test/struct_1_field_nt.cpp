/*
 * Copyright (C) 2018-2019 Caian Benedicto <caianbene@gmail.com>
 *
 * This file is part of f1d.
 *
 * f1d is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * f1d is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with f1d.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <f1d/fields.hpp>
#include <gtest/gtest.h>
#include <typeinfo>

#define MY_ASSERT_THROW_STRUCT_NAME(stmt, Name) \
    try { \
        (stmt); \
    } \
    catch (const std::exception& ex) { \
        \
        const std::string* sname; \
        sname = boost::get_error_info<f1d::struct_name>(ex); \
        \
        ASSERT_TRUE(sname != 0); \
        ASSERT_STREQ(sname->c_str(), Name); \
    } \
    catch (...) { \
        FAIL() << "Unexpected exception thrown by f.end()!"; \
    }

namespace test {

F1D_TRAITS_MAKE()

F1D_STRUCT_MAKE_NT(my_struct_1_nt,
    ( (field1, double) )
) // my_struct_1_nt

struct some_struct_1_nt
{
    int real_field1;
    char some_field2;
    float field1;
};

struct funct_1_1_nt
{
    template <unsigned int I, typename S, typename V>
    void operator ()(const V& v) const
    {
        V v2 = v + 1;
    }
};

struct funct_1_2_nt
{
    template <unsigned int I, typename S, typename V>
    void operator ()(V& v) const
    {
        v += 1;
    }
};

struct funct_1_3_nt
{
    double total;

    funct_1_3_nt() :
        total(0)
    {
    }

    template <unsigned int I, typename S, typename V>
    void operator ()(const V& v)
    {
        total += v + 1;
    }
};

struct funct_1_4_nt
{
    double total;

    funct_1_4_nt() :
        total(0)
    {
    }

    template <unsigned int I, typename S, typename V>
    void operator ()(V& v)
    {
        total += v + 1;
        v = total;
    }
};

}

/**
 * Test member access
 */
TEST(Struct1FieldsNTTest, AccessMembers)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    ms.field1 = v1;

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessStructName)
{
    EXPECT_STREQ(test::my_struct_1_nt::get_struct_name(), "my_struct_1_nt");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessCountMetadata)
{
    EXPECT_EQ(static_cast<unsigned int>(test::my_struct_1_nt::num_fields), 1);
    EXPECT_EQ(test::my_struct_1_nt::get_num_fields(), 1);
    EXPECT_EQ(static_cast<unsigned int>(
        test::my_struct_1_nt::num_fields),
        static_cast<unsigned int>(test::traits::
        num_fields<test::my_struct_1_nt>::value));
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessNameMetadata)
{
    EXPECT_STREQ(test::my_struct_1_nt::get_field_name(0), "field1");
    EXPECT_THROW(test::my_struct_1_nt::get_field_name(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1_nt::get_field_name(1), "my_struct_1_nt");

    try {
        test::my_struct_1_nt::get_field_name(1);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 1);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_1_nt::get_field_names()[0], "field1");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessTypeNameMetadata)
{
    EXPECT_STREQ(test::my_struct_1_nt::get_type_name(0), "double");
    EXPECT_THROW(test::my_struct_1_nt::get_type_name(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1_nt::get_type_name(1), "my_struct_1_nt");

    try {
        test::my_struct_1_nt::get_field_name(1);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 1);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessTypeNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_1_nt::get_type_names()[0], "double");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessTypeSizeMetadata)
{
    EXPECT_EQ(test::my_struct_1_nt::get_type_size(0), sizeof(double));
    EXPECT_THROW(test::my_struct_1_nt::get_type_size(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1_nt::get_type_size(1), "my_struct_1_nt");

    try {
        test::my_struct_1_nt::get_field_name(1);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 1);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessTypeSizeMetadata2)
{
    EXPECT_EQ(test::my_struct_1_nt::get_type_sizes()[0], sizeof(double));
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsNTTest, AccessIndexMetadata)
{
    EXPECT_EQ(test::my_struct_1_nt::get_field_index("field1"), 0);
    EXPECT_THROW(test::my_struct_1_nt::get_field_index("field2"), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1_nt::get_field_index("field2"), "my_struct_1_nt");

    try {
        test::my_struct_1_nt::get_field_index("field2");
    }
    catch (const std::exception& ex) {

        const std::string* name;
        name = boost::get_error_info<f1d::field_name>(ex);

        ASSERT_TRUE(name != 0);
        ASSERT_STREQ(name->c_str(), "field2");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test trait access
 */
TEST(Struct1FieldsNTTest, AccessTraits)
{
    EXPECT_EQ(typeid(double), typeid(test::traits::value_type<test::my_struct_1_nt, 0>::type));

    EXPECT_EQ(typeid(double), typeid(test::types::field1_t));

    test::my_struct_1_nt ms;

    EXPECT_EQ(typeid(ms.field1), typeid(test::traits::value_type<test::my_struct_1_nt, 0>::type));

    EXPECT_EQ(typeid(test::types::field1_f), typeid(test::traits::field_wrapper_type<test::my_struct_1_nt, 0>::type));
}

/**
 * Test factory without error
 */
TEST(Struct1FieldsNTTest, FactoryOK)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory without error multiple times.
 */
TEST(Struct1FieldsNTTest, FactoryOKX5)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    for (size_t i = 0 ; i < 5; i++) {
        ASSERT_NO_THROW(f.begin());
        ASSERT_NO_THROW(f.set_field1(v1));
        ASSERT_NO_THROW(f.end());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());

        EXPECT_EQ(f.get_field1(), v1);

        EXPECT_EQ(ms.field1, v1);
    }
}

/**
 * Test factory fail if begin is called before end.
 */
TEST(Struct1FieldsNTTest, FactoryDoubleBegin)
{
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW(f.begin(), f1d::not_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.begin(), "my_struct_1_nt");
}

/**
 * Test factory fail if get is called before set.
 */
TEST(Struct1FieldsNTTest, FactoryGetBeforeSet)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());

    ASSERT_THROW(f.get_field1(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field1(), "my_struct_1_nt");

    ASSERT_NO_THROW(f.set_field1(v1));

    EXPECT_EQ(f.get_field1(), v1);

    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory fail if another end is called after end.
 */
TEST(Struct1FieldsNTTest, FactoryDoubleEnd)
{
    const double v1 = 1.4;

    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW(f.end(), f1d::already_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1_nt");
}

/**
 * Test factory calling set multiple times, should
 * throw an exception for the repeated set and keep
 * the first one.
 */
TEST(Struct1FieldsNTTest, FactoryMultipleSet)
{
    const double v11 = 1.4;
    const double v12 = 5.9f;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v11));
    ASSERT_THROW   (f.set_field1(v12), f1d::already_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v12), "my_struct_1_nt");

    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v11);

    EXPECT_EQ(ms.field1, v11);
}

/**
 * Test factory calling set after end.
 */
TEST(Struct1FieldsNTTest, FactorySetAfterEnd)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW   (f.set_field1(v1), f1d::already_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v1), "my_struct_1_nt");

    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory with an end before begin
 */
TEST(Struct1FieldsNTTest, FactoryEndBeforeBegin)
{
    test::my_struct_1_nt_factory f;

    ASSERT_THROW(f.end(), f1d::not_intialized_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1_nt");
}

/**
 * Test factory with a set before begin
 */
TEST(Struct1FieldsNTTest, FactorySetBeforeBegin)
{
    const double v1 = 1.4;

    test::my_struct_1_nt_factory f;

    ASSERT_THROW(f.set_field1(v1), f1d::not_intialized_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v1), "my_struct_1_nt");
}

/**
 * Test factory with an end before setting all fields.
 */
TEST(Struct1FieldsNTTest, FactoryIncompleteSet1)
{
    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW   (f.end(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1_nt");

    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get(), "my_struct_1_nt");

    try {
        f.end();
    }
    catch (const std::exception& ex) {

        const f1d::pretty_uint_vector* uv;
        const f1d::pretty_string_vector* sv;

        uv = boost::get_error_info<f1d::field_indices>(ex);
        sv = boost::get_error_info<f1d::field_names>(ex);

        ASSERT_TRUE(uv != 0);
        ASSERT_TRUE(sv != 0);

        ASSERT_EQ(uv->values.size(), 1);
        ASSERT_EQ(sv->values.size(), 1);

        EXPECT_EQ(uv->values[0], 0);
        ASSERT_STREQ(sv->values[0].c_str(), "field1");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test the field type constructors
 */
TEST(Struct1FieldsNTTest, FieldConstruct)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);

    test::types::field1_f field1_1(v1);
    test::types::field1_f field1_2(field1_1);
    test::types::field1_f field1_3(ms);

    EXPECT_EQ(field1_1.get(), v1);
    EXPECT_EQ(field1_2.get(), v1);
    EXPECT_EQ(field1_3.get(), v1);
}

/**
 * Test the field type assign operators
 */
TEST(Struct1FieldsNTTest, FieldAssign)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);

    test::types::field1_f field1_1;
    test::types::field1_f field1_2;
    test::types::field1_f field1_3;
    test::types::field1_f field1_4;

    field1_1 = v1;
    field1_2 = field1_1;
    field1_3 = ms;
    field1_4.get() = v1;

    EXPECT_EQ(field1_1.get(), v1);
    EXPECT_EQ(field1_2.get(), v1);
    EXPECT_EQ(field1_3.get(), v1);
    EXPECT_EQ(field1_3.get(), v1);
}

/**
 * Test the field type cast operators
 */
TEST(Struct1FieldsNTTest, FieldCast)
{
    const double v1 = 1.4;

    test::types::field1_f field1(v1);

    const double vf1 = field1;

    EXPECT_EQ(field1.get(), v1);
    EXPECT_EQ(vf1, v1);
}

/**
 * Test the field type call operators
 */
TEST(Struct1FieldsNTTest, FieldApply)
{
    const double v1 = 1.4;

    test::types::field1_f field1(v1);

    double vf1;
    test::my_struct_1_nt ms;

    field1(vf1);
    field1(ms);

    EXPECT_EQ(field1.get(), v1);
    EXPECT_EQ(vf1, v1);
    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test the field type traits
 */
TEST(Struct1FieldsNTTest, FieldTraits)
{
    EXPECT_EQ(typeid(double), typeid(test::traits::field_type<test::types::field1_f>::type));

    EXPECT_EQ(0, static_cast<unsigned int>(test::traits::field_index<test::types::field1_f>::value));
}

/**
 * Test the field type set_member method
 */
TEST(Struct1FieldsNTTest, FieldSetMember)
{
    const double v1 = 1.3;

    test::types::field1_f field1(v1);

    test::my_struct_1_nt ms;
    test::some_struct_1_nt ss;

    field1.set_member(ms);
    field1.set_member(ss);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ss.field1, static_cast<float>(v1));
}

/**
 * Test the struct apply method
 */
TEST(Struct1FieldsNTTest, ApplyMethod)
{
    const double v1 = 10;

    test::my_struct_1_nt ms1;
    test::my_struct_1_nt ms2;
    test::my_struct_1_nt ms3;
    test::my_struct_1_nt ms4;
    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms1 = f.get());
    ASSERT_NO_THROW(ms2 = f.get());
    ASSERT_NO_THROW(ms3 = f.get());
    ASSERT_NO_THROW(ms4 = f.get());

    const test::funct_1_1_nt f1;
    const test::funct_1_2_nt f2;
    test::funct_1_3_nt f3;
    test::funct_1_4_nt f4;

    ms1.apply(f1);
    ms2.apply(f2);
    ms3.apply(f3);
    ms4.apply(f4);

    EXPECT_EQ(ms1.field1, v1);
    EXPECT_EQ(ms2.field1, (v1 + 1));
    EXPECT_EQ(ms3.field1, v1);
    EXPECT_EQ(ms4.field1, (v1 + 1));

    EXPECT_EQ(f3.total, (v1 + 1));
    EXPECT_EQ(f4.total, (v1 + 1));
}

/**
 * Test the struct capply method
 */
TEST(Struct1FieldsNTTest, CApplyMethod)
{
    const double v1 = 10;

    test::my_struct_1_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());

    const test::my_struct_1_nt ms1 = f.get();
    const test::my_struct_1_nt ms3 = f.get();

    const test::funct_1_1_nt f1;
    test::funct_1_3_nt f3;

    ms1.capply(f1);
    ms3.capply(f3);

    EXPECT_EQ(ms1.field1, v1);
    EXPECT_EQ(ms3.field1, v1);

    EXPECT_EQ(f3.total, (v1 + 1));
}

/**
 * Test factory set from field wrappers without error
 */
TEST(Struct1FieldsNTTest, FactoryFromFieldOK)
{
    const double v1 = 1.4;

    test::my_struct_1_nt ms;
    test::my_struct_1_nt_factory f;

    test::types::field1_f field1(v1);

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(field1(f));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);
}

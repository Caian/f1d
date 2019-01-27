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
 * along with GNU Make; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
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

F1D_STRUCT_MAKE(my_struct_1,
    1, (
        (field1, double)
    )
) // my_struct_1

}

/**
 * Test member access
 */
TEST(Struct1FieldsTest, AccessMembers)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    ms.field1 = v1;

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessStructName)
{
    EXPECT_STREQ(test::my_struct_1::get_struct_name(), "my_struct_1");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessCountMetadata)
{
    EXPECT_EQ(static_cast<unsigned int>(test::my_struct_1::num_fields), 1);
    EXPECT_EQ(test::my_struct_1::get_num_fields(), 1);
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessNameMetadata)
{
    EXPECT_STREQ(test::my_struct_1::get_field_name(0), "field1");
    EXPECT_THROW(test::my_struct_1::get_field_name(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1::get_field_name(1), "my_struct_1");

    try {
        test::my_struct_1::get_field_name(1);
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
TEST(Struct1FieldsTest, AccessNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_1::get_field_names()[0], "field1");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessTypeNameMetadata)
{
    EXPECT_STREQ(test::my_struct_1::get_type_name(0), "double");
    EXPECT_THROW(test::my_struct_1::get_type_name(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1::get_type_name(1), "my_struct_1");

    try {
        test::my_struct_1::get_field_name(1);
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
TEST(Struct1FieldsTest, AccessTypeNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_1::get_type_names()[0], "double");
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessTypeSizeMetadata)
{
    EXPECT_EQ(test::my_struct_1::get_type_size(0), sizeof(double));
    EXPECT_THROW(test::my_struct_1::get_type_size(1), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1::get_type_size(1), "my_struct_1");

    try {
        test::my_struct_1::get_field_name(1);
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
TEST(Struct1FieldsTest, AccessTypeSizeMetadata2)
{
    EXPECT_EQ(test::my_struct_1::get_type_sizes()[0], sizeof(double));
}

/**
 * Test metadata access
 */
TEST(Struct1FieldsTest, AccessIndexMetadata)
{
    EXPECT_EQ(test::my_struct_1::get_field_index("field1"), 0);
    EXPECT_THROW(test::my_struct_1::get_field_index("field2"), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_1::get_field_index("field2"), "my_struct_1");

    try {
        test::my_struct_1::get_field_index("field2");
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
 * Test member access
 */
TEST(Struct1FieldsTest, AccessTraits)
{
    EXPECT_EQ(typeid(double), typeid(test::traits::value_type<test::my_struct_1, 0>::type));

    EXPECT_EQ(typeid(double), typeid(test::types::field1_t));

    test::my_struct_1 ms;

    EXPECT_EQ(typeid(ms.field1), typeid(test::traits::value_type<test::my_struct_1, 0>::type));
}

/**
 * Test factory without error
 */
TEST(Struct1FieldsTest, FactoryOK)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory without error multiple times.
 */
TEST(Struct1FieldsTest, FactoryOKX5)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    for (size_t i = 0 ; i < 5; i++) {
        ASSERT_NO_THROW(f.begin());
        ASSERT_NO_THROW(f.set_field1(v1));
        ASSERT_NO_THROW(f.end());
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));

        EXPECT_EQ(f.get_field1(), v1);

        EXPECT_EQ(ms.field1, v1);
    }
}

/**
 * Test factory fail if begin is called before end.
 */
TEST(Struct1FieldsTest, FactoryDoubleBegin)
{
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW(f.begin(), f1d::not_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.begin(), "my_struct_1");
}

/**
 * Test factory fail if get is called before set.
 */
TEST(Struct1FieldsTest, FactoryGetBeforeSet)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());

    ASSERT_THROW(f.get_field1(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field1(), "my_struct_1");

    ASSERT_NO_THROW(f.set_field1(v1));

    EXPECT_EQ(f.get_field1(), v1);

    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory fail if another end is called after end.
 */
TEST(Struct1FieldsTest, FactoryDoubleEnd)
{
    const double v1 = 1.4;

    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW(f.end(), f1d::already_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1");
}

/**
 * Test factory calling set multiple times, should
 * throw an exception for the repeated set and keep
 * the first one.
 */
TEST(Struct1FieldsTest, FactoryMultipleSet)
{
    const double v11 = 1.4;
    const double v12 = 5.9f;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v11));
    ASSERT_THROW   (f.set_field1(v12), f1d::already_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v12), "my_struct_1");

    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(f.get_field1(), v11);

    EXPECT_EQ(ms.field1, v11);
}

/**
 * Test factory calling set after end.
 */
TEST(Struct1FieldsTest, FactorySetAfterEnd)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW   (f.set_field1(v1), f1d::already_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v1), "my_struct_1");

    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(f.get_field1(), v1);

    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test factory with an end before begin
 */
TEST(Struct1FieldsTest, FactoryEndBeforeBegin)
{
    test::my_struct_1_factory f;

    ASSERT_THROW(f.end(), f1d::not_intialized_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1");
}

/**
 * Test factory with a set before begin
 */
TEST(Struct1FieldsTest, FactorySetBeforeBegin)
{
    const double v1 = 1.4;

    test::my_struct_1_factory f;

    ASSERT_THROW(f.set_field1(v1), f1d::not_intialized_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.set_field1(v1), "my_struct_1");
}

/**
 * Test factory with an end before setting all fields.
 */
TEST(Struct1FieldsTest, FactoryIncompleteSet1)
{
    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW   (f.end(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.end(), "my_struct_1");

    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get(), "my_struct_1");

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
TEST(Struct1FieldsTest, FieldConstruct)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct1FieldsTest, FieldAssign)
{
    const double v1 = 1.4;

    test::my_struct_1 ms;
    test::my_struct_1_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct1FieldsTest, FieldCast)
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
TEST(Struct1FieldsTest, FieldApply)
{
    const double v1 = 1.4;

    test::types::field1_f field1(v1);

    double vf1;
    test::my_struct_1 ms;

    field1(vf1);
    field1(ms);

    EXPECT_EQ(field1.get(), v1);
    EXPECT_EQ(vf1, v1);
    EXPECT_EQ(ms.field1, v1);
}

/**
 * Test the field type traits
 */
TEST(Struct1FieldsTest, FieldTraits)
{
    EXPECT_EQ(typeid(double), typeid(test::traits::field_type<test::types::field1_f>::type));

    EXPECT_EQ(0, static_cast<unsigned int>(test::traits::field_index<test::types::field1_f>::value));
}

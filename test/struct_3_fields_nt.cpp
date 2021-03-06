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

F1D_STRUCT_MAKE_NT(my_struct_3_nt,
    ( (field1, float) )
    ( (field2, int  ) )
    ( (field3, char ) )
) // my_struct_3_nt

struct some_struct_3_nt
{
    short field2;
    int one_field;
    int field3;
    char other_field;
    double field1;
};

struct funct_3_1_nt
{
    template <unsigned int I, typename S, typename V>
    void operator ()(const V& v) const
    {
        V v2 = v + 1;
    }
};

struct funct_3_2_nt
{
    template <unsigned int I, typename S, typename V>
    void operator ()(V& v) const
    {
        v += 1;
    }
};

struct funct_3_3_nt
{
    double total;

    funct_3_3_nt() :
        total(0)
    {
    }

    template <unsigned int I, typename S, typename V>
    void operator ()(const V& v)
    {
        total += v + 1;
    }
};

struct funct_3_4_nt
{
    double total;

    funct_3_4_nt() :
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
TEST(Struct3FieldsNTTest, AccessMembers)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    ms.field1 = v1;
    ms.field2 = v2;
    ms.field3 = v3;

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessStructName)
{
    EXPECT_STREQ(test::my_struct_3_nt::get_struct_name(), "my_struct_3_nt");
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessCountMetadata)
{
    EXPECT_EQ(static_cast<unsigned int>(test::my_struct_3_nt::num_fields), 3);
    EXPECT_EQ(test::my_struct_3_nt::get_num_fields(), 3);
    EXPECT_EQ(static_cast<unsigned int>(
        test::my_struct_3_nt::num_fields),
        static_cast<unsigned int>(test::traits::
        num_fields<test::my_struct_3_nt>::value));
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessNameMetadata)
{
    EXPECT_STREQ(test::my_struct_3_nt::get_field_name(0), "field1");
    EXPECT_STREQ(test::my_struct_3_nt::get_field_name(1), "field2");
    EXPECT_STREQ(test::my_struct_3_nt::get_field_name(2), "field3");
    EXPECT_THROW(test::my_struct_3_nt::get_field_name(3), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_3_nt::get_field_name(3), "my_struct_3_nt");

    try {
        test::my_struct_3_nt::get_field_name(3);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 3);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_3_nt::get_field_names()[0], "field1");
    EXPECT_STREQ(test::my_struct_3_nt::get_field_names()[1], "field2");
    EXPECT_STREQ(test::my_struct_3_nt::get_field_names()[2], "field3");
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessTypeNameMetadata)
{
    EXPECT_STREQ(test::my_struct_3_nt::get_type_name(0), "float");
    EXPECT_STREQ(test::my_struct_3_nt::get_type_name(1), "int");
    EXPECT_STREQ(test::my_struct_3_nt::get_type_name(2), "char");
    EXPECT_THROW(test::my_struct_3_nt::get_type_name(3), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_3_nt::get_type_name(3), "my_struct_3_nt");

    try {
        test::my_struct_3_nt::get_field_name(3);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 3);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessTypeNameMetadata2)
{
    EXPECT_STREQ(test::my_struct_3_nt::get_type_names()[0], "float");
    EXPECT_STREQ(test::my_struct_3_nt::get_type_names()[1], "int");
    EXPECT_STREQ(test::my_struct_3_nt::get_type_names()[2], "char");
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessTypeSizeMetadata)
{
    EXPECT_EQ(test::my_struct_3_nt::get_type_size(0), sizeof(float));
    EXPECT_EQ(test::my_struct_3_nt::get_type_size(1), sizeof(int));
    EXPECT_EQ(test::my_struct_3_nt::get_type_size(2), sizeof(char));
    EXPECT_THROW(test::my_struct_3_nt::get_type_size(3), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_3_nt::get_type_size(3), "my_struct_3_nt");

    try {
        test::my_struct_3_nt::get_field_name(3);
    }
    catch (const std::exception& ex) {

        const unsigned int* index;
        index = boost::get_error_info<f1d::field_index>(ex);

        ASSERT_TRUE(index != 0);
        ASSERT_EQ(*index, 3);
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessTypeSizeMetadata2)
{
    EXPECT_EQ(test::my_struct_3_nt::get_type_sizes()[0], sizeof(float));
    EXPECT_EQ(test::my_struct_3_nt::get_type_sizes()[1], sizeof(int));
    EXPECT_EQ(test::my_struct_3_nt::get_type_sizes()[2], sizeof(char));
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsNTTest, AccessIndexMetadata)
{
    EXPECT_EQ(test::my_struct_3_nt::get_field_index("field1"), 0);
    EXPECT_EQ(test::my_struct_3_nt::get_field_index("field2"), 1);
    EXPECT_EQ(test::my_struct_3_nt::get_field_index("field3"), 2);
    EXPECT_THROW(test::my_struct_3_nt::get_field_index("field4"), f1d::not_found_exception);

    MY_ASSERT_THROW_STRUCT_NAME(test::my_struct_3_nt::get_field_index("field4"), "my_struct_3_nt");

    try {
        test::my_struct_3_nt::get_field_index("field4");
    }
    catch (const std::exception& ex) {

        const std::string* name;
        name = boost::get_error_info<f1d::field_name>(ex);

        ASSERT_TRUE(name != 0);
        ASSERT_STREQ(name->c_str(), "field4");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }
}

/**
 * Test trait access
 */
TEST(Struct3FieldsNTTest, AccessTraits)
{
    EXPECT_EQ(typeid(float), typeid(test::traits::value_type<test::my_struct_3_nt, 0>::type));
    EXPECT_EQ(typeid(int),   typeid(test::traits::value_type<test::my_struct_3_nt, 1>::type));
    EXPECT_EQ(typeid(char),  typeid(test::traits::value_type<test::my_struct_3_nt, 2>::type));

    EXPECT_EQ(typeid(float), typeid(test::types::field1_t));
    EXPECT_EQ(typeid(int),   typeid(test::types::field2_t));
    EXPECT_EQ(typeid(char),  typeid(test::types::field3_t));

    test::my_struct_3_nt ms;

    EXPECT_EQ(typeid(ms.field1), typeid(test::traits::value_type<test::my_struct_3_nt, 0>::type));
    EXPECT_EQ(typeid(ms.field2), typeid(test::traits::value_type<test::my_struct_3_nt, 1>::type));
    EXPECT_EQ(typeid(ms.field3), typeid(test::traits::value_type<test::my_struct_3_nt, 2>::type));

    EXPECT_EQ(typeid(test::types::field1_f), typeid(test::traits::field_wrapper_type<test::my_struct_3_nt, 0>::type));
    EXPECT_EQ(typeid(test::types::field2_f), typeid(test::traits::field_wrapper_type<test::my_struct_3_nt, 1>::type));
    EXPECT_EQ(typeid(test::types::field3_f), typeid(test::traits::field_wrapper_type<test::my_struct_3_nt, 2>::type));
}

/**
 * Test factory without error
 */
TEST(Struct3FieldsNTTest, FactoryOK)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test factory without error multiple times.
 */
TEST(Struct3FieldsNTTest, FactoryOKX5)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    for (size_t i = 0 ; i < 5; i++) {
        ASSERT_NO_THROW(f.begin());
        ASSERT_NO_THROW(f.set_field1(v1));
        ASSERT_NO_THROW(f.set_field2(v2));
        ASSERT_NO_THROW(f.set_field3(v3));
        ASSERT_NO_THROW(f.end());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());
        ASSERT_NO_THROW(ms = f.get());

        EXPECT_EQ(f.get_field1(), v1);
        EXPECT_EQ(f.get_field1(), v1);
        EXPECT_EQ(f.get_field2(), v2);
        EXPECT_EQ(f.get_field2(), v2);
        EXPECT_EQ(f.get_field3(), v3);
        EXPECT_EQ(f.get_field3(), v3);

        EXPECT_EQ(ms.field1, v1);
        EXPECT_EQ(ms.field2, v2);
        EXPECT_EQ(ms.field3, v3);
    }
}

/**
 * Test factory fail if begin is called before end.
 */
TEST(Struct3FieldsNTTest, FactoryDoubleBegin)
{
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW(f.begin(), f1d::not_finished_exception);
}

/**
 * Test factory fail if get is called before set.
 */
TEST(Struct3FieldsNTTest, FactoryGetBeforeSet)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());

    ASSERT_THROW(f.get_field1(), f1d::not_set_exception);
    ASSERT_THROW(f.get_field2(), f1d::not_set_exception);
    ASSERT_THROW(f.get_field3(), f1d::not_set_exception);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test factory fail if another end is called after end.
 */
TEST(Struct3FieldsNTTest, FactoryDoubleEnd)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW(f.end(), f1d::already_finished_exception);
}

/**
 * Test factory calling set multiple times, should
 * throw an exception for the repeated set and keep
 * the first one.
 */
TEST(Struct3FieldsNTTest, FactoryMultipleSet)
{
    const float v11 = 1.4f;
    const int   v21 = -7;
    const char  v31 = 'H';

    const float v12 = 5.9f;
    const int   v22 = 12;
    const char  v32 = 'p';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v11));
    ASSERT_THROW   (f.set_field1(v12), f1d::already_set_exception);
    ASSERT_NO_THROW(f.set_field2(v21));
    ASSERT_THROW   (f.set_field2(v22), f1d::already_set_exception);
    ASSERT_NO_THROW(f.set_field3(v31));
    ASSERT_THROW   (f.set_field3(v32), f1d::already_set_exception);
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v11);
    EXPECT_EQ(f.get_field2(), v21);
    EXPECT_EQ(f.get_field3(), v31);

    EXPECT_EQ(ms.field1, v11);
    EXPECT_EQ(ms.field2, v21);
    EXPECT_EQ(ms.field3, v31);
}

/**
 * Test factory calling set after end.
 */
TEST(Struct3FieldsNTTest, FactorySetAfterEnd)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW   (f.set_field1(v1), f1d::already_finished_exception);
    ASSERT_THROW   (f.set_field2(v2), f1d::already_finished_exception);
    ASSERT_THROW   (f.set_field3(v3), f1d::already_finished_exception);
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test factory with an end before begin
 */
TEST(Struct3FieldsNTTest, FactoryEndBeforeBegin)
{
    test::my_struct_3_nt_factory f;

    ASSERT_THROW(f.end(), f1d::not_intialized_exception);
}

/**
 * Test factory with a set before begin
 */
TEST(Struct3FieldsNTTest, FactorySetBeforeBegin)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt_factory f;

    ASSERT_THROW(f.set_field1(v1), f1d::not_intialized_exception);
    ASSERT_THROW(f.set_field2(v2), f1d::not_intialized_exception);
    ASSERT_THROW(f.set_field3(v3), f1d::not_intialized_exception);
}

/**
 * Test factory with an end before setting all fields.
 */
TEST(Struct3FieldsNTTest, FactoryIncompleteSet1)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

    EXPECT_THROW(f.get_field1(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field1(), "my_struct_3_nt");

    EXPECT_EQ   (f.get_field2(), v2);
    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    //

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

        EXPECT_EQ(uv->values[0], 1);
        ASSERT_STREQ(sv->values[0].c_str(), "field2");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }

    EXPECT_THROW(f.get_field2(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field2(), "my_struct_3_nt");

    EXPECT_EQ   (f.get_field1(), v1);
    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    //

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

        EXPECT_EQ(uv->values[0], 2);
        ASSERT_STREQ(sv->values[0].c_str(), "field3");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }

    EXPECT_THROW(f.get_field3(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field3(), "my_struct_3_nt");

    EXPECT_EQ   (f.get_field1(), v1);
    EXPECT_EQ   (f.get_field2(), v2);

    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test factory with an end before setting all fields.
 */
TEST(Struct3FieldsNTTest, FactoryIncompleteSet2)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

        ASSERT_EQ(uv->values.size(), 2);
        ASSERT_EQ(sv->values.size(), 2);

        EXPECT_EQ(uv->values[0], 0);
        ASSERT_STREQ(sv->values[0].c_str(), "field1");

        EXPECT_EQ(uv->values[1], 1);
        ASSERT_STREQ(sv->values[1].c_str(), "field2");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }

    EXPECT_THROW(f.get_field1(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field1(), "my_struct_3_nt");

    EXPECT_THROW(f.get_field2(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field2(), "my_struct_3_nt");

    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    //

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

        ASSERT_EQ(uv->values.size(), 2);
        ASSERT_EQ(sv->values.size(), 2);

        EXPECT_EQ(uv->values[0], 1);
        ASSERT_STREQ(sv->values[0].c_str(), "field2");

        EXPECT_EQ(uv->values[1], 2);
        ASSERT_STREQ(sv->values[1].c_str(), "field3");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }

    EXPECT_EQ   (f.get_field1(), v1);
    EXPECT_THROW(f.get_field2(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field2(), "my_struct_3_nt");

    EXPECT_THROW(f.get_field3(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field3(), "my_struct_3_nt");

    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    //

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_THROW   (f.end(), f1d::not_set_exception);
    ASSERT_THROW   ((ms = f.get()), f1d::not_finished_exception);

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

        ASSERT_EQ(uv->values.size(), 2);
        ASSERT_EQ(sv->values.size(), 2);

        EXPECT_EQ(uv->values[0], 0);
        ASSERT_STREQ(sv->values[0].c_str(), "field1");

        EXPECT_EQ(uv->values[1], 2);
        ASSERT_STREQ(sv->values[1].c_str(), "field3");
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown by f.end()!";
    }

    EXPECT_THROW(f.get_field1(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field1(), "my_struct_3_nt");

    EXPECT_THROW(f.get_field3(), f1d::not_set_exception);

    MY_ASSERT_THROW_STRUCT_NAME(f.get_field3(), "my_struct_3_nt");

    EXPECT_EQ   (f.get_field2(), v2);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test the field type constructors
 */
TEST(Struct3FieldsNTTest, FieldConstruct)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    test::types::field1_f field1_1(v1);
    test::types::field1_f field1_2(field1_1);
    test::types::field1_f field1_3(ms);

    EXPECT_EQ(field1_1.get(), v1);
    EXPECT_EQ(field1_2.get(), v1);
    EXPECT_EQ(field1_3.get(), v1);

    test::types::field2_f field2_1(v2);
    test::types::field2_f field2_2(field2_1);
    test::types::field2_f field2_3(ms);

    EXPECT_EQ(field2_1.get(), v2);
    EXPECT_EQ(field2_2.get(), v2);
    EXPECT_EQ(field2_3.get(), v2);

    test::types::field3_f field3_1(v3);
    test::types::field3_f field3_2(field3_1);
    test::types::field3_f field3_3(ms);

    EXPECT_EQ(field3_1.get(), v3);
    EXPECT_EQ(field3_2.get(), v3);
    EXPECT_EQ(field3_3.get(), v3);
}

/**
 * Test the field type assign operators
 */
TEST(Struct3FieldsNTTest, FieldAssign)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

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
    EXPECT_EQ(field1_4.get(), v1);

    test::types::field2_f field2_1;
    test::types::field2_f field2_2;
    test::types::field2_f field2_3;
    test::types::field2_f field2_4;

    field2_1 = v2;
    field2_2 = field2_1;
    field2_3 = ms;
    field2_4.get() = v2;

    EXPECT_EQ(field2_1.get(), v2);
    EXPECT_EQ(field2_2.get(), v2);
    EXPECT_EQ(field2_3.get(), v2);
    EXPECT_EQ(field2_4.get(), v2);

    test::types::field3_f field3_1;
    test::types::field3_f field3_2;
    test::types::field3_f field3_3;
    test::types::field3_f field3_4;

    field3_1 = v3;
    field3_2 = field3_1;
    field3_3 = ms;
    field3_4.get() = v3;

    EXPECT_EQ(field3_1.get(), v3);
    EXPECT_EQ(field3_2.get(), v3);
    EXPECT_EQ(field3_3.get(), v3);
    EXPECT_EQ(field3_4.get(), v3);
}

/**
 * Test the field type cast operators
 */
TEST(Struct3FieldsNTTest, FieldCast)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::types::field1_f field1(v1);
    test::types::field2_f field2(v2);
    test::types::field3_f field3(v3);

    const float vf1 = field1;
    const int   vf2 = field2;
    const char  vf3 = field3;

    EXPECT_EQ(field1.get(), v1);
    EXPECT_EQ(field2.get(), v2);
    EXPECT_EQ(field3.get(), v3);

    EXPECT_EQ(vf1, v1);
    EXPECT_EQ(vf2, v2);
    EXPECT_EQ(vf3, v3);
}

/**
 * Test the field type call operators
 */
TEST(Struct3FieldsNTTest, FieldApply)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::types::field1_f field1(v1);
    test::types::field2_f field2(v2);
    test::types::field3_f field3(v3);

    float vf1;
    int   vf2;
    char  vf3;
    test::my_struct_3_nt ms;

    field1(vf1);
    field2(vf2);
    field3(vf3);

    field1(ms);
    field2(ms);
    field3(ms);

    EXPECT_EQ(field1.get(), v1);
    EXPECT_EQ(field2.get(), v2);
    EXPECT_EQ(field3.get(), v3);

    EXPECT_EQ(vf1, v1);
    EXPECT_EQ(vf2, v2);
    EXPECT_EQ(vf3, v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test the field type traits
 */
TEST(Struct3FieldsNTTest, FieldTraits)
{
    EXPECT_EQ(typeid(float), typeid(test::traits::field_type<test::types::field1_f>::type));
    EXPECT_EQ(typeid(int),   typeid(test::traits::field_type<test::types::field2_f>::type));
    EXPECT_EQ(typeid(char),  typeid(test::traits::field_type<test::types::field3_f>::type));

    EXPECT_EQ(0, static_cast<unsigned int>(test::traits::field_index<test::types::field1_f>::value));
    EXPECT_EQ(1, static_cast<unsigned int>(test::traits::field_index<test::types::field2_f>::value));
    EXPECT_EQ(2, static_cast<unsigned int>(test::traits::field_index<test::types::field3_f>::value));
}

/**
 * Test the field type set_member method
 */
TEST(Struct3FieldsNTTest, FieldSetMember)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::types::field1_f field1(v1);
    test::types::field2_f field2(v2);
    test::types::field3_f field3(v3);

    float vf1;
    int   vf2;
    char  vf3;
    test::my_struct_3_nt ms;
    test::some_struct_3_nt ss;

    field1.set_member(ms);
    field2.set_member(ms);
    field3.set_member(ms);

    field1.set_member(ss);
    field2.set_member(ss);
    field3.set_member(ss);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);

    EXPECT_EQ(ss.field1, static_cast<double>(v1));
    EXPECT_EQ(ss.field2, static_cast<short>(v2));
    EXPECT_EQ(ss.field3, static_cast<int>(v3));
}

/**
 * Test the struct apply method
 */
TEST(Struct3FieldsNTTest, ApplyMethod)
{
    const float v1 = 10;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms1;
    test::my_struct_3_nt ms2;
    test::my_struct_3_nt ms3;
    test::my_struct_3_nt ms4;
    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms1 = f.get());
    ASSERT_NO_THROW(ms2 = f.get());
    ASSERT_NO_THROW(ms3 = f.get());
    ASSERT_NO_THROW(ms4 = f.get());

    const test::funct_3_1_nt f1;
    const test::funct_3_2_nt f2;
    test::funct_3_3_nt f3;
    test::funct_3_4_nt f4;

    ms1.apply(f1);
    ms2.apply(f2);
    ms3.apply(f3);
    ms4.apply(f4);

    EXPECT_EQ(ms1.field1, v1);
    EXPECT_EQ(ms1.field2, v2);
    EXPECT_EQ(ms1.field3, v3);

    EXPECT_EQ(ms2.field1, (v1 + 1));
    EXPECT_EQ(ms2.field2, (v2 + 1));
    EXPECT_EQ(ms2.field3, (v3 + 1));

    EXPECT_EQ(ms3.field1, v1);
    EXPECT_EQ(ms3.field2, v2);
    EXPECT_EQ(ms3.field3, v3);

    EXPECT_EQ(ms4.field1, (v1 + 1));
    EXPECT_EQ(ms4.field2, (v1 + 1 + v2 + 1));
    EXPECT_EQ(ms4.field3, (v1 + 1 + v2 + 1 + v3 + 1));

    EXPECT_EQ(f3.total, (v1 + 1 + v2 + 1 + v3 + 1));
    EXPECT_EQ(f4.total, (v1 + 1 + v2 + 1 + v3 + 1));
}

/**
 * Test the struct capply method
 */
TEST(Struct3FieldsNTTest, CApplyMethod)
{
    const float v1 = 10;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());

    const test::my_struct_3_nt ms1 = f.get();
    const test::my_struct_3_nt ms3 = f.get();

    const test::funct_3_1_nt f1;
    test::funct_3_3_nt f3;

    ms1.capply(f1);
    ms3.capply(f3);

    EXPECT_EQ(ms1.field1, v1);
    EXPECT_EQ(ms1.field2, v2);
    EXPECT_EQ(ms1.field3, v3);

    EXPECT_EQ(ms3.field1, v1);
    EXPECT_EQ(ms3.field2, v2);
    EXPECT_EQ(ms3.field3, v3);

    EXPECT_EQ(f3.total, (v1 + 1 + v2 + 1 + v3 + 1));
}

/**
 * Test factory set from field wrappers without error
 */
TEST(Struct3FieldsNTTest, FactoryFromFieldOK)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_nt ms;
    test::my_struct_3_nt_factory f;

    test::types::field1_f field1(v1);
    test::types::field2_f field2(v2);
    test::types::field3_f field3(v3);

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(field1(f));
    ASSERT_NO_THROW(field2(f));
    ASSERT_NO_THROW(field3(f));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW(ms = f.get());

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

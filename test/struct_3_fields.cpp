/*
 * Copyright (C) 2018 Caian Benedicto <caianbene@gmail.com>
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

namespace test {

F1D_STRUCT_MAKE(my_struct_3,
    3, (
        (field1, float),
        (field2, int  ),
        (field3, char )
    )
) // my_struct_3

}

/**
 * Test member access
 */
TEST(Struct3FieldsTest, AccessMembers)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
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
TEST(Struct3FieldsTest, AccessCountMetadata)
{
    EXPECT_EQ(static_cast<unsigned int>(test::my_struct_3::num_fields), 3);
    EXPECT_EQ(test::my_struct_3::get_num_fields(), 3);
}

/**
 * Test metadata access
 */
TEST(Struct3FieldsTest, AccessNameMetadata)
{
    EXPECT_STREQ(test::my_struct_3::get_field_name(0), "field1");
    EXPECT_STREQ(test::my_struct_3::get_field_name(1), "field2");
    EXPECT_STREQ(test::my_struct_3::get_field_name(2), "field3");
    EXPECT_THROW(test::my_struct_3::get_field_name(3), f1d::not_found_exception);

    try {
        test::my_struct_3::get_field_name(3);
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
TEST(Struct3FieldsTest, AccessTypeNameMetadata)
{
    EXPECT_STREQ(test::my_struct_3::get_type_name(0), "float");
    EXPECT_STREQ(test::my_struct_3::get_type_name(1), "int");
    EXPECT_STREQ(test::my_struct_3::get_type_name(2), "char");
    EXPECT_THROW(test::my_struct_3::get_type_name(3), f1d::not_found_exception);

    try {
        test::my_struct_3::get_field_name(3);
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
TEST(Struct3FieldsTest, AccessTypeSizeMetadata)
{
    EXPECT_EQ(test::my_struct_3::get_type_size(0), sizeof(float));
    EXPECT_EQ(test::my_struct_3::get_type_size(1), sizeof(int));
    EXPECT_EQ(test::my_struct_3::get_type_size(2), sizeof(char));
    EXPECT_THROW(test::my_struct_3::get_type_size(3), f1d::not_found_exception);

    try {
        test::my_struct_3::get_field_name(3);
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
TEST(Struct3FieldsTest, AccessIndexMetadata)
{
    EXPECT_EQ(test::my_struct_3::get_field_index("field1"), 0);
    EXPECT_EQ(test::my_struct_3::get_field_index("field2"), 1);
    EXPECT_EQ(test::my_struct_3::get_field_index("field3"), 2);
    EXPECT_THROW(test::my_struct_3::get_field_index("field4"), f1d::not_found_exception);

    try {
        test::my_struct_3::get_field_index("field4");
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
 * Test member access
 */
TEST(Struct3FieldsTest, AccessTraits)
{
    EXPECT_EQ(typeid(float), typeid(test::traits::value_type<test::my_struct_3, 0>::type));
    EXPECT_EQ(typeid(int),   typeid(test::traits::value_type<test::my_struct_3, 1>::type));
    EXPECT_EQ(typeid(char),  typeid(test::traits::value_type<test::my_struct_3, 2>::type));

    EXPECT_EQ(typeid(float), typeid(test::types::field1_t));
    EXPECT_EQ(typeid(int),   typeid(test::types::field2_t));
    EXPECT_EQ(typeid(char),  typeid(test::types::field3_t));

    test::my_struct_3 ms;

    EXPECT_EQ(typeid(ms.field1), typeid(test::traits::value_type<test::my_struct_3, 0>::type));
    EXPECT_EQ(typeid(ms.field2), typeid(test::traits::value_type<test::my_struct_3, 1>::type));
    EXPECT_EQ(typeid(ms.field3), typeid(test::traits::value_type<test::my_struct_3, 2>::type));
}

/**
 * Test factory without error
 */
TEST(Struct3FieldsTest, FactoryOK)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct3FieldsTest, FactoryOKX5)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

    for (size_t i = 0 ; i < 5; i++) {
        ASSERT_NO_THROW(f.begin());
        ASSERT_NO_THROW(f.set_field1(v1));
        ASSERT_NO_THROW(f.set_field2(v2));
        ASSERT_NO_THROW(f.set_field3(v3));
        ASSERT_NO_THROW(f.end());
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));
        ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct3FieldsTest, FactoryDoubleBegin)
{
    test::my_struct_3_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_THROW(f.begin(), f1d::not_finished_exception);
}

/**
 * Test factory fail if get is called before set.
 */
TEST(Struct3FieldsTest, FactoryGetBeforeSet)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

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
    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

/**
 * Test factory fail if another end is called after end.
 */
TEST(Struct3FieldsTest, FactoryDoubleEnd)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_factory f;

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
TEST(Struct3FieldsTest, FactoryMultipleSet)
{
    const float v11 = 1.4f;
    const int   v21 = -7;
    const char  v31 = 'H';

    const float v12 = 5.9f;
    const int   v22 = 12;
    const char  v32 = 'p';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v11));
    ASSERT_THROW   (f.set_field1(v12), f1d::already_set_exception);
    ASSERT_NO_THROW(f.set_field2(v21));
    ASSERT_THROW   (f.set_field2(v22), f1d::already_set_exception);
    ASSERT_NO_THROW(f.set_field3(v31));
    ASSERT_THROW   (f.set_field3(v32), f1d::already_set_exception);
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct3FieldsTest, FactorySetAfterEnd)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

    ASSERT_NO_THROW(f.begin());
    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_THROW   (f.set_field1(v1), f1d::already_finished_exception);
    ASSERT_THROW   (f.set_field2(v2), f1d::already_finished_exception);
    ASSERT_THROW   (f.set_field3(v3), f1d::already_finished_exception);
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct3FieldsTest, FactoryEndBeforeBegin)
{
    test::my_struct_3_factory f;

    ASSERT_THROW(f.end(), f1d::not_intialized_exception);
}

/**
 * Test factory with a set before begin
 */
TEST(Struct3FieldsTest, FactorySetBeforeBegin)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3_factory f;

    ASSERT_THROW(f.set_field1(v1), f1d::not_intialized_exception);
    ASSERT_THROW(f.set_field2(v2), f1d::not_intialized_exception);
    ASSERT_THROW(f.set_field3(v3), f1d::not_intialized_exception);
}

/**
 * Test factory with an end before setting all fields.
 */
TEST(Struct3FieldsTest, FactoryIncompleteSet1)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

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
    EXPECT_EQ   (f.get_field2(), v2);
    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
    EXPECT_EQ   (f.get_field1(), v1);
    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
    EXPECT_EQ   (f.get_field1(), v1);
    EXPECT_EQ   (f.get_field2(), v2);

    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
TEST(Struct3FieldsTest, FactoryIncompleteSet2)
{
    const float v1 = 1.4f;
    const int   v2 = -7;
    const char  v3 = 'H';

    test::my_struct_3 ms;
    test::my_struct_3_factory f;

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
    EXPECT_THROW(f.get_field2(), f1d::not_set_exception);
    EXPECT_EQ   (f.get_field3(), v3);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
    EXPECT_THROW(f.get_field3(), f1d::not_set_exception);

    ASSERT_NO_THROW(f.set_field2(v2));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

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
    EXPECT_THROW(f.get_field3(), f1d::not_set_exception);
    EXPECT_EQ   (f.get_field2(), v2);

    ASSERT_NO_THROW(f.set_field1(v1));
    ASSERT_NO_THROW(f.set_field3(v3));
    ASSERT_NO_THROW(f.end());
    ASSERT_NO_THROW((ms = f.get()));

    EXPECT_EQ(f.get_field1(), v1);
    EXPECT_EQ(f.get_field2(), v2);
    EXPECT_EQ(f.get_field3(), v3);

    EXPECT_EQ(ms.field1, v1);
    EXPECT_EQ(ms.field2, v2);
    EXPECT_EQ(ms.field3, v3);
}

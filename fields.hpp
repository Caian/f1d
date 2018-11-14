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

#pragma once

#include "exceptions.hpp"

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/algorithm/string/join.hpp>

#include <algorithm>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_TYPE_NAME(Name) \
    BOOST_PP_CAT(Name, _t)

#define F1D_STRUCT_FULL_TYPE(Namespace, Name) \
    Namespace::F1D_STRUCT_TYPE_NAME(Name)

#define F1D_STRUCT_ASSEMBLE_TYPEDEF(Type, Name) \
    typedef Type F1D_STRUCT_TYPE_NAME(Name);

#define F1D_STRUCT_ASSEMBLE_VALUE_TYPE(Type, SName, i) \
    template <> \
    struct value_type<SName, i> \
    { \
        typedef Type type; \
    };

#define F1D_STRUCT_ASSEMBLE_TYPES(_s, nothing, i, elem) \
    F1D_STRUCT_ASSEMBLE_TYPEDEF( \
        BOOST_PP_TUPLE_ELEM(2, 1, elem), \
        BOOST_PP_TUPLE_ELEM(2, 0, elem))

#define F1D_STRUCT_ASSEMBLE_TRAITS(_s, SName, i, elem) \
    F1D_STRUCT_ASSEMBLE_VALUE_TYPE( \
        BOOST_PP_TUPLE_ELEM(2, 1, elem), \
        SName, \
        i)

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_DECL_VAR(Type, Name) \
    Type Name;

#define F1D_STRUCT_ASSEMBLE_FIELD(Namespace, Name) \
    F1D_STRUCT_DECL_VAR( \
        F1D_STRUCT_FULL_TYPE(Namespace, Name), \
        Name)

#define F1D_STRUCT_ASSEMBLE_FIELDS(_s, Namespace, i, elem) \
    F1D_STRUCT_ASSEMBLE_FIELD( \
        Namespace, \
        BOOST_PP_TUPLE_ELEM(2, 0, elem))

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_DECL_INIT(Type, Name, Idx) \
    void BOOST_PP_CAT(set_, Name)(const Type& value) \
    { \
        if (!_begun) { \
            EX3_THROW(f1d::not_intialized_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        if (_ended) { \
            EX3_THROW(f1d::already_finished_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        if (_set_fields[Idx]) { \
            EX3_THROW(f1d::already_set_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_index(Idx) \
                << f1d::field_name(BOOST_PP_STRINGIZE(Name))); \
        } \
        _set_fields[Idx] = true; \
        _obj.Name = value; \
    } \
    const Type& BOOST_PP_CAT(get_, Name)() \
    { \
        if (!_begun) { \
            EX3_THROW(f1d::not_intialized_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        if (!_set_fields[Idx]) { \
            EX3_THROW(f1d::not_set_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_index(Idx) \
                << f1d::field_name(BOOST_PP_STRINGIZE(Name))); \
        } \
        return _obj.Name; \
    }

#define F1D_STRUCT_ASSEMBLE_INIT(Namespace, Name, Idx) \
    F1D_STRUCT_DECL_INIT( \
        F1D_STRUCT_FULL_TYPE(Namespace, Name), Name, Idx)

#define F1D_STRUCT_ASSEMBLE_INITS(_s, Namespace, i, elem) \
    F1D_STRUCT_ASSEMBLE_INIT( \
        Namespace, \
        BOOST_PP_TUPLE_ELEM(2, 0, elem), \
        i)

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_ASSEMBLE_NAME(Name) \
    BOOST_PP_STRINGIZE(Name) BOOST_PP_COMMA()

#define F1D_STRUCT_ASSEMBLE_NAMES(_s, nothing, i, elem) \
    F1D_STRUCT_ASSEMBLE_NAME( \
        BOOST_PP_TUPLE_ELEM(2, 0, elem))

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_ASSEMBLE_TNAME(Type) \
    BOOST_PP_STRINGIZE(Type) BOOST_PP_COMMA()

#define F1D_STRUCT_ASSEMBLE_TNAMES(_s, nothing, i, elem) \
    F1D_STRUCT_ASSEMBLE_TNAME( \
        BOOST_PP_TUPLE_ELEM(2, 1, elem))

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_ASSEMBLE_SNAME(Name, i) \
    if (name.compare(BOOST_PP_STRINGIZE(Name)) == 0) \
        return i;

#define F1D_STRUCT_ASSEMBLE_SNAMES(_s, nothing, i, elem) \
    F1D_STRUCT_ASSEMBLE_SNAME( \
        BOOST_PP_TUPLE_ELEM(2, 0, elem), \
        i)

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_ASSEMBLE_TSIZE(Type) \
    sizeof(Type) BOOST_PP_COMMA()

#define F1D_STRUCT_ASSEMBLE_TSIZES(_s, nothing, i, elem) \
    F1D_STRUCT_ASSEMBLE_TSIZE( \
        BOOST_PP_TUPLE_ELEM(2, 1, elem))

///////////////////////////////////////////////////////////////////////////////

#define F1D_STRUCT_MAKE_S1(Name, NF, Fields) \
namespace types { \
    BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_TYPES, 0, Fields) \
} \
struct Name { \
    static const unsigned int num_fields = NF; \
    static unsigned int get_num_fields() \
    { \
        return num_fields; \
    } \
    static const char* get_struct_name() \
    { \
        return BOOST_PP_STRINGIZE(Name); \
    } \
    BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_FIELDS, types, Fields) \
    static const char* get_field_name(unsigned int index) \
    { \
        if (index >= NF) { \
            EX3_THROW(f1d::not_found_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_index(index)); \
        } \
        static const char* field_names[] = { \
            BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_NAMES, 0, Fields) \
            "" \
        }; \
        return field_names[index]; \
    } \
    static const char* get_type_name(unsigned int index) \
    { \
        if (index >= NF) { \
            EX3_THROW(f1d::not_found_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_index(index)); \
        } \
        static const char* type_names[] = { \
            BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_TNAMES, 0, Fields) \
            "" \
        }; \
        return type_names[index]; \
    } \
    static unsigned int get_field_index(const std::string& name) \
    { \
        BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_SNAMES, 0, Fields) \
        EX3_THROW(f1d::not_found_exception() \
            << f1d::struct_name(get_struct_name()) \
            << f1d::field_name(name)); \
    } \
    static size_t get_type_size(unsigned int index) \
    { \
        if (index >= NF) { \
            EX3_THROW(f1d::not_found_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_index(index)); \
        } \
        static const size_t type_sizes[] = { \
            BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_TSIZES, 0, Fields) \
            0 \
        }; \
        return type_sizes[index]; \
    } \
}; \
class Name##_factory { \
private: \
    Name _obj; \
    bool _begun; \
    bool _ended; \
    std::vector<bool> _set_fields; \
    static const char* get_struct_name() \
    { \
        return Name::get_struct_name(); \
    } \
    bool all_set() const \
    { \
        for (size_t i = 0; i < _set_fields.size(); i++) \
            if (!_set_fields[i]) return false; \
        return true; \
    } \
    void assert_fields() const \
    { \
        bool failed = false; \
        std::vector<unsigned int> indices; \
        std::vector<std::string> names; \
        for (unsigned int i = 0; i < _set_fields.size(); i++) { \
            if (!_set_fields[i]) { \
                failed = true; \
                indices.push_back(i); \
                names.push_back(Name::get_field_name(i)); \
            } \
        } \
        if (failed) { \
            EX3_THROW(f1d::not_set_exception() \
                << f1d::struct_name(get_struct_name()) \
                << f1d::field_indices(indices) \
                << f1d::field_names(names)); \
        } \
    } \
public: \
    Name##_factory() : \
        _obj(), \
        _begun(false), \
        _ended(false), \
        _set_fields(NF) \
    { \
    } \
    void begin() \
    { \
        if (_begun && !_ended) {\
            EX3_THROW(f1d::not_finished_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        _begun = true; \
        _ended = false; \
        std::fill(_set_fields.begin(), _set_fields.end(), false); \
    } \
    void end() \
    { \
        if (!_begun) { \
            EX3_THROW(f1d::not_intialized_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        if (_ended) { \
            EX3_THROW(f1d::already_finished_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        assert_fields(); \
        _ended = true; \
    } \
    const Name& get() const \
    { \
        if (!_begun) { \
            EX3_THROW(f1d::not_intialized_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        if (!_ended) { \
            EX3_THROW(f1d::not_finished_exception() \
                << f1d::struct_name(get_struct_name())); \
        } \
        return _obj; \
    } \
    BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_INITS, types, Fields) \
}; \
namespace traits { \
    template <class T, unsigned int N> \
    struct value_type \
    { \
        typedef void type; \
    }; \
    BOOST_PP_SEQ_FOR_EACH_I(F1D_STRUCT_ASSEMBLE_TRAITS, Name, Fields) \
}

#define F1D_STRUCT_MAKE(Name, NF, Fields) \
    F1D_STRUCT_MAKE_S1(Name, NF, BOOST_PP_TUPLE_TO_SEQ(NF, Fields))

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

#include <ex3/exceptions.hpp>
#include <ex3/pretty.hpp>

namespace f1d {

typedef ex3::pretty_container<
    std::vector<unsigned int>
    > pretty_uint_vector;

typedef ex3::pretty_container<
    std::vector<std::string>
    > pretty_string_vector;

typedef boost::error_info<
    struct tag_struct_name,
    std::string
    > struct_name;

typedef boost::error_info<
    struct tag_field_index,
    unsigned int
    > field_index;

typedef boost::error_info<
    struct tag_field_name,
    std::string
    > field_name;

typedef boost::error_info<
    struct tag_field_indices,
    pretty_uint_vector
    > field_indices;

typedef boost::error_info<
    struct tag_field_names,
    pretty_string_vector
    > field_names;

class f1d_exception :
    public ex3::exception_base
{
};

class not_intialized_exception :
    public f1d_exception
{
};

class not_finished_exception :
    public f1d_exception
{
};

class already_finished_exception :
    public f1d_exception
{
};

class not_set_exception :
    public f1d_exception
{
};

class already_set_exception :
    public f1d_exception
{
};

class not_found_exception :
    public f1d_exception
{
};

}
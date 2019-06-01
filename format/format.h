/*
 * format.h
 * 
 * Copyright 2019 Kyle Barry u19232510
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <string>
#include <sstream>

namespace kblibs {

    /*
     * This function accepts a string replaces the first instance of {0} it finds with
     * the rhs value. It is the endpoint of the other format function which takes any length of
     * arguments.
     */
	template <typename T> std::string format(std::string&& lhs, const T& rhs) {
		std::string buf = lhs;
        
        //find the placeholder and throw an exception if it is not found
		size_t pos = buf.find("{0}");
		if (pos == std::string::npos) {
			throw std::runtime_error("No string placeholder '{0}' found!");
		}
		
		//get the iterators that point to positions just before and just after the placeholder
		std::string::iterator beg = buf.begin() + pos;
		std::string::iterator end = beg + 3;
        
        //extract the string prior to the placeholder
        std::string ret = std::string(buf.begin(), beg);
        
        //convert the rhs argument to a string
		std::ostringstream oss;
		oss << rhs;
		ret += oss.str();
        
        //extract the string that comes after the placeholder
		ret += std::string(end, buf.end());
        
        //return the interpolated string
		return ret;
	}
    
    /*
     * This function accepts a string replaces the first instance of {0} it finds with
     * the rhs value. This function accepts an arbritrary amount of arguments of varying mixed types
     * and unpacks them.
     */
	template <typename T, typename... Args> std::string format(std::string&& lhs, const T& rhs, const Args&... args) {
		std::string buf = lhs;
        
        //find the placeholder and throw an exception if it is not found
		size_t pos = buf.find("{0}");
		if (pos == std::string::npos) {
			throw std::runtime_error("No string placeholder '{0}' found!");
		}
		//get the iterators that point to positions just before and just after the placeholder
		std::string::iterator beg = buf.begin() + pos;
		std::string::iterator end = beg + 3;
        
        //extract the string prior to the placeholder
        std::string ret = std::string(buf.begin(), beg);
        
        //convert the rhs argument to a string
		std::ostringstream oss;
		oss << rhs;
		
		ret += oss.str();
        
        //extract the string that comes after the placeholder
		ret += std::string(end, buf.end());
        
        //return a partially formatted string, along with the partially unpacked arguments
		return format(std::move(ret), args...);
	}

	/*
     * This function accepts a string replaces the first instance of a given placeholder it finds with
     * the rhs value. It is the endpoint of the other format function which takes any length of
     * arguments.
     */
	template <typename T> std::string format_with_placeholder(std::string&& lhs, std::string&& placeholder, const T& rhs) {
		std::string buf = lhs;
		size_t pos = buf.find(placeholder);
		if (pos == std::string::npos) {
			std::string err = "No string placeholder '" + placeholder + "' found!";
			throw std::runtime_error(err);
		}
		std::string::iterator beg = buf.begin() + pos;
		std::string::iterator end = beg + placeholder.length();
		std::ostringstream oss;
		oss << rhs;
		std::string ret = std::string(buf.begin(), beg);
		ret += oss.str();
		ret += std::string(end, buf.end());
		return ret;
	}
	
	/*
     * This function accepts a string replaces the first instance of a given placeholder it finds with
     * the rhs value. This function accepts an arbritrary amount of arguments of varying mixed types
     * and unpacks them.
     */
	template <typename T, typename... Args> std::string format_with_placeholder(std::string&& lhs, std::string&& placeholder, const T& rhs, const Args&... args) {
		std::string buf = lhs;
		std::string p = placeholder;
		size_t pos = buf.find(p);
		if (pos == std::string::npos) {
			std::string err = "No string placeholder '" + p + "' found!";
			throw std::runtime_error(err);
		}
		std::string::iterator beg = buf.begin() + pos;
		std::string::iterator end = beg + p.length();
		std::ostringstream oss;
		oss << rhs;
		std::string ret = std::string(buf.begin(), beg);
		ret += oss.str();
		ret += std::string(end, buf.end());
		return format_with_placeholder(std::move(ret), std::move(p), args...);
	}
}
